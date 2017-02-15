// Quick test of whether OpenCL works.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <string.h>
#include <assert.h>

#include <CL/cl.h>

#define SUCCEED(e) (assert(e == 0))

const char *test_cl =
"__kernel void add_one(__global const int* in, __global int* out) \
{ out[get_global_id(0)] = in[get_global_id(0)] + 1; }";

int main() {
  int n = 1024;
  int *in_data = malloc(n * sizeof(int));
  int *out_data = malloc(n * sizeof(int));

  for (int i = 0; i < n; i++) {
    in_data[i] = i;
  }

  cl_int error;
  cl_platform_id platform;
  cl_device_id device;
  cl_uint platforms, devices;

  // Fetch the Platform and Device IDs; we only want one.
  error=clGetPlatformIDs(1, &platform, &platforms);
  error=clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 1, &device, &devices);
  cl_context_properties properties[]={
    CL_CONTEXT_PLATFORM, (cl_context_properties)platform,
    0};
  // Note that nVidia's OpenCL requires the platform property
  cl_context context=clCreateContext(properties, 1, &device, NULL, NULL, &error);
  cl_command_queue cq = clCreateCommandQueue(context, device, 0, &error);

  // Submit the source code of the kernel to OpenCL
  cl_program prog=clCreateProgramWithSource(context, 1, &test_cl, NULL, &error);
  // And compile it
  SUCCEED(clBuildProgram(prog, 0, NULL, "", NULL, NULL));

  // Allocate memory for the kernel to work with
  cl_mem inmem, outmem;
  inmem=clCreateBuffer(context, CL_MEM_READ_ONLY, n * sizeof(int), NULL, &error);
  outmem=clCreateBuffer(context, CL_MEM_WRITE_ONLY, n * sizeof(int), NULL, &error);

  // Get a handle and map parameters for the kernel
  cl_kernel k_test=clCreateKernel(prog, "add_one", &error);
  assert(error == CL_SUCCESS);
  clSetKernelArg(k_test, 0, sizeof(inmem), &inmem);
  clSetKernelArg(k_test, 1, sizeof(outmem), &outmem);

  // Send input data to OpenCL
  SUCCEED(clEnqueueWriteBuffer(cq, inmem, CL_TRUE, 0, n * sizeof(int), in_data, 0, NULL, NULL));
  // Perform the operation
  const size_t workers[] = {n};
  const size_t localworkers[] = {256};
  SUCCEED(clFinish(cq));
  SUCCEED(clEnqueueNDRangeKernel(cq, k_test, 1, NULL, workers, localworkers, 0, NULL, NULL));
  SUCCEED(clEnqueueReadBuffer(cq, outmem, CL_TRUE, 0, n * sizeof(int), out_data, 0, NULL, NULL));
  SUCCEED(clFinish(cq));

  for (int i = 0; i < n; i++) {
    assert(in_data[i] + 1 == out_data[i]);
  }

  return 0;
}

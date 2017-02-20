#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <ctype.h>
#include <errno.h>
#include <assert.h>
#include <getopt.h>
static int detail_memory = 0;
static int debugging = 0;
/* Crash and burn. */

#include <stdarg.h>

static const char *fut_progname;

void panic(int eval, const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
        fprintf(stderr, "%s: ", fut_progname);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
        exit(eval);
}

/* Some simple utilities for wall-clock timing.

   The function get_wall_time() returns the wall time in microseconds
   (with an unspecified offset).
*/

#ifdef _WIN32

#include <windows.h>

int64_t get_wall_time() {
  LARGE_INTEGER time,freq;
  assert(QueryPerformanceFrequency(&freq));
  assert(QueryPerformanceCounter(&time));
  return ((double)time.QuadPart / freq.QuadPart) * 1000000;
}

#else
/* Assuming POSIX */

#include <time.h>
#include <sys/time.h>

int64_t get_wall_time() {
  struct timeval time;
  assert(gettimeofday(&time,NULL) == 0);
  return time.tv_sec * 1000000 + time.tv_usec;
}

#endif

int64_t peak_mem_usage_default = 0;
int64_t cur_mem_usage_default = 0;
struct memblock {
    int *references;
    char *mem;
    int64_t size;
} ;
static void memblock_unref(struct memblock *block)
{
    if (block->references != NULL) {
        *block->references -= 1;
        if (detail_memory)
            fprintf(stderr,
                    "Unreferencing block in default space: %d references remaining.\n",
                    *block->references);
        if (*block->references == 0) {
            cur_mem_usage_default -= block->size;
            free(block->mem);
            free(block->references);
            block->references = NULL;
            if (detail_memory)
                fprintf(stderr, "%ld bytes freed (now allocated: %ld bytes)\n",
                        block->size, cur_mem_usage_default);
        }
    }
}
static void memblock_alloc(struct memblock *block, int32_t size)
{
    memblock_unref(block);
    block->mem = (char *) malloc(size);
    block->references = (int *) malloc(sizeof(int));
    *block->references = 1;
    block->size = size;
    cur_mem_usage_default += size;
    if (detail_memory)
        fprintf(stderr,
                "Allocated %d bytes in default space (now allocated: %ld bytes)",
                size, cur_mem_usage_default);
    if (cur_mem_usage_default > peak_mem_usage_default) {
        peak_mem_usage_default = cur_mem_usage_default;
        if (detail_memory)
            fprintf(stderr, " (new peak).\n", peak_mem_usage_default);
    } else if (detail_memory)
        fprintf(stderr, ".\n");
}
static void memblock_set(struct memblock *lhs, struct memblock *rhs)
{
    memblock_unref(lhs);
    (*rhs->references)++;
    *lhs = *rhs;
}
struct tuple_int32_t_mem_int32_t {
    int32_t elem_0;
    struct memblock elem_1;
    int32_t elem_2;
} ;
static struct tuple_int32_t_mem_int32_t
futhark_main(int32_t outer_loop_count_15648, int32_t numX_15649,
             int32_t numY_15650, int32_t numT_15651, float s0_15652,
             float _strike_15653, float t_15654, float alpha_15655,
             float nu_15656, float beta_15657);
static inline float futhark_log32(float x)
{
    return log(x);
}
static inline float futhark_sqrt32(float x)
{
    return sqrt(x);
}
static inline float futhark_exp32(float x)
{
    return exp(x);
}
static inline float futhark_cos32(float x)
{
    return cos(x);
}
static inline float futhark_sin32(float x)
{
    return sin(x);
}
static inline float futhark_acos32(float x)
{
    return acos(x);
}
static inline float futhark_asin32(float x)
{
    return asin(x);
}
static inline double futhark_atan32(float x)
{
    return atan(x);
}
static inline float futhark_atan2_32(float x, float y)
{
    return atan2(x, y);
}
static inline char futhark_isnan32(float x)
{
    return isnan(x);
}
static inline char futhark_isinf32(float x)
{
    return isinf(x);
}
static inline double futhark_log64(double x)
{
    return log(x);
}
static inline double futhark_sqrt64(double x)
{
    return sqrt(x);
}
static inline double futhark_exp64(double x)
{
    return exp(x);
}
static inline double futhark_cos64(double x)
{
    return cos(x);
}
static inline double futhark_sin64(double x)
{
    return sin(x);
}
static inline double futhark_acos64(double x)
{
    return acos(x);
}
static inline double futhark_asin64(double x)
{
    return asin(x);
}
static inline double futhark_atan64(double x)
{
    return atan(x);
}
static inline double futhark_atan2_64(double x, double y)
{
    return atan2(x, y);
}
static inline char futhark_isnan64(double x)
{
    return isnan(x);
}
static inline char futhark_isinf64(double x)
{
    return isinf(x);
}
static inline int8_t add8(int8_t x, int8_t y)
{
    return x + y;
}
static inline int16_t add16(int16_t x, int16_t y)
{
    return x + y;
}
static inline int32_t add32(int32_t x, int32_t y)
{
    return x + y;
}
static inline int64_t add64(int64_t x, int64_t y)
{
    return x + y;
}
static inline int8_t sub8(int8_t x, int8_t y)
{
    return x - y;
}
static inline int16_t sub16(int16_t x, int16_t y)
{
    return x - y;
}
static inline int32_t sub32(int32_t x, int32_t y)
{
    return x - y;
}
static inline int64_t sub64(int64_t x, int64_t y)
{
    return x - y;
}
static inline int8_t mul8(int8_t x, int8_t y)
{
    return x * y;
}
static inline int16_t mul16(int16_t x, int16_t y)
{
    return x * y;
}
static inline int32_t mul32(int32_t x, int32_t y)
{
    return x * y;
}
static inline int64_t mul64(int64_t x, int64_t y)
{
    return x * y;
}
static inline uint8_t udiv8(uint8_t x, uint8_t y)
{
    return x / y;
}
static inline uint16_t udiv16(uint16_t x, uint16_t y)
{
    return x / y;
}
static inline uint32_t udiv32(uint32_t x, uint32_t y)
{
    return x / y;
}
static inline uint64_t udiv64(uint64_t x, uint64_t y)
{
    return x / y;
}
static inline uint8_t umod8(uint8_t x, uint8_t y)
{
    return x % y;
}
static inline uint16_t umod16(uint16_t x, uint16_t y)
{
    return x % y;
}
static inline uint32_t umod32(uint32_t x, uint32_t y)
{
    return x % y;
}
static inline uint64_t umod64(uint64_t x, uint64_t y)
{
    return x % y;
}
static inline int8_t sdiv8(int8_t x, int8_t y)
{
    int8_t q = x / y;
    int8_t r = x % y;
    
    return q - ((r != 0 && r < 0 != y < 0) ? 1 : 0);
}
static inline int16_t sdiv16(int16_t x, int16_t y)
{
    int16_t q = x / y;
    int16_t r = x % y;
    
    return q - ((r != 0 && r < 0 != y < 0) ? 1 : 0);
}
static inline int32_t sdiv32(int32_t x, int32_t y)
{
    int32_t q = x / y;
    int32_t r = x % y;
    
    return q - ((r != 0 && r < 0 != y < 0) ? 1 : 0);
}
static inline int64_t sdiv64(int64_t x, int64_t y)
{
    int64_t q = x / y;
    int64_t r = x % y;
    
    return q - ((r != 0 && r < 0 != y < 0) ? 1 : 0);
}
static inline int8_t smod8(int8_t x, int8_t y)
{
    int8_t r = x % y;
    
    return r + (r == 0 || (x > 0 && y > 0) || (x < 0 && y < 0) ? 0 : y);
}
static inline int16_t smod16(int16_t x, int16_t y)
{
    int16_t r = x % y;
    
    return r + (r == 0 || (x > 0 && y > 0) || (x < 0 && y < 0) ? 0 : y);
}
static inline int32_t smod32(int32_t x, int32_t y)
{
    int32_t r = x % y;
    
    return r + (r == 0 || (x > 0 && y > 0) || (x < 0 && y < 0) ? 0 : y);
}
static inline int64_t smod64(int64_t x, int64_t y)
{
    int64_t r = x % y;
    
    return r + (r == 0 || (x > 0 && y > 0) || (x < 0 && y < 0) ? 0 : y);
}
static inline int8_t squot8(int8_t x, int8_t y)
{
    return x / y;
}
static inline int16_t squot16(int16_t x, int16_t y)
{
    return x / y;
}
static inline int32_t squot32(int32_t x, int32_t y)
{
    return x / y;
}
static inline int64_t squot64(int64_t x, int64_t y)
{
    return x / y;
}
static inline int8_t srem8(int8_t x, int8_t y)
{
    return x % y;
}
static inline int16_t srem16(int16_t x, int16_t y)
{
    return x % y;
}
static inline int32_t srem32(int32_t x, int32_t y)
{
    return x % y;
}
static inline int64_t srem64(int64_t x, int64_t y)
{
    return x % y;
}
static inline uint8_t shl8(uint8_t x, uint8_t y)
{
    return x << y;
}
static inline uint16_t shl16(uint16_t x, uint16_t y)
{
    return x << y;
}
static inline uint32_t shl32(uint32_t x, uint32_t y)
{
    return x << y;
}
static inline uint64_t shl64(uint64_t x, uint64_t y)
{
    return x << y;
}
static inline uint8_t lshr8(uint8_t x, uint8_t y)
{
    return x >> y;
}
static inline uint16_t lshr16(uint16_t x, uint16_t y)
{
    return x >> y;
}
static inline uint32_t lshr32(uint32_t x, uint32_t y)
{
    return x >> y;
}
static inline uint64_t lshr64(uint64_t x, uint64_t y)
{
    return x >> y;
}
static inline int8_t ashr8(int8_t x, int8_t y)
{
    return x >> y;
}
static inline int16_t ashr16(int16_t x, int16_t y)
{
    return x >> y;
}
static inline int32_t ashr32(int32_t x, int32_t y)
{
    return x >> y;
}
static inline int64_t ashr64(int64_t x, int64_t y)
{
    return x >> y;
}
static inline uint8_t and8(uint8_t x, uint8_t y)
{
    return x & y;
}
static inline uint16_t and16(uint16_t x, uint16_t y)
{
    return x & y;
}
static inline uint32_t and32(uint32_t x, uint32_t y)
{
    return x & y;
}
static inline uint64_t and64(uint64_t x, uint64_t y)
{
    return x & y;
}
static inline uint8_t or8(uint8_t x, uint8_t y)
{
    return x | y;
}
static inline uint16_t or16(uint16_t x, uint16_t y)
{
    return x | y;
}
static inline uint32_t or32(uint32_t x, uint32_t y)
{
    return x | y;
}
static inline uint64_t or64(uint64_t x, uint64_t y)
{
    return x | y;
}
static inline uint8_t xor8(uint8_t x, uint8_t y)
{
    return x ^ y;
}
static inline uint16_t xor16(uint16_t x, uint16_t y)
{
    return x ^ y;
}
static inline uint32_t xor32(uint32_t x, uint32_t y)
{
    return x ^ y;
}
static inline uint64_t xor64(uint64_t x, uint64_t y)
{
    return x ^ y;
}
static inline char ult8(uint8_t x, uint8_t y)
{
    return x < y;
}
static inline char ult16(uint16_t x, uint16_t y)
{
    return x < y;
}
static inline char ult32(uint32_t x, uint32_t y)
{
    return x < y;
}
static inline char ult64(uint64_t x, uint64_t y)
{
    return x < y;
}
static inline char ule8(uint8_t x, uint8_t y)
{
    return x <= y;
}
static inline char ule16(uint16_t x, uint16_t y)
{
    return x <= y;
}
static inline char ule32(uint32_t x, uint32_t y)
{
    return x <= y;
}
static inline char ule64(uint64_t x, uint64_t y)
{
    return x <= y;
}
static inline char slt8(int8_t x, int8_t y)
{
    return x < y;
}
static inline char slt16(int16_t x, int16_t y)
{
    return x < y;
}
static inline char slt32(int32_t x, int32_t y)
{
    return x < y;
}
static inline char slt64(int64_t x, int64_t y)
{
    return x < y;
}
static inline char sle8(int8_t x, int8_t y)
{
    return x <= y;
}
static inline char sle16(int16_t x, int16_t y)
{
    return x <= y;
}
static inline char sle32(int32_t x, int32_t y)
{
    return x <= y;
}
static inline char sle64(int64_t x, int64_t y)
{
    return x <= y;
}
static inline int8_t pow8(int8_t x, int8_t y)
{
    int8_t res = 1, rem = y;
    
    while (rem != 0) {
        if (rem & 1)
            res *= x;
        rem >>= 1;
        x *= x;
    }
    return res;
}
static inline int16_t pow16(int16_t x, int16_t y)
{
    int16_t res = 1, rem = y;
    
    while (rem != 0) {
        if (rem & 1)
            res *= x;
        rem >>= 1;
        x *= x;
    }
    return res;
}
static inline int32_t pow32(int32_t x, int32_t y)
{
    int32_t res = 1, rem = y;
    
    while (rem != 0) {
        if (rem & 1)
            res *= x;
        rem >>= 1;
        x *= x;
    }
    return res;
}
static inline int64_t pow64(int64_t x, int64_t y)
{
    int64_t res = 1, rem = y;
    
    while (rem != 0) {
        if (rem & 1)
            res *= x;
        rem >>= 1;
        x *= x;
    }
    return res;
}
static inline int8_t sext_i8_i8(int8_t x)
{
    return x;
}
static inline int16_t sext_i8_i16(int8_t x)
{
    return x;
}
static inline int32_t sext_i8_i32(int8_t x)
{
    return x;
}
static inline int64_t sext_i8_i64(int8_t x)
{
    return x;
}
static inline int8_t sext_i16_i8(int16_t x)
{
    return x;
}
static inline int16_t sext_i16_i16(int16_t x)
{
    return x;
}
static inline int32_t sext_i16_i32(int16_t x)
{
    return x;
}
static inline int64_t sext_i16_i64(int16_t x)
{
    return x;
}
static inline int8_t sext_i32_i8(int32_t x)
{
    return x;
}
static inline int16_t sext_i32_i16(int32_t x)
{
    return x;
}
static inline int32_t sext_i32_i32(int32_t x)
{
    return x;
}
static inline int64_t sext_i32_i64(int32_t x)
{
    return x;
}
static inline int8_t sext_i64_i8(int64_t x)
{
    return x;
}
static inline int16_t sext_i64_i16(int64_t x)
{
    return x;
}
static inline int32_t sext_i64_i32(int64_t x)
{
    return x;
}
static inline int64_t sext_i64_i64(int64_t x)
{
    return x;
}
static inline uint8_t zext_i8_i8(uint8_t x)
{
    return x;
}
static inline uint16_t zext_i8_i16(uint8_t x)
{
    return x;
}
static inline uint32_t zext_i8_i32(uint8_t x)
{
    return x;
}
static inline uint64_t zext_i8_i64(uint8_t x)
{
    return x;
}
static inline uint8_t zext_i16_i8(uint16_t x)
{
    return x;
}
static inline uint16_t zext_i16_i16(uint16_t x)
{
    return x;
}
static inline uint32_t zext_i16_i32(uint16_t x)
{
    return x;
}
static inline uint64_t zext_i16_i64(uint16_t x)
{
    return x;
}
static inline uint8_t zext_i32_i8(uint32_t x)
{
    return x;
}
static inline uint16_t zext_i32_i16(uint32_t x)
{
    return x;
}
static inline uint32_t zext_i32_i32(uint32_t x)
{
    return x;
}
static inline uint64_t zext_i32_i64(uint32_t x)
{
    return x;
}
static inline uint8_t zext_i64_i8(uint64_t x)
{
    return x;
}
static inline uint16_t zext_i64_i16(uint64_t x)
{
    return x;
}
static inline uint32_t zext_i64_i32(uint64_t x)
{
    return x;
}
static inline uint64_t zext_i64_i64(uint64_t x)
{
    return x;
}
static inline float fdiv32(float x, float y)
{
    return x / y;
}
static inline float fadd32(float x, float y)
{
    return x + y;
}
static inline float fsub32(float x, float y)
{
    return x - y;
}
static inline float fmul32(float x, float y)
{
    return x * y;
}
static inline float fpow32(float x, float y)
{
    return pow(x, y);
}
static inline char cmplt32(float x, float y)
{
    return x < y;
}
static inline char cmple32(float x, float y)
{
    return x <= y;
}
static inline float sitofp_i8_f32(int8_t x)
{
    return x;
}
static inline float sitofp_i16_f32(int16_t x)
{
    return x;
}
static inline float sitofp_i32_f32(int32_t x)
{
    return x;
}
static inline float sitofp_i64_f32(int64_t x)
{
    return x;
}
static inline float uitofp_i8_f32(uint8_t x)
{
    return x;
}
static inline float uitofp_i16_f32(uint16_t x)
{
    return x;
}
static inline float uitofp_i32_f32(uint32_t x)
{
    return x;
}
static inline float uitofp_i64_f32(uint64_t x)
{
    return x;
}
static inline int8_t fptosi_f32_i8(float x)
{
    return x;
}
static inline int16_t fptosi_f32_i16(float x)
{
    return x;
}
static inline int32_t fptosi_f32_i32(float x)
{
    return x;
}
static inline int64_t fptosi_f32_i64(float x)
{
    return x;
}
static inline uint8_t fptoui_f32_i8(float x)
{
    return x;
}
static inline uint16_t fptoui_f32_i16(float x)
{
    return x;
}
static inline uint32_t fptoui_f32_i32(float x)
{
    return x;
}
static inline uint64_t fptoui_f32_i64(float x)
{
    return x;
}
static inline double fdiv64(double x, double y)
{
    return x / y;
}
static inline double fadd64(double x, double y)
{
    return x + y;
}
static inline double fsub64(double x, double y)
{
    return x - y;
}
static inline double fmul64(double x, double y)
{
    return x * y;
}
static inline double fpow64(double x, double y)
{
    return pow(x, y);
}
static inline char cmplt64(double x, double y)
{
    return x < y;
}
static inline char cmple64(double x, double y)
{
    return x <= y;
}
static inline double sitofp_i8_f64(int8_t x)
{
    return x;
}
static inline double sitofp_i16_f64(int16_t x)
{
    return x;
}
static inline double sitofp_i32_f64(int32_t x)
{
    return x;
}
static inline double sitofp_i64_f64(int64_t x)
{
    return x;
}
static inline double uitofp_i8_f64(uint8_t x)
{
    return x;
}
static inline double uitofp_i16_f64(uint16_t x)
{
    return x;
}
static inline double uitofp_i32_f64(uint32_t x)
{
    return x;
}
static inline double uitofp_i64_f64(uint64_t x)
{
    return x;
}
static inline int8_t fptosi_f64_i8(double x)
{
    return x;
}
static inline int16_t fptosi_f64_i16(double x)
{
    return x;
}
static inline int32_t fptosi_f64_i32(double x)
{
    return x;
}
static inline int64_t fptosi_f64_i64(double x)
{
    return x;
}
static inline uint8_t fptoui_f64_i8(double x)
{
    return x;
}
static inline uint16_t fptoui_f64_i16(double x)
{
    return x;
}
static inline uint32_t fptoui_f64_i32(double x)
{
    return x;
}
static inline uint64_t fptoui_f64_i64(double x)
{
    return x;
}
static inline float fpconv_f32_f32(float x)
{
    return x;
}
static inline double fpconv_f32_f64(float x)
{
    return x;
}
static inline float fpconv_f64_f32(double x)
{
    return x;
}
static inline double fpconv_f64_f64(double x)
{
    return x;
}
static int detail_timing = 0;
static
struct tuple_int32_t_mem_int32_t futhark_main(int32_t outer_loop_count_15648,
                                              int32_t numX_15649,
                                              int32_t numY_15650,
                                              int32_t numT_15651,
                                              float s0_15652,
                                              float _strike_15653,
                                              float t_15654, float alpha_15655,
                                              float nu_15656, float beta_15657)
{
    int32_t out_memsizze_17870;
    struct memblock out_mem_17869;
    
    out_mem_17869.references = NULL;
    
    int32_t out_arrsizze_17871;
    float res_15663;
    
    res_15663 = futhark_log32(alpha_15655);
    
    float x_15665 = sitofp_i32_f32(numT_15651);
    float y_15666 = x_15665 - 1.0F;
    int32_t bytes_17755 = 4 * numT_15651;
    struct memblock mem_17756;
    
    mem_17756.references = NULL;
    memblock_alloc(&mem_17756, bytes_17755);
    for (int32_t i_17077 = 0; i_17077 < numT_15651; i_17077++) {
        float y_15669 = sitofp_i32_f32(i_17077);
        float x_15670 = t_15654 * y_15669;
        float res_15671 = x_15670 / y_15666;
        
        *(float *) &mem_17756.mem[i_17077 * 4] = res_15671;
    }
    
    float x_15672 = 20.0F * alpha_15655;
    float x_15673 = x_15672 * s0_15652;
    float res_15674;
    
    res_15674 = futhark_sqrt32(t_15654);
    
    float res_15675 = x_15673 * res_15674;
    float x_15676 = 10.0F * nu_15656;
    float res_15677 = x_15676 * res_15674;
    float y_15678 = sitofp_i32_f32(numX_15649);
    float res_15679 = res_15675 / y_15678;
    float y_15680 = sitofp_i32_f32(numY_15650);
    float res_15681 = res_15677 / y_15680;
    float trunc_arg_15682 = s0_15652 / res_15679;
    int32_t res_15683 = fptosi_f32_i32(trunc_arg_15682);
    int32_t res_15684 = sdiv32(numY_15650, 2);
    float x_15686 = sitofp_i32_f32(res_15683);
    float y_15687 = x_15686 * res_15679;
    int32_t bytes_17757 = 4 * numX_15649;
    struct memblock mem_17758;
    
    mem_17758.references = NULL;
    memblock_alloc(&mem_17758, bytes_17757);
    for (int32_t i_17081 = 0; i_17081 < numX_15649; i_17081++) {
        float x_15690 = sitofp_i32_f32(i_17081);
        float x_15691 = x_15690 * res_15679;
        float x_15692 = x_15691 - y_15687;
        float res_15693 = x_15692 + s0_15652;
        
        *(float *) &mem_17758.mem[i_17081 * 4] = res_15693;
    }
    
    float x_15695 = sitofp_i32_f32(res_15684);
    float y_15696 = x_15695 * res_15681;
    int32_t bytes_17759 = 4 * numY_15650;
    struct memblock mem_17760;
    
    mem_17760.references = NULL;
    memblock_alloc(&mem_17760, bytes_17759);
    for (int32_t i_17085 = 0; i_17085 < numY_15650; i_17085++) {
        float x_15699 = sitofp_i32_f32(i_17085);
        float x_15700 = x_15699 * res_15681;
        float x_15701 = x_15700 - y_15696;
        float res_15702 = x_15701 + res_15663;
        
        *(float *) &mem_17760.mem[i_17085 * 4] = res_15702;
    }
    
    struct memblock mem_17762;
    
    mem_17762.references = NULL;
    memblock_alloc(&mem_17762, 12);
    *(float *) &mem_17762.mem[0] = 0.0F;
    *(float *) &mem_17762.mem[4] = 0.0F;
    *(float *) &mem_17762.mem[8] = 0.0F;
    
    struct memblock mem_17764;
    
    mem_17764.references = NULL;
    memblock_alloc(&mem_17764, 12);
    memmove(mem_17764.mem + 0, mem_17762.mem + 0, 3 * sizeof(float));
    
    int32_t n_15705 = numX_15649 - 2;
    int32_t binop_x_17766 = 4 * n_15705;
    int32_t bytes_17765 = binop_x_17766 * 3;
    struct memblock mem_17767;
    
    mem_17767.references = NULL;
    memblock_alloc(&mem_17767, bytes_17765);
    
    struct memblock mem_17769;
    
    mem_17769.references = NULL;
    memblock_alloc(&mem_17769, 12);
    for (int32_t i_17089 = 0; i_17089 < n_15705; i_17089++) {
        int32_t res_15712 = i_17089 + 1;
        float x_15717 = *(float *) &mem_17758.mem[res_15712 * 4];
        float y_15722 = *(float *) &mem_17758.mem[i_17089 * 4];
        float res_15723 = x_15717 - y_15722;
        int32_t i_15724 = res_15712 + 1;
        float x_15729 = *(float *) &mem_17758.mem[i_15724 * 4];
        float res_15730 = x_15729 - x_15717;
        float y_15732 = res_15723 + res_15730;
        float x_15734 = 2.0F / res_15723;
        float arr_elem_15735 = x_15734 / y_15732;
        float x_15736 = 1.0F / res_15723;
        float y_15737 = 1.0F / res_15730;
        float y_15738 = x_15736 + y_15737;
        float x_15739 = 2.0F * y_15738;
        float negate_arg_15740 = x_15739 / y_15732;
        float arr_elem_15741 = 0.0F - negate_arg_15740;
        float x_15742 = 2.0F / res_15730;
        float arr_elem_15743 = x_15742 / y_15732;
        
        *(float *) &mem_17769.mem[0] = arr_elem_15735;
        *(float *) &mem_17769.mem[4] = arr_elem_15741;
        *(float *) &mem_17769.mem[8] = arr_elem_15743;
        for (int32_t i_17876 = 0; i_17876 < 3; i_17876++) {
            *(float *) &mem_17767.mem[(i_17089 * 3 + i_17876) * 4] =
                *(float *) &mem_17769.mem[i_17876 * 4];
        }
    }
    
    int32_t conc_tmp_15746 = 1 + n_15705;
    int32_t n_15749 = numY_15650 - 2;
    int32_t binop_x_17772 = 4 * n_15749;
    int32_t bytes_17771 = binop_x_17772 * 3;
    struct memblock mem_17773;
    
    mem_17773.references = NULL;
    memblock_alloc(&mem_17773, bytes_17771);
    
    struct memblock mem_17775;
    
    mem_17775.references = NULL;
    memblock_alloc(&mem_17775, 12);
    for (int32_t i_17093 = 0; i_17093 < n_15749; i_17093++) {
        int32_t res_15756 = i_17093 + 1;
        float x_15761 = *(float *) &mem_17760.mem[res_15756 * 4];
        float y_15766 = *(float *) &mem_17760.mem[i_17093 * 4];
        float res_15767 = x_15761 - y_15766;
        int32_t i_15768 = res_15756 + 1;
        float x_15773 = *(float *) &mem_17760.mem[i_15768 * 4];
        float res_15774 = x_15773 - x_15761;
        float y_15776 = res_15767 + res_15774;
        float x_15778 = 2.0F / res_15767;
        float arr_elem_15779 = x_15778 / y_15776;
        float x_15780 = 1.0F / res_15767;
        float y_15781 = 1.0F / res_15774;
        float y_15782 = x_15780 + y_15781;
        float x_15783 = 2.0F * y_15782;
        float negate_arg_15784 = x_15783 / y_15776;
        float arr_elem_15785 = 0.0F - negate_arg_15784;
        float x_15786 = 2.0F / res_15774;
        float arr_elem_15787 = x_15786 / y_15776;
        
        *(float *) &mem_17775.mem[0] = arr_elem_15779;
        *(float *) &mem_17775.mem[4] = arr_elem_15785;
        *(float *) &mem_17775.mem[8] = arr_elem_15787;
        for (int32_t i_17878 = 0; i_17878 < 3; i_17878++) {
            *(float *) &mem_17773.mem[(i_17093 * 3 + i_17878) * 4] =
                *(float *) &mem_17775.mem[i_17878 * 4];
        }
    }
    
    int32_t conc_tmp_15790 = 1 + n_15749;
    int32_t upper_bound_15793 = numT_15651 - 1;
    int32_t upper_bound_less_one_15794 = upper_bound_15793 - 1;
    float replicate_v_15795 = nu_15656 * nu_15656;
    float x_15796 = 0.5F * nu_15656;
    float x_15797 = x_15796 * nu_15656;
    int32_t y_15799 = numX_15649 - 1;
    int32_t y_15801 = numY_15650 - 1;
    char x_15806 = sle32(0, res_15684);
    char y_15807 = slt32(res_15684, numY_15650);
    char assert_arg_15808 = x_15806 && y_15807;
    char bounds_check_15809;
    
    if (!assert_arg_15808) {
        fprintf(stderr, "Assertion %s at %s failed.\n", "assert_arg_15808",
                "./LocVolCalib.fut:223:6-223:6");
        abort();
    }
    
    char x_15810 = sle32(0, res_15683);
    char y_15811 = slt32(res_15683, numX_15649);
    char assert_arg_15812 = x_15810 && y_15811;
    char bounds_check_15813;
    
    if (!assert_arg_15812) {
        fprintf(stderr, "Assertion %s at %s failed.\n", "assert_arg_15812",
                "./LocVolCalib.fut:223:6-223:6");
        abort();
    }
    
    float x_15814 = 0.5F * replicate_v_15795;
    int32_t bytes_17777 = 4 * outer_loop_count_15648;
    struct memblock mem_17778;
    
    mem_17778.references = NULL;
    memblock_alloc(&mem_17778, bytes_17777);
    
    struct memblock mem_17780;
    
    mem_17780.references = NULL;
    memblock_alloc(&mem_17780, bytes_17757);
    
    int32_t bytes_17781 = bytes_17759 * numX_15649;
    struct memblock mem_17783;
    
    mem_17783.references = NULL;
    memblock_alloc(&mem_17783, bytes_17781);
    
    struct memblock mem_17786;
    
    mem_17786.references = NULL;
    memblock_alloc(&mem_17786, bytes_17781);
    
    struct memblock mem_17788;
    
    mem_17788.references = NULL;
    memblock_alloc(&mem_17788, bytes_17757);
    
    struct memblock mem_17790;
    
    mem_17790.references = NULL;
    memblock_alloc(&mem_17790, bytes_17757);
    
    struct memblock mem_17792;
    
    mem_17792.references = NULL;
    memblock_alloc(&mem_17792, bytes_17757);
    
    struct memblock mem_17794;
    
    mem_17794.references = NULL;
    memblock_alloc(&mem_17794, bytes_17757);
    
    struct memblock mem_17796;
    
    mem_17796.references = NULL;
    memblock_alloc(&mem_17796, bytes_17757);
    
    struct memblock mem_17798;
    
    mem_17798.references = NULL;
    memblock_alloc(&mem_17798, 4);
    
    struct memblock mem_17800;
    
    mem_17800.references = NULL;
    memblock_alloc(&mem_17800, 4);
    
    struct memblock mem_17802;
    
    mem_17802.references = NULL;
    memblock_alloc(&mem_17802, 4);
    
    struct memblock mem_17804;
    
    mem_17804.references = NULL;
    memblock_alloc(&mem_17804, 4);
    
    struct memblock mem_17806;
    
    mem_17806.references = NULL;
    memblock_alloc(&mem_17806, 4);
    
    struct memblock mem_17808;
    
    mem_17808.references = NULL;
    memblock_alloc(&mem_17808, bytes_17757);
    
    struct memblock mem_17810;
    
    mem_17810.references = NULL;
    memblock_alloc(&mem_17810, 4);
    
    struct memblock mem_17812;
    
    mem_17812.references = NULL;
    memblock_alloc(&mem_17812, 4);
    
    struct memblock mem_17814;
    
    mem_17814.references = NULL;
    memblock_alloc(&mem_17814, 4);
    
    struct memblock mem_17816;
    
    mem_17816.references = NULL;
    memblock_alloc(&mem_17816, bytes_17757);
    
    struct memblock mem_17818;
    
    mem_17818.references = NULL;
    memblock_alloc(&mem_17818, 4);
    
    struct memblock mem_17820;
    
    mem_17820.references = NULL;
    memblock_alloc(&mem_17820, 4);
    
    struct memblock mem_17822;
    
    mem_17822.references = NULL;
    memblock_alloc(&mem_17822, 4);
    
    struct memblock mem_17824;
    
    mem_17824.references = NULL;
    memblock_alloc(&mem_17824, bytes_17757);
    
    struct memblock mem_17827;
    
    mem_17827.references = NULL;
    memblock_alloc(&mem_17827, bytes_17759);
    
    struct memblock mem_17829;
    
    mem_17829.references = NULL;
    memblock_alloc(&mem_17829, bytes_17759);
    
    struct memblock mem_17831;
    
    mem_17831.references = NULL;
    memblock_alloc(&mem_17831, bytes_17759);
    
    struct memblock mem_17833;
    
    mem_17833.references = NULL;
    memblock_alloc(&mem_17833, bytes_17759);
    
    struct memblock mem_17835;
    
    mem_17835.references = NULL;
    memblock_alloc(&mem_17835, 4);
    
    struct memblock mem_17837;
    
    mem_17837.references = NULL;
    memblock_alloc(&mem_17837, 4);
    
    struct memblock mem_17839;
    
    mem_17839.references = NULL;
    memblock_alloc(&mem_17839, 4);
    
    struct memblock mem_17841;
    
    mem_17841.references = NULL;
    memblock_alloc(&mem_17841, 4);
    
    struct memblock mem_17843;
    
    mem_17843.references = NULL;
    memblock_alloc(&mem_17843, 4);
    
    int32_t bytes_17844 = bytes_17757 * numY_15650;
    struct memblock mem_17846;
    
    mem_17846.references = NULL;
    memblock_alloc(&mem_17846, bytes_17844);
    
    struct memblock mem_17848;
    
    mem_17848.references = NULL;
    memblock_alloc(&mem_17848, bytes_17759);
    
    struct memblock mem_17850;
    
    mem_17850.references = NULL;
    memblock_alloc(&mem_17850, bytes_17759);
    
    struct memblock mem_17852;
    
    mem_17852.references = NULL;
    memblock_alloc(&mem_17852, 4);
    
    struct memblock mem_17854;
    
    mem_17854.references = NULL;
    memblock_alloc(&mem_17854, 4);
    
    struct memblock mem_17856;
    
    mem_17856.references = NULL;
    memblock_alloc(&mem_17856, 4);
    
    struct memblock mem_17858;
    
    mem_17858.references = NULL;
    memblock_alloc(&mem_17858, bytes_17759);
    
    struct memblock mem_17860;
    
    mem_17860.references = NULL;
    memblock_alloc(&mem_17860, 4);
    
    struct memblock mem_17862;
    
    mem_17862.references = NULL;
    memblock_alloc(&mem_17862, 4);
    
    struct memblock mem_17864;
    
    mem_17864.references = NULL;
    memblock_alloc(&mem_17864, 4);
    
    struct memblock mem_17866;
    
    mem_17866.references = NULL;
    memblock_alloc(&mem_17866, bytes_17759);
    for (int32_t i_17468 = 0; i_17468 < outer_loop_count_15648; i_17468++) {
        float y_15818 = sitofp_i32_f32(i_17468);
        float res_15819 = 1.0000000474974513e-3F * y_15818;
        
        for (int32_t i_17097 = 0; i_17097 < numX_15649; i_17097++) {
            float xi_15821 = *(float *) &mem_17758.mem[i_17097 * 4];
            float arg_15822 = xi_15821 - res_15819;
            char cond_15823 = 0.0F < arg_15822;
            float res_15824;
            
            if (cond_15823) {
                res_15824 = arg_15822;
            } else {
                res_15824 = 0.0F;
            }
            *(float *) &mem_17780.mem[i_17097 * 4] = res_15824;
        }
        for (int32_t i_17881 = 0; i_17881 < numY_15650; i_17881++) {
            memmove(mem_17783.mem + numX_15649 * i_17881 * 4, mem_17780.mem + 0,
                    numX_15649 * sizeof(float));
        }
        for (int32_t i_15828 = 0; i_15828 < upper_bound_15793; i_15828++) {
            int32_t i_15829 = upper_bound_less_one_15794 - i_15828;
            float y_15830 = *(float *) &mem_17756.mem[i_15829 * 4];
            float y_15831 = x_15797 * y_15830;
            int32_t i_15842 = i_15829 + 1;
            float x_15843 = *(float *) &mem_17756.mem[i_15842 * 4];
            float y_15844 = x_15843 - y_15830;
            float res_15845 = 1.0F / y_15844;
            
            for (int32_t i_17278 = 0; i_17278 < numY_15650; i_17278++) {
                float yj_15931 = *(float *) &mem_17760.mem[i_17278 * 4];
                char cond_16047 = slt32(0, i_17278);
                char cond_16055 = slt32(i_17278, y_15801);
                char index_concat_cmp_17550 = sle32(conc_tmp_15790, i_17278);
                float index_concat_branch_17554;
                
                if (index_concat_cmp_17550) {
                    int32_t index_concat_i_17551 = i_17278 - conc_tmp_15790;
                    float index_concat_17552 =
                          *(float *) &mem_17764.mem[(index_concat_i_17551 * 3 +
                                                     1) * 4];
                    
                    index_concat_branch_17554 = index_concat_17552;
                } else {
                    char index_concat_cmp_17672 = sle32(1, i_17278);
                    float index_concat_branch_17676;
                    
                    if (index_concat_cmp_17672) {
                        int32_t index_concat_i_17673 = i_17278 - 1;
                        float index_concat_17674 =
                              *(float *) &mem_17773.mem[(index_concat_i_17673 *
                                                         3 + 1) * 4];
                        
                        index_concat_branch_17676 = index_concat_17674;
                    } else {
                        float index_concat_17675 =
                              *(float *) &mem_17764.mem[(i_17278 * 3 + 1) * 4];
                        
                        index_concat_branch_17676 = index_concat_17675;
                    }
                    index_concat_branch_17554 = index_concat_branch_17676;
                }
                
                float y_16064 = x_15814 * index_concat_branch_17554;
                
                for (int32_t i_17101 = 0; i_17101 < numX_15649; i_17101++) {
                    float res_el_16009 = *(float *) &mem_17783.mem[(i_17278 *
                                                                    numX_15649 +
                                                                    i_17101) *
                                                                   4];
                    float xi_16011 = *(float *) &mem_17758.mem[i_17101 * 4];
                    float res_16015;
                    
                    res_16015 = futhark_log32(xi_16011);
                    
                    float x_16016 = beta_15657 * res_16015;
                    float x_16017 = x_16016 + yj_15931;
                    float y_16018 = x_16017 - y_15831;
                    float arg_16019 = 2.0F * y_16018;
                    float res_16020;
                    
                    res_16020 = futhark_exp32(arg_16019);
                    
                    char cond_16021 = slt32(0, i_17101);
                    float res_16022;
                    
                    if (cond_16021) {
                        float x_16023 = 0.5F * res_16020;
                        char index_concat_cmp_17482 = sle32(conc_tmp_15746,
                                                            i_17101);
                        float index_concat_branch_17486;
                        
                        if (index_concat_cmp_17482) {
                            int32_t index_concat_i_17483 = i_17101 -
                                    conc_tmp_15746;
                            float index_concat_17484 =
                                  *(float *) &mem_17764.mem[index_concat_i_17483 *
                                                            3 * 4];
                            
                            index_concat_branch_17486 = index_concat_17484;
                        } else {
                            char index_concat_cmp_17678 = sle32(1, i_17101);
                            float index_concat_branch_17682;
                            
                            if (index_concat_cmp_17678) {
                                int32_t index_concat_i_17679 = i_17101 - 1;
                                float index_concat_17680 =
                                      *(float *) &mem_17767.mem[index_concat_i_17679 *
                                                                3 * 4];
                                
                                index_concat_branch_17682 = index_concat_17680;
                            } else {
                                float index_concat_17681 =
                                      *(float *) &mem_17764.mem[i_17101 * 3 *
                                                                4];
                                
                                index_concat_branch_17682 = index_concat_17681;
                            }
                            index_concat_branch_17486 =
                                index_concat_branch_17682;
                        }
                        
                        float y_16025 = x_16023 * index_concat_branch_17486;
                        int32_t i_16026 = i_17101 - 1;
                        float y_16027 = *(float *) &mem_17783.mem[(i_17278 *
                                                                   numX_15649 +
                                                                   i_16026) *
                                                                  4];
                        float res_16028 = y_16025 * y_16027;
                        
                        res_16022 = res_16028;
                    } else {
                        res_16022 = 0.0F;
                    }
                    
                    char cond_16029 = slt32(i_17101, y_15799);
                    float res_16030;
                    
                    if (cond_16029) {
                        float x_16031 = 0.5F * res_16020;
                        char index_concat_cmp_17492 = sle32(conc_tmp_15746,
                                                            i_17101);
                        float index_concat_branch_17496;
                        
                        if (index_concat_cmp_17492) {
                            int32_t index_concat_i_17493 = i_17101 -
                                    conc_tmp_15746;
                            float index_concat_17494 =
                                  *(float *) &mem_17764.mem[(index_concat_i_17493 *
                                                             3 + 2) * 4];
                            
                            index_concat_branch_17496 = index_concat_17494;
                        } else {
                            char index_concat_cmp_17684 = sle32(1, i_17101);
                            float index_concat_branch_17688;
                            
                            if (index_concat_cmp_17684) {
                                int32_t index_concat_i_17685 = i_17101 - 1;
                                float index_concat_17686 =
                                      *(float *) &mem_17767.mem[(index_concat_i_17685 *
                                                                 3 + 2) * 4];
                                
                                index_concat_branch_17688 = index_concat_17686;
                            } else {
                                float index_concat_17687 =
                                      *(float *) &mem_17764.mem[(i_17101 * 3 +
                                                                 2) * 4];
                                
                                index_concat_branch_17688 = index_concat_17687;
                            }
                            index_concat_branch_17496 =
                                index_concat_branch_17688;
                        }
                        
                        float y_16033 = x_16031 * index_concat_branch_17496;
                        int32_t i_16034 = i_17101 + 1;
                        float y_16035 = *(float *) &mem_17783.mem[(i_17278 *
                                                                   numX_15649 +
                                                                   i_16034) *
                                                                  4];
                        float res_16036 = y_16033 * y_16035;
                        
                        res_16030 = res_16036;
                    } else {
                        res_16030 = 0.0F;
                    }
                    
                    float x_16037 = 0.5F * res_16020;
                    char index_concat_cmp_17560 = sle32(conc_tmp_15746,
                                                        i_17101);
                    float index_concat_branch_17564;
                    
                    if (index_concat_cmp_17560) {
                        int32_t index_concat_i_17561 = i_17101 - conc_tmp_15746;
                        float index_concat_17562 =
                              *(float *) &mem_17764.mem[(index_concat_i_17561 *
                                                         3 + 1) * 4];
                        
                        index_concat_branch_17564 = index_concat_17562;
                    } else {
                        char index_concat_cmp_17690 = sle32(1, i_17101);
                        float index_concat_branch_17694;
                        
                        if (index_concat_cmp_17690) {
                            int32_t index_concat_i_17691 = i_17101 - 1;
                            float index_concat_17692 =
                                  *(float *) &mem_17767.mem[(index_concat_i_17691 *
                                                             3 + 1) * 4];
                            
                            index_concat_branch_17694 = index_concat_17692;
                        } else {
                            float index_concat_17693 =
                                  *(float *) &mem_17764.mem[(i_17101 * 3 + 1) *
                                                            4];
                            
                            index_concat_branch_17694 = index_concat_17693;
                        }
                        index_concat_branch_17564 = index_concat_branch_17694;
                    }
                    
                    float y_16039 = x_16037 * index_concat_branch_17564;
                    float res_16041 = y_16039 * res_el_16009;
                    float x_16042 = res_16022 + res_16041;
                    float res_16043 = x_16042 + res_16030;
                    float x_16044 = res_15845 * res_el_16009;
                    float y_16045 = 0.5F * res_16043;
                    float res_16046 = x_16044 + y_16045;
                    float res_16048;
                    
                    if (cond_16047) {
                        float index_concat_branch_17510;
                        
                        if (index_concat_cmp_17550) {
                            int32_t index_concat_i_17507 = i_17278 -
                                    conc_tmp_15790;
                            float index_concat_17508 =
                                  *(float *) &mem_17764.mem[index_concat_i_17507 *
                                                            3 * 4];
                            
                            index_concat_branch_17510 = index_concat_17508;
                        } else {
                            char index_concat_cmp_17696 = sle32(1, i_17278);
                            float index_concat_branch_17700;
                            
                            if (index_concat_cmp_17696) {
                                int32_t index_concat_i_17697 = i_17278 - 1;
                                float index_concat_17698 =
                                      *(float *) &mem_17773.mem[index_concat_i_17697 *
                                                                3 * 4];
                                
                                index_concat_branch_17700 = index_concat_17698;
                            } else {
                                float index_concat_17699 =
                                      *(float *) &mem_17764.mem[i_17278 * 3 *
                                                                4];
                                
                                index_concat_branch_17700 = index_concat_17699;
                            }
                            index_concat_branch_17510 =
                                index_concat_branch_17700;
                        }
                        
                        float y_16051 = x_15814 * index_concat_branch_17510;
                        int32_t i_16052 = i_17278 - 1;
                        float y_16053 = *(float *) &mem_17783.mem[(i_16052 *
                                                                   numX_15649 +
                                                                   i_17101) *
                                                                  4];
                        float res_16054 = y_16051 * y_16053;
                        
                        res_16048 = res_16054;
                    } else {
                        res_16048 = 0.0F;
                    }
                    
                    float res_16056;
                    
                    if (cond_16055) {
                        float index_concat_branch_17524;
                        
                        if (index_concat_cmp_17550) {
                            int32_t index_concat_i_17521 = i_17278 -
                                    conc_tmp_15790;
                            float index_concat_17522 =
                                  *(float *) &mem_17764.mem[(index_concat_i_17521 *
                                                             3 + 2) * 4];
                            
                            index_concat_branch_17524 = index_concat_17522;
                        } else {
                            char index_concat_cmp_17702 = sle32(1, i_17278);
                            float index_concat_branch_17706;
                            
                            if (index_concat_cmp_17702) {
                                int32_t index_concat_i_17703 = i_17278 - 1;
                                float index_concat_17704 =
                                      *(float *) &mem_17773.mem[(index_concat_i_17703 *
                                                                 3 + 2) * 4];
                                
                                index_concat_branch_17706 = index_concat_17704;
                            } else {
                                float index_concat_17705 =
                                      *(float *) &mem_17764.mem[(i_17278 * 3 +
                                                                 2) * 4];
                                
                                index_concat_branch_17706 = index_concat_17705;
                            }
                            index_concat_branch_17524 =
                                index_concat_branch_17706;
                        }
                        
                        float y_16059 = x_15814 * index_concat_branch_17524;
                        int32_t i_16060 = i_17278 + 1;
                        float y_16061 = *(float *) &mem_17783.mem[(i_16060 *
                                                                   numX_15649 +
                                                                   i_17101) *
                                                                  4];
                        float res_16062 = y_16059 * y_16061;
                        
                        res_16056 = res_16062;
                    } else {
                        res_16056 = 0.0F;
                    }
                    
                    float res_16066 = y_16064 * res_el_16009;
                    float x_16067 = res_16048 + res_16066;
                    float res_16068 = x_16067 + res_16056;
                    float res_16069 = res_16046 + res_16068;
                    float index_concat_branch_17540;
                    
                    if (index_concat_cmp_17560) {
                        int32_t index_concat_i_17537 = i_17101 - conc_tmp_15746;
                        float index_concat_17538 =
                              *(float *) &mem_17764.mem[index_concat_i_17537 *
                                                        3 * 4];
                        
                        index_concat_branch_17540 = index_concat_17538;
                    } else {
                        char index_concat_cmp_17708 = sle32(1, i_17101);
                        float index_concat_branch_17712;
                        
                        if (index_concat_cmp_17708) {
                            int32_t index_concat_i_17709 = i_17101 - 1;
                            float index_concat_17710 =
                                  *(float *) &mem_17767.mem[index_concat_i_17709 *
                                                            3 * 4];
                            
                            index_concat_branch_17712 = index_concat_17710;
                        } else {
                            float index_concat_17711 =
                                  *(float *) &mem_17764.mem[i_17101 * 3 * 4];
                            
                            index_concat_branch_17712 = index_concat_17711;
                        }
                        index_concat_branch_17540 = index_concat_branch_17712;
                    }
                    
                    float y_16072 = x_16037 * index_concat_branch_17540;
                    float y_16073 = 0.5F * y_16072;
                    float res_16074 = 0.0F - y_16073;
                    float y_16077 = 0.5F * y_16039;
                    float res_16078 = res_15845 - y_16077;
                    float index_concat_branch_17532;
                    
                    if (index_concat_cmp_17560) {
                        int32_t index_concat_i_17529 = i_17101 - conc_tmp_15746;
                        float index_concat_17530 =
                              *(float *) &mem_17764.mem[(index_concat_i_17529 *
                                                         3 + 2) * 4];
                        
                        index_concat_branch_17532 = index_concat_17530;
                    } else {
                        char index_concat_cmp_17714 = sle32(1, i_17101);
                        float index_concat_branch_17718;
                        
                        if (index_concat_cmp_17714) {
                            int32_t index_concat_i_17715 = i_17101 - 1;
                            float index_concat_17716 =
                                  *(float *) &mem_17767.mem[(index_concat_i_17715 *
                                                             3 + 2) * 4];
                            
                            index_concat_branch_17718 = index_concat_17716;
                        } else {
                            float index_concat_17717 =
                                  *(float *) &mem_17764.mem[(i_17101 * 3 + 2) *
                                                            4];
                            
                            index_concat_branch_17718 = index_concat_17717;
                        }
                        index_concat_branch_17532 = index_concat_branch_17718;
                    }
                    
                    float y_16080 = x_16037 * index_concat_branch_17532;
                    float y_16081 = 0.5F * y_16080;
                    float res_16082 = 0.0F - y_16081;
                    
                    *(float *) &mem_17788.mem[i_17101 * 4] = res_16074;
                    *(float *) &mem_17790.mem[i_17101 * 4] = res_16078;
                    *(float *) &mem_17792.mem[i_17101 * 4] = res_16082;
                    *(float *) &mem_17794.mem[i_17101 * 4] = res_16069;
                }
                
                float res_16087 = *(float *) &mem_17790.mem[0];
                float stream_accres_17153;
                float stream_accres_17154;
                float stream_accres_17155;
                float stream_accres_17156;
                float acc_17160;
                float acc_17157;
                float acc_17158;
                float acc_17159;
                
                acc_17157 = 1.0F;
                acc_17158 = 0.0F;
                acc_17159 = 0.0F;
                acc_17160 = 1.0F;
                for (int32_t loopind_17161 = 0; loopind_17161 < numX_15649;
                     loopind_17161++) {
                    char cond_16196 = slt32(0, loopind_17161);
                    float res_16197;
                    float res_16198;
                    float res_16199;
                    float res_16200;
                    
                    if (cond_16196) {
                        float res_16201 =
                              *(float *) &mem_17790.mem[loopind_17161 * 4];
                        float x_16202 =
                              *(float *) &mem_17788.mem[loopind_17161 * 4];
                        int32_t i_16203 = loopind_17161 - 1;
                        float y_16204 = *(float *) &mem_17792.mem[i_16203 * 4];
                        float y_16205 = x_16202 * y_16204;
                        float res_16206 = 0.0F - y_16205;
                        
                        res_16197 = res_16201;
                        res_16198 = res_16206;
                        res_16199 = 1.0F;
                        res_16200 = 0.0F;
                    } else {
                        res_16197 = 1.0F;
                        res_16198 = 0.0F;
                        res_16199 = 0.0F;
                        res_16200 = 1.0F;
                    }
                    
                    float res_16208 = 1.0F / res_16197;
                    float res_16212 = res_16197 * res_16208;
                    float res_16216 = res_16198 * res_16208;
                    float res_16220 = res_16199 * res_16208;
                    float res_16224 = res_16200 * res_16208;
                    
                    *(float *) &mem_17798.mem[0] = res_16212;
                    *(float *) &mem_17800.mem[0] = res_16216;
                    *(float *) &mem_17802.mem[0] = res_16220;
                    *(float *) &mem_17804.mem[0] = res_16224;
                    
                    float lstel_tmp_16235 = *(float *) &mem_17798.mem[0];
                    float lstel_tmp_16236 = *(float *) &mem_17800.mem[0];
                    float lstel_tmp_16237 = *(float *) &mem_17802.mem[0];
                    float lstel_tmp_16238 = *(float *) &mem_17804.mem[0];
                    float y_16265 = acc_17157 * lstel_tmp_16235;
                    float res_16266 = 1.0F / y_16265;
                    float x_16267 = lstel_tmp_16235 * acc_17157;
                    float y_16268 = lstel_tmp_16236 * acc_17159;
                    float x_16269 = x_16267 + y_16268;
                    float res_16270 = x_16269 * res_16266;
                    float x_16271 = lstel_tmp_16235 * acc_17158;
                    float y_16272 = lstel_tmp_16236 * acc_17160;
                    float x_16273 = x_16271 + y_16272;
                    float res_16274 = x_16273 * res_16266;
                    float x_16275 = lstel_tmp_16237 * acc_17157;
                    float y_16276 = lstel_tmp_16238 * acc_17159;
                    float x_16277 = x_16275 + y_16276;
                    float res_16278 = x_16277 * res_16266;
                    float x_16279 = lstel_tmp_16237 * acc_17158;
                    float y_16280 = lstel_tmp_16238 * acc_17160;
                    float x_16281 = x_16279 + y_16280;
                    float res_16282 = x_16281 * res_16266;
                    float x_16306 = res_16270 * res_16087;
                    float x_16307 = x_16306 + res_16274;
                    float x_16308 = res_16278 * res_16087;
                    float y_16309 = x_16308 + res_16282;
                    float res_16310 = x_16307 / y_16309;
                    
                    *(float *) &mem_17806.mem[0] = res_16310;
                    
                    float values_17176 = *(float *) &mem_17806.mem[0];
                    
                    *(float *) &mem_17796.mem[loopind_17161 * 4] = values_17176;
                    
                    float acc_tmp_17888 = res_16270;
                    float acc_tmp_17889 = res_16274;
                    float acc_tmp_17890 = res_16278;
                    float acc_tmp_17891;
                    
                    acc_tmp_17891 = res_16282;
                    acc_17157 = acc_tmp_17888;
                    acc_17158 = acc_tmp_17889;
                    acc_17159 = acc_tmp_17890;
                    acc_17160 = acc_tmp_17891;
                }
                stream_accres_17153 = acc_17157;
                stream_accres_17154 = acc_17158;
                stream_accres_17155 = acc_17159;
                stream_accres_17156 = acc_17160;
                
                float res_16317 = *(float *) &mem_17794.mem[0];
                float stream_accres_17204;
                float stream_accres_17205;
                float acc_17206;
                float acc_17207;
                
                acc_17206 = 0.0F;
                acc_17207 = 1.0F;
                for (int32_t loopind_17208 = 0; loopind_17208 < numX_15649;
                     loopind_17208++) {
                    char cond_16370 = slt32(0, loopind_17208);
                    float res_16371;
                    float res_16372;
                    
                    if (cond_16370) {
                        float res_16373 =
                              *(float *) &mem_17794.mem[loopind_17208 * 4];
                        float x_16374 =
                              *(float *) &mem_17788.mem[loopind_17208 * 4];
                        int32_t i_16375 = loopind_17208 - 1;
                        float y_16376 = *(float *) &mem_17796.mem[i_16375 * 4];
                        float y_16377 = x_16374 / y_16376;
                        float res_16378 = 0.0F - y_16377;
                        
                        res_16371 = res_16373;
                        res_16372 = res_16378;
                    } else {
                        res_16371 = 0.0F;
                        res_16372 = 1.0F;
                    }
                    *(float *) &mem_17810.mem[0] = res_16371;
                    *(float *) &mem_17812.mem[0] = res_16372;
                    
                    float lstel_tmp_16388 = *(float *) &mem_17810.mem[0];
                    float lstel_tmp_16389 = *(float *) &mem_17812.mem[0];
                    float y_16397 = lstel_tmp_16389 * acc_17206;
                    float res_16398 = lstel_tmp_16388 + y_16397;
                    float res_16399 = acc_17207 * lstel_tmp_16389;
                    float y_16406 = res_16399 * res_16317;
                    float res_16407 = res_16398 + y_16406;
                    
                    *(float *) &mem_17814.mem[0] = res_16407;
                    
                    float values_17223 = *(float *) &mem_17814.mem[0];
                    
                    *(float *) &mem_17808.mem[loopind_17208 * 4] = values_17223;
                    
                    float acc_tmp_17893 = res_16398;
                    float acc_tmp_17894;
                    
                    acc_tmp_17894 = res_16399;
                    acc_17206 = acc_tmp_17893;
                    acc_17207 = acc_tmp_17894;
                }
                stream_accres_17204 = acc_17206;
                stream_accres_17205 = acc_17207;
                
                float x_16412 = *(float *) &mem_17808.mem[y_15799 * 4];
                float y_16413 = *(float *) &mem_17796.mem[y_15799 * 4];
                float res_16414 = x_16412 / y_16413;
                float stream_accres_17251;
                float stream_accres_17252;
                float acc_17253;
                float acc_17254;
                
                acc_17253 = 0.0F;
                acc_17254 = 1.0F;
                for (int32_t loopind_17255 = 0; loopind_17255 < numX_15649;
                     loopind_17255++) {
                    int32_t x_16471 = numX_15649 - loopind_17255;
                    int32_t res_16472 = x_16471 - 1;
                    char cond_16473 = slt32(0, loopind_17255);
                    float res_16474;
                    float res_16475;
                    
                    if (cond_16473) {
                        float x_16476 = *(float *) &mem_17808.mem[res_16472 *
                                                                  4];
                        float y_16477 = *(float *) &mem_17796.mem[res_16472 *
                                                                  4];
                        float res_16478 = x_16476 / y_16477;
                        float x_16479 = *(float *) &mem_17792.mem[res_16472 *
                                                                  4];
                        float y_16480 = x_16479 / y_16477;
                        float res_16481 = 0.0F - y_16480;
                        
                        res_16474 = res_16478;
                        res_16475 = res_16481;
                    } else {
                        res_16474 = 0.0F;
                        res_16475 = 1.0F;
                    }
                    *(float *) &mem_17818.mem[0] = res_16474;
                    *(float *) &mem_17820.mem[0] = res_16475;
                    
                    float lstel_tmp_16491 = *(float *) &mem_17818.mem[0];
                    float lstel_tmp_16492 = *(float *) &mem_17820.mem[0];
                    float y_16500 = lstel_tmp_16492 * acc_17253;
                    float res_16501 = lstel_tmp_16491 + y_16500;
                    float res_16502 = acc_17254 * lstel_tmp_16492;
                    float y_16509 = res_16502 * res_16414;
                    float res_16510 = res_16501 + y_16509;
                    
                    *(float *) &mem_17822.mem[0] = res_16510;
                    
                    float values_17270 = *(float *) &mem_17822.mem[0];
                    
                    *(float *) &mem_17816.mem[loopind_17255 * 4] = values_17270;
                    
                    float acc_tmp_17896 = res_16501;
                    float acc_tmp_17897;
                    
                    acc_tmp_17897 = res_16502;
                    acc_17253 = acc_tmp_17896;
                    acc_17254 = acc_tmp_17897;
                }
                stream_accres_17251 = acc_17253;
                stream_accres_17252 = acc_17254;
                for (int32_t i_17274 = 0; i_17274 < numX_15649; i_17274++) {
                    int32_t x_16517 = numX_15649 - i_17274;
                    int32_t i_16518 = x_16517 - 1;
                    float res_16519 = *(float *) &mem_17816.mem[i_16518 * 4];
                    
                    *(float *) &mem_17824.mem[i_17274 * 4] = res_16519;
                }
                for (int32_t i_17900 = 0; i_17900 < numX_15649; i_17900++) {
                    *(float *) &mem_17786.mem[(i_17278 * numX_15649 + i_17900) *
                                              4] =
                        *(float *) &mem_17824.mem[i_17900 * 4];
                }
            }
            for (int32_t i_17285 = 0; i_17285 < numY_15650; i_17285++) {
                char index_concat_cmp_17613 = sle32(conc_tmp_15790, i_17285);
                float index_concat_branch_17617;
                
                if (index_concat_cmp_17613) {
                    int32_t index_concat_i_17614 = i_17285 - conc_tmp_15790;
                    float index_concat_17615 =
                          *(float *) &mem_17764.mem[index_concat_i_17614 * 3 *
                                                    4];
                    
                    index_concat_branch_17617 = index_concat_17615;
                } else {
                    char index_concat_cmp_17720 = sle32(1, i_17285);
                    float index_concat_branch_17724;
                    
                    if (index_concat_cmp_17720) {
                        int32_t index_concat_i_17721 = i_17285 - 1;
                        float index_concat_17722 =
                              *(float *) &mem_17773.mem[index_concat_i_17721 *
                                                        3 * 4];
                        
                        index_concat_branch_17724 = index_concat_17722;
                    } else {
                        float index_concat_17723 =
                              *(float *) &mem_17764.mem[i_17285 * 3 * 4];
                        
                        index_concat_branch_17724 = index_concat_17723;
                    }
                    index_concat_branch_17617 = index_concat_branch_17724;
                }
                
                float y_16536 = x_15814 * index_concat_branch_17617;
                float y_16537 = 0.5F * y_16536;
                float res_16538 = 0.0F - y_16537;
                float index_concat_branch_17609;
                
                if (index_concat_cmp_17613) {
                    int32_t index_concat_i_17606 = i_17285 - conc_tmp_15790;
                    float index_concat_17607 =
                          *(float *) &mem_17764.mem[(index_concat_i_17606 * 3 +
                                                     1) * 4];
                    
                    index_concat_branch_17609 = index_concat_17607;
                } else {
                    char index_concat_cmp_17726 = sle32(1, i_17285);
                    float index_concat_branch_17730;
                    
                    if (index_concat_cmp_17726) {
                        int32_t index_concat_i_17727 = i_17285 - 1;
                        float index_concat_17728 =
                              *(float *) &mem_17773.mem[(index_concat_i_17727 *
                                                         3 + 1) * 4];
                        
                        index_concat_branch_17730 = index_concat_17728;
                    } else {
                        float index_concat_17729 =
                              *(float *) &mem_17764.mem[(i_17285 * 3 + 1) * 4];
                        
                        index_concat_branch_17730 = index_concat_17729;
                    }
                    index_concat_branch_17609 = index_concat_branch_17730;
                }
                
                float y_16540 = x_15814 * index_concat_branch_17609;
                float y_16541 = 0.5F * y_16540;
                float res_16542 = res_15845 - y_16541;
                float index_concat_branch_17601;
                
                if (index_concat_cmp_17613) {
                    int32_t index_concat_i_17598 = i_17285 - conc_tmp_15790;
                    float index_concat_17599 =
                          *(float *) &mem_17764.mem[(index_concat_i_17598 * 3 +
                                                     2) * 4];
                    
                    index_concat_branch_17601 = index_concat_17599;
                } else {
                    char index_concat_cmp_17732 = sle32(1, i_17285);
                    float index_concat_branch_17736;
                    
                    if (index_concat_cmp_17732) {
                        int32_t index_concat_i_17733 = i_17285 - 1;
                        float index_concat_17734 =
                              *(float *) &mem_17773.mem[(index_concat_i_17733 *
                                                         3 + 2) * 4];
                        
                        index_concat_branch_17736 = index_concat_17734;
                    } else {
                        float index_concat_17735 =
                              *(float *) &mem_17764.mem[(i_17285 * 3 + 2) * 4];
                        
                        index_concat_branch_17736 = index_concat_17735;
                    }
                    index_concat_branch_17601 = index_concat_branch_17736;
                }
                
                float y_16544 = x_15814 * index_concat_branch_17601;
                float y_16545 = 0.5F * y_16544;
                float res_16546 = 0.0F - y_16545;
                
                *(float *) &mem_17827.mem[i_17285 * 4] = res_16538;
                *(float *) &mem_17829.mem[i_17285 * 4] = res_16542;
                *(float *) &mem_17831.mem[i_17285 * 4] = res_16546;
            }
            
            float res_16547 = *(float *) &mem_17829.mem[0];
            float stream_accres_17332;
            float stream_accres_17333;
            float stream_accres_17334;
            float stream_accres_17335;
            float acc_17336;
            float acc_17337;
            float acc_17338;
            float acc_17339;
            
            acc_17336 = 1.0F;
            acc_17337 = 0.0F;
            acc_17338 = 0.0F;
            acc_17339 = 1.0F;
            for (int32_t loopind_17340 = 0; loopind_17340 < numY_15650;
                 loopind_17340++) {
                char cond_16656 = slt32(0, loopind_17340);
                float res_16657;
                float res_16658;
                float res_16659;
                float res_16660;
                
                if (cond_16656) {
                    float res_16661 = *(float *) &mem_17829.mem[loopind_17340 *
                                                                4];
                    float x_16662 = *(float *) &mem_17827.mem[loopind_17340 *
                                                              4];
                    int32_t i_16663 = loopind_17340 - 1;
                    float y_16664 = *(float *) &mem_17831.mem[i_16663 * 4];
                    float y_16665 = x_16662 * y_16664;
                    float res_16666 = 0.0F - y_16665;
                    
                    res_16657 = res_16661;
                    res_16658 = res_16666;
                    res_16659 = 1.0F;
                    res_16660 = 0.0F;
                } else {
                    res_16657 = 1.0F;
                    res_16658 = 0.0F;
                    res_16659 = 0.0F;
                    res_16660 = 1.0F;
                }
                
                float res_16668 = 1.0F / res_16657;
                float res_16672 = res_16657 * res_16668;
                float res_16676 = res_16658 * res_16668;
                float res_16680 = res_16659 * res_16668;
                float res_16684 = res_16660 * res_16668;
                
                *(float *) &mem_17835.mem[0] = res_16672;
                *(float *) &mem_17837.mem[0] = res_16676;
                *(float *) &mem_17839.mem[0] = res_16680;
                *(float *) &mem_17841.mem[0] = res_16684;
                
                float lstel_tmp_16695 = *(float *) &mem_17835.mem[0];
                float lstel_tmp_16696 = *(float *) &mem_17837.mem[0];
                float lstel_tmp_16697 = *(float *) &mem_17839.mem[0];
                float lstel_tmp_16698 = *(float *) &mem_17841.mem[0];
                float y_16725 = acc_17336 * lstel_tmp_16695;
                float res_16726 = 1.0F / y_16725;
                float x_16727 = lstel_tmp_16695 * acc_17336;
                float y_16728 = lstel_tmp_16696 * acc_17338;
                float x_16729 = x_16727 + y_16728;
                float res_16730 = x_16729 * res_16726;
                float x_16731 = lstel_tmp_16695 * acc_17337;
                float y_16732 = lstel_tmp_16696 * acc_17339;
                float x_16733 = x_16731 + y_16732;
                float res_16734 = x_16733 * res_16726;
                float x_16735 = lstel_tmp_16697 * acc_17336;
                float y_16736 = lstel_tmp_16698 * acc_17338;
                float x_16737 = x_16735 + y_16736;
                float res_16738 = x_16737 * res_16726;
                float x_16739 = lstel_tmp_16697 * acc_17337;
                float y_16740 = lstel_tmp_16698 * acc_17339;
                float x_16741 = x_16739 + y_16740;
                float res_16742 = x_16741 * res_16726;
                float x_16766 = res_16730 * res_16547;
                float x_16767 = x_16766 + res_16734;
                float x_16768 = res_16738 * res_16547;
                float y_16769 = x_16768 + res_16742;
                float res_16770 = x_16767 / y_16769;
                
                *(float *) &mem_17843.mem[0] = res_16770;
                
                float values_17355 = *(float *) &mem_17843.mem[0];
                
                *(float *) &mem_17833.mem[loopind_17340 * 4] = values_17355;
                
                float acc_tmp_17904 = res_16730;
                float acc_tmp_17905 = res_16734;
                float acc_tmp_17906 = res_16738;
                float acc_tmp_17907;
                
                acc_tmp_17907 = res_16742;
                acc_17336 = acc_tmp_17904;
                acc_17337 = acc_tmp_17905;
                acc_17338 = acc_tmp_17906;
                acc_17339 = acc_tmp_17907;
            }
            stream_accres_17332 = acc_17336;
            stream_accres_17333 = acc_17337;
            stream_accres_17334 = acc_17338;
            stream_accres_17335 = acc_17339;
            
            float y_16777 = *(float *) &mem_17833.mem[y_15801 * 4];
            
            for (int32_t i_17462 = 0; i_17462 < numX_15649; i_17462++) {
                for (int32_t i_17359 = 0; i_17359 < numY_15650; i_17359++) {
                    float u_el_16811 = *(float *) &mem_17786.mem[(i_17359 *
                                                                  numX_15649 +
                                                                  i_17462) * 4];
                    char cond_16812 = slt32(0, i_17359);
                    float res_16813;
                    
                    if (cond_16812) {
                        char index_concat_cmp_17631 = sle32(conc_tmp_15790,
                                                            i_17359);
                        float index_concat_branch_17635;
                        
                        if (index_concat_cmp_17631) {
                            int32_t index_concat_i_17632 = i_17359 -
                                    conc_tmp_15790;
                            float index_concat_17633 =
                                  *(float *) &mem_17764.mem[index_concat_i_17632 *
                                                            3 * 4];
                            
                            index_concat_branch_17635 = index_concat_17633;
                        } else {
                            char index_concat_cmp_17738 = sle32(1, i_17359);
                            float index_concat_branch_17742;
                            
                            if (index_concat_cmp_17738) {
                                int32_t index_concat_i_17739 = i_17359 - 1;
                                float index_concat_17740 =
                                      *(float *) &mem_17773.mem[index_concat_i_17739 *
                                                                3 * 4];
                                
                                index_concat_branch_17742 = index_concat_17740;
                            } else {
                                float index_concat_17741 =
                                      *(float *) &mem_17764.mem[i_17359 * 3 *
                                                                4];
                                
                                index_concat_branch_17742 = index_concat_17741;
                            }
                            index_concat_branch_17635 =
                                index_concat_branch_17742;
                        }
                        
                        float y_16816 = x_15814 * index_concat_branch_17635;
                        int32_t i_16817 = i_17359 - 1;
                        float y_16818 = *(float *) &mem_17783.mem[(i_16817 *
                                                                   numX_15649 +
                                                                   i_17462) *
                                                                  4];
                        float res_16819 = y_16816 * y_16818;
                        
                        res_16813 = res_16819;
                    } else {
                        res_16813 = 0.0F;
                    }
                    
                    char cond_16820 = slt32(i_17359, y_15801);
                    float res_16821;
                    
                    if (cond_16820) {
                        char index_concat_cmp_17641 = sle32(conc_tmp_15790,
                                                            i_17359);
                        float index_concat_branch_17645;
                        
                        if (index_concat_cmp_17641) {
                            int32_t index_concat_i_17642 = i_17359 -
                                    conc_tmp_15790;
                            float index_concat_17643 =
                                  *(float *) &mem_17764.mem[(index_concat_i_17642 *
                                                             3 + 2) * 4];
                            
                            index_concat_branch_17645 = index_concat_17643;
                        } else {
                            char index_concat_cmp_17744 = sle32(1, i_17359);
                            float index_concat_branch_17748;
                            
                            if (index_concat_cmp_17744) {
                                int32_t index_concat_i_17745 = i_17359 - 1;
                                float index_concat_17746 =
                                      *(float *) &mem_17773.mem[(index_concat_i_17745 *
                                                                 3 + 2) * 4];
                                
                                index_concat_branch_17748 = index_concat_17746;
                            } else {
                                float index_concat_17747 =
                                      *(float *) &mem_17764.mem[(i_17359 * 3 +
                                                                 2) * 4];
                                
                                index_concat_branch_17748 = index_concat_17747;
                            }
                            index_concat_branch_17645 =
                                index_concat_branch_17748;
                        }
                        
                        float y_16824 = x_15814 * index_concat_branch_17645;
                        int32_t i_16825 = i_17359 + 1;
                        float y_16826 = *(float *) &mem_17783.mem[(i_16825 *
                                                                   numX_15649 +
                                                                   i_17462) *
                                                                  4];
                        float res_16827 = y_16824 * y_16826;
                        
                        res_16821 = res_16827;
                    } else {
                        res_16821 = 0.0F;
                    }
                    
                    char index_concat_cmp_17651 = sle32(conc_tmp_15790,
                                                        i_17359);
                    float index_concat_branch_17655;
                    
                    if (index_concat_cmp_17651) {
                        int32_t index_concat_i_17652 = i_17359 - conc_tmp_15790;
                        float index_concat_17653 =
                              *(float *) &mem_17764.mem[(index_concat_i_17652 *
                                                         3 + 1) * 4];
                        
                        index_concat_branch_17655 = index_concat_17653;
                    } else {
                        char index_concat_cmp_17750 = sle32(1, i_17359);
                        float index_concat_branch_17754;
                        
                        if (index_concat_cmp_17750) {
                            int32_t index_concat_i_17751 = i_17359 - 1;
                            float index_concat_17752 =
                                  *(float *) &mem_17773.mem[(index_concat_i_17751 *
                                                             3 + 1) * 4];
                            
                            index_concat_branch_17754 = index_concat_17752;
                        } else {
                            float index_concat_17753 =
                                  *(float *) &mem_17764.mem[(i_17359 * 3 + 1) *
                                                            4];
                            
                            index_concat_branch_17754 = index_concat_17753;
                        }
                        index_concat_branch_17655 = index_concat_branch_17754;
                    }
                    
                    float y_16829 = x_15814 * index_concat_branch_17655;
                    float y_16830 = *(float *) &mem_17783.mem[(i_17359 *
                                                               numX_15649 +
                                                               i_17462) * 4];
                    float res_16831 = y_16829 * y_16830;
                    float x_16832 = res_16813 + res_16831;
                    float res_16833 = x_16832 + res_16821;
                    float x_16834 = res_15845 * u_el_16811;
                    float y_16835 = 0.5F * res_16833;
                    float res_16836 = x_16834 - y_16835;
                    
                    *(float *) &mem_17848.mem[i_17359 * 4] = res_16836;
                }
                
                float res_16838 = *(float *) &mem_17848.mem[0];
                float stream_accres_17388;
                float stream_accres_17389;
                float acc_17390;
                float acc_17391;
                
                acc_17390 = 0.0F;
                acc_17391 = 1.0F;
                for (int32_t loopind_17392 = 0; loopind_17392 < numY_15650;
                     loopind_17392++) {
                    char cond_16891 = slt32(0, loopind_17392);
                    float res_16892;
                    float res_16893;
                    
                    if (cond_16891) {
                        float res_16894 =
                              *(float *) &mem_17848.mem[loopind_17392 * 4];
                        float x_16895 =
                              *(float *) &mem_17827.mem[loopind_17392 * 4];
                        int32_t i_16896 = loopind_17392 - 1;
                        float y_16897 = *(float *) &mem_17833.mem[i_16896 * 4];
                        float y_16898 = x_16895 / y_16897;
                        float res_16899 = 0.0F - y_16898;
                        
                        res_16892 = res_16894;
                        res_16893 = res_16899;
                    } else {
                        res_16892 = 0.0F;
                        res_16893 = 1.0F;
                    }
                    *(float *) &mem_17852.mem[0] = res_16892;
                    *(float *) &mem_17854.mem[0] = res_16893;
                    
                    float lstel_tmp_16909 = *(float *) &mem_17852.mem[0];
                    float lstel_tmp_16910 = *(float *) &mem_17854.mem[0];
                    float y_16918 = lstel_tmp_16910 * acc_17390;
                    float res_16919 = lstel_tmp_16909 + y_16918;
                    float res_16920 = acc_17391 * lstel_tmp_16910;
                    float y_16927 = res_16920 * res_16838;
                    float res_16928 = res_16919 + y_16927;
                    
                    *(float *) &mem_17856.mem[0] = res_16928;
                    
                    float values_17407 = *(float *) &mem_17856.mem[0];
                    
                    *(float *) &mem_17850.mem[loopind_17392 * 4] = values_17407;
                    
                    float acc_tmp_17911 = res_16919;
                    float acc_tmp_17912;
                    
                    acc_tmp_17912 = res_16920;
                    acc_17390 = acc_tmp_17911;
                    acc_17391 = acc_tmp_17912;
                }
                stream_accres_17388 = acc_17390;
                stream_accres_17389 = acc_17391;
                
                float x_16933 = *(float *) &mem_17850.mem[y_15801 * 4];
                float res_16934 = x_16933 / y_16777;
                float stream_accres_17435;
                float stream_accres_17436;
                float acc_17437;
                float acc_17438;
                
                acc_17437 = 0.0F;
                acc_17438 = 1.0F;
                for (int32_t loopind_17439 = 0; loopind_17439 < numY_15650;
                     loopind_17439++) {
                    int32_t x_16991 = numY_15650 - loopind_17439;
                    int32_t res_16992 = x_16991 - 1;
                    char cond_16993 = slt32(0, loopind_17439);
                    float res_16994;
                    float res_16995;
                    
                    if (cond_16993) {
                        float x_16996 = *(float *) &mem_17850.mem[res_16992 *
                                                                  4];
                        float y_16997 = *(float *) &mem_17833.mem[res_16992 *
                                                                  4];
                        float res_16998 = x_16996 / y_16997;
                        float x_16999 = *(float *) &mem_17831.mem[res_16992 *
                                                                  4];
                        float y_17000 = x_16999 / y_16997;
                        float res_17001 = 0.0F - y_17000;
                        
                        res_16994 = res_16998;
                        res_16995 = res_17001;
                    } else {
                        res_16994 = 0.0F;
                        res_16995 = 1.0F;
                    }
                    *(float *) &mem_17860.mem[0] = res_16994;
                    *(float *) &mem_17862.mem[0] = res_16995;
                    
                    float lstel_tmp_17011 = *(float *) &mem_17860.mem[0];
                    float lstel_tmp_17012 = *(float *) &mem_17862.mem[0];
                    float y_17020 = lstel_tmp_17012 * acc_17437;
                    float res_17021 = lstel_tmp_17011 + y_17020;
                    float res_17022 = acc_17438 * lstel_tmp_17012;
                    float y_17029 = res_17022 * res_16934;
                    float res_17030 = res_17021 + y_17029;
                    
                    *(float *) &mem_17864.mem[0] = res_17030;
                    
                    float values_17454 = *(float *) &mem_17864.mem[0];
                    
                    *(float *) &mem_17858.mem[loopind_17439 * 4] = values_17454;
                    
                    float acc_tmp_17914 = res_17021;
                    float acc_tmp_17915;
                    
                    acc_tmp_17915 = res_17022;
                    acc_17437 = acc_tmp_17914;
                    acc_17438 = acc_tmp_17915;
                }
                stream_accres_17435 = acc_17437;
                stream_accres_17436 = acc_17438;
                for (int32_t i_17458 = 0; i_17458 < numY_15650; i_17458++) {
                    int32_t x_17037 = numY_15650 - i_17458;
                    int32_t i_17038 = x_17037 - 1;
                    float res_17039 = *(float *) &mem_17858.mem[i_17038 * 4];
                    
                    *(float *) &mem_17866.mem[i_17458 * 4] = res_17039;
                }
                for (int32_t i_17918 = 0; i_17918 < numY_15650; i_17918++) {
                    *(float *) &mem_17846.mem[(i_17462 * numY_15650 + i_17918) *
                                              4] =
                        *(float *) &mem_17866.mem[i_17918 * 4];
                }
            }
            for (int32_t i_17919 = 0; i_17919 < numY_15650; i_17919++) {
                for (int32_t i_17920 = 0; i_17920 < numX_15649; i_17920++) {
                    *(float *) &mem_17783.mem[(i_17919 * numX_15649 + i_17920) *
                                              4] =
                        *(float *) &mem_17846.mem[(i_17920 * numY_15650 +
                                                   i_17919) * 4];
                }
            }
        }
        
        float res_17042 = *(float *) &mem_17783.mem[(res_15684 * numX_15649 +
                                                     res_15683) * 4];
        
        *(float *) &mem_17778.mem[i_17468 * 4] = res_17042;
    }
    memblock_set(&out_mem_17869, &mem_17778);
    out_arrsizze_17871 = outer_loop_count_15648;
    out_memsizze_17870 = bytes_17777;
    
    struct tuple_int32_t_mem_int32_t retval_17921;
    
    retval_17921.elem_0 = out_memsizze_17870;
    retval_17921.elem_1.references = NULL;
    memblock_set(&retval_17921.elem_1, &out_mem_17869);
    retval_17921.elem_2 = out_arrsizze_17871;
    memblock_unref(&out_mem_17869);
    memblock_unref(&mem_17756);
    memblock_unref(&mem_17758);
    memblock_unref(&mem_17760);
    memblock_unref(&mem_17762);
    memblock_unref(&mem_17764);
    memblock_unref(&mem_17767);
    memblock_unref(&mem_17769);
    memblock_unref(&mem_17773);
    memblock_unref(&mem_17775);
    memblock_unref(&mem_17778);
    memblock_unref(&mem_17780);
    memblock_unref(&mem_17783);
    memblock_unref(&mem_17786);
    memblock_unref(&mem_17788);
    memblock_unref(&mem_17790);
    memblock_unref(&mem_17792);
    memblock_unref(&mem_17794);
    memblock_unref(&mem_17796);
    memblock_unref(&mem_17798);
    memblock_unref(&mem_17800);
    memblock_unref(&mem_17802);
    memblock_unref(&mem_17804);
    memblock_unref(&mem_17806);
    memblock_unref(&mem_17808);
    memblock_unref(&mem_17810);
    memblock_unref(&mem_17812);
    memblock_unref(&mem_17814);
    memblock_unref(&mem_17816);
    memblock_unref(&mem_17818);
    memblock_unref(&mem_17820);
    memblock_unref(&mem_17822);
    memblock_unref(&mem_17824);
    memblock_unref(&mem_17827);
    memblock_unref(&mem_17829);
    memblock_unref(&mem_17831);
    memblock_unref(&mem_17833);
    memblock_unref(&mem_17835);
    memblock_unref(&mem_17837);
    memblock_unref(&mem_17839);
    memblock_unref(&mem_17841);
    memblock_unref(&mem_17843);
    memblock_unref(&mem_17846);
    memblock_unref(&mem_17848);
    memblock_unref(&mem_17850);
    memblock_unref(&mem_17852);
    memblock_unref(&mem_17854);
    memblock_unref(&mem_17856);
    memblock_unref(&mem_17858);
    memblock_unref(&mem_17860);
    memblock_unref(&mem_17862);
    memblock_unref(&mem_17864);
    memblock_unref(&mem_17866);
    return retval_17921;
}
#include <inttypes.h>

struct array_reader {
  char* elems;
  int64_t n_elems_space;
  int64_t elem_size;
  int64_t n_elems_used;
  int64_t *shape;
  int (*elem_reader)(void*);
};

static int peekc() {
  int c = getchar();
  ungetc(c,stdin);
  return c;
}

static int next_is_not_constituent() {
  int c = peekc();
  return c == EOF || !isalnum(c);
}

static void skipspaces() {
  int c = getchar();
  if (isspace(c)) {
    skipspaces();
  } else if (c == '-' && peekc() == '-') {
    // Skip to end of line.
    for (; c != '\n' && c != EOF; c = getchar());
    // Next line may have more spaces.
    skipspaces();
  } else if (c != EOF) {
    ungetc(c, stdin);
  }
}

static int read_str_elem(struct array_reader *reader) {
  int ret;
  if (reader->n_elems_used == reader->n_elems_space) {
    reader->n_elems_space *= 2;
    reader->elems = (char*) realloc(reader->elems,
                                    reader->n_elems_space * reader->elem_size);
  }

  ret = reader->elem_reader(reader->elems + reader->n_elems_used * reader->elem_size);

  if (ret == 0) {
    reader->n_elems_used++;
  }

  return ret;
}

static int read_str_array_elems(struct array_reader *reader, int dims) {
  int c;
  int ret;
  int first = 1;
  char *knows_dimsize = (char*) calloc(dims,sizeof(char));
  int cur_dim = dims-1;
  int64_t *elems_read_in_dim = (int64_t*) calloc(dims,sizeof(int64_t));
  while (1) {
    skipspaces();

    c = getchar();
    if (c == ']') {
      if (knows_dimsize[cur_dim]) {
        if (reader->shape[cur_dim] != elems_read_in_dim[cur_dim]) {
          ret = 1;
          break;
        }
      } else {
        knows_dimsize[cur_dim] = 1;
        reader->shape[cur_dim] = elems_read_in_dim[cur_dim];
      }
      if (cur_dim == 0) {
        ret = 0;
        break;
      } else {
        cur_dim--;
        elems_read_in_dim[cur_dim]++;
      }
    } else if (c == ',') {
      skipspaces();
      c = getchar();
      if (c == '[') {
        if (cur_dim == dims - 1) {
          ret = 1;
          break;
        }
        first = 1;
        cur_dim++;
        elems_read_in_dim[cur_dim] = 0;
      } else if (cur_dim == dims - 1) {
        ungetc(c, stdin);
        ret = read_str_elem(reader);
        if (ret != 0) {
          break;
        }
        elems_read_in_dim[cur_dim]++;
      } else {
        ret = 1;
        break;
      }
    } else if (c == EOF) {
      ret = 1;
      break;
    } else if (first) {
      if (c == '[') {
        if (cur_dim == dims - 1) {
          ret = 1;
          break;
        }
        cur_dim++;
        elems_read_in_dim[cur_dim] = 0;
      } else {
        ungetc(c, stdin);
        ret = read_str_elem(reader);
        if (ret != 0) {
          break;
        }
        elems_read_in_dim[cur_dim]++;
        first = 0;
      }
    } else {
      ret = 1;
      break;
    }
  }

  free(knows_dimsize);
  free(elems_read_in_dim);
  return ret;
}

static int read_str_empty_array(const char *type_name, int64_t *shape, int64_t dims) {
  char c;
  if (scanf("empty") == EOF) {
    return 1;
  }

  c = getchar();
  if (c != '(') {
    return 1;
  }

  for (int i = 0; i < dims-1; i++) {
    c = getchar();
    if (c != '[') {
      return 1;
    }
    c = getchar();
    if (c != ']') {
      return 1;
    }
  }

  int n = strlen(type_name);
  for (int i = 0; i < n; i++) {
    c = getchar();
    if (c != type_name[i]) {
      return 1;
    }
  }

  if (getchar() != ')') {
    return 1;
  }

  for (int i = 0; i < dims; i++) {
    shape[i] = 0;
  }

  return 0;
}

static int read_str_array(int64_t elem_size, int (*elem_reader)(void*),
                      const char *type_name,
                      void **data, int64_t *shape, int64_t dims) {
  int ret;
  struct array_reader reader;
  int64_t read_dims = 0;
  while (1) {
    int c;
    skipspaces();
    c = getchar();
    if (c=='[') {
      read_dims++;
    } else {
      if (c != EOF) {
        ungetc(c, stdin);
      }
      break;
    }
  }

  if (read_dims == 0) {
    return read_str_empty_array(type_name, shape, dims);
  }

  if (read_dims != dims) {
    return 1;
  }

  reader.shape = shape;
  reader.n_elems_used = 0;
  reader.elem_size = elem_size;
  reader.n_elems_space = 16;
  reader.elems = (char*) realloc(*data, elem_size*reader.n_elems_space);
  reader.elem_reader = elem_reader;

  ret = read_str_array_elems(&reader, dims);

  *data = reader.elems;

  return ret;
}

static int read_str_int8(void* dest) {
  skipspaces();
  /* Some platforms (WINDOWS) does not support scanf %hhd or its
     cousin, %SCNi8.  Read into int first to avoid corrupting
     memory.

     https://gcc.gnu.org/bugzilla/show_bug.cgi?id=63417  */
  int x;
  if (scanf("%i", &x) == 1) {
    *(int8_t*)dest = x;
    scanf("i8");
    return next_is_not_constituent() ? 0 : 1;
  } else {
    return 1;
  }
}

static int read_str_int16(void* dest) {
  skipspaces();
  if (scanf("%"SCNi16, (int16_t*)dest) == 1) {
    scanf("i16");
    return next_is_not_constituent() ? 0 : 1;
  } else {
    return 1;
  }
}

static int read_str_int32(void* dest) {
  skipspaces();
  if (scanf("%"SCNi32, (int32_t*)dest) == 1) {
    scanf("i32");
    return next_is_not_constituent() ? 0 : 1;
  } else {
    return 1;
  }
}

static int read_str_int64(void* dest) {
  skipspaces();
  if (scanf("%"SCNi64, (int64_t*)dest) == 1) {
    scanf("i64");
    return next_is_not_constituent() ? 0 : 1;
  } else {
    return 1;
  }
}

static int read_str_float(void* dest) {
  skipspaces();
  if (scanf("%f", (float*)dest) == 1) {
    scanf("f32");
    return next_is_not_constituent() ? 0 : 1;
  } else {
    return 1;
  }
}

static int read_str_double(void* dest) {
  skipspaces();
  if (scanf("%lf", (double*)dest) == 1) {
    scanf("f64");
    return next_is_not_constituent() ? 0 : 1;
  } else {
    return 1;
  }
}

static int read_str_bool(void* dest) {
  /* This is a monstrous hack.  Maybe we should get a proper lexer in here. */
  char b[4];
  skipspaces();
  if (scanf("%4c", b) == 1) {
    if (strncmp(b, "true", 4) == 0) {
      *(char*)dest = 1;
      return 0;
    } else if (strncmp(b, "fals", 4) == 0 && getchar() == 'e') {
      *(char*)dest = 0;
      return 0;
    } else {
      return 1;
    }
  } else {
    return 1;
  }
}

// taken from http://esr.ibiblio.org/?p=5095
#define IS_BIG_ENDIAN (*(uint16_t *)"\0\xff" < 0x100)

#define READ_BINARY_VERSION 1

typedef struct {
  const char binname[4]; // used for parsing binary date
  const char* type_name; // used for printing
  const int size;
} primtype_info_t;

const primtype_info_t FUTHARK_PRIMTYPES[] = {
  {.binname = "  i8", .type_name = "i8",   .size = 1},
  {.binname = " i16", .type_name = "i16",  .size = 2},
  {.binname = " i32", .type_name = "i32",  .size = 4},
  {.binname = " i64", .type_name = "i64",  .size = 8},
  {.binname = " f32", .type_name = "f32",  .size = 4},
  {.binname = " f64", .type_name = "f64",  .size = 8},
  {.binname = "bool", .type_name = "bool", .size = 1},
};

// These indices should match up with the information above
typedef enum {
  FUTHARK_INT8 = 0,
  FUTHARK_INT16 = 1,
  FUTHARK_INT32 = 2,
  FUTHARK_INT64 = 3,
  FUTHARK_FLOAT32 = 4,
  FUTHARK_FLOAT64 = 5,
  FUTHARK_BOOL = 6,

  // Please add new types above this line -- we exploit that enums are just
  // ints, and use this value to loop through all types we know.
  FUTHARK_NUM_PRIMTYPES
} primtype_t;


////////////////////////////////////////////////////////////////////////////////
// Little endian
////////////////////////////////////////////////////////////////////////////////

static int read_byte(void* dest) {
  int num_elems_read = fread(dest, 1, 1, stdin);
  return num_elems_read == 1 ? 0 : 1;
}

static int read_le_2byte(void* dest) {
  int num_elems_read = fread(dest, 2, 1, stdin);
  return num_elems_read == 1 ? 0 : 1;
}

static int read_le_4byte(void* dest) {
  int num_elems_read = fread(dest, 4, 1, stdin);
  return num_elems_read == 1 ? 0 : 1;
}

static int read_le_8byte(void* dest) {
  int num_elems_read = fread(dest, 8, 1, stdin);
  return num_elems_read == 1 ? 0 : 1;
}

////////////////////////////////////////////////////////////////////////////////
// Big endian
////////////////////////////////////////////////////////////////////////////////

static int read_be_2byte(void* dest) {
  char* destc = (char*) dest;
  int num_matched = scanf("%c%c", destc+1, destc+0);
  return num_matched == 2 ? 0 : 1;
}

static int read_be_4byte(void* dest) {
  char* destc = (char*) dest;
  int num_matched = scanf("%c%c%c%c", destc+3, destc+2, destc+1, destc+0);
  return num_matched == 4 ? 0 : 1;
}

static int read_be_8byte(void* dest) {
  char* destc = (char*) dest;
  int num_matched = scanf("%c%c%c%c%c%c%c%c", destc+7, destc+6, destc+5,
                          destc+4, destc+3, destc+2, destc+1, destc+0);
  return num_matched == 8 ? 0 : 1;
}

////////////////////////////////////////////////////////////////////////////////
// General value interface
////////////////////////////////////////////////////////////////////////////////

static int read_is_binary() {
  skipspaces();
  int c = getchar();
  if (c == 'b') {
    int8_t bin_version;
    int ret = read_byte(&bin_version);

    if (ret != 0) { panic(1, "binary-input: could not read version.\n"); }

    if (bin_version != READ_BINARY_VERSION) {
      panic(1, "binary-input: File uses version %i, but I only understand version %i.\n",
            bin_version, READ_BINARY_VERSION);
    }

    return 1;
  }
  ungetc(c, stdin);
  return 0;
}

static primtype_t read_bin_read_type_enum() {
  char read_binname[4];

  int num_matched = scanf("%4c", read_binname);
  if (num_matched != 1) { panic(1, "binary-input: Couldn't read element type.\n"); }

  for (int i=0; i<FUTHARK_NUM_PRIMTYPES; i++) {
    // I compare the 4 characters manually instead of using strncmp because
    // this allows any value to be used, also NULL bytes
    if ( (read_binname[0] == FUTHARK_PRIMTYPES[i].binname[0]) &&
         (read_binname[1] == FUTHARK_PRIMTYPES[i].binname[1]) &&
         (read_binname[2] == FUTHARK_PRIMTYPES[i].binname[2]) &&
         (read_binname[3] == FUTHARK_PRIMTYPES[i].binname[3]) ) {
      return i;
    }
  }
  panic(1, "binary-input: Did not recognize the type '%s'.\n", read_binname);
}

static void read_bin_ensure_scalar(primtype_t expected_type) {
  int8_t bin_dims;
  int ret = read_byte(&bin_dims);
  if (ret != 0) { panic(1, "binary-input: Couldn't get dims.\n"); }

  if (bin_dims != 0) {
    panic(1, "binary-input: Expected scalar (0 dimensions), but got array with %i dimensions.\n",
          bin_dims);
  }

  primtype_t bin_type_enum = read_bin_read_type_enum();
  if (bin_type_enum != expected_type) {
    panic(1, "binary-input: Expected scalar of type %s but got scalar of type %s.\n",
          FUTHARK_PRIMTYPES[expected_type].type_name,
          FUTHARK_PRIMTYPES[bin_type_enum].type_name);
  }
}

static int read_int8(void* dest) {
  if (read_is_binary()) {
    read_bin_ensure_scalar(FUTHARK_INT8);
    return read_byte(dest);
  }
  return read_str_int8(dest);
}

static int read_int16(void* dest) {
  if (read_is_binary()) {
    read_bin_ensure_scalar(FUTHARK_INT16);
    if (IS_BIG_ENDIAN) {
      return read_be_2byte(dest);
    } else {
      return read_le_2byte(dest);
    }
  }
  return read_str_int16(dest);
}

static int read_int32(void* dest) {
  if (read_is_binary()) {
    read_bin_ensure_scalar(FUTHARK_INT32);
    if (IS_BIG_ENDIAN) {
      return read_be_4byte(dest);
    } else {
      return read_le_4byte(dest);
    }
  }
  return read_str_int32(dest);
}

static int read_int64(void* dest) {
  if (read_is_binary()) {
    read_bin_ensure_scalar(FUTHARK_INT64);
    if (IS_BIG_ENDIAN) {
      return read_be_8byte(dest);
    } else {
      return read_le_8byte(dest);
    }
  }
  return read_str_int64(dest);
}

static int read_float(void* dest) {
  if (read_is_binary()) {
    read_bin_ensure_scalar(FUTHARK_FLOAT32);
    if (IS_BIG_ENDIAN) {
      return read_be_4byte(dest);
    } else {
      return read_le_4byte(dest);
    }
  }
  return read_str_float(dest);
}

static int read_double(void* dest) {
  if (read_is_binary()) {
    read_bin_ensure_scalar(FUTHARK_FLOAT64);
    if (IS_BIG_ENDIAN) {
      return read_be_8byte(dest);
    } else {
      return read_le_8byte(dest);
    }
  }
  return read_str_double(dest);
}

static int read_bool(void* dest) {
  if (read_is_binary()) {
    read_bin_ensure_scalar(FUTHARK_BOOL);
    return read_byte(dest);
  }
  return read_str_bool(dest);
}

////////////////////////////////////////////////////////////////////////////////
// General array interface
////////////////////////////////////////////////////////////////////////////////

static int read_array(primtype_t expected_type, int64_t elem_size, int (*elem_reader)(void*),
                      const char *type_name, void **data, int64_t *shape, int64_t dims) {
  if (!read_is_binary()) {
    return read_str_array(elem_size, elem_reader, type_name, data, shape, dims);
  }

  // now we know it is binary :)
  int ret;

  int8_t bin_dims;
  ret = read_byte(&bin_dims);
  if (ret != 0) { panic(1, "binary-input: Couldn't get dims.\n"); }

  if (bin_dims != dims) {
    panic(1, "binary-input: Expected %i dimensions, but got array with %i dimensions.\n",
          dims, bin_dims);
  }

  primtype_t bin_type_enum = read_bin_read_type_enum();
  const primtype_info_t bin_primtype = FUTHARK_PRIMTYPES[bin_type_enum];
  if (expected_type != bin_type_enum) {
    panic(1, "binary-input: Expected %iD-array with element type '%s' but got %iD-array with element type '%s'.\n",
          dims, FUTHARK_PRIMTYPES[expected_type].type_name, dims, bin_primtype.type_name);
  }

  if (elem_size != bin_primtype.size) {
    panic(1, "binary-input: The RTS expected type %s to use %i bytes per element, but the call to `read_array` tells me to use %i bytes per element.\n",
          bin_primtype.type_name, bin_primtype.size, elem_size);
  }

  uint64_t elem_count = 1;
  for (int i=0; i<dims; i++) {
    uint64_t bin_shape;
    ret = IS_BIG_ENDIAN ? read_be_8byte(&bin_shape) : read_le_8byte(&bin_shape);
    if (ret != 0) { panic(1, "binary-input: Couldn't read size for dimension %i of array.\n", i); }
    elem_count *= bin_shape;
    shape[i] = (int64_t) bin_shape;
  }

  void* tmp = realloc(*data, elem_count * elem_size);
  if (tmp == NULL) {
    panic(1, "binary-input: Failed to allocate array of size %i.\n",
          elem_count * elem_size);
  }
  *data = tmp;

  size_t num_elems_read = fread(*data, elem_size, elem_count, stdin);
  if (num_elems_read != elem_count) {
    panic(1, "binary-input: tried to read %i elements of an array, but only got %i elements.\n",
          elem_count, num_elems_read);
  }

  // If we're on big endian platform we must change all multibyte elements
  // from using little endian to big endian
  if (IS_BIG_ENDIAN && elem_size != 1) {
    char* elems = (char*) *data;
    for (uint64_t i=0; i<elem_count; i++) {
      char* elem = elems+(i*elem_size);
      for (int j=0; j<elem_size/2; j++) {
        char head = elem[j];
        int tail_index = elem_size-1-j;
        elem[j] = elem[tail_index];
        elem[tail_index] = head;
      }
    }
  }

  return 0;
}

static FILE *runtime_file;
static int perform_warmup = 0;
static int num_runs = 1;
static const char *entry_point = "main";
int parse_options(int argc, char *const argv[])
{
    int ch;
    static struct option long_options[] = {{"write-runtime-to",
                                            required_argument, NULL, 1},
                                           {"runs", required_argument, NULL, 2},
                                           {"memory-reporting", no_argument,
                                            NULL, 3}, {"entry-point",
                                                       required_argument, NULL,
                                                       4}, {0, 0, 0, 0}};
    
    while ((ch = getopt_long(argc, argv, ":t:r:me:", long_options, NULL)) !=
           -1) {
        if (ch == 1 || ch == 't') {
            runtime_file = fopen(optarg, "w");
            if (runtime_file == NULL)
                panic(1, "Cannot open %s: %s\n", optarg, strerror(errno));
        }
        if (ch == 2 || ch == 'r') {
            num_runs = atoi(optarg);
            perform_warmup = 1;
            if (num_runs <= 0)
                panic(1, "Need a positive number of runs, not %s\n", optarg);
        }
        if (ch == 3 || ch == 'm')
            detail_memory = 1;
        if (ch == 4 || ch == 'e')
            entry_point = optarg;
        if (ch == ':')
            panic(-1, "Missing argument for option %s\n", argv[optind - 1]);
        if (ch == '?')
            panic(-1, "Unknown option %s\n", argv[optind - 1]);
    }
    return optind;
}
void entry_main()

{
    int64_t t_start, t_end;
    int time_runs;
    int32_t outer_loop_count_15648;
    int32_t numX_15649;
    int32_t numY_15650;
    int32_t numT_15651;
    float s0_15652;
    float _strike_15653;
    float t_15654;
    float alpha_15655;
    float nu_15656;
    float beta_15657;
    struct tuple_int32_t_mem_int32_t main_ret_17922;
    
    if (read_int32(&outer_loop_count_15648) != 0)
        panic(1, "Syntax error when reading %s.\n", "i32");
    if (read_int32(&numX_15649) != 0)
        panic(1, "Syntax error when reading %s.\n", "i32");
    if (read_int32(&numY_15650) != 0)
        panic(1, "Syntax error when reading %s.\n", "i32");
    if (read_int32(&numT_15651) != 0)
        panic(1, "Syntax error when reading %s.\n", "i32");
    if (read_float(&s0_15652) != 0)
        panic(1, "Syntax error when reading %s.\n", "f32");
    if (read_float(&_strike_15653) != 0)
        panic(1, "Syntax error when reading %s.\n", "f32");
    if (read_float(&t_15654) != 0)
        panic(1, "Syntax error when reading %s.\n", "f32");
    if (read_float(&alpha_15655) != 0)
        panic(1, "Syntax error when reading %s.\n", "f32");
    if (read_float(&nu_15656) != 0)
        panic(1, "Syntax error when reading %s.\n", "f32");
    if (read_float(&beta_15657) != 0)
        panic(1, "Syntax error when reading %s.\n", "f32");
    
    int32_t out_memsizze_17870;
    struct memblock out_mem_17869;
    
    out_mem_17869.references = NULL;
    
    int32_t out_arrsizze_17871;
    
    if (perform_warmup) {
        time_runs = 0;
        t_start = get_wall_time();
        main_ret_17922 = futhark_main(outer_loop_count_15648, numX_15649,
                                      numY_15650, numT_15651, s0_15652,
                                      _strike_15653, t_15654, alpha_15655,
                                      nu_15656, beta_15657);
        t_end = get_wall_time();
        
        long elapsed_usec = t_end - t_start;
        
        if (time_runs && runtime_file != NULL)
            fprintf(runtime_file, "%ld\n", elapsed_usec);
        memblock_unref(&main_ret_17922.elem_1);
    }
    time_runs = 1;
    /* Proper run. */
    for (int run = 0; run < num_runs; run++) {
        if (run == num_runs - 1)
            detail_timing = 1;
        t_start = get_wall_time();
        main_ret_17922 = futhark_main(outer_loop_count_15648, numX_15649,
                                      numY_15650, numT_15651, s0_15652,
                                      _strike_15653, t_15654, alpha_15655,
                                      nu_15656, beta_15657);
        t_end = get_wall_time();
        
        long elapsed_usec = t_end - t_start;
        
        if (time_runs && runtime_file != NULL)
            fprintf(runtime_file, "%ld\n", elapsed_usec);
        if (run < num_runs - 1) {
            memblock_unref(&main_ret_17922.elem_1);
        }
    }
    out_memsizze_17870 = main_ret_17922.elem_0;
    out_mem_17869 = main_ret_17922.elem_1;
    out_arrsizze_17871 = main_ret_17922.elem_2;
    if (out_arrsizze_17871 * 1 == 0)
        printf("empty(%s)", "f32");
    else {
        int print_i_17923;
        
        putchar('[');
        for (print_i_17923 = 0; print_i_17923 < out_arrsizze_17871;
             print_i_17923++) {
            float *print_elem_17924 = (float *) out_mem_17869.mem +
                  print_i_17923 * 1;
            
            fprintf(stdout, "%.6ff32", *print_elem_17924);
            if (print_i_17923 != out_arrsizze_17871 - 1)
                printf(", ");
        }
        putchar(']');
    }
    printf("\n");
    memblock_unref(&main_ret_17922.elem_1);
}
typedef void entry_point_fun();
struct entry_point_entry {
    const char *name;
    entry_point_fun *fun;
} ;
int main(int argc, char **argv)
{
    fut_progname = argv[0];
    
    struct entry_point_entry entry_points[] = {{.name ="main", .fun =
                                                entry_main}};
    int parsed_options = parse_options(argc, argv);
    
    argc -= parsed_options;
    argv += parsed_options;
    
    int num_entry_points = sizeof(entry_points) / sizeof(entry_points[0]);
    entry_point_fun *entry_point_fun = NULL;
    
    for (int i = 0; i < num_entry_points; i++) {
        if (strcmp(entry_points[i].name, entry_point) == 0) {
            entry_point_fun = entry_points[i].fun;
            break;
        }
    }
    if (entry_point_fun == NULL) {
        fprintf(stderr,
                "No entry point '%s'.  Select another with --entry-point.  Options are:\n",
                entry_point);
        for (int i = 0; i < num_entry_points; i++)
            fprintf(stderr, "%s\n", entry_points[i].name);
        return 1;
    }
    entry_point_fun();
    if (runtime_file != NULL)
        fclose(runtime_file);
    if (detail_memory) {
        fprintf(stderr, "Peak memory usage for default space: %ld bytes.\n",
                peak_mem_usage_default);
    }
    return 0;
}

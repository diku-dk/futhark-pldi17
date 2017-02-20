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
struct tuple_int32_t_mem_int32_t_int32_t_int32_t {
    int32_t elem_0;
    struct memblock elem_1;
    int32_t elem_2;
    int32_t elem_3;
    int32_t elem_4;
} ;
static struct tuple_int32_t_mem_int32_t_int32_t_int32_t
futhark_main(int32_t points_mem_sizze_1683, struct memblock points_mem_1684,
             int32_t n_1336, int32_t d_1337, int32_t threshold_1338,
             int32_t k_1339, int32_t max_iterations_1340);
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
struct tuple_int32_t_mem_int32_t_int32_t_int32_t futhark_main(int32_t points_mem_sizze_1683,
                                                              struct memblock points_mem_1684,
                                                              int32_t n_1336,
                                                              int32_t d_1337,
                                                              int32_t threshold_1338,
                                                              int32_t k_1339,
                                                              int32_t max_iterations_1340)
{
    int32_t out_memsizze_1731;
    struct memblock out_mem_1730;
    
    out_mem_1730.references = NULL;
    
    int32_t out_arrsizze_1732;
    int32_t out_arrsizze_1733;
    int32_t scalar_out_1734;
    int32_t binop_x_1686 = 4 * k_1339;
    int32_t bytes_1685 = binop_x_1686 * d_1337;
    struct memblock mem_1687;
    
    mem_1687.references = NULL;
    memblock_alloc(&mem_1687, bytes_1685);
    for (int32_t i_1586 = 0; i_1586 < k_1339; i_1586++) {
        for (int32_t i_1736 = 0; i_1736 < d_1337; i_1736++) {
            *(float *) &mem_1687.mem[(i_1586 * d_1337 + i_1736) * 4] =
                *(float *) &points_mem_1684.mem[(i_1586 * d_1337 + i_1736) * 4];
        }
    }
    
    int32_t bytes_1689 = 4 * n_1336;
    struct memblock mem_1690;
    
    mem_1690.references = NULL;
    memblock_alloc(&mem_1690, bytes_1689);
    for (int32_t i_1590 = 0; i_1590 < n_1336; i_1590++) {
        int32_t res_1349 = smod32(i_1590, k_1339);
        
        *(int32_t *) &mem_1690.mem[i_1590 * 4] = res_1349;
    }
    
    char res_1350 = slt32(0, max_iterations_1340);
    char y_1352 = slt32(0, k_1339);
    char bounds_check_1353;
    
    if (!y_1352) {
        fprintf(stderr, "Assertion %s at %s failed.\n", "y_1352",
                "./kmeans.fut:24:62-24:62");
        abort();
    }
    
    int32_t bytes_1695 = bytes_1689 * k_1339;
    struct memblock mem_1697;
    
    mem_1697.references = NULL;
    memblock_alloc(&mem_1697, bytes_1695);
    
    struct memblock mem_1701;
    
    mem_1701.references = NULL;
    memblock_alloc(&mem_1701, binop_x_1686);
    
    struct memblock mem_1704;
    
    mem_1704.references = NULL;
    memblock_alloc(&mem_1704, binop_x_1686);
    
    int32_t bytes_1705 = bytes_1695 * d_1337;
    struct memblock mem_1708;
    
    mem_1708.references = NULL;
    memblock_alloc(&mem_1708, bytes_1705);
    
    struct memblock mem_1711;
    
    mem_1711.references = NULL;
    memblock_alloc(&mem_1711, bytes_1685);
    
    int32_t bytes_1712 = 4 * d_1337;
    struct memblock mem_1713;
    
    mem_1713.references = NULL;
    memblock_alloc(&mem_1713, bytes_1712);
    
    struct memblock mem_1720;
    
    mem_1720.references = NULL;
    memblock_alloc(&mem_1720, bytes_1712);
    
    struct memblock double_buffer_mem_1726;
    
    double_buffer_mem_1726.references = NULL;
    memblock_alloc(&double_buffer_mem_1726, bytes_1689);
    
    struct memblock double_buffer_mem_1727;
    
    double_buffer_mem_1727.references = NULL;
    memblock_alloc(&double_buffer_mem_1727, bytes_1685);
    
    struct memblock mem_1699;
    
    mem_1699.references = NULL;
    memblock_alloc(&mem_1699, bytes_1689);
    
    struct memblock mem_1718;
    
    mem_1718.references = NULL;
    memblock_alloc(&mem_1718, bytes_1685);
    
    struct memblock membership_mem_1723;
    
    membership_mem_1723.references = NULL;
    
    struct memblock cluster_centres_mem_1725;
    
    cluster_centres_mem_1725.references = NULL;
    
    char nameless_1354;
    int32_t i_1357;
    struct memblock membership_mem_1692;
    
    membership_mem_1692.references = NULL;
    
    int32_t i_1361;
    struct memblock cluster_centres_mem_1694;
    
    cluster_centres_mem_1694.references = NULL;
    
    char loop_while_1358;
    
    memblock_set(&membership_mem_1692, &mem_1690);
    memblock_set(&cluster_centres_mem_1694, &mem_1687);
    loop_while_1358 = res_1350;
    i_1361 = 0;
    while (loop_while_1358) {
        for (int32_t i_1614 = 0; i_1614 < n_1336; i_1614++) {
            float res_1469;
            float acc_1597 = 0.0F;
            
            for (int32_t i_1596 = 0; i_1596 < d_1337; i_1596++) {
                float binop_param_x_1474 =
                      *(float *) &points_mem_1684.mem[(i_1614 * d_1337 +
                                                       i_1596) * 4];
                float binop_param_y_1475 =
                      *(float *) &cluster_centres_mem_1694.mem[i_1596 * 4];
                float res_1476 = binop_param_x_1474 - binop_param_y_1475;
                float res_1477 = fpow32(res_1476, 2.0F);
                float res_1478 = acc_1597 + res_1477;
                float acc_tmp_1746 = res_1478;
                
                acc_1597 = acc_tmp_1746;
            }
            res_1469 = acc_1597;
            
            int32_t res_1480;
            float res_1481;
            int32_t acc_1609;
            float acc_1610;
            
            acc_1609 = 0;
            acc_1610 = res_1469;
            for (int32_t i_1608 = 0; i_1608 < k_1339; i_1608++) {
                float res_1500;
                float acc_1603 = 0.0F;
                
                for (int32_t i_1602 = 0; i_1602 < d_1337; i_1602++) {
                    float binop_param_x_1505 =
                          *(float *) &points_mem_1684.mem[(i_1614 * d_1337 +
                                                           i_1602) * 4];
                    float binop_param_y_1506 =
                          *(float *) &cluster_centres_mem_1694.mem[(i_1608 *
                                                                    d_1337 +
                                                                    i_1602) *
                                                                   4];
                    float res_1507 = binop_param_x_1505 - binop_param_y_1506;
                    float res_1508 = fpow32(res_1507, 2.0F);
                    float res_1509 = acc_1603 + res_1508;
                    float acc_tmp_1749 = res_1509;
                    
                    acc_1603 = acc_tmp_1749;
                }
                res_1500 = acc_1603;
                
                char cond_1511 = acc_1610 < res_1500;
                int32_t res_1512;
                float res_1513;
                
                if (cond_1511) {
                    res_1512 = acc_1609;
                    res_1513 = acc_1610;
                } else {
                    res_1512 = i_1608;
                    res_1513 = res_1500;
                }
                
                int32_t acc_tmp_1747 = res_1512;
                float acc_tmp_1748;
                
                acc_tmp_1748 = res_1513;
                acc_1609 = acc_tmp_1747;
                acc_1610 = acc_tmp_1748;
            }
            res_1480 = acc_1609;
            res_1481 = acc_1610;
            for (int32_t i_1750 = 0; i_1750 < k_1339; i_1750++) {
                *(int32_t *) &mem_1701.mem[i_1750 * 4] = 0;
            }
            
            char x_1517 = sle32(0, res_1480);
            char y_1518 = slt32(res_1480, k_1339);
            char assert_arg_1519 = x_1517 && y_1518;
            char bounds_check_1520;
            
            if (!assert_arg_1519) {
                fprintf(stderr, "Assertion %s at %s failed.\n",
                        "assert_arg_1519", "./kmeans.fut:34:36-34:36");
                abort();
            }
            *(int32_t *) &mem_1701.mem[res_1480 * 4] = 1;
            for (int32_t i_1751 = 0; i_1751 < k_1339; i_1751++) {
                *(int32_t *) &mem_1697.mem[(i_1614 * k_1339 + i_1751) * 4] =
                    *(int32_t *) &mem_1701.mem[i_1751 * 4];
            }
            *(int32_t *) &mem_1699.mem[i_1614 * 4] = res_1480;
        }
        for (int32_t i_1627 = 0; i_1627 < k_1339; i_1627++) {
            int32_t res_1527;
            int32_t acc_1623 = 0;
            
            for (int32_t i_1622 = 0; i_1622 < n_1336; i_1622++) {
                int32_t binop_param_y_1529 =
                        *(int32_t *) &mem_1697.mem[(i_1622 * k_1339 + i_1627) *
                                                   4];
                int32_t res_1530 = acc_1623 + binop_param_y_1529;
                int32_t acc_tmp_1753 = res_1530;
                
                acc_1623 = acc_tmp_1753;
            }
            res_1527 = acc_1623;
            *(int32_t *) &mem_1704.mem[i_1627 * 4] = res_1527;
        }
        for (int32_t i_1636 = 0; i_1636 < n_1336; i_1636++) {
            int32_t c_1533 = *(int32_t *) &mem_1699.mem[i_1636 * 4];
            
            for (int32_t i_1755 = 0; i_1755 < k_1339; i_1755++) {
                for (int32_t i_1756 = 0; i_1756 < d_1337; i_1756++) {
                    *(float *) &mem_1711.mem[(i_1755 * d_1337 + i_1756) * 4] =
                        0.0F;
                }
            }
            
            int32_t tofloat_arg_1535 = *(int32_t *) &mem_1704.mem[c_1533 * 4];
            float y_1536 = sitofp_i32_f32(tofloat_arg_1535);
            
            for (int32_t i_1632 = 0; i_1632 < d_1337; i_1632++) {
                float binop_param_noncurried_1538 =
                      *(float *) &points_mem_1684.mem[(i_1636 * d_1337 +
                                                       i_1632) * 4];
                float res_1539 = binop_param_noncurried_1538 / y_1536;
                
                *(float *) &mem_1713.mem[i_1632 * 4] = res_1539;
            }
            for (int32_t i_1758 = 0; i_1758 < d_1337; i_1758++) {
                *(float *) &mem_1711.mem[(c_1533 * d_1337 + i_1758) * 4] =
                    *(float *) &mem_1713.mem[i_1758 * 4];
            }
            for (int32_t i_1759 = 0; i_1759 < k_1339; i_1759++) {
                for (int32_t i_1760 = 0; i_1760 < d_1337; i_1760++) {
                    *(float *) &mem_1708.mem[(i_1636 * (k_1339 * d_1337) +
                                              i_1759 * d_1337 + i_1760) * 4] =
                        *(float *) &mem_1711.mem[(i_1759 * d_1337 + i_1760) *
                                                 4];
                }
            }
        }
        for (int32_t i_1651 = 0; i_1651 < k_1339; i_1651++) {
            for (int32_t i_1646 = 0; i_1646 < d_1337; i_1646++) {
                float res_1546;
                float acc_1642 = 0.0F;
                
                for (int32_t i_1641 = 0; i_1641 < n_1336; i_1641++) {
                    float binop_param_y_1548 =
                          *(float *) &mem_1708.mem[(i_1641 * (k_1339 * d_1337) +
                                                    i_1651 * d_1337 + i_1646) *
                                                   4];
                    float res_1549 = acc_1642 + binop_param_y_1548;
                    float acc_tmp_1763 = res_1549;
                    
                    acc_1642 = acc_tmp_1763;
                }
                res_1546 = acc_1642;
                *(float *) &mem_1720.mem[i_1646 * 4] = res_1546;
            }
            for (int32_t i_1764 = 0; i_1764 < d_1337; i_1764++) {
                *(float *) &mem_1718.mem[(i_1651 * d_1337 + i_1764) * 4] =
                    *(float *) &mem_1720.mem[i_1764 * 4];
            }
        }
        
        int32_t res_1557;
        int32_t acc_1659 = 0;
        
        for (int32_t i_1658 = 0; i_1658 < n_1336; i_1658++) {
            int32_t binop_param_y_1562 = *(int32_t *) &mem_1699.mem[i_1658 * 4];
            int32_t binop_param_x_1563 =
                    *(int32_t *) &membership_mem_1692.mem[i_1658 * 4];
            char res_1564 = binop_param_x_1563 == binop_param_y_1562;
            int32_t res_1565;
            
            if (res_1564) {
                res_1565 = 0;
            } else {
                res_1565 = 1;
            }
            
            int32_t res_1566 = acc_1659 + res_1565;
            int32_t acc_tmp_1765 = res_1566;
            
            acc_1659 = acc_tmp_1765;
        }
        res_1557 = acc_1659;
        
        int32_t res_1568 = i_1361 + 1;
        char cond_1569 = slt32(threshold_1338, res_1557);
        char loop_cond_1570;
        
        if (cond_1569) {
            char res_1571 = slt32(res_1568, max_iterations_1340);
            
            loop_cond_1570 = res_1571;
        } else {
            loop_cond_1570 = 0;
        }
        memmove(double_buffer_mem_1726.mem + 0, mem_1699.mem + 0, n_1336 *
                sizeof(int32_t));
        memmove(double_buffer_mem_1727.mem + 0, mem_1718.mem + 0, k_1339 *
                d_1337 * sizeof(float));
        
        struct memblock membership_mem_tmp_1738;
        
        membership_mem_tmp_1738.references = NULL;
        memblock_set(&membership_mem_tmp_1738, &double_buffer_mem_1726);
        
        struct memblock cluster_centres_mem_tmp_1739;
        
        cluster_centres_mem_tmp_1739.references = NULL;
        memblock_set(&cluster_centres_mem_tmp_1739, &double_buffer_mem_1727);
        
        char loop_while_tmp_1740 = loop_cond_1570;
        int32_t i_tmp_1743;
        
        i_tmp_1743 = res_1568;
        memblock_set(&membership_mem_1692, &membership_mem_tmp_1738);
        memblock_set(&cluster_centres_mem_1694, &cluster_centres_mem_tmp_1739);
        loop_while_1358 = loop_while_tmp_1740;
        i_1361 = i_tmp_1743;
        memblock_unref(&membership_mem_tmp_1738);
        memblock_unref(&cluster_centres_mem_tmp_1739);
    }
    nameless_1354 = loop_while_1358;
    memblock_set(&membership_mem_1723, &membership_mem_1692);
    memblock_set(&cluster_centres_mem_1725, &cluster_centres_mem_1694);
    i_1357 = i_1361;
    memblock_set(&out_mem_1730, &cluster_centres_mem_1725);
    out_arrsizze_1732 = k_1339;
    out_arrsizze_1733 = d_1337;
    out_memsizze_1731 = bytes_1685;
    scalar_out_1734 = i_1357;
    
    struct tuple_int32_t_mem_int32_t_int32_t_int32_t retval_1766;
    
    retval_1766.elem_0 = out_memsizze_1731;
    retval_1766.elem_1.references = NULL;
    memblock_set(&retval_1766.elem_1, &out_mem_1730);
    retval_1766.elem_2 = out_arrsizze_1732;
    retval_1766.elem_3 = out_arrsizze_1733;
    retval_1766.elem_4 = scalar_out_1734;
    memblock_unref(&out_mem_1730);
    memblock_unref(&mem_1687);
    memblock_unref(&mem_1690);
    memblock_unref(&mem_1697);
    memblock_unref(&mem_1701);
    memblock_unref(&mem_1704);
    memblock_unref(&mem_1708);
    memblock_unref(&mem_1711);
    memblock_unref(&mem_1713);
    memblock_unref(&mem_1720);
    memblock_unref(&double_buffer_mem_1726);
    memblock_unref(&double_buffer_mem_1727);
    memblock_unref(&mem_1699);
    memblock_unref(&mem_1718);
    memblock_unref(&membership_mem_1723);
    memblock_unref(&cluster_centres_mem_1725);
    memblock_unref(&membership_mem_1692);
    memblock_unref(&cluster_centres_mem_1694);
    return retval_1766;
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
    int32_t points_mem_sizze_1683;
    struct memblock points_mem_1684;
    
    points_mem_1684.references = NULL;
    memblock_alloc(&points_mem_1684, 0);
    
    int32_t n_1336;
    int32_t d_1337;
    int32_t threshold_1338;
    int32_t k_1339;
    int32_t max_iterations_1340;
    struct tuple_int32_t_mem_int32_t_int32_t_int32_t main_ret_1767;
    
    if (read_int32(&threshold_1338) != 0)
        panic(1, "Syntax error when reading %s.\n", "i32");
    if (read_int32(&k_1339) != 0)
        panic(1, "Syntax error when reading %s.\n", "i32");
    if (read_int32(&max_iterations_1340) != 0)
        panic(1, "Syntax error when reading %s.\n", "i32");
    {
        int64_t shape[2];
        
        if (read_array(FUTHARK_FLOAT32, sizeof(float), read_str_float, "f32",
                       (void **) &points_mem_1684.mem, shape, 2) != 0)
            panic(1, "Syntax error when reading %s.\n", "[][]f32");
        n_1336 = shape[0];
        d_1337 = shape[1];
        points_mem_sizze_1683 = sizeof(float) * shape[0] * shape[1];
        points_mem_1684.size = points_mem_sizze_1683;
    }
    
    int32_t out_memsizze_1731;
    struct memblock out_mem_1730;
    
    out_mem_1730.references = NULL;
    
    int32_t out_arrsizze_1732;
    int32_t out_arrsizze_1733;
    int32_t scalar_out_1734;
    
    if (perform_warmup) {
        time_runs = 0;
        t_start = get_wall_time();
        main_ret_1767 = futhark_main(points_mem_sizze_1683, points_mem_1684,
                                     n_1336, d_1337, threshold_1338, k_1339,
                                     max_iterations_1340);
        t_end = get_wall_time();
        
        long elapsed_usec = t_end - t_start;
        
        if (time_runs && runtime_file != NULL)
            fprintf(runtime_file, "%ld\n", elapsed_usec);
        memblock_unref(&main_ret_1767.elem_1);
    }
    time_runs = 1;
    /* Proper run. */
    for (int run = 0; run < num_runs; run++) {
        if (run == num_runs - 1)
            detail_timing = 1;
        t_start = get_wall_time();
        main_ret_1767 = futhark_main(points_mem_sizze_1683, points_mem_1684,
                                     n_1336, d_1337, threshold_1338, k_1339,
                                     max_iterations_1340);
        t_end = get_wall_time();
        
        long elapsed_usec = t_end - t_start;
        
        if (time_runs && runtime_file != NULL)
            fprintf(runtime_file, "%ld\n", elapsed_usec);
        if (run < num_runs - 1) {
            memblock_unref(&main_ret_1767.elem_1);
        }
    }
    memblock_unref(&points_mem_1684);
    out_memsizze_1731 = main_ret_1767.elem_0;
    out_mem_1730 = main_ret_1767.elem_1;
    out_arrsizze_1732 = main_ret_1767.elem_2;
    out_arrsizze_1733 = main_ret_1767.elem_3;
    scalar_out_1734 = main_ret_1767.elem_4;
    if (out_arrsizze_1732 * out_arrsizze_1733 == 0)
        printf("empty(%s)", "[]f32");
    else {
        int print_i_1768;
        
        putchar('[');
        for (print_i_1768 = 0; print_i_1768 < out_arrsizze_1732;
             print_i_1768++) {
            float *print_elem_1769 = (float *) out_mem_1730.mem + print_i_1768 *
                  out_arrsizze_1733;
            
            if (out_arrsizze_1733 * 1 == 0)
                printf("empty(%s)", "f32");
            else {
                int print_i_1770;
                
                putchar('[');
                for (print_i_1770 = 0; print_i_1770 < out_arrsizze_1733;
                     print_i_1770++) {
                    float *print_elem_1771 = (float *) print_elem_1769 +
                          print_i_1770 * 1;
                    
                    fprintf(stdout, "%.6ff32", *print_elem_1771);
                    if (print_i_1770 != out_arrsizze_1733 - 1)
                        printf(", ");
                }
                putchar(']');
            }
            if (print_i_1768 != out_arrsizze_1732 - 1)
                printf(", ");
        }
        putchar(']');
    }
    printf("\n");
    fprintf(stdout, "%di32", scalar_out_1734);
    printf("\n");
    memblock_unref(&main_ret_1767.elem_1);
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

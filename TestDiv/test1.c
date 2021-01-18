#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>

typedef struct div_info_s div_info_t;
struct div_info_s {
	uint32_t magic;
	size_t d;
};

void div_init(div_info_t *div_info, size_t divisor);
size_t div_compute(div_info_t *div_info, size_t n);

static uint64_t MAX = ((uint64_t)(1) << 32) - 1;
int  main(int argc, char **argv){

    srand(1);
    struct timespec tt1, tt2;
    div_info_t DIV;
    u_int64_t divisor=rand();
    u_int64_t ans;
    u_int64_t num;
    div_init(&DIV, divisor) ;

    srand(1);

    clock_gettime(CLOCK_MONOTONIC, &tt1);
    for(u_int64_t i=1 ; i< 10000 ;i++){
        num=rand();
        ans= num / divisor;
    }
    clock_gettime(CLOCK_MONOTONIC, &tt2);
    long long time1 = (long long) (tt2.tv_sec * 1e9 + tt2.tv_nsec) - (long long) (tt1.tv_sec * 1e9 + tt1.tv_nsec);

    srand(1);
    clock_gettime(CLOCK_MONOTONIC, &tt1);
    for(u_int64_t i=1 ; i< 10000 ;i++){
        num =rand();
        ans = div_compute(&DIV, num);
    }
    clock_gettime(CLOCK_MONOTONIC, &tt2);
    long long time2 = (long long) (tt2.tv_sec * 1e9 + tt2.tv_nsec) -(long long) (tt1.tv_sec * 1e9 + tt1.tv_nsec);
    printf("div: %lld\n",  time1 );
    printf("quick div: %lld\n",  time2 );
    
    return 0;
}
void div_init(div_info_t *div_info, size_t divisor) {
	
    // divisor can not be zero
	//assert(divisor != 0);
	/*
	 * This would make the value of magic too high to fit into a uint32_t
	 * (we would want magic = 2^32 exactly). This would mess with code gen
	 * on 32-bit machines.
	 */
	//assert(divisor!= 1);
    

    // 2^k
	uint64_t two_to_k = ((uint64_t)1 << 32);
	uint32_t magic = (uint32_t)(two_to_k / divisor);
    
	/*
	 * We want magic = ceil(2^k / d), but C gives us floor. We have to
	 * increment it unless the result was exact (i.e. unless d is a power of
	 * two).
	 */
	if (two_to_k % divisor != 0) {
		magic++;
	}
    
	div_info->magic = magic;
	div_info->d = divisor;
    
}
size_t div_compute(div_info_t *div_info, size_t n) {
	//assert(n <= (uint32_t)-1);
	/*
	 * This generates, e.g. mov; imul; shr on x86-64. On a 32-bit machine,
	 * the compilers I tried were all smart enough to turn this into the
	 * appropriate "get the high 32 bits of the result of a multiply" (e.g.
	 * mul; mov edx eax; on x86, umull on arm, etc.).
	 */
	size_t i = ((uint64_t)n * (uint64_t)div_info->magic) >> 32;
    //assert(i * div_info->d == n);
	return i;
}

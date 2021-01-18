#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct div_info_s div_info_t;
struct div_info_s {
	uint32_t magic;
	size_t d;
};

void div_init(div_info_t *div_info, size_t divisor);
static inline size_t div_compute(div_info_t *div_info, size_t n);

int  main(int argc, char **argv){

    div_info_t *test=malloc(sizeof(div_info_t));
    div_init(test,7);
    int queotient=div_compute(test,22);
    printf("%d\n",queotient);
    return 0;
}

void div_init(div_info_t *div_info, size_t divisor) {
	
    // divisor can not be zero
	assert(divisor != 0);
	/*
	 * This would make the value of magic too high to fit into a uint32_t
	 * (we would want magic = 2^32 exactly). This would mess with code gen
	 * on 32-bit machines.
	 */
	assert(divisor!= 1);
    

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
static inline size_t div_compute(div_info_t *div_info, size_t n) {
	assert(n <= (uint32_t)-1);
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
 
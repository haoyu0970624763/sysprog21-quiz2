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
int main()
{
    struct timespec t1, t2;
    long long time1[5000];
    long long time2[5000];
    long long total1=0,total2=0;
    long long avg_time1;
    long long avg_time2;


    for (uint64_t i = 2; i <= 5001; i++) {

        uint64_t num = rand() % MAX;
        uint64_t divisor = rand();

        
        div_info_t DIV;
        div_init(&DIV, divisor); 
        
        clock_gettime(CLOCK_MONOTONIC, &t1);
        size_t ans1 = div_compute(&DIV, num);
        clock_gettime(CLOCK_MONOTONIC, &t2);

        time1[i-2] = (long long) (t2.tv_sec * 1e9 + t2.tv_nsec) - (long long) (t1.tv_sec * 1e9 + t1.tv_nsec);
                          
        clock_gettime(CLOCK_MONOTONIC, &t1);
        size_t ans2 = num / divisor;
        clock_gettime(CLOCK_MONOTONIC, &t2);

        time2[i-2] = (long long) (t2.tv_sec * 1e9 + t2.tv_nsec) - (long long) (t1.tv_sec * 1e9 + t1.tv_nsec);

    }   
    for (uint64_t i = 0; i < 5000; i++)
    {
        total1 += time1[i];
        total2 += time2[i];
    }
    avg_time1 =total1/5000;
    avg_time2=total2/5000;

    printf("average time for quick div is %lld ns\n",avg_time1);
    printf("average time for div is %lld ns\n",avg_time2);
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

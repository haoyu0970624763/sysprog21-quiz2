#include <stdio.h>
#include <stdlib.h>

int singleNumber(int *nums, int numsSize)
{
    int apprear1 = 0, apprear2 = 0, apprear3 = 0;
    int tmp1=0,tmp2=0;
    for(int i=0;i<numsSize;i++) {

        apprear1 = (~(apprear2 | apprear1) & nums[i]) | apprear1 & ~nums[i] | apprear3 & nums[i];
        apprear2 = tmp1 & nums[i] | tmp2 & ~nums[i];
        apprear3 = tmp2 & nums[i] | apprear3 & ~nums[i];
        tmp1 = apprear1;
        tmp2 = apprear2;
    }
    return apprear1;
}

void main()
{
    int nums_3[] = {1,1,1,5,7,7,7};
    printf("%d\n", singleNumber(nums_3, 7)); 
}
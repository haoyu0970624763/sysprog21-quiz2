#include <stdio.h>
#include <stdlib.h>

int singleNumber(int *nums, int numsSize)
{
    int appear1 = 0, appear2 = 0, appear3 = 0;
    int tmp1=0,tmp2=0,tmp3=0;
    for(int i=0;i<numsSize;i++) {
        appear1 = (~(tmp2 | tmp1) & nums[i]) | tmp1 & ~nums[i] | tmp3 & nums[i];
        appear2 = tmp1 & nums[i] | tmp2 & ~nums[i];
        appear3 = tmp2 & nums[i] | appear3 & ~nums[i];
        tmp1 = appear1;
        tmp2 = appear2;
        tmp3 =appear3;
    }
    return appear1;

}

void main()
{
    int nums_3[] = {1,1,1,5,7,7,7};
    printf("%d\n", singleNumber(nums_3, 7)); 
}
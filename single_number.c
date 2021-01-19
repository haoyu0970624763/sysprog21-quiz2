#include <stdio.h>
#include <stdlib.h>

int singleNumber(int *nums, int numsSize)
{
    int last1 = 0, last2 = 0, output = 0;
    for(int i=0;i<numsSize;i++) {
        output = (nums[i] & ~(last1 | last2)) | (~nums[i] & last1);
        last2 = last1 & nums[i] | last2 & ~nums[i];
        last1 = output & nums[i] | last1 & ~nums[i];
    }
    return output;
} 

void main()
{
    int nums_3[] = {1,1,1,2,3,3,3};
    printf("%d\n", singleNumber(nums_3, 7)); 
}
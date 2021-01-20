#include <stdio.h>
#include <stdlib.h>

int singleNumber(int *nums,int repeatSize,int numsSize)
{
    int appear[repeatSize];
    int tmp[repeatSize];
    int tmpResult=0;

    for(int i=0;i<repeatSize;i++){
        appear[i]=0;
        tmp[i]=0;
    }

    for(int i=0;i<numsSize;i++) {

        for(int j=0 ; j < repeatSize-1 ; j++){
            tmpResult = tmpResult | tmp[j];
        }

        appear[0] = ( (~tmpResult) & nums[i]) | tmp[0] & ~nums[i] | tmp[repeatSize-1] & nums[i] ;

        for(int j=1 ; j < repeatSize ; j++){
            appear[j] = tmp[j-1] & nums[i] | tmp[j] & ~nums[i];
        }
        
        for(int j=0 ; j < repeatSize ; j++){
            tmp[j] = appear[j];
        }
    }
    return appear[0];

}

void main()
{
    int nums_3[] = {1,1,1,5,7,7,7};
    int nums_4[] = {2,2,4,2,2,8,8,8,8};
    printf("%d\n", singleNumber(nums_3, 3,7)); 
    printf("%d\n", singleNumber(nums_4, 4,9)); 
}

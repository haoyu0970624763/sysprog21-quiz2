#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>




int  main(){

    srand(1);
    int divisor=rand();
    int ans;
    int num;
    
    srand(1);
	
    for(int  i=1 ; i< 100000000 ;i++){
        num=rand();
        ans= num / divisor;
    }
	
    
    return 0;
}

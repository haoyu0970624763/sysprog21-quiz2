#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint64_t HexToDigit(char* in) {

    char *tmp_ptr=in;
    char *reverse;
    uint64_t payload = 0, value = 0;
    if (in[0] == '0' && in[1] == 'x')
        tmp_ptr=&in[2];

    memset(reverse,'\0',strlen(tmp_ptr)+1);
    // To fix the difference of the endian
    for (int i = 0; i < strlen(tmp_ptr); i++)
    {
        reverse[i]=tmp_ptr[strlen(tmp_ptr)-1-i];
    }
    memcpy(&payload, reverse , sizeof(char)*strlen(tmp_ptr));
    
    uint64_t letter = payload & 0x4040404040404040;
    uint64_t shift = (letter >> 3) | (letter >> 6);
    uint64_t tmp=(payload + shift) & 0x0F0F0F0F0F0F0F0F;
    int i=strlen(tmp_ptr);
    
    for( int i=strlen(tmp_ptr); i!=0 ; i--){
        value= value << 4;        
        value |= ((tmp >> (i-1)*8) & 0x0F);
    }
    return value;
}

int main()
{
    printf("%ld\n", HexToDigit("0x12"));
    return 0;
}
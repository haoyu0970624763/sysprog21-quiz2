#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define PACKED_BYTE(b) (((uint64_t)(b) & (0xff)) * 0x0101010101010101u)

bool is_alphabet(const char str[], size_t size)
{
    if (size == 0)
        return false;
    int i = 0;
    while ((i + 8) <= size) {
        uint64_t payload;
        memcpy(&payload, str + i, 8); 
        uint64_t A = payload + PACKED_BYTE(128 - 'A' );  
        uint64_t Z = payload + PACKED_BYTE(128 - 'Z' - 1); 
        uint64_t a = payload + PACKED_BYTE(128 - 'a' );  
        uint64_t z = payload + PACKED_BYTE(128 - 'z' - 1); 
        uint64_t lowerMask = (a ^ z) & PACKED_BYTE(0x80);
        uint64_t upperMask = (A ^ Z) & PACKED_BYTE(0x80);        
        if (( lowerMask | upperMask ) ^ PACKED_BYTE(0x80)){
            return false;
        }   
        i += 8;
    }   
    while (i < size) {
        if ( (str[i] < 65 || (str[i] > 90 && str[i] < 97) || str[i] > 122))
            return false;
        i++;
    }   
    return true;
}

int main() {
    char t[] = {"avdkjfkl"};
    char s[] = {"Abdsk."};

    if (is_alphabet(t, strlen(t)))
        printf("TRUE\n");
    else{
        printf("FALSE\n");
    }
    if (is_alphabet(s, strlen(s)))
        printf("TRUE\n");
    else
    {
        printf("FALSE\n");
    }
    
    return 0;
}

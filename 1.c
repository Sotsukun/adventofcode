#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "common.h"

static uint8_t *str = 0;
static uint16_t counter = 0;

bool endOfString() {
    return str[counter] == 0;
}

void nextChar()
{
    counter++;
}


uint8_t readInt() {
    uint8_t result = 0;
    if (str[counter] != 0) {
        result = charToInt(str[counter]);
    }
    
    return result;
}

uint8_t readNext() {
    uint8_t result = 0;
    if (str[counter+1] != 0) {
        result = charToInt(str[counter+1]);
    }
    else {
        result = charToInt(str[0]);
    }
    
    return result;
}

uint8_t readHalfway() {
    uint16_t len = strlen(str);
    
    return charToInt(str[(counter+len/2)%len]);
}

int main(int argc, char *argv[]) 
{
    uint16_t result1 = 0;
    uint16_t result2 = 0;
    
    str = (uint8_t*)argv[1];
    
    while(!endOfString())
    {
        if(readInt() == readNext()) {
            result1 += readInt();
        }
        
        if(readInt() == readHalfway()) {
            result2 += readInt();
        }
        
        nextChar();
    }
    
    printf("%d\r\n", result1);
    printf("%d\r\n", result2);
}

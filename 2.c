#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"


typedef enum {
    SUCCESS,
    EOL,
    EOF,
    ERROR
} readLineResult_t;


/* Statics */
static uint8_t *pString = NULL;


/* Functions */
void setString(uint8_t *pStr)
{
    pString = pStr;
}

readLineResult_t readInt(uint16_t *pNum)
{
    uint8_t *pReadChar = pString;
    uint8_t numLength = 0;

    if(pReadChar == NULL) {
        return ERROR;
    }

    if(*pReadChar == '\n') {
        return EOL;
    }
    if(*pReadChar == '\0') {
        return EOF;
    }

    // Read ahead to find if an endline is reached before the next number
    while(*pReadChar != ' ')
    {
        if(*pReadChar == '\n') {
            break;
        }

        numLength++;
        pReadChar++;
    }

    // Skip the next space
    while(*pReadChar == ' ')
    {
        numLength++;
        pReadChar++;
    }

    // Reset the string pointer
    pReadChar = pString;

    // Read the integer from the string
    *pNum = atoi((const char*)pReadChar);

    // Move the string pointer to the next number
    pString += numLength;

    return SUCCESS;
}


int main(int argc, char *argv[])
{
    uint8_t *numbers =  "1234 2345 235 34556342\n"
    uint16_t num = 0;

    setString(numbers);

    while(readInt(&num) == SUCCESS) {
        printf("%d\r\n", num);
    }
}

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "common.h"


typedef enum {
    SUCCESS,
    EOL,
    EOFILE,
    ERROR
} readLineResult_t;


/* Statics */
static uint8_t *pString = NULL;
static uint8_t *pLine = NULL;


/* Functions */
void setString(uint8_t *pStr)
{
    pString = pStr;
    pLine = pStr;
}

readLineResult_t readInt(uint16_t *pNum)
{
    uint8_t *pReadChar = pString;

    if(pReadChar == NULL) {
        return ERROR;
    }

    if(*pReadChar == '\n') {
        return EOL;
    }
    if(*pReadChar == '\0') {
        return EOFILE;
    }

    // Read ahead to find if an endline is reached before the next number
    while(*pReadChar != ' ')
    {
        if(*pReadChar == '\n') {
            break;
        }

        pReadChar++;
    }

    // Skip the next space
    while(*pReadChar == ' ')
    {
        pReadChar++;
    }
    
    uint8_t *pNextChar = pReadChar;

    // Reset the string pointer
    pReadChar = pString;

    // Read the integer from the string
    *pNum = atoi((const char*)pReadChar);

    // Move the string pointer to the next number
    pString = pNextChar;

    return SUCCESS;
}

bool isEndLine()
{
    return *pString == '\n';
}

void moveToNextLine()
{
    while(*pString != '\n') {
        pString++;
    }
    pString++;
    pLine = pString;
}

void returnToStartOfLine()
{
    pString = pLine;
}

bool isEndOfFile()
{
    return *pString == '\0';
}

void lineToNums(uint16_t *nums)
{
    uint16_t i =0;
    
    while(!isEndLine()) {
        readInt(&nums[i]);
        i++;
    }
}


uint16_t getLineDiff()
{
    uint16_t minVal = UINT16_MAX;
    uint16_t maxVal = 0;
    
    while(!isEndLine()) {
        uint16_t num = 0;
        
        readInt(&num);
        
        minVal = minVal < num ? minVal : num;
        maxVal = maxVal > num ? maxVal : num;
    }
    
    moveToNextLine();
    
    return maxVal - minVal;
}

uint16_t getLineDiv()
{
    uint16_t nums[16] = {0};
    uint16_t result = 0;
    
    lineToNums(nums);
    
    for(uint8_t i=0; i<16; i++) {
        for(uint8_t j=0; j<16; j++) {
            if((nums[i] % nums[j] == 0) && (i != j)) {
                result = nums[i]/nums[j];
            }
        }
    }
    
    moveToNextLine();
    
    return result;
}

int main(int argc, char *argv[])
{
    uint8_t *numbers =  "5048    177     5280    5058    4504    3805    5735    220     4362    1809    1521    230     772     1088    178     1794\n"
                        "6629    3839    258     4473    5961    6539    6870    4140    4638    387     7464    229     4173    5706    185     271\n"
                        "5149    2892    5854    2000    256     3995    5250    249     3916    184     2497    210     4601    3955    1110    5340\n"
                        "153     468     550     126     495     142     385     144     165     188     609     182     439     545     608     319\n"
                        "1123    104     567     1098    286     665     1261    107     227     942     1222    128     1001    122     69      139\n"
                        "111     1998    1148    91      1355    90      202     1522    1496    1362    1728    109     2287    918     2217    1138\n"
                        "426     372     489     226     344     431     67      124     120     386     348     153     242     133     112     369\n"
                        "1574    265     144     2490    163     749     3409    3086    154     151     133     990     1002    3168    588     2998\n"
                        "173     192     2269    760     1630    215     966     2692    3855    3550    468     4098    3071    162     329     3648\n"
                        "1984    300     163     5616    4862    586     4884    239     1839    169     5514    4226    5551    3700    216     5912\n"
                        "1749    2062    194     1045    2685    156     3257    1319    3199    2775    211     213     1221    198     2864    2982\n"
                        "273     977     89      198     85      1025    1157    1125    69      94      919     103     1299    998     809     478\n"
                        "1965    6989    230     2025    6290    2901    192     215     4782    6041    6672    7070    7104    207     7451    5071\n"
                        "1261    77      1417    1053    2072    641     74      86      91      1878    1944    2292    1446    689     2315    1379\n"
                        "296     306     1953    3538    248     1579    4326    2178    5021    2529    794     5391    4712    3734    261     4362\n"
                        "2426    192     1764    288     4431    2396    2336    854     2157    216     4392    3972    229     244     4289    1902\n";
    uint16_t num = 0;

    setString(numbers);
    
    while(!isEndOfFile())
    {
        uint16_t diff = getLineDiff();
        num += diff;
    }
    
    printf("Checksum: %d\r\n", num);
    
    
    num = 0;
    setString(numbers);
    
    while(!isEndOfFile())
    {
        uint16_t diff = getLineDiv();
        num += diff;
    }
    
    printf("Checksum: %d\r\n", num);
}


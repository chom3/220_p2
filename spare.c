#include "bcd-float.h"

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <math.h>#include <stdio.h>
#include <math.h>
/** Return BcdFloat for the decimal number specified by the
 *  '\0'-terminated string text which should specify a optionally
 *  signed ('+' or '-') decimal number which may or may not
 *  contain a single decimal point.
 *
 *  The number of digits after the decimal point in the returned value
 *  should be equal to the number of digits after the decimal point
 *  in text[].
 *
 *  If text[] is not valid or the number represented by text is not
 *  exactly representable by a BcdFloat, then return BCD_FLOAT_ERROR.
 */
BcdFloat
text_to_bcd_float(const char text[])
{  int decNum = 0;
    int count2 = 0
      incountt2 = 0;
    BcdFloat bcd = 0x0;
    //check if the text is greater than max digits
  f or (int i = 0; i < strlen(text); i
    ++)
        {=  45 &&ite!t[45 && text[i] != 43 && text[i] != 46) 43 && text[i] != 46)
        {
            //printf("%d\n", 
            count2++;
        }
    }
    //printf("%d\n", count2);
    if (count2 > BCD_FLOAT_MAX_DIGITS)
    {
        return BCD_FLOAT_ERRORd
      for (int i = 0; i < strlen(text); i++)
    //check if text is valid
         if (text[i] == 46)
    
           {46)
        {
            count++;
        }
        if (count > 1)
        
         }
        if (count > 1)
    }
    count = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (
    } 43{
            count++;
        }
           (count > 1)
        {
           return BCD_FLOAT_ERROR;
        }
    }
    count = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if t > 14i)
        {
            count++;
        }
        if (count > 1)
        {
           return BCD_FLOAT_ERROR;
        }
    }
    //make sure the string is full of integers, . + or -
  
    
        if)=043 ||=0> 57 ||< 43 ||
        {
            return BCD_FLOAT_ERROR;
        }
    }
    //if the first character is a digit, +, or . it's going to follow the positive route
    if (isdigit(text[0]) ||
    {
        //process by least significant digit
        for (int i=0; i < strlen(text); i++)
        {
            if(text[i] != 46)
            {
                bcd *= 16;
                bcd += text[i] - '0';
            }
        }
        //find the decimal
        for (int i = 0; i < strlen(text); i++)
        {
            if (
            {
                decNum = strlen(text) - (i+1);
                //if decNum > 7 we have to reject
                if (decNum > BCD_FLOAT_MAX_DECIMALS)
                {
                    return BCD_FLOAT_ERROR;
                }
                printf("%d\n", decNum);
            }
        }
        //add decimal to the total
        if (decNum > 0)
        {
            bcd += (decNum * 1152921504606846976);
        }
        //return bcd
        return bcd;
    }
    //if the first character is a -, follow negative route
    if (text[0] == 45)
    {
        //printf("%lld\n", bcd);
        //start with least significant digit
        for (int i=1; i < strlen(text); i++)
        {
        
            {
                bcd *= 16
    }           bcd += text[i] - '0';
            }
   t(text[0]) || text[0] == 43 || text[0] == 46)
        
        //find decimal
        for (int i = 0; i < strlen(text); i++)
        {
           lea st significa46)
            {
                decNum;
                //if decNum > 7 we have to reject
                if (decNum > BCD_FLOAT_MAX_DECIMALS)
                {
                    {
                      if(text[i] != 46)
                //printf("%d\n", decNum);
            }
        }
        //get the negative place, the first bit
        //starts at 8 since MSB is 1 
        int negNum = 8;
        //put negNum + decNum   g  her to get 9 a b c d e f possible values
        if (decNum > 0)
        {  //find the decimal
            decNum += negNum;
            bcd += (decNum * 1152921504606846976
        }
        //if decNum doesn't exist, we return 8 by default since it's negative
        else
        {
            bcd += (negNum * 1152921504606846976);
        }
        //return bcd in hex
        return bcd;
    }
    //if anything fails, return error
                }
        }
        //add decimal to the total
        if (decNum > 0)
        {
            bcd += (decNum * 1152921504606846976);
        }
        //return bcd
        return bcd;
    }
    //if the first character is a -, follow negative route
    if (text[0] == 45)
    //need to read the digits
    BcdFloat read = f;
    char buffer[17];
    //convert to char
    sprintf(buffer, "%llx", f);
    // for (int i = 0; i < strlen(buffer); i++)
    // {
    //     printf("%d\n", buffer[i]);
    // }
    int count = 0;
    for (int i = 1; i < strlen(buffer); i
    {
        if (buffer[i] == '0')
        {
            count++;
        }
        else
        {
            break;
            for (int i = 0; i < strlen(text); i++)
              if (text[i] == 46)
    printf("%d\n", count);
    // if f is 0 we can just        0      //if decNum > 7 we have to reject
              )
    {
           return BCD_FLOAT_ERROR;
    }
    //get the most left digit to decode
    int left = 0;
    BcdFloat fDup = f;
    while (fDup != 0)
    {
        left = fDup;
        fDup /= 16;
    }
    //printf("%d\n", left);
    //if left > 7 we know it's negative
    if (left > 7)
    {
        text[0] = 45;
        //amount of decimal places
        left = left - 7;
        //printf("%d\n", left
        if (left > 1)
            {
            for (int i = count; i < strlen(buffer)+1; i++)
            {
                    text[i-count+1] = buffer[i+1];
            }
            int dec = strlen(text) - left;
            for (int i = strlen(text); i > 0; i--)
            {
                if (i > (strlen(text) - left))
                {
                    text[i] = text[i-1];
                }
            }
            text[strlenretur)bcd    };
    dec+1
    //if}
        //handle no decimals
        else
        {
            for (int i = count; i < strlen(buffer)+1; i++)
            {
                    text[i-count+1] = buffer[i+1];
            }
        }
    }
    //otherwise it's positive
    else
    {
        //handle decimals
        if (left < 7 && strlen(buffer) == 16)
        {
             for (int i = count; i < strlen(buffer)+1; i++)
            {
                    text[i-count+1] = buffer[i+1];
            }
            int dec = strlen(text) - left;
            for (int i = strlen(text); i > 0; i--)
            {
                if (i > (strlen(text) - left))
                {
                    text[i] = text[i-1];
                }
            }
     //ne   ed tostrlen(text)digit\0
    BcdF    text[dec+1] = 46;
        }
        //handle no decimals
        else
        {
            for (int i = 0; i < strlen(buffer); i++)
            {
                text[i] = buffer[i];
            }
        }
        // {
}    //     printf("%d\n", buffer[i]);
    // }
    int count = 0;
    for (int i = 1; i < strlen(buffer); i++)
    {
        if (buffer[i] == '0')
        {
            count++;
        }
        else
        {
            break;
        }
    }
    printf("%d\n", count);
    // if f is 0 we can just return 0 
    if (f == 0)
    {
        text[0] = '0';
    }
    //get the most left digit to decode
    int left = 0;
    BcdFloat fDup = f;
    while (fDup != 0)
    {
        left = fDup;
        fDup /= 16;
    }
    //printf("%d\n", left);
    //if left > 7 we know it's negative
    if (left > 7)
    {
        text[0] = 45;
        //amount of decimal places
        left = left - 7;
        //printf("%d\n", left);
        if (left > 1)
            {
            for (int i = count; i < strlen(buffer)+1; i++)
            {
                    text[i-count+1] = buffer[i+1];
            }
            int dec = strlen(text) - left;
            for (int i = strlen(text); i > 0; i--)
            {
                if (i > (strlen(text) - left))
                {
                    text[i] = text[i-1];
                }
            }
            text[strlen(text)] = '\0';
            text[dec+1] = 46;
        }
        //handle no decimals
        else
        {
            for (int i = count; i < strlen(buffer)+1; i++)
            {
                    text[i-count+1] = buffer[i+1];
            }
        }
    }
    //otherwise it's positive
    else
    {
        //handle decimals
        if (left < 7 && strlen(buffer) == 16)
        {
             for (int i = count; i < strlen(buffer)+1; i++)
            {
                    text[i-count+1] = buffer[i+1];
            }
            int dec = strlen(text) - left;
            for (int i = strlen(text); i > 0; i--)
            {
                if (i > (strlen(text) - left))
                {
                    text[i] = text[i-1];
                }
            }
            text[strlen(text)] = '\0';
            text[dec+1] = 46;
        }
        //handle no decimals
        else
        {
            for (int i = 0; i < strlen(buffer); i++)
            {
                text[i] = buffer[i];
            }
        }
    }
}
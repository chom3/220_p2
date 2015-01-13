#include "bcd-float.h"

#include <ctype.h>
#include <stdbool.h>
#include <string.h>

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
{
  //initialize variables
  bool zeroFull = true;
  bool falseZero = false;
  bool decimalExist = false;
  bool signExist = false;
  int zero = 0;
  int moveValues = (strlen(text) - 1);
  //look for -
  for(int i = 0; i < strlen(text); i++)
  {
    if(text[0] == '-')
    {
      falseZero = true;
    }
    //look for 0s
    else
    {
      int addedZero = (text[i] - '0');
      if(addedZero > 0)
      {
        zeroFull = false;
      }
      zero = zero + addedZero;
    }
  }
  //if 0 just return 0
  if(zero == 0 && !falseZero && zeroFull)
  {
    return 0;
  }
  //look for errors
  if(strlen(text) > 0 && strlen(text) < 18)
  {
    //look for decimal
    for(int i = 0; i < strlen(text); i++)
    {
      if(text[i] == '.')
      {
        if(decimalExist)
        {
          return BCD_FLOAT_ERROR;
        }
        decimalExist = true;
      }
      //look for + - sign
      if(text[i] == '-' || text[i] == '+')
      {
        signExist = true;
      }
    }
    //need to shift
    if(decimalExist)
    {
      moveValues--;
    }
    //need to shift
    if(signExist)
    {
      moveValues--;
    }
  }
  //or return error if too many
  else{
    return BCD_FLOAT_ERROR;
  }
  //if above possible length return error
  if(strlen(text) > 17)
  {
    return BCD_FLOAT_ERROR;
  }
  //error handling, greater than possible length and no - or +
  if(strlen(text) > 15 && !decimalExist && !(text[0] == '-' || text[0] == '+')){
    return BCD_FLOAT_ERROR;
  }
  //bcd return
  BcdFloat bcd = 0;
  for(int i = 0; i < (strlen(text)); i++){
    //if not a number it fails
    if(i == 0 && (text[i] != 43 && text[i] != 45
    && text[i] != 46 && text[i] != 48 && text[i] != 49
    && text[i] != 50 && text[i] != 51 && text[i] != 52
    && text[i] != 53 && text[i] != 54 && text[i] != 55
    && text[i] != 56 && text[i] != 57))
    {
      return BCD_FLOAT_ERROR;
    }
    //if not a number it fails
    if(i > 0 && (text[i] != 46 && text[i] != 48
    && text[i] != 49 && text[i] != 50 && text[i] != 51
    && text[i] != 52 && text[i] != 53 && text[i] != 54
    && text[i] != 55 && text[i] != 56 && text[i] != 57))
    {
      return BCD_FLOAT_ERROR;
    }
    //if length and 16 + there is a sign it works, otherwise fails
    if(((strlen(text) == 17) && !(text[0] == '+' || text[0] == '-')))
    {
      return BCD_FLOAT_ERROR;
    }
    //if - we automatically assume 8 for leftmost bit
    if(text[i] == '-')
    {
      BcdFloat n = (0x8000000000000000);
      bcd += n;
      
    }
    //else it's below 8 for decimals
    else if(text[i] == '.')
    {
      BcdFloat n = ((strlen(text) - 1) - i);
      //if it's higher than decimal max we fail
      if(n > BCD_FLOAT_MAX_DECIMALS){
        return BCD_FLOAT_ERROR;
      }
      n = n;
      n = n << 60;
      bcd += n;
    }
    //+ isn't necessary
    else if(text[i] == '+')
    {}
    //add the values to bcd
    else{
      BcdFloat n = (text[i] - '0');
      n = n << ((moveValues) * 4);
      moveValues--;
      bcd += n;
    }
  }
  //if strlen too big we have an error
  if(!decimalExist && strlen(text) == 17)
  {
    return BCD_FLOAT_ERROR;
  }
  //return finished product
  return bcd;
}


/** Convert the BcdFloat f to its nul-terminated string representation
 *  in text[] (which is assumed to have space for at least
 *  BCD_FLOAT_MAX_STRING_LENGTH + 1 characters).  Avoid non-significant
 *  zero's before the decimal point.
 */
void
bcd_float_to_text(const BcdFloat f, char text[])
{
  //initialize variables
  //figure out possible negative numbers
  BcdFloat negative = (f & 0xf000000000000000);
  negative = (negative >> 60);
  int place = 0;
  bool decimalExist = false;
  bool wasReached = false;
  //if f == 0 we can just return 0
  if(f == 0)
  {
    text[0] = '0';
  }
  //place negative sign in text
  if(negative > 7)
  {
    text[place] = '-';
    place++;
  }
  //need to place negative decimals as well
  if(negative > 0)
  {
    negative &= 0x7;
    if(negative > 0)
    {
      decimalExist = true;
    }
  }
  //if there's just a decimal and 0 we know it's going to be 0.0
  if(f == 0x1000000000000000)
  {
    text[0] = '0';
    text[1] = '.';
    text[2] = '0';
  }
  //now we can take a duplicate f and check to write text
  for(int i = 0; i < 15; i++)
  {
    BcdFloat fDup = f;
    BcdFloat fCheck = 0xf00000000000000;
    fCheck = (fCheck >> (i * 4));
    fCheck = (fCheck & fDup);
    fCheck = (fCheck >> ((14 - i) * 4));
    //if we reach it we want to pass it
    if(fCheck > 0)
    {
      wasReached = true;
    }
    //need to avoid decimal place
    if(fCheck > 0 || wasReached)
    {
      char input = (char)(((int)'0')+fCheck);
      text[place] = input;
      place++;
    }
    //if decimal exist we need to place it in
    if(decimalExist && ((15 - (i + 1)) == negative))
    {
      if(text[0] == '\0')
      {
        //pad with 0
        text[place] = '0';
        place++;
        text[place] = '.';
        place++;
        wasReached = true;
      }
      //place decimal in negative spot
      else if(text[0] == '-' && text[1] == '\0')
      {
        text[place] = '0';
        place++;
        text[place] = '.';
        place++;
        wasReached = true;
      }
      //just place decimal
      else
      {
        text[place] = '.';
        place++;
        wasReached = true;
      }
    }
  }
}

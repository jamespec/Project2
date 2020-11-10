#include <stdio.h>
#include <string.h>

#include "parse.h"

/*
 * getISBM:
 * 
 * reads the next chars for an ISBM from input starting at index 'start'.
 * If found, the value is copied to output and the index of the next unused 
 * char is returned.
 * Else, a -1 is returned.
 * 
 * ISBM is 10 characters, ignoring spaces and '-'
 * The last digit is a check digit
 */

int getISBM( char input[], int nextChar, char output[] ) 
{
    if( strlen(input) == 0 )
        return -1;

    int digitsSoFar=0;
    while( digitsSoFar < 10 && input[nextChar] != '\0' ) {
        if( input[nextChar] != ' ' && input[nextChar] != '-' ) {
            output[digitsSoFar++] = input[nextChar];
        }
        nextChar++;
    }
    // null terminate the output string.
    output[digitsSoFar] = '\0';

    if( digitsSoFar < 10 )
        return -1;

    // sum up the first 9 digits
    // substract '0' to convert from char digit to number.
    int s=0;
    for(int i=0; i<9; i++) {
        s += (10-i) * (output[i] - '0');
    }

    // calculate the expected check
    int mod11 = (s % 11);
    int check = (mod11 == 0) ? 0 : (11 - mod11);

    // special case when check is 10, an X is used instead
    // first check for check digit of 0-9, then check 10
    // output[9] is the 10th digit, the check
    if( check < 10 && check != (output[9]-'0') )
        return -1;
    else if( check == 10 && output[9] != 'X')
        return -1;
    
    return nextChar;
}

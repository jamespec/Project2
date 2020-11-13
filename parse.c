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

int getISBN( char input[], int nextChar, char output[] ) 
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
        s += ((10-i) * (output[i] - '0'));
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

int getTitle( char input[], int nextChar, char output[] ) 
{
    if( strlen(input) == 0 )
        return -1;

    int numQuotes=0;
    int nextOutChar=0;
    while( numQuotes < 2 && input[nextChar] != '\0' ) 
    {
        if( input[nextChar] == '\"' ) {
            numQuotes++;
        }
        else if( numQuotes == 0 && input[nextChar] != ' ' ) {
            // If we haven't found the first quote only spaces are allowed.
            return -1; 
        }
        else if( numQuotes == 1 ) {
            output[nextOutChar++] = input[nextChar];
        }
        nextChar++;
    }
    // null terminate the output string.
    output[nextOutChar] = '\0';

    if( numQuotes != 2 ) {
        // The input ended before we found the second quote, error!
        return -1;
    }

    return nextChar;
}

// reads the last name, anything up to and including the comma is consumed.
// the nextChar index is returned, in this case the index to the char after the comma.
// If a comma is not found before the end of the input a -1 is returned.
int getLast( char input[], int nextChar, char output[] )
{
    if( strlen(input) == 0 )
        return -1;

    int nextOutChar=0;
    while( input[nextChar] != ',' && input[nextChar] != '\0' ) 
    {
        if( input[nextChar] != ' ' )
            output[nextOutChar++] = input[nextChar];

        nextChar++;
    }
    // null terminate the output string.
    output[nextOutChar] = '\0';

    if( input[nextChar] != ',' )
        return -1;

    // consume the ','
    nextChar++;

    return nextChar;
}


// reads the first name, anything up to the end of the input is consumed.
// the nextChar index is returned, in this case the index of the '\0' at the end.
// The only error occurs when an empty input is passed in, returning -1
int getFirst( char input[], int nextChar, char output[] )
{
    if( strlen(input) == 0 )
        return -1;

    int nextOutChar=0;
    while( input[nextChar] != '\0' )
    {
        if( input[nextChar] != ' ' )
            output[nextOutChar++] = input[nextChar];
            
        nextChar++;
    }
    // null terminate the output string.
    output[nextOutChar] = '\0';

    return nextChar;
}

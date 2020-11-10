#include <stdio.h>

#include "parse.h"

int findLine(char s[], int lim);

int main() {
    char line[300];

    // 1550225480 - 
    // 1 * 10 
    char test_line[] = "   1-550-225  48-0QQQQ  ";
    char output[100];
    int nextChar = 0;

    int count = findLine(line, 300);
    while( count > 0 ) {
        int result = getISBM( test_line, nextChar, output );
        if( result < 0 )
            printf("Error is ISBM\n");
        else
        {
            printf("ISBM: %s\n", output);
        }

        count = findLine(line, 300);
    }
}

//Reference to Get Line Function from textbook
int findLine(char s[], int lim) {
    int c, i;

    for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
        s[i] = c;
    if(c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

#include <stdio.h>

#include "parse.h"

int findLine(char s[], int lim);

int main() {
    char line[300];

    char isbn[12];
    char title[200];

    int count = findLine(line, 300);
    while( count > 0 ) {
        printf("input: %s", line);

        int nextChar = getISBN( line, 0, isbn );
        if( nextChar > 0 ) {
            nextChar = getTitle( line, nextChar, title );
            if( nextChar > 0 ) {
                printf("ISBM: %s  Title: %s\n", isbn, title );
            }
            else {
                printf("Error in title\n");
            }
        }
        else {
            printf("Error in ISBM\n");
        }

        printf("\n");

        count = findLine(line, 300);
        nextChar=0;
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

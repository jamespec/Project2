#include <stdio.h>
#include <string.h>

#include "parse.h"
#include "book_list.h"

int findLine(char s[], int lim);

int main() {
    struct book *list_head=0;

    char line[300];

    char isbn[12];
    char title[200];
    char last[50];
    char first[50];
    struct book book;

    int inputLines = 0;
    int accepted=0;

    int count = findLine(line, 300);
    while( count > 0 ) { 
        inputLines++;

        int nextChar = getISBN( line, 0, isbn );
        if( nextChar > 0 ) {
            nextChar = getTitle( line, nextChar, title );
            if( nextChar > 0 ) {
                nextChar = getLast( line, nextChar, last );
                if( nextChar > 0 ) {
                    nextChar = getFirst( line, nextChar, first );
                    if( nextChar > 0 ) {
                        accepted++;

                        fillBook( &book, isbn, title, last, first );

                        struct book *found = findBookByISBN( list_head, isbn );
                        if( found ) {
                            if( compareBooks( found, &book ) == 0 )
                                found->count++;
                            // else
                            // mismatched info! Figure out what to do
                        }
                        else {
                            // not found, add new
                            list_head = add( list_head, &book );
                        }
                    }
                }
            }
        }

        count = findLine(line, 300);
        nextChar=0;
    }

    printf("%d lines of input wew processed.\n\n", inputLines);
    printBookTitles(list_head);
    printf("\n%d lines of input were accepted.\n", accepted );
    printf("%d lines of input were rejected.\n", (inputLines-accepted));
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

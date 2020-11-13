#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "parse.h"
#include "book_list.h"

int findLine(char s[], int lim);
int iswhitespace( char s[] );

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
    int rejected=0;

    int count = findLine(line, 300);
    while( count > 0 ) { 
        inputLines++;

        if( iswhitespace(line) == 0 )
            continue;

        int nextChar = getISBN( line, 0, isbn );
        if( nextChar > 0 ) {
            nextChar = getTitle( line, nextChar, title );
            if( nextChar > 0 ) {
                nextChar = getLast( line, nextChar, last );
                if( nextChar > 0 ) {
                    nextChar = getFirst( line, nextChar, first );
                    if( nextChar > 0 ) {
                        fillBook( &book, isbn, title, last, first );

                        struct book *found = findBookByISBN( list_head, isbn );
                        if( found ) {
                            if( compareBooks( found, &book ) == 0 ) {
                                found->count++;
                                accepted++;
                            }
                            else
                            {
                                rejected++;
                            }
                        }
                        else {
                            // not found, add new
                            list_head = add( list_head, &book );
                            accepted++;
                        }
                    }
                    else
                        rejected++;
                }
                else
                    rejected++;
            }
            else
                rejected++;
        }
        else
            rejected++;

        count = findLine(line, 300);
        nextChar=0;
    }

    printf("%d lines of input wew processed.\n\n", inputLines);
    printBookTitles(list_head);
    printf("\n%d lines of input were accepted.\n", accepted );
    printf("%d lines of input were rejected.\n", rejected );
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

int iswhitespace( char s[] ) {
    int count=0;

    for( int i=0; s[i]; i++ )
        if( isspace(s[i]) )
            count++;

    return count;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bad_line_list.h"


struct bad_line *addBadLine( struct bad_line *head, char line[] )
{
    struct bad_line *temp = (struct bad_line *)malloc(sizeof(struct bad_line));

    temp->line = (char *)malloc( strlen(line)+1 );
    strcpy( temp->line, line );
    temp->next = head;

    return temp;
}

void printBadLines( struct bad_line *head )
{
    if( !head )
        return;

    if( head->next )
        printBadLines( head->next );

    printf("%s", head->line);
}

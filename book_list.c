#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "book_list.h"


void fillBook( struct book *book, char isbn[], char title[], char last[], char first[] )
{
    strcpy( book->isbn, isbn );
    strcpy( book->title, title );
    strcpy( book->last, last );
    strcpy( book->first, first );
    book->count = 0;
    book->next = 0;
}

// Adds a new book to a linked list and returns the new head
struct book *add(struct book *head, struct book *newBook ) 
{
    struct book *temp = (struct book *)malloc(sizeof(struct book));
    *temp = *newBook;
    temp->count = 1;
    temp->next = head;

    return temp;
}

void printBookList(struct book *head)
{
    while( head ) {
        printf("ISBN: %s  Title: %-60.60s  Last: %s  First: %s  Count: %d\n", 
            head->isbn, head->title, head->last, head->first, head->count );

        head = head->next;
    }
}

void printBookTitles(struct book *head)
{
    while( head ) {
        printf("%s: %d\n", head->title, head->count );
        head = head->next;
    }
}

// returns the book if found or zero if not
struct book *findBookByISBN( struct book *head, char isbn[] )
{
    while( head ) {
        if( strcmp( head->isbn, isbn ) == 0 )
            break;

        head = head->next;
    }
    return head;
}

// returns
//  0, if book1 equals book2
//  1, if book1 has a different isbn as book2
// -1, if the isbn is the same both info is different, a bad row
int compareBooks( struct book *book1, struct book *book2 )
{
    if( strcmp(book1->isbn, book2->isbn) != 0 )
        return 1;

    if( strcmp(book1->title, book2->title) != 0 )
        return -1;

    if( strcmp(book1->last, book2->last) != 0 )
        return -1;

    if( strcmp(book1->first, book2->first) != 0 )
        return -1;

    return 0;
}

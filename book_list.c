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

// Adds a new book to the list at the location that that makes the list ordered by title.
struct book *add(struct book *head, struct book *newBook, int byAuthor ) 
{
    struct book *temp = (struct book *)malloc(sizeof(struct book));
    *temp = *newBook;
    temp->count = 1;

    if( !head || compareBooks(temp, head, byAuthor) < 0 ) {
        temp->next = head;
        return temp;
    }

    struct book *current = head;
    while( current->next && compareBooks(current->next, temp, byAuthor) < 0 )
        current = current->next;

    temp->next = current->next;
    current->next = temp;

    return head;
}

void printBookList(struct book *head )
{
    while( head ) {
        printf("%s (%s): %d\n", head->title, head->last, head->count );

// Usefull for debugging, prints all fields.      
//        printf("ISBN: %s  Title: %-60.60s  Last: %s  First: %s  Count: %d\n", 
//            head->isbn, head->title, head->last, head->first, head->count );

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

// Compares books
// if byAuthor is false:
//   by title then last, first and finally isbn
//  -1, if book1 sorts before book2
//   0, if book1 is entirely equal to book2
//   1, if book1 sorts after book2
// if byAuthor is true:
//   by last, first, title and finally isbn
//  -1, if book1 sorts before book2
//   0, if book1 is entirely equal to book2
//   1, if book1 sorts after book2

int compareBooks( struct book *book1, struct book *book2, int byAuthor )
{
    int c;

    if( byAuthor ) {
        int c = strcmp(book1->last, book2->last);
        if( c != 0 )
            return c;

        // Last name is the same, look at first name
        c = strcmp(book1->first, book2->first);
        if( c != 0 )
            return c;

        // first name is the same, look at title
        c = strcmp(book1->title, book2->title);
        if( c != 0 )
            return c;

        return strcmp(book1->title, book2->title);
    }
    else {
        c = strcmp(book1->title, book2->title);
        if( c != 0 )
            return c;

        c = strcmp(book1->last, book2->last);
        if( c != 0 )
            return c;

        c = strcmp(book1->first, book2->first);
        if( c != 0 )
            return c;

        return strcmp(book1->isbn, book2->isbn);
    }
}

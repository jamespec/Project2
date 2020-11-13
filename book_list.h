
struct book {
    char isbn[12];
    char title[200];
    char last[50];
    char first[50];
    int count;
    struct book *next;
};

void fillBook( struct book *book, char isbn[], char title[], char last[], char first[] );
struct book *add(struct book *head, struct book *newBook, int sortByAuthor );
void printBookList(struct book *head );
struct book *findBookByISBN( struct book *head, char isbn[] );

int compareBooks( struct book *book1, struct book *book2, int byAuthor );

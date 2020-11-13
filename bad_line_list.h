
struct bad_line {
    char *line;
    struct bad_line *next;
};

struct bad_line *addBadLine( struct bad_line *head, char line[] );
void printBadLines( struct bad_line *head );

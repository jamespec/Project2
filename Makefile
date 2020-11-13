
project2: project2.o parse.o book_list.o bad_line_list.o
	gcc -g -o $@ $^

project2.o: project2.c parse.h book_list.h bad_line_list.h
	gcc -c $< -g

parse.o: parse.c parse.h
	gcc -c $< -g

book_list.o: book_list.c book_list.h
	gcc -c $< -g

bad_line_list.o: bad_line_list.c bad_line_list.h
	gcc -c $< -g

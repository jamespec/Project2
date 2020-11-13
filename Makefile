
project2: project2.o parse.o book_list.o
	gcc -g -o $@ $^

%.o: %.c %.h
	gcc -c $< -g

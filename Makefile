
project2: project2.o parse.o
	gcc -g -o $@ $^

%.o: %.c
	gcc -c $< -g

FILE = analyzer.c interpter.c main.c tree.c
BF = test.bf
NAME = BFinterpter

s:
	gcc -w -c $(FILE)
	gcc *.o -o $(NAME)
	rm *.o
clean:
	rm *.o
run:
	cat $(BF)
	./$(NAME) $(BF)
warn:
	gcc -c $(FILE)
	gcc *.o -o $(NAME)
	rm *.o
tst:
	gcc -w -c $(FILE)
	gcc *.o -o $(NAME)
	rm *.o
	cat $(BF)
	./$(NAME) $(BF)

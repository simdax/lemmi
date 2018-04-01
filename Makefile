SRCS = parse.c test.c

all:
	make -C libft
	gcc -g $(SRCS) -Ilibft  -Llibft -lft

run: all
	./a.out

debug: all
	lldb a.out

valgrind: all
	valgrind --leak-check=full ./a.out

norminette:
	norminette $(SRCS)

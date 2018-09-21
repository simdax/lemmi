LIBFT_PATH=../libft
SRCS = parse.c test.c array_utils.c getnames.c

all:
	make -C $(LIBFT_PATH)
	gcc -g $(SRCS) -I$(LIBFT_PATH)  -L$(LIBFT_PATH) -lft

run: all
	./a.out

debug: all
	lldb a.out

valgrind: all
	valgrind --leak-check=full ./a.out

norminette:
	norminette $(SRCS)

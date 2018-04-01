SRCS = parse.c test.c

all:
	make -C libft
	gcc -g $(SRCS) -Ilibft  -Llibft -lft

run: all
	./a.out

debug:
	lldb a.out

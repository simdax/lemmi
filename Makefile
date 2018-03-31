all:
	make -C libft
	gcc -g main.c -Ilibft  -Llibft -lft

run: all
	./a.out

debug:
	lldb a.out

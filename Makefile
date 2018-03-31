all:
	make -C libft
	gcc main.c -Ilibft  -Llibft -lft

run: all
	./a.out

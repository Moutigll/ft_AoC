CC = gcc
CFLAGS = -Wall -Werror -Wextra -I../libft/include
SRC = main.c compute_part1.c compute_part2.c
LIBFT = ../libft/libft.a

all: $(LIBFT) 06

06: $(SRC) $(LIBFT)
	$(CC) $(CFLAGS) $(SRC) -o 06 $(LIBFT)

$(LIBFT):
	@make -C ../libft

clean:
	rm -f *.o
	@make -C ../libft clean

fclean: clean
	rm -f 06
	@make -C ../libft fclean

re: fclean all

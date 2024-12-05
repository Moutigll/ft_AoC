CC = gcc
CFLAGS = -Wall -Werror -Wextra -I../libft/include
SRC = main.c parsing.c part2.c
LIBFT = ../libft/libft.a

all: $(LIBFT) 05

05: $(SRC) $(LIBFT)
	$(CC) $(CFLAGS) $(SRC) -o 05 $(LIBFT)

$(LIBFT):
	@make -C ../libft

clean:
	rm -f *.o
	@make -C ../libft clean

fclean: clean
	rm -f 04
	@make -C ../libft fclean

re: fclean all

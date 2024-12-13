CC = gcc
CFLAGS = -Wall -Werror -Wextra -I../libft/include
SRC = main.c
LIBFT = ../libft/libft.a

all: $(LIBFT) 13

13: $(SRC) $(LIBFT)
	$(CC) $(CFLAGS) $(SRC) -o 13 $(LIBFT)

$(LIBFT):
	@make -C ../libft

clean:
	rm -f *.o
	@make -C ../libft clean

fclean: clean
	rm -f 13
	@make -C ../libft fclean

re: fclean all

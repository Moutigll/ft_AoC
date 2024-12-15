CC = gcc
CFLAGS = -Wall -Werror -Wextra -I../libft/include
SRC = main.c utils.c
LIBFT = ../libft/libft.a

all: $(LIBFT) 15

15: $(SRC) $(LIBFT)
	$(CC) $(CFLAGS) $(SRC) -o 15 $(LIBFT)

$(LIBFT):
	@make -C ../libft

clean:
	rm -f *.o
	@make -C ../libft clean

fclean: clean
	rm -f 15
	@make -C ../libft fclean

re: fclean all

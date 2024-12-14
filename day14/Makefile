CC = gcc
CFLAGS = -Wall -Werror -Wextra -I../libft/include
SRC = main.c utils.c
LIBFT = ../libft/libft.a

all: $(LIBFT) 14

14: $(SRC) $(LIBFT)
	$(CC) $(CFLAGS) $(SRC) -o 14 $(LIBFT)

$(LIBFT):
	@make -C ../libft

clean:
	rm -f *.o
	@make -C ../libft clean

fclean: clean
	rm -f 14
	@make -C ../libft fclean

re: fclean all

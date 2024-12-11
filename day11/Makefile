CC = gcc
CFLAGS = -Wall -Werror -Wextra -I../libft/include -lm
SRC = main.c utils.c
LIBFT = ../libft/libft.a

all: $(LIBFT) 11

11: $(SRC) $(LIBFT)
	$(CC) $(SRC) -o 11 $(LIBFT) $(CFLAGS)

$(LIBFT):
	@make -C ../libft

clean:
	rm -f *.o
	@make -C ../libft clean

fclean: clean
	rm -f 11
	@make -C ../libft fclean

re: fclean all

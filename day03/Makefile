CC = gcc
CFLAGS = -Wall -Werror -Wextra -I../libft/include
SRC = main.c
LIBFT = ../libft/libft.a

all: $(LIBFT) 03

03: $(SRC) $(LIBFT)
	$(CC) $(CFLAGS) $(SRC) -o 03 $(LIBFT)

$(LIBFT):
	@make -C ../libft

clean:
	rm -f *.o
	@make -C ../libft clean

fclean: clean
	rm -f 01
	@make -C ../libft fclean

re: fclean all

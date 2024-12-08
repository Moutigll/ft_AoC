CC = gcc
CFLAGS = -Wall -Werror -Wextra -I../libft/include
SRC = main.c compute.c
LIBFT = ../libft/libft.a

all: $(LIBFT) 08

08: $(SRC) $(LIBFT)
	$(CC) $(CFLAGS) $(SRC) -o 08 $(LIBFT)

$(LIBFT):
	@make -C ../libft

clean:
	rm -f *.o
	@make -C ../libft clean

fclean: clean
	rm -f 08
	@make -C ../libft fclean

re: fclean all

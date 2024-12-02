CC = gcc
CFLAGS = -Wall -Werror -Wextra -I../libft/include
SRC = main.c get_list.c compute.c
LIBFT = ../libft/libft.a

all: $(LIBFT) 01

01: $(SRC) $(LIBFT)
	$(CC) $(CFLAGS) $(SRC) -o 01 $(LIBFT)

$(LIBFT):
	@make -C ../libft

clean:
	rm -f *.o
	@make -C ../libft clean

fclean: clean
	rm -f 01
	@make -C ../libft fclean

re: fclean all

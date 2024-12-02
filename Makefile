CC = gcc
CFLAGS = -Wall -Werror -Wextra -I libft/include
LIBFT = libft/libft.a
NAME = $(DAY)
SRC_DIR = day$(DAY)
EXEC = all.out

all: $(NAME)


$(NAME):
	@echo "Entering $(SRC_DIR) directory"
	@make -C $(SRC_DIR)
	@mv $(SRC_DIR)/$(NAME) .
	@make -C $(SRC_DIR) clean

clean:
	@make -C libft clean
	@rm -f 01

fclean: clean
	@make -C libft fclean

re: fclean all

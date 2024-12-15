CC = gcc
CFLAGS = -Wall -Werror -Wextra -fPIE -I libft/include
LIBFT = libft/libft.a
NAME = $(DAY)
SRC_DIR = day$(DAY)
EXEC = all.out

all: $(NAME)


$(NAME): clean
	@echo "Entering $(SRC_DIR) directory"
	@make -C $(SRC_DIR)
	@mv $(SRC_DIR)/$(NAME) .
	@make -C $(SRC_DIR) clean

clean:
	@make -C libft clean
	@rm -f 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15

fclean: clean
	@make -C libft fclean

re: fclean all

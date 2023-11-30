
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = so_long.c \
	so_long_utils.c \
	is_map_valid.c \
	is_map_valid2.c \
	draw_map.c
OBJ = $(SRC:.c=.o)
NAME = so_long

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ) libft/libft.a printf/libftprintf.a
	$(CC) -o $(NAME) $(OBJ) -Llibft -Lprintf -lft -lftprintf

libft/libft.a :
	$(MAKE) -C libft -f Makefile

printf/libftprintf.a :
	$(MAKE) -C printf -f Makefile

clean:
	$(MAKE) -C libft -f Makefile clean
	$(MAKE) -C printf -f Makefile clean
	rm -f $(OBJ)

fclean: clean
	$(MAKE) -C libft -f Makefile fclean
	$(MAKE) -C printf -f Makefile fclean
	rm -f $(NAME)

re: fclean all
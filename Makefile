
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = so_long.c \
	so_long_utils.c \
	is_map_valid.c \
	are_chars_valid.c \
	run_map_init.c \
	run_map.c
OBJ = $(SRC:.c=.o)
NAME = so_long
MLX = -L/usr/local/lib -lmlx -framework OpenGL -framework AppKit

.PHONY: all clean fclean re

all: $(NAME)

#Quitar -g3 -fsanitize=address
$(NAME): $(OBJ) libft/libft.a printf/libftprintf.a
	$(CC) -o $(NAME) $(OBJ) $(MLX) -Llibft -Lprintf -lft -lftprintf -g3 -fsanitize=address

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
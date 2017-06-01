INCLUDES	+= fdf fdf_draw fdf_env_build
INCLUDES	+= fdf_hooks
INCLUDES	:= $(addprefix src/, $(INCLUDES))
INCLUDES	:= $(addsuffix .o, $(INCLUDES))
CC			:= gcc
FLAGS		+= -Wall -Wextra -Werror -Ilibft/include/ -Iinclude/ -Imlx
FLAGS		+= -g
FRAME		:= -framework OpenGL -framework Appkit
NAME		:= fdf

.PHONY: clean fclean re all

all: $(NAME)

$(NAME): $(INCLUDES) libft/libftprintf.a mlx/libmlx.a
	@echo 'Building $(NAME)'
	@$(CC) $(FLAGS) $(FRAME) $^ -o $@

%.o: %.c
	$(CC) $(FLAGS) -c $^ -o $@

libft/libftprintf.a:
	@make -C libft/

mlx/libmlx.a:
	@make -C mlx/

clean:
	@echo 'Removing $(NAME)--object files'
	@rm -rf $(INCLUDES)
	@make -C libft/ clean
	@make -C mlx/ clean

fclean: clean
	@echo 'Removing $(NAME)'
	@rm -rf $(NAME)
	@make -C libft/ fclean

re: fclean all

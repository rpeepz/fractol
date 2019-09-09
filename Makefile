# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/09 00:09:32 by rpapagna          #+#    #+#              #
#    Updated: 2019/05/20 17:09:29 by rpapagna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= fractol

#COLORS
GREEN	= \033[0;32m
RED		= \033[0;31m
YELLOW	= \033[0;33m
NC		= \033[0m

SRC		= main.c \
		error.c

FLAGS	= -Wall -Wextra -Werror
INC		= -I fractol.h
#MLX COMPILE ORDER
MLX_LNK	= -L ./minilibx_macos -l mlx_macos -framework AppKit -framework OpenGL
#LIB COMPILE ORDER
FT_LNK	= -L ./libft -l ft

.PHONY:	all clean fclean re debug

all:	$(NAME)

clean:
		@make -C libft clean
		@make -C minilibx clean
		@printf "[$(RED)clean   mlx$(NC)]\t[:######    :]\r"
		@make -C minilibx_macos clean
		@printf "[$(RED)clean   mlx$(NC)]\t[:##########:]\r"
		@rm -rf $(NAME).dSYM
		@printf "[$(RED)full  clean$(NC)]\t[:##########:]\n"

fclean: clean
		@make -C libft fclean
		@rm -rf $(NAME)
		@printf "[$(RED)full  clean$(NC)]\t[:##########:]\n"

re: fclean all

$(NAME):
		@make -C libft
		@make -C minilibx_macos
		@printf "[$(GREEN)fractol$(NC) ]\t[:##        :]\r"
		@gcc $(FLAGS) $(addprefix src/,$(SRC)) $(INC) $(MLX_LNK) $(FT_LNK) -o $(NAME)
		@printf "[$(GREEN)fractol$(NC) ]\t[:##########:]\n"

debug:
		@rm -rf $(NAME)
		@rm -rf $(NAME).dSYM
		@gcc $(FLAGS) -g $(addprefix src/,$(SRC)) $(MLX_LNK) $(FT_LNK) $(INC) -o $(NAME) -fsanitize=address
		@printf "[$(YELLOW)debug   $(NC)]\t[$(RED):##########:$(NC)]\n"

quick:
		@rm -rf $(NAME)
		@rm -rf $(NAME).dSYM
		@gcc -Wall -Wextra -g $(addprefix src/,$(SRC)) $(MLX_LNK) $(FT_LNK) $(INC) -o $(NAME)
		@printf "[$(YELLOW)make  quick$(NC)]\t[:##########:]\n"
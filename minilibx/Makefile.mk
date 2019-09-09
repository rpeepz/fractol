##
## Makefile for MiniLibX in /home/boulon/work/c/raytraceur/minilibx
## 
## Made by Olivier Crouzet
## Login   <ol@epitech.net>
## 
## Started on  Tue Oct  5 15:56:43 2004 Olivier Crouzet
## Last update Tue May 15 15:41:20 2007 Olivier Crouzet
##

## Please use configure script

RED		= \033[0;31m
CYN		= \033[0;36m
NC		= \033[0m

INC		=%%%%
HT		=%%%%
DOCP	=%%%%

CC		= @gcc -w

NAME	= libmlx.a
OBJ_PATH= obj

SRC	=mlx_clear_window.c \
	mlx_destroy_image.c \
	mlx_destroy_window.c \
	mlx_expose_hook.c \
	mlx_flush_event.c \
	mlx_get_color_value.c \
	mlx_get_data_addr.c \
	mlx_hook.c \
	mlx_init.c \
	mlx_int_anti_resize_win.c \
	mlx_int_do_nothing.c \
	mlx_int_get_visual.c \
	mlx_int_param_event.c \
	mlx_int_set_win_event_mask.c \
	mlx_int_str_to_wordtab.c \
	mlx_int_wait_first_expose.c \
	mlx_key_hook.c \
	mlx_lib_xpm.c \
	mlx_loop_hook.c \
	mlx_loop.c \
	mlx_mouse_hook.c \
	mlx_new_image.c \
	mlx_new_window.c \
	mlx_pixel_put.c \
	mlx_put_image_to_window.c \
	mlx_rgb.c \
	mlx_string_put.c \
	mlx_xpm.c

OBJ	= $(addprefix $(OBJ_PATH)/,$(SRC:.c=.o))
CFLAGS	= -O3 -I$(INC)

all: $(NAME) $(DOCP)

$(NAME): $(OBJ)
	@printf "[$(CYN)create$(NC)]\t[:#######   :]\r"
	@ar -rcs $(NAME) $(OBJ)
	@printf "[$(CYN)create$(NC)]\t[:##########:]\n"

$(OBJ_PATH):
	@printf "[$(CYN)create$(NC)]\t[:#         :]\r"
	@mkdir -p $@

$(OBJ_PATH)/%.o: src/%.c | $(OBJ_PATH)
	@printf "[$(CYN)create$(NC)]\t[:#####     :]\r"
	@cc -w $(CFLAGS) -o $@ -c $<

do_cp:
	@cp $(NAME) libmlx_$(HT).a

clean:
	@printf "[rm      obj]\t[:          :]\r"
	@rm -f $(OBJ) $(NAME) *~ core *.core
	@rm -rf $(OBJ_PATH)
	@printf "[$(RED)rm      obj$(NC)]\t[:##########:]\r"
	
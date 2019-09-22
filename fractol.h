/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 02:06:55 by rpapagna          #+#    #+#             */
/*   Updated: 2019/09/22 04:07:17 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../libft/includes/libft.h"
# include "minilibx/includes/mlx.h"
# include "keys.h"
# include <math.h>
# include <stdio.h>

# define USAGE "usage: ./fractol [ 1 | 2 | 3 ]"
# define WIDTH 1000
# define HEIGHT 1000

/*
**	STRUCTS
*/

typedef struct			s_input
{
	char				misdown;
	char				kydown;
	int					lock;
	int					mx;
	int					my;
	int					mlastx;
	int					mlasty;
}						t_input;

typedef struct			s_cam
{
	double				offsetx;
	double				offsety;
	double				x;
	double				y;
	double				zoom;
	size_t				scale;
}						t_cam;

typedef struct			s_image
{
	void				*image;
	char				*ptr;
	int					bpp;
	int					stride;
	int					endian;
}						t_image;

typedef struct			s_pix
{
	double				a;
	double				b;
	double				complex[2];
	double				formula[2];
	int					color[3];
}						t_pix;

typedef struct			s_palette
{
	int					color[3];
	struct s_palette	*next;
}						t_palette;

typedef struct			s_frac
{
	size_t				max_i;
	void				*mlx;
	void				*window;
	t_input				*in;
	t_image				*image;
	t_cam				*cam;
	t_palette			*palette;
	char				type;
}						t_frac;

t_frac					*init(char *title, int type);
t_frac					*fracdel(t_frac *frac);
t_image					*del_image(t_frac *frac, t_image *img);

void					render(t_frac *frac);
float					map_zeromin(float in_value, float in_max,
	float start, float end);
int						rbg_color(int r, int g, int b);

/*
**	INPUTS
*/

int						hook_mouseup(int button, int x, int y, t_frac *frac);
int						hook_mousedown(int button, int x, int y, t_frac *frac);
int						hook_mousemove(int x, int y, t_frac *frac);
int						hook_keydown(int key, t_frac *frac);

double					convert_(double z_vector, double min, double max);
int						shift_color(int c1, int c2, double p);

#endif

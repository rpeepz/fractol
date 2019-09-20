/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 02:06:55 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/22 18:04:26 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../libft/includes/libft.h"
# include "minilibx/includes/mlx.h"
# include "keys.h"
# include <math.h>


# define USAGE "usage: ./fractol [-1 | -2 | -3]"
# define WIDTH 400
# define HEIGHT 600


/*
**	STRUCTS
*/

typedef struct	s_input
{
	char		misdown;
	char		kydown;
	int			lock;
	int			mx;
	int			my;
	int			mlastx;
	int			mlasty;
}				t_input;

typedef struct	s_cam
{
	double		offsetx;
	double		offsety;
	double		x;
	double		y;
	int			scale;
}				t_cam;

typedef struct	s_image
{
	void		*image;
	char		*ptr;
	int			bpp;
	int			stride;
	int			endian;
}				t_image;

typedef struct	s_pix
{
	double		x;
	double		y;
	int			color;
}				t_pix;

typedef struct	s_frac
{
	void		*mlx;
	void		*window;
	t_input		*in;
	t_image		*image;
	t_cam		*cam;
	float		x;
	float		y;
}				t_frac;

t_frac			*init(char *title);
t_frac			*fracdel(t_frac *frac);
t_image			*new_image(t_frac *frac);
t_image			*del_image(t_frac *frac, t_image *img);

void			render(t_frac *frac);


/*
**	INPUTS
*/

int				hook_mouseup(int button, int x, int y, t_frac *frac);
int				hook_mousedown(int button, int x, int y, t_frac *frac);
int				hook_mousemove(int x, int y, t_frac *frac);
int				hook_keydown(int key, t_frac *frac);

double			convert_(double z_vector, double min, double max);
int				shift_color(int c1, int c2, double p);

#endif

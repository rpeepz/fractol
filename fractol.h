/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 02:06:55 by rpapagna          #+#    #+#             */
/*   Updated: 2019/09/25 18:31:00 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft/includes/libft.h"
# include "minilibx/includes/mlx.h"
# include "keys.h"
# include <math.h>
# include <pthread.h>
# include <stdio.h>

# define USAGE "usage: ./fractol [ 1 | 2 | 3 | 4 ]"
# define VALID_IN1(x) (x == KEY_PLUS || x == KEY_MINUS || x == KEY_SPACE)
# define VALID_IN2(x) (x == KEY_LEFT || x == KEY_RIGHT)
# define VALID_IN3(x) (x == KEY_UP || x == KEY_DOWN || x == KEY_R || x == KEY_P)
# define STATIC_ZOOM(x) (x == PG_UP || x == PG_DOWN)
# define WIDTH 1280
# define HEIGHT 720
# define DEBUG 0
# define CORE_MODE 1
# define THREAD_COUNT 8

/*
**	STRUCTS
*/

typedef struct			s_input
{
	int					lock;
	int					psy;
	int					mx;
	int					my;
	int					mlastx;
	int					mlasty;
}						t_input;

typedef struct			s_cam
{
	double				offsetx;
	double				offsety;
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
	double				w;
	double				h;
	double				xmin;
	double				xmax;
	double				ymin;
	double				ymax;
	double				c[2];
	int					color[3];
}						t_pix;

typedef struct			s_palette
{
	int					color[3];
	struct s_palette	*next;
}						t_palette;

typedef struct			s_psych
{
	int					color[3];
}						t_psych;

typedef struct			s_frac
{
	void				*mlx;
	void				*win;
	t_input				*in;
	t_image				*image;
	t_cam				*cam;
	t_palette			*palette;
	t_psych				**psych;
	char				type;
	size_t				max_i;
}						t_frac;

typedef struct			s_point
{
	size_t				x;
	size_t				y;
}						t_point;

typedef struct			s_frac_thread
{
	t_frac				*frac;
	t_pix				pix;
	int					i;
}						t_frac_thread;

void					render(t_frac *frac);
void					render_thread(t_frac *frac, t_pix pix);

size_t					define_pixel(t_point pixel, t_frac *frac, t_pix *pix);
void					get_color(t_frac *frac, t_pix *pix, size_t n);

t_frac					*init(char *title, int type);
t_frac					*del_frac(t_frac *frac);
t_image					*del_image(t_frac *frac, t_image *img);
void					init_pix(t_pix *pix, t_frac *frac);

int						ft_help(void);
int						ft_out(int key);
int						rbg_color(int r, int g, int b);
void					set_palettes(t_frac *frac, int i);

int						hook_keydown(int key, t_frac *frac);
int						hook_mousedown(int button, int x, int y, t_frac *frac);
int						hook_mousemove(int x, int y, t_frac *frac);

#endif

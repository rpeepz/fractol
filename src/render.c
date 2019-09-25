/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 20:11:33 by rpapagna          #+#    #+#             */
/*   Updated: 2019/09/24 17:03:30 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void	get_color(t_frac *frac, t_pix *pix, size_t n)
{
	if (frac->in->psy)
	{
		pix->color[0] = frac->psych[n % 10]->color[0];
		pix->color[1] = frac->psych[n % 10]->color[1];
		pix->color[2] = frac->psych[n % 10]->color[2];
	}
	else
	{
		pix->color[0] = frac->palette->color[0] +
			map_zeromin(n, frac->max_i, 0, 255);
		pix->color[1] = frac->palette->color[1] +
			map_zeromin(n, frac->max_i, 0, 255);
		pix->color[2] = frac->palette->color[2] +
			map_zeromin(n, frac->max_i, 0, 255);
	}
	if (n == frac->max_i)
	{
		pix->color[0] = 0;
		pix->color[1] = 0;
		pix->color[2] = 0;
	}
}

void	get_frac(t_frac *frac, t_pix *pix)
{
	if (frac->type == 1 || frac->type == 3)
	{
		pix->complex[0] = pix->a;
		pix->complex[1] = pix->b;
	}
	else
	{
		pix->complex[0] = map_zeromin(frac->in->my, HEIGHT, -1.5, 1.5);
		pix->complex[1] = map_zeromin(frac->in->mx, WIDTH, -1.5, 1.5);
	}
}

size_t	define_pixel(t_point pixel, t_frac *frac, t_pix *pix)
{
	size_t		n;
	double		aa;
	double		bb;
	double		twoab;

	pix->a = (map_zeromin(pixel.x, WIDTH, pix->xmin, pix->xmax) /
		(frac->cam->zoom));
	pix->b = (map_zeromin(pixel.y, HEIGHT, pix->ymin, pix->ymax) /
		(frac->cam->zoom));
	get_frac(frac, pix);
	n = 0;
	while (n < frac->max_i)
	{
		aa = pix->a * pix->a;
		bb = pix->b * pix->b;
		twoab = 2.0 * pix->a * pix->b;
		pix->a = frac->type > 2 ? abs_double(aa - bb + pix->complex[0]) :
											aa - bb + pix->complex[0];
		pix->b = frac->type > 2 ? abs_double(twoab) + pix->complex[1] :
											twoab + pix->complex[1];
		if (pix->a * pix->a + pix->b * pix->b > 4)
			break ;
		n++;
	}
	return (n);
}

void	render(t_frac *frac)
{
	t_point		pixel;
	size_t		n;
	t_pix		pix;

	ft_bzero(frac->image->ptr, WIDTH * HEIGHT * frac->image->bpp);
	init_pix(&pix, frac);
	if (!THREAD_MODE)
	{
		pixel.x = -1;
		while (++pixel.x < WIDTH)
		{
			pixel.y = -1;
			while (++pixel.y < HEIGHT)
			{
				n = define_pixel(pixel, frac, &pix);
				get_color(frac, &pix, n);
				*(int *)(frac->image->ptr +
				(pixel.x + pixel.y * WIDTH) * frac->image->bpp) =
					(int)rbg_color(pix.color[0], pix.color[1], pix.color[2]);
			}
		}
	}
	else
		render_thread(frac, pix);
	mlx_put_image_to_window(frac->mlx, frac->window, frac->image->image, 0, 0);
}

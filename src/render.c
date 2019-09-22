/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 20:11:33 by rpapagna          #+#    #+#             */
/*   Updated: 2019/09/22 04:55:07 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void	get_color(t_frac *frac, t_pix *pix, size_t n)
{
	pix->color[0] = frac->palette->color[0];
	pix->color[1] = frac->palette->color[1];
	pix->color[2] = frac->palette->color[2];
	if (n == frac->max_i)
	{
		pix->color[0] = 0;
		pix->color[1] = 0;
		pix->color[2] = 0;
	}
}

void	get_frac(t_frac *frac, t_pix *pix)
{
	if (frac->type == 1)
	{
		pix->complex[0] = pix->a;
		pix->complex[1] = pix->b;
	}
	else
	{
		pix->complex[0] = map_zeromin(frac->in->mx, WIDTH, -1, 1);
		pix->complex[1] = map_zeromin(frac->in->my, HEIGHT, -1.5, 1.5);
	}
	pix->formula[0] = 0;
	pix->formula[1] = 0;
}

size_t	do_imaginary(size_t x, size_t y, t_frac *frac, t_pix *pix)
{
	size_t		n;

	pix->a = map_zeromin(x, WIDTH, -4, 4) /
		(frac->cam->zoom) + frac->cam->offsetx;
	pix->b = map_zeromin(y, HEIGHT, -4, 4) /
		(frac->cam->zoom) + frac->cam->offsety;
	get_frac(frac, pix);
	n = -1;
	while (++n < frac->max_i)
	{
		pix->formula[0] = pix->a * pix->a - pix->b * pix->b;
		pix->formula[1] = 2 * pix->a * pix->b;
		pix->a = pix->formula[0] + pix->complex[0];
		pix->b = pix->formula[1] + pix->complex[1];
		if (pix->a * pix->a + pix->b * pix->b > 5)
			break ;
	}
	return (n);
}

void	render(t_frac *frac)
{
	size_t		x;
	size_t		y;
	size_t		n;
	t_pix		pix;

	frac->max_i = 100 + frac->cam->scale;
	ft_printf("frac type = %d\n ", frac->type);
	ft_bzero(frac->image->ptr, WIDTH * HEIGHT * frac->image->bpp);
	x = -1;
	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
		{
			n = do_imaginary(x, y, frac, &pix);
			get_color(frac, &pix, n);
			*(int *)(frac->image->ptr + (x + y * WIDTH) * frac->image->bpp) =
				(int)rbg_color(pix.color[0], pix.color[1], pix.color[2]);
		}
	}
	mlx_put_image_to_window(frac->mlx, frac->window, frac->image->image, 0, 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 05:02:30 by rpapagna          #+#    #+#             */
/*   Updated: 2019/09/21 16:56:56 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"
#include <stdio.h>

float	map(float in_value, float in_max, float start, float end)
{
	if (in_value >= in_max)
		return (end);
	if (in_value <= 0)
		return (start);
	return (in_value * ((end - start) / (in_max)) + start);
}

int		rbg_color(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	render(t_frac *frac)
{
	int			x;
	int			y;
	double		ca;
	double		cb;
	double		a;
	double		b;
	double		aa;
	double		bb;
	int			n;
	int			color_r;
	int			color_g;
	int			color_b;
	int			pix;
	uint16_t	iterations;

	iterations = 100 + frac->cam->scale;
	printf("itter = %d\n ", iterations);
	ft_bzero(frac->image->ptr, WIDTH * HEIGHT * frac->image->bpp);
	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			// map percentage based on coordinate
			a = map(x, WIDTH, -2, 2);
			b = map(y, HEIGHT, -1.2, 1.2);
			//orignal coordinates
			ca = a;
			cb = b;
			ca = map(frac->in->mx, WIDTH, -1, 1);
			cb = map(frac->in->my, HEIGHT, -1.5, 1.5);
			//next iteration initialize
			aa = 0;
			bb = 0;
			n = 0;
			while (n < iterations)
			{
				// calculate a^2
				aa = a * a - b * b;
				// calculate 2ab
				bb = 2 * a * b;
				// next a = current a^2 + original a
				a = aa + ca;
				// next b = current 2ab + original b
				b = bb + cb;
				//check if a + b drifts toward infinity
				if (a * a + b * b > 500)
					break ;
				n++;
			}
			color_r = map(n, iterations, 0, 50);
			color_g = map(n, iterations, 0, 100);
			color_b = map(n, iterations, 0, 255);
			if (n == iterations)
			{
				color_r = 0;
				color_g = 0;
				color_b = 0;
			}
			pix = (x + y * WIDTH) * frac->image->bpp;
			*(int *)(frac->image->ptr + pix) = (int)rbg_color(color_r, color_g, color_b);
			// mlx_pixel_put(frac->mlx, frac->window, x, y,
			//	(int)rbg_color(color_r, color_g, color_b));
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(frac->mlx, frac->window, frac->image->image, 0, 0);
}

int		parse(char **av, int i, int j)
{
	av = 0;
	i = 0;
	j = 0;
	return (0);
}

int		main(int ac, char **av)
{
	t_frac	*frac;

	if (ac < 2)
		return (ft_printf("%s\n", USAGE));
	frac = init("fractol");
	parse(av, 1, 0);
	render(frac);
	mlx_key_hook(frac->window, hook_keydown, frac);
	mlx_hook(frac->window, 4, 0, hook_mousedown, frac);
	mlx_hook(frac->window, 6, 0, hook_mousemove, frac);
	mlx_hook(frac->window, 5, 0, hook_mouseup, frac);
	mlx_loop(frac->mlx);
	return (0);
}

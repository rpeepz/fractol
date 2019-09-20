/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 05:02:30 by rpapagna          #+#    #+#             */
/*   Updated: 2019/09/20 03:43:16 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

float	map(float in_value, float in_max, float start, float end)
{
	float		map;
	float		stop;

	stop = 0;
	if (fork() == 0)
	{
		if (start < 0)
			while (start < 0)
			{
				stop++;
				start++;
			}
		start += stop;
	}
	else
	{
		if (end < 0)
			while (end < 0)
			{
				stop++;
				start++;
			}
		end += stop;
	}
	wait(NULL);
	map = in_value / in_max * 100;
}

void	render(t_frac *frac)
{
	uint16_t maxiterations = 100;

	for (int x = 0; x < WIDTH; x++) {
		for (int y = 0; y < HEIGHT; y++) {
			// map percentage based on coordinate
			double a = map(x, WIDTH, -2, 1);
			double b = map(y, HEIGHT, -0.8, 1.2);

			//orignal coordinates
			int ca = a;
			int cb = b;
			//next iteration init;
			int z = 0;
			int aa = 0;
			int bb = 0;
			for (int n = z; n < maxiterations; n++) {
				z = n;
				// calculate a^2
				aa = a * a - b * b;
				// calculate 2ab
				bb = 2 * a * b;
				// next a = current a^2 + original a
				a = aa + ca;
				// next b = current 2ab + original b
				b = bb + cb;
				//check if a + b drifts toward infinity
				if (a * a + b * b > 32)
					break;
			}

			var color_r = map(z, 0, maxiterations, 0, 1);
			//color_r = map(sqrt(color_r), 0, 1, 0, 50);
			var color_g = map(z, 0, maxiterations, 0, 1);
			//color_g = map(sqrt(color_g), 0, 1, 50, 150);
			var color_b = map(z, 0, maxiterations, 0, 1);
			// color_b = map(sqrt(color_b), 0, 1, 100, 255);

			if (z == maxiterations) {
				color_r = 0;
				color_g = 0;
				color_b = 0;
			  }

			var pix = (x + y * width) * 4;
			mlx_pixel_put(frac->mlx, frac->window, x, y, )
			mlx_pixel_put(frac->mlx, frac->window, x, y, )
			mlx_pixel_put(frac->mlx, frac->window, x, y, )
			mlx_pixel_put(frac->mlx, frac->window, x, y, )
			pixels[pix + 0] = color_r;
			pixels[pix + 1] = color_g;
			pixels[pix + 2] = color_b;
			pixels[pix + 3] = 255;
		}
	}
	updatePixels();
}

int		parse(char **av, int i, int j)
{
	av = 0;
	return i = j = 0;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 05:02:30 by rpapagna          #+#    #+#             */
/*   Updated: 2019/09/22 03:39:01 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

float	map_zeromin(float in_value, float in_max, float start, float end)
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

int		main(int ac, char **av)
{
	t_frac	*frac;
	int		type;

	if (ac == 2 && (!ft_strcmp(av[1], "1") || !ft_strcmp(av[1], "2") ||
		!ft_strcmp(av[1], "3")))
		type = ft_atoi(av[1]);
	else
		return (ft_printf("%s\n", USAGE));
	frac = init("fractol", type);
	render(frac);
	mlx_key_hook(frac->window, hook_keydown, frac);
	mlx_hook(frac->window, 4, 0, hook_mousedown, frac);
	mlx_hook(frac->window, 6, 0, hook_mousemove, frac);
	mlx_hook(frac->window, 5, 0, hook_mouseup, frac);
	mlx_loop(frac->mlx);
	return (0);
}

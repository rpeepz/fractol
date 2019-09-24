/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 05:02:30 by rpapagna          #+#    #+#             */
/*   Updated: 2019/09/23 23:01:56 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

int		main(int ac, char **av)
{
	t_frac	*frac;
	int		type;

	if (ac == 2 && (!ft_strcmp(av[1], "1") || !ft_strcmp(av[1], "2") ||
		!ft_strcmp(av[1], "3") || !ft_strcmp(av[1], "4")))
		type = ft_atoi(av[1]);
	else
		return (ft_printf("%s\n", USAGE));
	frac = init("fractol", type);
	render(frac);
	mlx_key_hook(frac->window, hook_keydown, frac);
	mlx_hook(frac->window, 4, 0, hook_mousedown, frac);
	mlx_hook(frac->window, 6, 0, hook_mousemove, frac);
	mlx_loop(frac->mlx);
	return (0);
}

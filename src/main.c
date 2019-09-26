/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 05:02:30 by rpapagna          #+#    #+#             */
/*   Updated: 2019/09/26 01:11:24 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

int		main(int ac, char **av)
{
	t_frac	*frac;
	int		type;

	if (ac == 3 && ac--)
		if (fork())
			av[1] = av[2];
	if (ac == 2 && (!ft_strcmp(av[1], "1") || !ft_strcmp(av[1], "2") ||
		!ft_strcmp(av[1], "3") || !ft_strcmp(av[1], "4")))
		type = ft_atoi(av[1]);
	else if (av[1] && !ft_strcmp(av[1], "help"))
		return (ft_help());
	else
		return (ft_printf("%s\n", USAGE));
	if (!(frac = init("fractol", type)))
		return (ft_out(-42));
	render(frac);
	mlx_key_hook(frac->win, hook_keydown, frac);
	mlx_hook(frac->win, 4, 0, hook_mousedown, frac);
	mlx_hook(frac->win, 6, 0, hook_mousemove, frac);
	mlx_loop(frac->mlx);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 20:35:44 by rpapagna          #+#    #+#             */
/*   Updated: 2019/09/26 00:51:20 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

int		ft_out(int key)
{
	if (key == KEY_PLUS)
		printf("Max itterations + 10\n");
	else if (key == KEY_MINUS)
		printf("Max itterations - 5\n");
	else if (key == KEY_UP)
		printf("Offset Y + 0.01\n");
	else if (key == KEY_DOWN)
		printf("Offset Y - 0.01\n");
	else if (key == KEY_LEFT)
		printf("Offset X - 0.01\n");
	else if (key == KEY_RIGHT)
		printf("Offset X + 0.01\n");
	else if (key == KEY_R)
		printf("Reset Zoom & Itteration\n");
	else if (key == KEY_SPACE)
		printf("Next Color palette\n");
	else if (key == SCROLL_UP)
		printf("Zoom level + ");
	else if (key == SCROLL_DOWN)
		printf("Zoom level - ");
	else if (key == -42)
		printf("Malloc Error\n");
	return (1);
}

int		ft_help(void)
{
	ft_printf("Controls:\n");
	ft_printf("%11c\tIncrease itterations\n%11c\tDecrease itterations\n",
	'+', '-');
	ft_printf("%11s\tMove fractol image in window\n", "arrow keys");
	ft_printf("%11s\tCycle color palette\n", "space bar");
	ft_printf("%11c\tToggle psychedelic color scheme\n", 'P');
	ft_printf("%11c\tToggle mouse lock\n", 'C');
	ft_printf("%11s\tIncrease zoom (static)\n%11s\tDecrease zoom (static)\n",
	"page up", "page down");
	ft_printf("%11s\tIncrease / Decrease zoom (follow cursor)\n",
	"mouse wheel");
	ft_printf("%11c\tReset position, itterations & zoom\n", 'R');
	ft_printf("%11s\tQuit\n", "esc");
	return (1);
}

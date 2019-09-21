/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 13:14:09 by rpapagna          #+#    #+#             */
/*   Updated: 2019/09/21 16:54:10 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

int		hook_mousedown(int button, int x, int y, t_frac *frac)
{
	(void)x;
	if (y < 0)
		return (0);
	if (button == SCROLL_DOWN || button == SCROLL_UP)
	{
		if (frac->cam->scale < -89 && button == SCROLL_DOWN)
			;
		else
			frac->cam->scale += (button == SCROLL_DOWN) ? -10 : 10;
		ft_printf("scroll %d\n", button);
		render(frac);
	}
	else
		frac->in->misdown |= 1 << button;
	return (0);
}

int		hook_mouseup(int button, int x, int y, t_frac *frac)
{
	(void)x;
	(void)y;
	frac->in->misdown &= ~(1 << button);
	return (0);
}

int		hook_mousemove(int x, int y, t_frac *frac)
{
	if (frac->in->lock)
	{
		frac->in->mlastx = frac->in->mx;
		frac->in->mlasty = frac->in->my;
		frac->in->mx = x;
		frac->in->my = y;
		render(frac);
	}
	return (0);
}

int		hook_keydown(int key, t_frac *frac)
{
	(void)frac;
	ft_printf("key: %d\n", key);
	ft_printf("lock: %d\n", frac->in->lock);
	if (key == KEY_ESC)
	{
		system("leaks fractol");
		exit(EXIT_SUCCESS);
	}
	if (key == KEY_PLUS)
		frac->x++;
	if (key == KEY_MINUS)
		frac->x--;
	if (key == KEY_C)
		frac->in->lock = (frac->in->lock) ? 0 : 1;
	// render(frac);
	return (0);
}

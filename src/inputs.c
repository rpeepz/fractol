/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 13:14:09 by rpapagna          #+#    #+#             */
/*   Updated: 2019/09/19 14:44:39 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

int		hook_mousedown(int button, int x, int y, t_frac *frac)
{
	(void)x;
	if (y < 0)
		return (0);
	if (button == SCROLL_DOWN || button == SCROLL_UP)
		ft_printf("scroll %d\n", button);
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
	frac->in->mlastx = frac->in->mx;
	frac->in->mlasty = frac->in->my;
	frac->in->mx = x;
	frac->in->my = y;
	if (frac->in->misdown & (1 << 1))
	{
		frac->cam->x += (frac->in->mlasty - y) / 350.0f;
		frac->cam->y -= (frac->in->mlastx - x) / 400.0f;
	}
	return (0);
}

int		hook_keydown(int key, t_frac *frac)
{
	(void)frac;
	ft_printf("key: %d\n", key);
	ft_printf("mouseX: %d\n", frac->in->mx);
	ft_printf("mouseY: %d\n", frac->in->my);
	if (key == KEY_ESC)
		exit(EXIT_SUCCESS);
	if (key == KEY_PLUS)
        frac->x++;
	if (key == KEY_MINUS)
        frac->x--;
	if (key == KEY_C)
        frac->in->lock = (frac->in->lock) ? 0 : 1;
    // render(frac);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 13:14:09 by rpapagna          #+#    #+#             */
/*   Updated: 2019/09/22 04:59:21 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

int		hook_mousedown(int btn, int x, int y, t_frac *frac)
{
	int		zoom;

	(void)x;
	(void)y;
	if (btn == SCRL_UP || (btn == SCRL_DWN && frac->max_i > 0))
	{
		zoom = (frac->cam->zoom / 100 + 1);
		if (btn == SCRL_UP)
			frac->cam->zoom += zoom;
		else if (btn == SCRL_DWN)
			frac->cam->zoom -= zoom;
		render(frac);
		printf("%f\n", frac->cam->zoom);
	}
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
	if (!frac->in->lock && frac->type)
	{
		if (x > 0 && y > 0 && x < WIDTH && y < HEIGHT)
		{
			frac->in->mlastx = frac->in->mx;
			frac->in->mlasty = frac->in->my;
			frac->in->mx = x;
			frac->in->my = y;
		}
		render(frac);
	}
	else
	{
		;
	}
	return (0);
}

int		hook_keydown(int key, t_frac *frac)
{
	(void)frac;
	ft_printf("key: %d\n", key);
	ft_printf("lock: %d\n", frac->in->lock);
	if (key == KEY_ESC)
		exit(EXIT_SUCCESS);
	if (key == KEY_PLUS)
		frac->cam->scale += 10;
	if (key == KEY_MINUS)
		frac->cam->scale -= 5;
	if (key == KEY_UP || key == KEY_DOWN)
		frac->cam->offsety += (key == KEY_UP) ? 0.1 : -0.1;
	if (key == KEY_RIGHT || key == KEY_LEFT)
		frac->cam->offsetx += (key == KEY_LEFT) ? 0.1 : -0.1;
	if (key == KEY_R)
	{
		frac->cam->scale = 0;
		frac->cam->zoom = 0.5;
	}
	if (key == KEY_C)
		frac->in->lock = (frac->in->lock) ? 0 : 1;
	if (key == KEY_SPACE)
		frac->palette = frac->palette->next;
	render(frac);
	return (0);
}

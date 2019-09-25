/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 13:14:09 by rpapagna          #+#    #+#             */
/*   Updated: 2019/09/24 14:49:21 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

int		ft_out(int key)
{
	IF_RETURN(DEBUG == 0, 1);
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
	else if (key == KEY_ESC)
		printf("Goodbye!\n");
	return (1);
}

int		hook_mousedown(int btn, int x, int y, t_frac *frac)
{
	float		zoom;

	(void)x;
	(void)y;
	if (btn == SCROLL_UP || (btn == SCROLL_DOWN))
	{
		zoom = (frac->cam->zoom / 100 + 1);
		if (btn == SCROLL_DOWN && (zoom > frac->cam->zoom))
			printf("Minimum Zoom reached\n");
		else
		{
			if (btn == SCROLL_UP && ft_out(btn))
				frac->cam->zoom += zoom;
			else if (btn == SCROLL_DOWN && ft_out(btn))
				frac->cam->zoom -= zoom;
			if (DEBUG)
				printf("%f\n", frac->cam->zoom);
			render(frac);
		}
	}
	return (0);
}

int		hook_mousemove(int x, int y, t_frac *frac)
{
	if (!frac->in->lock && !(frac->type % 2))
	{
		if (x > 0 && y > 0 && x < WIDTH && y < HEIGHT)
		{
			frac->in->mlastx = frac->in->mx;
			frac->in->mlasty = frac->in->my;
			frac->in->mx = x;
			frac->in->my = y;
			render(frac);
		}
	}
	else
	{
		;
	}
	return (0);
}

void	in_key(t_frac *frac, int key)
{
	if (key == KEY_PLUS && ft_out(key))
		frac->max_i += 10;
	else if (key == KEY_MINUS)
	{
		if (frac->max_i > 6 && ft_out(key))
			frac->max_i -= 5;
		else if (DEBUG)
			printf("key: '-' max itterations - 0\n");
	}
	else if ((key == KEY_UP || key == KEY_DOWN) && ft_out(key))
		frac->cam->offsety -= (key == KEY_UP) ? 0.01 : -0.01;
	else if ((key == KEY_RIGHT || key == KEY_LEFT) && ft_out(key))
		frac->cam->offsetx -= (key == KEY_LEFT) ? 0.01 : -0.01;
}

int		hook_keydown(int key, t_frac *frac)
{
	if (key == KEY_PLUS || key == KEY_MINUS ||
		key == KEY_UP || key == KEY_DOWN ||
		key == KEY_RIGHT || key == KEY_LEFT)
		in_key(frac, key);
	else if (key == KEY_R && ft_out(key))
	{
		frac->max_i = 60;
		frac->cam->zoom = 1.01;
	}
	else if (key == KEY_P && printf("Key: 'P' Psych: %s\n",
		frac->in->psy ? "Off" : "On"))
		frac->in->psy = (frac->in->psy) ? 0 : 1;
	else if (key == KEY_C && printf("Key: 'C' Lock: %s\n",
		frac->in->lock ? "Off" : "On"))
		frac->in->lock = (frac->in->lock) ? 0 : 1;
	else if (key == KEY_SPACE && ft_out(key))
		frac->palette = frac->palette->next;
	else if (key == KEY_ESC && ft_out(key))
		exit(EXIT_SUCCESS);
	render(frac);
	return (0);
}

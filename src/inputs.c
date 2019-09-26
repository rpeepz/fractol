/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 13:14:09 by rpapagna          #+#    #+#             */
/*   Updated: 2019/09/26 00:53:35 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

int				hook_mousedown(int btn, int x, int y, t_frac *frac)
{
	double		zoom;

	if (btn == SCROLL_UP || (btn == SCROLL_DOWN) || STATIC_ZOOM(btn))
	{
		zoom = (frac->cam->zoom / 100 + 1);
		if ((btn == SCROLL_DOWN || btn == PG_DOWN) && (zoom > frac->cam->zoom))
			printf("Minimum Zoom reached\n");
		else
		{
			if ((btn == SCROLL_UP || btn == PG_UP) && (DEBUG ? ft_out(btn) : 1))
				frac->cam->zoom += zoom;
			else if ((btn == SCROLL_DOWN || btn == PG_DOWN) &&
				(DEBUG ? ft_out(btn) : 1))
				frac->cam->zoom -= zoom;
			if (!STATIC_ZOOM(btn))
			{
				frac->cam->offsetx += 0.005 * (x - (WIDTH / 2));
				frac->cam->offsety += 0.005 * (y - (HEIGHT / 2));
			}
			if (DEBUG)
				printf("%f\n", frac->cam->zoom);
			render(frac);
		}
	}
	return (0);
}

int				hook_mousemove(int x, int y, t_frac *frac)
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

static void		in_key(t_frac *frac, int key)
{
	if (key == KEY_PLUS && (DEBUG ? ft_out(key) : 1))
		frac->max_i += 10;
	else if (key == KEY_MINUS)
	{
		if (frac->max_i > 6 && (DEBUG ? ft_out(key) : 1))
			frac->max_i -= 5;
		else if (DEBUG)
			printf("key: '-' max itterations - 0\n");
	}
	else if (key == KEY_SPACE && (DEBUG ? ft_out(key) : 1))
		frac->palette = frac->palette->next;
	else if ((key == KEY_UP || key == KEY_DOWN) && (DEBUG ? ft_out(key) : 1))
		frac->cam->offsety -= (key == KEY_UP) ? 0.35 : -0.35;
	else if ((key == KEY_RIGHT || key == KEY_LEFT) && (DEBUG ? ft_out(key) : 1))
		frac->cam->offsetx -= (key == KEY_LEFT) ? 0.35 : -0.35;
}

int				hook_keydown(int key, t_frac *frac)
{
	if (VALID_IN1(key) || VALID_IN2(key) || key == KEY_UP || key == KEY_DOWN)
		in_key(frac, key);
	else if (STATIC_ZOOM(key))
		hook_mousedown(key, 0, 0, frac);
	else if (key == KEY_C && printf("Key: 'C' Lock: %s\n",
		frac->in->lock ? "Off" : "On"))
		frac->in->lock = (frac->in->lock) ? 0 : 1;
	else if (key == KEY_R && (DEBUG ? ft_out(key) : 1))
	{
		frac->max_i = 60;
		frac->cam->zoom = 1.01;
		frac->cam->offsetx = WIDTH / 2;
		frac->cam->offsety = HEIGHT / 2;
	}
	else if (key == KEY_P && printf("Key: 'P' Psych: %s\n",
		frac->in->psy ? "Off" : "On"))
		frac->in->psy = (frac->in->psy) ? 0 : 1;
	else if (key == KEY_ESC && printf("Goodbye!\n"))
	{
		if (DEBUG)
			system("leaks fractol");
		exit((int)del_frac(&frac, 0));
	}
	IF_THEN(VALID_IN1(key) || VALID_IN2(key) || VALID_IN3(key), render(frac));
	return (0);
}

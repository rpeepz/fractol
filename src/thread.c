/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 12:40:37 by rpapagna          #+#    #+#             */
/*   Updated: 2019/09/25 18:41:21 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void	*thread_op(void *arg)
{
	t_frac_thread	*p;
	t_frac			*frac;
	t_pix			pix;
	t_point			pixel;
	size_t			n;

	p = (t_frac_thread *)arg;
	frac = p->frac;
	pix = p->pix;
	pixel.x = ((WIDTH / THREAD_COUNT) * (p->i)) - 1;
	while (++(pixel.x) < (size_t)((WIDTH / THREAD_COUNT) * (p->i + 1)))
	{
		pixel.y = -1;
		while (++(pixel.y) < HEIGHT)
		{
			n = define_pixel(pixel, frac, &pix);
			get_color(frac, &pix, n);
			*(int *)(frac->image->ptr +
			(pixel.x + pixel.y * WIDTH) * frac->image->bpp) =
				(int)rbg_color(pix.color[0], pix.color[1], pix.color[2]);
		}
	}
	pthread_exit(NULL);
}

void	render_thread(t_frac *frac, t_pix pix)
{
	t_frac_thread	p[THREAD_COUNT];
	pthread_t		t[THREAD_COUNT];
	int				i;

	i = -1;
	while (++i < (THREAD_COUNT))
	{
		p[i].frac = frac;
		p[i].pix = pix;
		p[i].i = i;
		pthread_create(&t[i], NULL, thread_op, &p[i]);
	}
	i = -1;
	while (++i < (THREAD_COUNT))
	{
		pthread_join(t[i], NULL);
	}
}

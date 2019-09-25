/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 12:40:37 by rpapagna          #+#    #+#             */
/*   Updated: 2019/09/24 17:03:55 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void    *thread_op(void *arg)
{
	t_thread_ptr	*p;
	t_frac			*frac;
	t_pix			pix;
	t_point			pixel;
	size_t			n;

	p = (t_thread_ptr *)arg;
	frac = p->frac;
	pix = p->pix;
	pixel.x = ((WIDTH / THREAD_MODE) * (p->i)) - 1;
	while (++(pixel.x) < (size_t)((WIDTH / THREAD_MODE) * (p->i + 1)))
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
	return (NULL);
}

void	render_thread(t_frac *frac, t_pix pix)
{
	t_thread_ptr	p;
    pthread_t		*t;
	int				i;

	p.frac = frac;
	p.pix = pix;
    t = malloc(sizeof(pthread_t) * (THREAD_MODE));
	i = 0;
	while (i < (THREAD_MODE))
	{
		p.i = i;
		pthread_create(&t[i], NULL, thread_op, (void *)&p);
		i++;
	}
	i = 0;
	while (i < (THREAD_MODE))
	{
		pthread_join(t[i], NULL);
		i++;
	}
}
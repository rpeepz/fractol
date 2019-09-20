/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 13:14:09 by rpapagna          #+#    #+#             */
/*   Updated: 2019/09/19 14:35:52 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

t_frac			*fracdel(t_frac *frac)
{
	if (frac->window != NULL)
		mlx_destroy_window(frac->mlx, frac->window);
	if (frac->in != NULL)
		ft_memdel((void **)&frac->in);
	if (frac->image != NULL)
		del_image(frac, frac->image);
	ft_memdel((void **)&frac);
	return (NULL);
}

t_frac		*init(char *title)
{
	t_frac	*frac;

	if (!(frac = ft_memalloc(sizeof(t_frac))))
		return (NULL);
	if (!(frac->mlx = mlx_init()) ||
		!(frac->window = mlx_new_window(frac->mlx, WIDTH, HEIGHT, title)) ||
		!(frac->in = ft_memalloc(sizeof(t_input))) ||
		!(frac->cam = ft_memalloc(sizeof(t_cam))) ||
		!(frac->image = new_image(frac)))
		return (fracdel(frac));
	frac->cam->x = 0.8;
	frac->cam->y = 0.0;
	frac->cam->scale = 32;
	frac->cam->offsetx = WIDTH / 2;
	frac->cam->offsety = HEIGHT / 2;
	return (frac);
}

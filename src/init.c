/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 13:14:09 by rpapagna          #+#    #+#             */
/*   Updated: 2019/09/23 22:56:49 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

t_image		*new_image(t_frac *frac)
{
	t_image		*img;

	if (!(img = ft_memalloc(sizeof(t_image))))
		return (NULL);
	if (!(img->image = mlx_new_image(frac->mlx, WIDTH, HEIGHT)))
		return (del_image(frac, img));
	img->ptr = mlx_get_data_addr(img->image, &img->bpp, &img->stride,
			&img->endian);
	img->bpp /= 8;
	return (img);
}

void		init_pix(t_pix *pix)
{
	pix->w = 5;
	pix->h = (pix->w * HEIGHT) / WIDTH;
	pix->xmin = -(pix->w / 2);
	pix->ymin = -(pix->h / 2);
	pix->xmax = pix->xmin + pix->w;
	pix->ymax = pix->ymin + pix->h;
}

t_frac		*del_frac(t_frac *frac)
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

t_image		*del_image(t_frac *frac, t_image *img)
{
	if (img != NULL)
	{
		if (img->image != NULL)
			mlx_destroy_image(frac->mlx, img->image);
		ft_memdel((void **)&img);
	}
	return (NULL);
}

t_frac		*init(char *title, int type)
{
	t_frac	*frac;

	if (!(frac = ft_memalloc(sizeof(t_frac))))
		return (NULL);
	if (!(frac->mlx = mlx_init()) ||
		!(frac->window = mlx_new_window(frac->mlx, WIDTH, HEIGHT, title)) ||
		!(frac->in = ft_memalloc(sizeof(t_input))) ||
		!(frac->image = new_image(frac)) ||
		!(frac->cam = ft_memalloc(sizeof(t_cam))) ||
		!(frac->palette = ft_memalloc(sizeof(t_palette))) ||
		!(frac->psych = ft_memalloc(sizeof(t_psych *) * 11)))
		return (del_frac(frac));
	frac->psych[10] = NULL;
	set_palettes(frac, 0);
	frac->type = type;
	frac->max_i = 60;
	frac->in->mx = ((WIDTH * 70) / 100);
	frac->in->my = ((HEIGHT * 30) / 100);
	frac->cam->offsetx = WIDTH / 2;
	frac->cam->offsety = HEIGHT / 2;
	frac->cam->zoom = 1.01;
	return (frac);
}

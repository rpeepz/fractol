/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 13:14:09 by rpapagna          #+#    #+#             */
/*   Updated: 2019/09/26 00:49:44 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void			init_pix(t_pix *pix, t_frac *frac)
{
	pix->w = 5;
	pix->h = (pix->w * HEIGHT) / WIDTH;
	pix->xmin = -(pix->w / 2);
	pix->ymin = -(pix->h / 2);
	pix->xmax = pix->xmin + pix->w;
	pix->ymax = pix->ymin + pix->h;
	pix->xmin = pix->xmin - (WIDTH / 2) + frac->cam->offsetx;
	pix->ymin = pix->ymin - (HEIGHT / 2) + frac->cam->offsety;
	pix->xmax = pix->xmax - (WIDTH / 2) + frac->cam->offsetx;
	pix->ymax = pix->ymax - (HEIGHT / 2) + frac->cam->offsety;
}

static t_image	*new_image(t_frac *frac)
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

t_image			*del_image(t_frac *frac, t_image *img)
{
	if (img != NULL)
	{
		if (img->image != NULL)
			mlx_destroy_image(frac->mlx, img->image);
		ft_memdel((void **)&img);
	}
	return (NULL);
}

t_frac			*del_frac(t_frac **fractol, int i)
{
	t_frac	*frac;

	frac = *fractol;
	if (i)
		i = del_palettes(fractol);
	while (i < 10)
		IF_THEN(frac->psych[i], ft_memdel((void **)&frac->psych[i++]));
	IF_THEN(frac->psych, free(frac->psych));
	IF_THEN(frac->palette, ft_memdel((void **)&frac->palette));
	IF_THEN(frac->cam != NULL, ft_memdel((void **)&frac->cam));
	IF_THEN(frac->image != NULL, del_image(frac, frac->image));
	IF_THEN(frac->in != NULL, ft_memdel((void **)&frac->in));
	IF_THEN(frac->win != NULL, mlx_destroy_window(frac->mlx, frac->win));
	IF_THEN(frac->mlx != NULL, ft_memdel((void **)&frac->mlx));
	ft_memdel((void **)&frac);
	return (NULL);
}

t_frac			*init(char *title, int type)
{
	t_frac	*frac;

	if (!(frac = ft_memalloc(sizeof(t_frac))))
		return (NULL);
	if (!(frac->mlx = mlx_init()) ||
		!(frac->win = mlx_new_window(frac->mlx, WIDTH, HEIGHT, title)) ||
		!(frac->in = ft_memalloc(sizeof(t_input))) ||
		!(frac->image = new_image(frac)) ||
		!(frac->cam = ft_memalloc(sizeof(t_cam))) ||
		!(frac->palette = ft_memalloc(sizeof(t_palette))) ||
		!(frac->psych = ft_memalloc(sizeof(t_psych *) * 11)))
		return (del_frac(&frac, 0));
	frac->psych[10] = NULL;
	if (set_palettes(frac, 0))
		return (del_frac(&frac, 1));
	frac->type = type;
	frac->max_i = 60;
	frac->in->mx = ((WIDTH * 70) / 100);
	frac->in->my = ((HEIGHT * 30) / 100);
	frac->cam->offsetx = WIDTH / 2;
	frac->cam->offsety = HEIGHT / 2;
	frac->cam->zoom = 1.01;
	return (frac);
}

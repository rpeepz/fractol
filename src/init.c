/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 13:14:09 by rpapagna          #+#    #+#             */
/*   Updated: 2019/09/22 04:57:03 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

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

t_image			*new_image(t_frac *frac)
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

void			new_palette(t_frac *frac)
{
	frac->palette = malloc(sizeof(t_palette));
	frac->palette->color[0] = 0;
	frac->palette->color[1] = 100;
	frac->palette->color[2] = 180;
	frac->palette->next = malloc(sizeof(t_palette));
	frac->palette->next->color[0] = 150;
	frac->palette->next->color[1] = 150;
	frac->palette->next->color[2] = 150;
	frac->palette->next->next = malloc(sizeof(t_palette));
	frac->palette->next->next->color[0] = 0;
	frac->palette->next->next->color[1] = 130;
	frac->palette->next->next->color[2] = 100;
	frac->palette->next->next->next = malloc(sizeof(t_palette));
	frac->palette->next->next->next->color[0] = 20;
	frac->palette->next->next->next->color[1] = 0;
	frac->palette->next->next->next->color[2] = 180;
	frac->palette->next->next->next->next = frac->palette;
}

t_frac			*init(char *title, int type)
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
	new_palette(frac);
	frac->type = type;
	frac->in->mx = WIDTH / 2;
	frac->in->my = HEIGHT / 2;
	frac->cam->x = 0.0;
	frac->cam->y = 0.0;
	frac->cam->scale = 0;
	frac->cam->zoom = 0.5;
	frac->cam->offsetx = 0.0;
	frac->cam->offsety = 0.0;
	return (frac);
}

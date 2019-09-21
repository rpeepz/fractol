/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 13:14:09 by rpapagna          #+#    #+#             */
/*   Updated: 2019/09/21 16:50:39 by rpapagna         ###   ########.fr       */
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

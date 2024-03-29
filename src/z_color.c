/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_color.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 20:35:44 by rpapagna          #+#    #+#             */
/*   Updated: 2019/09/26 00:52:19 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

int			rbg_color(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

static void	set_psych1(t_frac *frac)
{
	frac->psych[0]->color[0] = 41;
	frac->psych[0]->color[1] = 44;
	frac->psych[0]->color[2] = 232;
	frac->psych[1]->color[0] = 242;
	frac->psych[1]->color[1] = 187;
	frac->psych[1]->color[2] = 7;
	frac->psych[2]->color[0] = 175;
	frac->psych[2]->color[1] = 7;
	frac->psych[2]->color[2] = 242;
	frac->psych[3]->color[0] = 52;
	frac->psych[3]->color[1] = 242;
	frac->psych[3]->color[2] = 7;
	frac->psych[4]->color[0] = 242;
	frac->psych[4]->color[1] = 7;
	frac->psych[4]->color[2] = 7;
}

static void	set_psych2(t_frac *frac)
{
	frac->psych[5]->color[0] = 33;
	frac->psych[5]->color[1] = 6;
	frac->psych[5]->color[2] = 165;
	frac->psych[6]->color[0] = 244;
	frac->psych[6]->color[1] = 239;
	frac->psych[6]->color[2] = 100;
	frac->psych[7]->color[0] = 174;
	frac->psych[7]->color[1] = 95;
	frac->psych[7]->color[2] = 175;
	frac->psych[8]->color[0] = 21;
	frac->psych[8]->color[1] = 124;
	frac->psych[8]->color[2] = 77;
	frac->psych[9]->color[0] = 219;
	frac->psych[9]->color[1] = 139;
	frac->psych[9]->color[2] = 10;
}

int			set_palettes(t_frac *frac, int i)
{
	frac->palette->color[0] = 100;
	frac->palette->color[1] = 100;
	frac->palette->color[2] = 100;
	if (!(frac->palette->next = ft_memalloc(sizeof(t_palette))))
		return (1);
	frac->palette->next->color[1] = 160;
	frac->palette->next->color[2] = 160;
	if (!(frac->palette->next->next = ft_memalloc(sizeof(t_palette))))
		return (1);
	frac->palette->next->next->color[0] = 130;
	frac->palette->next->next->color[1] = 100;
	if (!(frac->palette->next->next->next = ft_memalloc(sizeof(t_palette))))
		return (1);
	frac->palette->next->next->next->color[0] = 60;
	frac->palette->next->next->next->color[2] = 120;
	frac->palette->next->next->next->next = frac->palette;
	while (i < 10)
		if (!(frac->psych[i++] = ft_memalloc(sizeof(t_psych))))
			return (1);
	set_psych1(frac);
	set_psych2(frac);
	return (0);
}

int			del_palettes(t_frac **fractol)
{
	t_frac	*frac;

	frac = *fractol;
	IF_THEN(frac->palette->next->next->next,
		ft_memdel((void **)&frac->palette->next->next->next));
	IF_THEN(frac->palette->next->next,
		ft_memdel((void **)&frac->palette->next->next));
	IF_THEN(frac->palette->next, ft_memdel((void **)&frac->palette->next));
	return (0);
}

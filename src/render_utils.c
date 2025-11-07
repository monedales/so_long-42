/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mona <mona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:15:00 by mona              #+#    #+#             */
/*   Updated: 2025/11/07 12:54:49 by mona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	put_pixel(t_sprite *frame, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= frame->width || y < 0 || y >= frame->height)
		return ;
	dst = frame->addr + (y * frame->line_len + x * (frame->bpp / 8));
	*(unsigned int *)dst = color;
}

static int	get_pixel_color(t_sprite *sprite, int x, int y)
{
	char	*src;

	if (x < 0 || x >= sprite->width || y < 0 || y >= sprite->height)
		return (TRANSPARENT_COLOR);
	src = sprite->addr + (y * sprite->line_len + x * (sprite->bpp / 8));
	return (*(int *)src);
}

void	draw_sprite_opaque(t_sprite *frame, t_sprite *sprite, int px, int py)
{
	int		x;
	int		y;
	int		color;

	y = 0;
	while (y < sprite->height)
	{
		x = 0;
		while (x < sprite->width)
		{
			color = get_pixel_color(sprite, x, y);
			put_pixel(frame, px + x, py + y, color);
			x++;
		}
		y++;
	}
}

void	draw_sprite_to_frame(t_sprite *frame, t_sprite *sprite, int px, int py)
{
	int		x;
	int		y;
	int		color;

	y = 0;
	while (y < sprite->height)
	{
		x = 0;
		while (x < sprite->width)
		{
			color = get_pixel_color(sprite, x, y);
			if (color != TRANSPARENT_COLOR)
				put_pixel(frame, px + x, py + y, color);
			x++;
		}
		y++;
	}
}

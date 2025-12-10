/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mona <mona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:15:00 by mona              #+#    #+#             */
/*   Updated: 2025/12/10 14:38:36 by mona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Draws a single pixel to the frame buffer.
 *
 * Low-level function that writes a color value directly to the frame
 * buffer at the specified pixel coordinates. Performs boundary checking
 * to prevent writing outside the frame buffer. This function directly
 * manipulates the image data using pointer arithmetic based on the
 * frame's line length and bits per pixel.
 * 
 * @param frame Pointer to the frame buffer sprite structure.
 * @param x The x-coordinate of the pixel (in pixels, not grid).
 * @param y The y-coordinate of the pixel (in pixels, not grid).
 * @param color The color value to write (in RGB format).
 */
void	put_pixel(t_sprite *frame, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= frame->width || y < 0 || y >= frame->height)
		return ;
	dst = frame->addr + (y * frame->line_len + x * (frame->bpp / 8));
	*(unsigned int *)dst = color;
}

/**
 * @brief Retrieves the color of a pixel from a sprite.
 *
 * Reads the color value at the specified coordinates from a sprite's
 * image data. Performs boundary checking and returns the transparent
 * color (magenta #FF00FF) if the coordinates are out of bounds.
 * This helper function is used during sprite rendering to sample colors.
 * 
 * @param sprite Pointer to the sprite to read from.
 * @param x The x-coordinate within the sprite.
 * @param y The y-coordinate within the sprite.
 *
 * @return The color value at (x, y), or TRANSPARENT_COLOR if out of bounds.
 */
static int	get_pixel_color(t_sprite *sprite, int x, int y)
{
	char	*src;

	if (x < 0 || x >= sprite->width || y < 0 || y >= sprite->height)
		return (TRANSPARENT_COLOR);
	src = sprite->addr + (y * sprite->line_len + x * (sprite->bpp / 8));
	return (*(int *)src);
}

/**
 * @brief Draws a sprite to the frame buffer without transparency.
 *
 * Copies all pixels from a sprite to the frame buffer at the specified
 * position, including transparent pixels. This is used for backgrounds
 * or tiles that should completely overwrite what's behind them.
 * Every pixel from the sprite is written to the frame, creating an
 * opaque rectangular copy.
 * 
 * @param frame Pointer to the destination frame buffer.
 * @param sprite Pointer to the source sprite to draw.
 * @param px The x-coordinate in the frame where the sprite's top-left starts.
 * @param py The y-coordinate in the frame where the sprite's top-left starts.
 */
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

/**
 * @brief Draws a sprite to the frame buffer with transparency support.
 *
 * Copies pixels from a sprite to the frame buffer while respecting
 * transparency. Pixels matching the TRANSPARENT_COLOR (magenta #FF00FF)
 * are skipped, allowing the background to show through. This is the
 * primary rendering function for game objects like the player, collectibles,
 * exit, and platforms that need to be layered over the background.
 * 
 * @param frame Pointer to the destination frame buffer.
 * @param sprite Pointer to the source sprite to draw.
 * @param px The x-coordinate in the frame where the sprite's top-left starts.
 * @param py The y-coordinate in the frame where the sprite's top-left starts.
 */
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

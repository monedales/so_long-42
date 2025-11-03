/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maria-ol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:18:25 by maria-ol          #+#    #+#             */
/*   Updated: 2025/11/03 15:47:17 by maria-ol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
	{
		write(2, "Error\nusage: ./so_long <map.ber>\n", 33);
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening map");
		return (1);
	}
	write(1, "Map loaded successfully (test only)\n", 36);
	close(fd);
	return (0);
}

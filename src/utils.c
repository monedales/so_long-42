/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mona <mona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 18:17:46 by mona              #+#    #+#             */
/*   Updated: 2025/11/04 19:18:34 by mona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**ft_append_line(char **map, char *line, int count)
{
	char	**new_map;
	int		i;

	new_map = ft_calloc(count + 2, sizeof(char *)); // +1 pra nova linha, +1 pra NULL
	if (!new_map)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_map[i] = map[i];
		i++;
	}
	new_map[count] = ft_strdup(line); // duplica a linha
	if (!new_map[count])
		return (NULL);
	free(map); // libera o array antigo (não as strings dentro dele!)
	return (new_map);
}

int	has_valid_counts(char **map)
{
	int	i;
	int	j;
	int	p_count;
	int	e_count;
	int	c_count;

	p_count = 0;
	e_count = 0;
	c_count = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P')
				p_count++;
			else if (map[i][j] == 'E')
				e_count++;
			else if (map[i][j] == 'C')
				c_count++;
			j++;
		}
		i++;
	}
	return (p_count == 1 && e_count == 1 && c_count >= 1);
}

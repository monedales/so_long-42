/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maria-ol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 18:17:46 by mona              #+#    #+#             */
/*   Updated: 2025/11/05 15:00:20 by maria-ol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	has_ber_extension(const char *filename)
{
	size_t	len;

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	if (ft_strncmp(filename + len - 4, ".ber", 4) == 0)
		return (1);
	return (0);
}

char	**ft_append_line(char **map, char *line, int count)
{
	char	**new_map;
	int		i;

	new_map = ft_calloc(count + 2, sizeof(char *));
	if (!new_map)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_map[i] = map[i];
		i++;
	}
	new_map[count] = ft_strdup(line);
	if (!new_map[count])
		return (NULL);
	free(map);
	return (new_map);
}

static void	count_elements(char c, int *p, int *e, int *coll)
{
	if (c == 'P')
		(*p)++;
	else if (c == 'E')
		(*e)++;
	else if (c == 'C')
		(*coll)++;
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
			count_elements(map[i][j], &p_count, &e_count, &c_count);
			j++;
		}
		i++;
	}
	return (p_count == 1 && e_count == 1 && c_count >= 1);
}

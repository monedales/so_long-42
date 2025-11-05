/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_path_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maria-ol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:00:00 by maria-ol          #+#    #+#             */
/*   Updated: 2025/11/05 14:51:57 by maria-ol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_visited_partial(char **visited, int until)
{
	while (until > 0)
		free(visited[--until]);
	free(visited);
}

char	**create_visited_map(int width, int height)
{
	char	**visited;
	int		i;

	visited = ft_calloc(height + 1, sizeof(char *));
	if (!visited)
		return (NULL);
	i = 0;
	while (i < height)
	{
		visited[i] = ft_calloc(width + 1, sizeof(char));
		if (!visited[i])
		{
			free_visited_partial(visited, i);
			return (NULL);
		}
		i++;
	}
	return (visited);
}

void	free_visited(char **visited)
{
	int	i;

	if (!visited)
		return ;
	i = 0;
	while (visited[i])
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}

int	check_accessible(char **map, char **visited, int height)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (map[i][j])
		{
			if ((map[i][j] == 'C' || map[i][j] == 'E') && !visited[i][j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

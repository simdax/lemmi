/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getnames.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 20:08:04 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/01 20:33:27 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lemmi.h"

void		getnames3(t_array *array, t_node *sol, char *line)
{
	char	**infos;

	infos = ft_strsplit(line, ' ');
	sol->name = ft_strdup(infos[0]);
	sol->x = ft_atoi(infos[1]);
	sol->y = ft_atoi(infos[2]);
	array_add(array, sol, 1);
	ft_free_strsplit(infos);
}

void		getnames2(t_map *map, t_array *array, char *line, int *flag)
{
	static t_node	sol = (t_node){0, 0, 0};
	char			**infos;

	if (line[0] == '#')
	{
		line += 2;
		if (ft_strequ(line, "start"))
			*flag = 1;
		else if (ft_strequ(line, "end"))
			*flag = -1;
	}
	else if (!(infos = ft_strsplit(line, '-'))[1])
	{
		getnames3(array, &sol, line);
		if (!map->start && *flag == 1)
			map->start = sol.name;
		else if (!map->end && *flag == -1)
			map->end = sol.name;
		++(map->salles);
		ft_free_strsplit(infos);
	}
	else
		ft_free_strsplit(infos);
}

t_array		*get_names(t_map *map)
{
	char	*line;
	t_array	*array;
	int		fd;
	int		start_end;

	start_end = 0;
	array = array_new(sizeof(t_node), 8);
	if ((fd = open("config", O_RDONLY)) != -1)
	{
		while (get_next_line(fd, &line) > 0)
		{
			getnames2(map, array, line, &start_end);
			free(line);
		}
	}
	return (array);
}

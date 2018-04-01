/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 21:30:19 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/01 15:56:14 by scornaz          ###   ########.fr       */
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
		if (!map->start && *flag == 1)
			map->start = sol.name;
		else if (!map->end && *flag == -1)
			map->end = sol.name;
		++(map->salles);
		getnames3(array, &sol, line);
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

char		*get_txt(void)
{
	char	*line;
	char	**split_line;
	t_array	*array;
	int		fd;

	array = array_new(1, 4);
	if ((fd = open("config", O_RDONLY)) != -1)
	{
		while (get_next_line(fd, &line) > 0)
		{
			split_line = ft_strsplit(line, '-');
			if (split_line[1])
			{
				array_add(array, line, ft_strlen(line));
				array_add(array, " ", 1);
			}
			ft_free_strsplit(split_line);
			free(line);
		}
	}
	((char*)array->mem)[array->cursor] = 0;
	line = array->mem;
	free(array);
	return (line);
}

t_array		*parse(t_map *map)
{
	int		i;
	char	**connexions;
	t_array	*list;

	i = 0;
	map->connexions = get_txt();
	list = get_names(map);
	connexions = ft_strsplit(map->connexions, ' ');
	hydrate(list, connexions, map->salles);
	ft_free_strsplit(connexions);
	free(map->connexions);
	return (list);
}

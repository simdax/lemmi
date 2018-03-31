/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 21:30:19 by scornaz           #+#    #+#             */
/*   Updated: 2018/03/31 23:55:49 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lemmi.h"

t_array		*hydrate(t_array *list, char **connexions, int salles)
{
	t_node	*node;
	t_node	sol;
	char	**names;
	int		i;
	int		j;

	i = -1;
	while (++i < salles)
	{
		node = ((t_node*)(list->mem) + i);
		node->connexions = array_new(sizeof(char), 4);
		j = 0;
		while (connexions[j])
		{
			names = ft_strsplit(connexions[j], '-');
			if (ft_strequ(names[0], node->name))
			{
				array_add(node->connexions, names[1], ft_strlen(names[1]));
				array_add(node->connexions, "|", 1);
			}
			++j;
		}
	}
	return (list);
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
	else if (!ft_strsplit(line, '-')[1])
	{
		infos = ft_strsplit(line, ' ');
		sol.name = infos[0];
		if (!map->start && *flag == 1)
			map->start = sol.name;
		else if (!map->end && *flag == -1)
			map->end = sol.name;
		++(map->salles);
		sol.x = ft_atoi(infos[1]);
		sol.y = ft_atoi(infos[2]);
		array_add(array, &sol, 1);
	}
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
			getnames2(map, array, line, &start_end);
	}
	return (array);
}

char		*get_txt(void)
{
	char	*line;
	t_array	*array;
	int		fd;

	array = array_new(1, 4);
	if ((fd = open("config", O_RDONLY)) != -1)
	{
		while (get_next_line(fd, &line) > 0)
			if (ft_strsplit(line, '-')[1])
			{
				array_add(array, line, ft_strlen(line));
				array_add(array, " ", 1);
			}
	}
	((char*)array->mem)[array->cursor] = 0;
	return (array->mem);
}

int			main(void)
{
	int		i;
	t_map	map;
	char	**connexions;
	t_array	*list;
	t_node	*nodes;

	map = (t_map){0, 0, 0, get_txt()};
	i = 0;
	list = get_names(&map);
	connexions = ft_strsplit(map.connexions, ' ');
	hydrate(list, connexions, map.salles);
	nodes = ((t_node*)(list->mem));
	printf("%s et %s", map.start, map.end);
	while (i < map.salles)
	{
		printf("name : %s %d et %d\n", nodes->name, nodes->y, nodes->x);
		printf("%d et %d\n",
				nodes->sol_from_start,
				nodes->sol_from_end);
		printf("%s\n", (char*)nodes->connexions->mem);
		++nodes;
		++i;
	}
	array_free(list);
	return (0);
}

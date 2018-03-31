/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 21:30:19 by scornaz           #+#    #+#             */
/*   Updated: 2018/03/31 23:26:54 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lemmi.h"

t_array		*hydrate(char **connexions, int salles)
{
	t_array	*array;
	t_array	*list;
	t_node	sol;
	int		i;
	int		j;

	i = -1;
	list = array_new(sizeof(t_node), 4);
	sol = (t_node){0, 0, 0, 0, 0, 0};
	while (++i < salles)
	{
		sol.connexions = array_new(sizeof(char), 4);
		array_add(list, &sol, 1);
		j = 0;
		while (connexions[j])
		{
			array = ((t_node*)(list->mem))[i].connexions;
			char **names = ft_strsplit(connexions[j], '-');
			char name[2]; name[0] = i + '0'; name[1] = 0;
			if (ft_strequ(names[0], name))
			{
				array_add(array, names[1], ft_strlen(names[1]));
				array_add(array, "|", 1);
			}
			++j;
		}
	}
	return (list);
}

t_node		*get_names(t_map *map)
{
	char	*line;
	char	**infos;
	t_array	*array;
	int		fd;
	t_node  sol;
	int start = 0;
	int end = 0;
	
	array = array_new(sizeof(t_node), 8);
	if ((fd = open("config", O_RDONLY)) != -1)
	{
		while (get_next_line(fd, &line) > 0)
		{
			if (line[0] == '#')
			{
				line += 2;
				if (ft_strequ(line, "start"))
					start = 1;
				else if (ft_strequ(line, "end"))
					end = 1;
			}
			else if (!ft_strsplit(line, '-')[1])
			{
				infos = ft_strsplit(line, ' ');
				sol.name = infos[0];
				if (start)
					map->start = sol.name;
				else if (end)
					map->end = sol.name;
				++(map->salles);
				sol.x = ft_atoi(infos[1]);
				sol.y = ft_atoi(infos[2]);
				array_add(array, &sol, 1);
				start = 0;
				end = 0;
			}
		}
	}
	return (array->mem);	
}

char		*get_txt()
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

char		*rm_char(char *str, char c)
{
	char	*ret;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(str);
	ret = malloc(len + 1);
	while (*str)
	{
		if (*str != c)
			ret[i++] = *str;
		++str;
	}
//	free(str - len - 1);
	ret[i] = 0;
	return (ret);
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
	nodes = get_names(&map);
	connexions = ft_strsplit(map.connexions, ' ');
	printf("%s et %s", map.start, map.end);
//	list = hydrate(connexions, map.salles);
//	nodes = ((t_node*)(list->mem));
	while (i < map.salles)
	{
		printf("name : %s %d et %d\n",
			   nodes->name, nodes->y,
				nodes->x);
		/* printf("%d et %d\n", */
		/* 		nodes->sol_from_start, */
		/* 		nodes->sol_from_end); */
//		printf("%s\n", (char*)nodes->connexions->mem);
		++nodes;
		++i;
	}
//	array_free(list);
	return (0);
}

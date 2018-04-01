/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 21:30:19 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/01 20:39:06 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lemmi.h"

void		multiple_connexions(t_array *array, char *line, char **split_line)
{
	char	*tmp;
	t_array	*inverse_str;

	inverse_str = array_new(1, 8);
	array_add(inverse_str, split_line[1], ft_strlen(split_line[1]));
	array_add(inverse_str, "-", 1);
	array_add(inverse_str, split_line[0], ft_strlen(split_line[0]));
	tmp = inverse_str->mem;
	tmp[inverse_str->cursor] = 0;
	if (array->mem && (ft_strstr(array->mem, line)
					   || ft_strstr(array->mem, tmp)))
		return ;
	array_add(array, line, ft_strlen(line));
	array_add(array, " ", 1);
	array_add(array, tmp, ft_strlen(tmp));
	array_add(array, " ", 1);
	array_free(inverse_str);
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
				multiple_connexions(array, line, split_line);
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

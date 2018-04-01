/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 11:44:44 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/01 13:37:41 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemmi.h"

void	print_nodes(t_array *list, t_map *map)
{
	t_node	*nodes;
	int		i;

	i = 0;
	nodes = ((t_node*)(list->mem));
	printf("%s et %s", map->start, map->end);
	while (i < map->salles)
	{
		printf("name : %s %d et %d\n", nodes->name, nodes->y, nodes->x);
		printf("%d et %d\n",
				nodes->sol_from_start,
				nodes->sol_from_end);
		printf("connexions: %s\n", (char*)nodes->connexions->mem);
		++nodes;
		++i;
	}
}

void	process(t_array *nodes, char *start, char *end)
{
	t_node	*start_node;
	t_node	*end_node;

}

void	free_f(t_array *array)
{
	t_node	*node;
	int		i;

	i = 0;
	node = ((t_node*)array->mem);
	while (i < array->cursor)
	{
		free(node[i].name);
		node[i].name = 0;
		array_free(node[i].connexions);
		node[i].connexions = 0;
//		node = 0;
		++i;
	}
	free(node);
}

int		main(void)
{
	t_array	*nodes;
	t_map	map;

	map = (t_map){0, 0, 0};
	nodes = parse(&map);
	print_nodes(nodes, &map);
	process(nodes, map.start, map.end);
	array_free2(nodes, free_f);
}

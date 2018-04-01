/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 11:44:44 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/01 15:55:06 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemmi.h"

void	transform(void *n, t_array *array)
{
	char	**connexions;
	t_node	*node_ptr;
	int		i;
	t_node	*node;

	i = 0;
	node = n;
	node->connexions_ptr = array_new(sizeof(t_node*), 8);
	connexions = ft_strsplit(node->connexions->mem, '|');
	while (connexions[i])
	{
		printf("%s\n", connexions[i]);
		if ((node_ptr = array_find(array, p_strequ, connexions[i])))
			array_add(node->connexions_ptr, node_ptr, 1);
		++i;
	}
	ft_free_strsplit(connexions);
}

void	process(t_array *nodes, char *start, char *end)
{
	t_node	*start_node;
	t_node	*end_node;

	array_for_each(nodes, transform);
}

int		main(void)
{
	t_array	*nodes;
	t_map	map;

	map = (t_map){0, 0, 0};
	nodes = parse(&map);
	process(nodes, map.start, map.end);
	print_nodes(nodes, &map);
	array_free2(nodes, free_f);
}

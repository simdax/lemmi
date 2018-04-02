/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 11:44:44 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/02 12:09:16 by scornaz          ###   ########.fr       */
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
	connexions = ft_strsplit(node->connexions->mem, '|');
	node->connexions_ptr = array_new(sizeof(t_node*), 8);
	while (connexions[i])
	{
		if ((node_ptr = array_find(array, p_strequ, connexions[i])))
		{
				printf("dans transform %p\n", node_ptr);
				array_add(node->connexions_ptr, &node_ptr, 1);
		}		
		++i;
	}
	ft_free_strsplit(connexions);
}

t_node	*node_find_name(t_node *node, const char *string)
{
	char	**connexions;
	t_node	*match;
	int		i;

	i = 0;
	match = 0;
	connexions = ft_strsplit(node->connexions->mem, '|');
	while (connexions[i])
	{
		if (ft_strequ(string, connexions[i]))
		{
			match = array_at(i, node->connexions_ptr);
			break ;
		}
		++i;
	}
	ft_free_strsplit(connexions);
	return (match);
}

void	search(void *n, void *end, t_array *array)
{
	t_node	*node;

	node = n;
	print_node(node, 0);
	//array_for_each(node->connexions_ptr, print_node);
	if (node_find_name(node, end))
		printf("trouve !");
	else
		array_for_each2(node->connexions_ptr, end, search);
}

void	process(t_array *nodes, char *start, char *end)
{
	t_node		*start_node;
	t_node		*end_node;
	unsigned	i;

	start_node = array_find(nodes, p_strequ, start);
	end_node = array_find(nodes, p_strequ, end);
	if (start_node)
	{
		printf("on commence la recherche !\n");
		search(start_node, end, nodes);
	}
	if (end_node)
	{
		printf("on commence la recherche !\n");
		search(end_node, start, nodes);
	}
}

int		main(void)
{
	t_array	*nodes;
	t_map	map;

	map = (t_map){0, 0, 0};
	nodes = parse(&map);
	array_for_each(nodes, transform);
	printf("start %s et end %s\n", map.start, map.end);
	array_for_each(nodes, print_node);
//	process(nodes, map.start, map.end);
	array_free2(nodes, free_f);
}

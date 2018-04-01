/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 11:44:44 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/01 14:11:49 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemmi.h"

void	p_array_p(void *node, t_array *array)
{
	t_node	*nodes;

	nodes = node;
	printf("name : %s\npos: %d et %d\n", nodes->name, nodes->y, nodes->x);
	printf("solutions: %d et %d\n",
		   nodes->sol_from_start,
		   nodes->sol_from_end);
	printf("connexions: %s\n\\\\\\\n", (char*)nodes->connexions->mem);
}

void	print_nodes(t_array *list, t_map *map)
{
	t_node	*nodes;
	/* int		i; */

	/* i = 0; */
//	nodes = ((t_node*)(list->mem));
	printf("start %s et end %s\n", map->start, map->end);
	array_for_each(list, p_array_p);
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
		array_free(node[i].connexions);
		++i;
	}
	free(node);
}

/* void	find_node(t_array *node, char *start, char *end) */
/* { */
/* 	char	**connexions; */

/* 	connexions = ft_strsplit(node->connexions, "|"); */
/* 	while (connexions) */
/* 	{ */
/* 		if (ft_streq(*connexions, start)) */
/* 			printf("find start!"); */
/* 		else if (ft_streq(*connexions, end)) */
/* 			printf("find end!"); */
/* 		else */
/* 			find_node(); */
/* 		++connexions; */
/* 	}	 */
/* 	ft_free_strsplit(connexions); */
/* } */

void	process(t_array *nodes, char *start, char *end)
{
	t_node	*start_node;
	t_node	*end_node;

	
}


int		main(void)
{
	t_array	*nodes;
	t_map	map;

	map = (t_map){0, 0, 0};
	nodes = parse(&map);
	print_nodes(nodes, &map);
//	process(nodes, map.start, map.end);
	array_free2(nodes, free_f);
}

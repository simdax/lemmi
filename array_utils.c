/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 15:48:12 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/02 14:11:19 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemmi.h"

void		p(void *data, t_array *array)
{
	printf(" %s", (*(t_node**)data)->name);
}

void		print_node(void *n, t_array *array)
{
	t_node	*node;

	node = n;
	printf("name : %s\npos: %d et %d\n", node->name, node->y, node->x);
	printf("solutions: %d et %d\n", node->sol_from_start, node->sol_from_end);
	printf("connexions :");
	if (node->connexions_ptr)
		array_for_each(node->connexions_ptr, p);
	printf("\n\\\\\\\n");
	fflush(stdout);
}

int			p_strequ(void *a, void *b)
{
	return (ft_strequ(((t_node*)a)->name, b));
}

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
			ft_free_strsplit(names);
		}
	}
	return (list);
}

void		free_f(t_array *array)
{
	t_node	*node;
	int		i;

	i = 0;
	node = ((t_node*)array->mem);
	while (i < array->cursor)
	{
		free(node[i].name);
		array_free(node[i].connexions);
		array_free(node[i].connexions_ptr);
		++i;
	}
	free(node);
}

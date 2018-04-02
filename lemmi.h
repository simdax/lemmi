/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemmi.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 21:30:39 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/02 12:54:08 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMMI_H
# define LEMMI_H

# include "libft.h"

typedef struct	s_node {
	char			*name;
	int				x;
	int				y;
	int				sol_from_start;
	int				sol_from_end;
	t_array			*connexions;
	t_array			*connexions_ptr;
}				t_node;

typedef struct	s_map {
	char	*start;
	char	*end;
	int		salles;
	char	*connexions;
	char	*names;
}				t_map;

typedef struct	s_search{
	char	*goal;
	t_array	*memoization;
}				t_search;

void		print_nodes(t_array *list, t_map *map);
void		print_node(void *n, t_array *array);
void		free_f(t_array *array);
t_array		*get_names(t_map *map);
t_array		*hydrate(t_array *list, char **connexions, int salles);
int			p_strequ(void *a, void *b);
t_array		*parse(t_map *map);

#endif

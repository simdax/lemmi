/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemmi.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 21:30:39 by scornaz           #+#    #+#             */
/*   Updated: 2018/04/01 11:27:23 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMMI_H
# define LEMMI_H

# include "libft.h"

typedef struct	s_node {
	char	*name;
	int		x;
	int		y;
	int		sol_from_start;
	int		sol_from_end;
	t_array	*connexions;
}				t_node;

typedef struct	s_map {
	char	*start;
	char	*end;
	int		salles;
	char	*connexions;
	char	*names;
}				t_map;

t_array			*parse(t_map *map);

#endif

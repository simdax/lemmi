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
		printf("%s\n", (char*)nodes->connexions->mem);
		++nodes;
		++i;
	}
}

int		main(void)
{
	t_array	*nodes;
	t_map	map;

	map = (t_map){0, 0, 0};
	nodes = parse(&map);
	print_nodes(nodes, &map);
	array_free(nodes);
}

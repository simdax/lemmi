#include "libft.h"

typedef struct	s_sol {
	int		sol_from_start;
	int		sol_from_end;
	t_array	*connexions;
}				t_sol;

int main()
{
	t_array	*list;
	t_sol	sol;

	list = array_new(sizeof(t_sol), 4);
	sol = (t_sol){0, 0, 0};
	int i = -1;
	int salles=7;
	char **connexions = ft_strsplit("04 06 13 43 52 35 42 21 76 72 74 65", ' ');
	while (++i < 7)
	{
		sol.connexions = array_new(sizeof(char), 4);
		array_add(list, &sol, 1);
		int j = 0;
		while (connexions[j])
		{
			t_array *array;
			array = ((t_sol*)(list->mem))[i].connexions;
			if (connexions[j][0] == (i + '0'))
			{
				printf("match @ %d\n", j);
				array_add(array, &connexions[j][1], 1);
				array_add(array, "|", 1);
			}
//			array_add(array, 0, 1);
			++j;
		}			
	}
	while(--i >= 0)
	{
		t_array *array;
		array = ((t_sol*)(list->mem))[i].connexions;
		printf("%s\n", (char*)array->mem);
	}
	//array_free();
	return (0);
}

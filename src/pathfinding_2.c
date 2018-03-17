/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 03:09:29 by rnugroho          #+#    #+#             */
/*   Updated: 2018/03/17 05:19:36 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int
	**ft_init_tab(int size)
{
	int **tab;
	int i;
	int j;

	i = -1;
	tab = (int **)malloc(sizeof(*tab) * size);
	while (++i < size)
	{
		j = -1;
		tab[i] = (int *)malloc(sizeof(**tab) * size);
		while (++j < size)
			tab[i][j] = 0;
	}
	return (tab);
}

void
	pf_print_tab(int **tab, int row, int col)
{
	int i;
	int j;

	i = 0;
	ft_printf("   ");
	while (i < col)
	{
		ft_printf("%*w%2d%w ", RED, i);
		i++;
	}
	i = 0;
	ft_printf("\n");
	while (i < row)
	{
		j = -1;
		ft_printf("%*w%2d%w ", RED, i);
		while (++j < col)
			ft_printf("%*w%2d%w ", (tab[i][j] == 1 ? GREEN : EOF),
				tab[i][j]);
		ft_printf("\n");
		i++;
	}
}

static int
	get_min_path(int **routetab, int size, int row, int end)
{
	int col;
	int min;
	int node;

	col = 0;
	min = size + 1;
	node = size;
	while (col < size)
	{
		if (routetab[row][col] == 1 &&
			routetab[end][col] < min)
		{
			min = routetab[end][col];
			node = col;
		}
		col++;
	}
	return (node);
}

static int
	in_solutions(t_array *sol, int node)
{
	int i;

	i = 0;
	while (i < (int)sol->size)
	{
		if (ARRAY_DATA(sol, i) == node)
			return (1);
		i++;
	}
	return (0);
}

/*
** Does not tolerate any intersections
*/

int
	path_finder_1(int ***routetab, int size, t_array *sol, int end)
{
	int node;
	int	temp;

	node = get_min_path(*routetab, size, ARRAY_DATA(sol, sol->size - 1), end);
	if (node == end)
		return (fta_append(sol, &node, 1) || 1);
	while (node < size && (*routetab)[end][node] < size + 1 &&
		!in_solutions(sol, node))
	{
		fta_append(sol, &node, 1);
		temp = (*routetab)[end][node];
		(*routetab)[end][node] = size + 1;
		if (path_finder_1(routetab, size, sol, end))
			return (1);
		fta_popback(sol, 1);
		node = get_min_path(*routetab, size,
				ARRAY_DATA(sol, sol->size - 1), end);
	}
	return (0);
}

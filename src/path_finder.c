/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 03:09:29 by rnugroho          #+#    #+#             */
/*   Updated: 2018/03/13 17:59:17 by rnugroho         ###   ########.fr       */
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

static void
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

int
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

int
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
	path_finder_1(int ***routetab, int size, t_array	*sol, int end)
{
	int node;
	int row;
	int	temp;
	int t_node;

	row = ARRAY_DATA(sol, sol->size - 1);
	node = get_min_path(*routetab, size, row, end);
	if (node == end)
	{
		fta_append(sol, &node, 1);
		return (1);
	}
	while (node < size && (*routetab)[end][node] < size + 1 &&
		!in_solutions(sol, node))
	{
		fta_append(sol, &node, 1);
		temp = (*routetab)[end][node];
		(*routetab)[end][node] = size + 1;
		if (path_finder_1(routetab, size, sol, end))
			return (1);
		fta_popback(sol, 1);
		t_node = node;
		node = get_min_path(*routetab, size, row, end);
		(*routetab)[end][t_node] = temp;
	}
	return (0);
}

/*
** Tolerate intersections but always try to avoid it.
*/

int
	path_finder_2(int ***routetab, int size, t_array	*sol, int end)
{
	int node;
	int row;
	int t_node;

	row = ARRAY_DATA(sol, sol->size - 1);
	node = get_min_path(*routetab, size, row, end);
	if (node == end)
	{
		fta_append(sol, &node, 1);
		return (1);
	}
	while (node < size && (*routetab)[end][node] < size + 1)
	{
		fta_append(sol, &node, 1);
		(*routetab)[row][node] = size + 1;
		if (path_finder_2(routetab, size, sol, end))
			return (1);
		fta_popback(sol, 1);
		t_node = node;
		//update routing table
		node = get_min_path(*routetab, size, row, end);
		(*routetab)[row][t_node] = 1;
	}
	return (0);
}

void
	path_finder_dummy()
{
	int	**routetab;
	int	tab[8][8] = {
		{0, 3, 2, 2, 1, 2, 1, 2},
		{3, 0, 1, 1, 2, 2, 3, 2},
		{2, 1, 0, 2, 1, 1, 2, 1},
		{2, 1, 2, 0, 1, 1, 2, 2},
		{1, 2, 1, 1, 0, 2, 2, 1},
		{2, 2, 1, 1, 2, 0, 3, 2},
		{1, 3, 3, 3, 2, 3, 0, 1},
		{2, 2, 1, 2, 1, 2, 1, 0}};
	int i;
	int j;
	t_array	sol;

	i = -1;
	routetab = ft_init_tab(8);
	while (++i < 8)
	{
		j = -1;
		while (++j < 8)
			routetab[i][j] = tab[i][j];
	}
	int start = 1;
	int end = 0;

	sol = NEW_ARRAY(int);
	fta_append(&sol, &start, 1);
	ft_printfln("First Algorithm:");
	pf_print_tab(routetab, 8, 8);
	while (path_finder_1(&routetab, 8, &sol, end))
	{
		fta_printdata_int(sol);
		pf_print_tab(routetab, 8, 8);
		fta_clear(&sol);
		sol = NEW_ARRAY(int);
		fta_append(&sol, &start, 1);
	}

	i = -1;
	while (++i < 8)
	{
		j = -1;
		while (++j < 8)
			routetab[i][j] = tab[i][j];
	}
	fta_clear(&sol);
	sol = NEW_ARRAY(int);
	fta_append(&sol, &start, 1);
	ft_printfln("Second Algorithm:");
	pf_print_tab(routetab, 8, 8);
	while (path_finder_2(&routetab, 8, &sol, end))
	{
		fta_printdata_int(sol);
		pf_print_tab(routetab, 8, 8);
		fta_clear(&sol);
		sol = NEW_ARRAY(int);
		fta_append(&sol, &start, 1);
	}
}

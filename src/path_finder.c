/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 03:09:29 by rnugroho          #+#    #+#             */
/*   Updated: 2018/03/15 15:52:01 by rnugroho         ###   ########.fr       */
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
	path_finder_1(int ***routetab, int size, t_array *sol, int end)
{
	int node;
	int	temp;
	int t_node;

	node = get_min_path(*routetab, size, ARRAY_DATA(sol, sol->size - 1), end);
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
		node = get_min_path(*routetab, size,
				ARRAY_DATA(sol, sol->size - 1), end);
		(*routetab)[end][t_node] = temp;
	}
	return (0);
}

/*
** Tolerate intersections but always try to avoid it.
*/

int
	path_finder_2(int ***routetab, int size, t_array *sol, int end)
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
	ft_distance(int **connections, int size)
{
	int i;
	int j;
	int col;
	int updated;

	i = -1;
	while (++i < size)
	{
		j = 0;
		while (j < size)
		{
			col = 0;
			updated = 0;
			while (col < size)
			{
				if (connections[j][col] + connections[i][j] < connections[i][col])
				{
					connections[i][col] = connections[j][col] + connections[i][j];
					updated = 1;
				}
				col++;
			}
			j = (updated ? 0 : j + 1);
		}
	}
}

void
	distance_calc_dummy()
{
	int			**routetab;
	int	tab[8][8] = {
		{0, 9, 9, 9, 1, 9, 1, 9},
		{9, 0, 1, 1, 9, 9, 9, 9},
		{9, 1, 0, 9, 1, 1, 9, 1},
		{9, 1, 9, 0, 1, 1, 9, 9},
		{1, 9, 1, 1, 0, 9, 9, 1},
		{9, 9, 1, 1, 9, 0, 1, 9},
		{1, 9, 9, 9, 9, 1, 0, 1},
		{9, 9, 1, 9, 1, 9, 1, 0}};
	int i;
	int j;
	int size = 8;

	i = -1;
	routetab = ft_init_tab(8);
	while (++i < 8)
	{
		j = -1;
		while (++j < 8)
			routetab[i][j] = tab[i][j];
	}
	ft_distance(routetab, size);
	pf_print_tab(routetab, 8, 8);
}

char	*fta_string_(t_array *self, char *(*f)(long))
{
	t_array		ans;
	int			i;
	char		*tmp;

	ans = NEW_ARRAY(char);
	i = 0;
	while (i < (int)self->size)
	{
		tmp = f(((int*)self->data)[i]);
		fta_append(&ans, tmp, ft_strlen(tmp));
		fta_append(&ans, " ", 1);
		i++;
	}
	fta_trim(self);
	return ((char *)ans.data);
}

t_array
	**append_solutions(t_array **sols, int nb_sols, t_array sol)
{
	t_array		**temp;

	temp = (t_array**)malloc(sizeof(t_array*) * nb_sols + 1);
	if (nb_sols > 0)
	{
		ft_memcpy(temp, sols, sizeof(t_array*) * nb_sols);
		free(sols);
	}
	sols = temp;
	sols[nb_sols] = (t_array*)malloc(sizeof(t_array));
	ft_memcpy(sols[nb_sols], &sol, sizeof(t_array));
	sols[nb_sols]->data = (int*)malloc(sizeof(int) * sol.size);
	ft_memcpy(sols[nb_sols]->data, sol.data, sizeof(int) * sol.size);
	return (sols);
}

void
	path_finder_dummy()
{
	int			**routetab;
	const int	tab[8][8] = {
		{0, 3, 2, 2, 1, 2, 1, 2},
		{3, 0, 1, 1, 2, 2, 3, 2},
		{2, 1, 0, 2, 1, 1, 2, 1},
		{2, 1, 2, 0, 1, 1, 2, 2},
		{1, 2, 1, 1, 0, 2, 2, 1},
		{2, 2, 1, 1, 2, 0, 1, 2},
		{1, 3, 3, 3, 2, 1, 0, 1},
		{2, 2, 1, 2, 1, 2, 1, 0}};
	int			i;
	int			j;
	t_array		sol;
	t_array		**sols;
	int			nb_sols;
	t_node 		*nodes;

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
	// int	nb_ants = 5;
	int	nb_room = 8;

	sol = NEW_ARRAY(int);
	fta_append(&sol, &start, 1);
	ft_printfln("First Algorithm:");
	pf_print_tab(routetab, 8, 8);
	nb_sols = 0;
	while (path_finder_1(&routetab, 8, &sol, end))
	{
		fta_printdata_int(&sol);
		pf_print_tab(routetab, 8, 8);
		sols = append_solutions(sols, nb_sols, sol);
		nb_sols++;;
		fta_clear(&sol);
		sol = NEW_ARRAY(int);
		fta_append(&sol, &start, 1);
	}
	i = 0;
	while (i < nb_sols)
	{
		fta_printdata_int(sols[i]);
		i++;
	}
	nodes = (t_node*)malloc(sizeof(t_node) * nb_room);
	nodes[1] = (t_node){1, "Room 1", 23, 5};
	nodes[2] = (t_node){2, "Room 2", 16, 7};
	nodes[3] = (t_node){3, "Room 3", 16, 3};
	nodes[4] = (t_node){4, "Room 4", 16, 5};
	nodes[5] = (t_node){5, "Room 5", 9, 3};
	nodes[6] = (t_node){6, "Room 6", 1, 5};
	nodes[7] = (t_node){7, "Room 7", 4, 7};
	nodes[0] = (t_node){0, "Room 0", 9, 5};
}

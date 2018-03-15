/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 03:09:29 by rnugroho          #+#    #+#             */
/*   Updated: 2018/03/15 20:42:11 by rnugroho         ###   ########.fr       */
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
	solutions_to_cmds(t_array **sols, t_array *cmds, int nb_ants, int nb_sols)
{
	int		col;
	int		row;
	int		offset;
	char	*temp;

	row = 0;
	while (1)
	{
		col = -1;
		offset = 1;
		while (++col < nb_ants)
		{
			if (col % nb_sols == 0)
				offset--;
			if ((offset + row) < 0)
				temp = ft_itoa(((int*)sols[col % nb_sols]->data)[0]);
			else if ((offset + row) > (int)sols[col % nb_sols]->size - 1)
				temp = ft_itoa(((int*)sols[col % nb_sols]->data)[sols[col % nb_sols]->size - 1]);
			else
				temp = ft_itoa(((int*)sols[col % nb_sols]->data)[offset + row]);
			fta_append(cmds, temp, ft_strlen(temp));
			free(temp);
			fta_append(cmds, " ", 1);
		}
		fta_append(cmds, "\n", 1);
		if (offset + row++ == (int)sols[(col - 1) % nb_sols]->size - 1)
			break ;
	};
}

int
	run_path_finder(int **routetab, int size, t_array ***sols, int start, int end)
{
	t_array		sol;
	int			nb_sols;

	nb_sols = 0;
	sol = NEW_ARRAY(int);
	fta_append(&sol, &start, 1);
	while (path_finder_1(&routetab, size, &sol, end))
	{
		*sols = append_solutions((*sols), nb_sols, sol);
		nb_sols++;;
		fta_clear(&sol);
		sol = NEW_ARRAY(int);
		fta_append(&sol, &start, 1);
	}
	fta_clear(&sol);
	return (nb_sols);
}

int			ft_pathfinding(t_lem_in *l)
{
	int			**connections;
	t_node		*rooms;
	t_array		**sols;
	t_array		cmds;
	int			nb_sols;
	int			i;

	if (!(connections = ft_init_table(l)))
		return (-1);
	if (!(rooms = ft_init_rooms(l)))
	{
		ft_free_int_tab(connections, l->nb_rooms);
		return (-1);
	}
	ft_distance(connections, l->nb_rooms);
	nb_sols = run_path_finder(connections, l->nb_rooms, &sols,
	li_get_nodes_index(rooms, l, l->start), li_get_nodes_index(rooms, l, l->end));
	cmds = NEW_ARRAY(char);

	solutions_to_cmds(sols, &cmds, l->nb_ants, nb_sols);
	i = 0;
	while (i < nb_sols)
	{
		fta_clear(sols[i]);
		free(sols[i]);
		i++;
	}
	run_print_map(connections, l->nb_rooms, rooms, cmds);
	fta_clear(&cmds);
	free(sols);
	ft_free_int_tab(connections, l->nb_rooms);
	ft_free_nodes(rooms, l->nb_rooms);
	return (0);
}

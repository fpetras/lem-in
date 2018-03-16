/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 03:09:29 by rnugroho          #+#    #+#             */
/*   Updated: 2018/03/16 09:08:17 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_array	**append_solutions(t_array **sols, int nb_sols, t_array sol)
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

void			solutions_to_cmds(t_array **sols, t_array *cmds,
				int nb_ants, int nb_sols)
{
	int		col;
	int		row;
	int		offset;
	char	*temp;

	row = 0;
	while (row >= 0)
	{
		col = -1;
		offset = 1;
		while (++col < nb_ants)
		{
			offset = (col % nb_sols == 0) ? offset - 1 : offset;
			if ((offset + row) < 0)
				temp = ft_itoa(((int*)sols[col % nb_sols]->data)[0]);
			else 
				temp = ((offset + row) > (int)sols[col % nb_sols]->size - 1) ?
					ft_itoa(((int*)sols[col % nb_sols]->data)[sols[col % nb_sols]->size - 1]) :
					ft_itoa(((int*)sols[col % nb_sols]->data)[offset + row]);
			fta_append_space(cmds, temp);
			free(temp);
		}
		fta_append(cmds, "\n", 1);
		row = (offset + row == (int)sols[(col - 1) % nb_sols]->size - 1) ? -1 : row + 1;
	};
}

int			run_path_finder(int **routetab, int size, t_array ***sols,
			int start, int end)
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

static void	li_print_solutions(t_array a_cmds, t_node *rooms, t_lem_in *l)
{
	int			i;
	int			j;
	char		**cmds;
	char		**icmds;

	i = 0;
	cmds = ft_strsplit(((char*)a_cmds.data), '\n');
	while (cmds[i])
	{
		icmds = ft_strsplit(cmds[i], ' ');
		j = 0;
		if (i > 0)
			ft_printf("\n");
		while (j < ft_wordcounter(cmds[i], ' '))
		{
			if (li_get_nodes_index(rooms, l, l->end) != ft_atoi(icmds[j]) &&
				li_get_nodes_index(rooms, l, l->start) != ft_atoi(icmds[j]))
			ft_printf("L%d-%s ", j + 1, li_get_nodes_name(rooms, l, ft_atoi(icmds[j])));
			j++;
		}
		ft_strtab_free(icmds);
		i++;
	}
	ft_strtab_free(cmds);
}

int			ft_pathfinding(char **map, t_lem_in *l)
{
	int			**connections;
	t_node		*rooms;
	t_array		**sols;
	t_array		cmds;
	int			nb_sols;

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
	if (g_option_v == 1)
		run_print_map(connections, l->nb_rooms, rooms, cmds);
	ft_print_tab(map);
	li_print_solutions(cmds, rooms, l);
	free_sols_cmds(sols, cmds, nb_sols);
	ft_free_int_tab(connections, l->nb_rooms);
	ft_free_nodes(rooms, l->nb_rooms);
	return (0);
}

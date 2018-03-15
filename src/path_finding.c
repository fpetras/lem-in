/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 08:35:09 by fpetras           #+#    #+#             */
/*   Updated: 2018/03/15 20:01:42 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
		i = 0;
	while (i < nb_sols)
	{
		fta_printdata_int(sols[i]);
		i++;
	}
	solutions_to_cmds(sols, &cmds, l->nb_ants, nb_sols);
	run_print_map(connections, l->nb_rooms, rooms, cmds);
	ft_free_int_tab(connections, l->nb_rooms);
	ft_free_nodes(rooms, l->nb_rooms);
	return (0);
}

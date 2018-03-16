/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   route_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 19:54:04 by rnugroho          #+#    #+#             */
/*   Updated: 2018/03/16 08:53:25 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		ft_distance(int **routes, int size)
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
				if (routes[j][col] + routes[i][j] < routes[i][col])
				{
					routes[i][col] = routes[j][col] + routes[i][j];
					updated = 1;
				}
				col++;
			}
			j = (updated) ? 0 : j + 1;
		}
	}
}

static int	ft_connections(int i, int j, t_lem_in *l)
{
	int k;

	k = 0;
	while (l->links[k])
	{
		if (ft_strstr(l->links[k], l->rooms[i]) &&
			ft_strstr(l->links[k], l->rooms[j]))
			return (1);
		k++;
	}
	return (l->nb_rooms + 1);
}

int			**ft_init_table(t_lem_in *l)
{
	int i;
	int j;
	int **connections;

	i = -1;
	if (!(connections = (int**)malloc(sizeof(int*) * l->nb_rooms + 1)))
		return (NULL);
	while (++i < l->nb_rooms)
	{
		j = -1;
		if (!(connections[i] = (int*)malloc(sizeof(int) * l->nb_rooms + 1)))
		{
			free(connections);
			return (NULL);
		}
		while (++j < l->nb_rooms)
		{
			if (i == j)
				connections[i][j] = 0;
			else
				connections[i][j] = ft_connections(i, j, l);
		}
	}
	return (connections);
}

t_node		*ft_init_rooms(t_lem_in *l)
{
	int		i;
	t_node	*rooms;

	i = 0;
	if (!(rooms = (t_node*)malloc(sizeof(t_node) * l->nb_rooms)))
		return (NULL);
	while (i < l->nb_rooms)
	{
		rooms[i].index = i;
		rooms[i].name = ft_strdup(l->rooms[i]);
		ft_add_coordinates(l->rooms[i]);
		rooms[i].col = ft_atoi(&l->rooms[i][ft_1st_coord_index(l->rooms[i])]);
		rooms[i].row = ft_atoi(&l->rooms[i][ft_2nd_coord_index(l->rooms[i])]);
		i++;
	}
	return (rooms);
}

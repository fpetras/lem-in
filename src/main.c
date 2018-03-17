/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 09:34:58 by fpetras           #+#    #+#             */
/*   Updated: 2018/03/17 06:51:26 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int
	ft_init_struct(t_lem_in *l, char **map)
{
	l->i = 0;
	l->j = 0;
	l->k = 0;
	l->nb_ants = 0;
	l->start = NULL;
	l->end = NULL;
	if ((l->nb_rooms = ft_count_rooms(map)) == -1)
		return (-1);
	l->nb_links = ft_count_links(map);
	if ((l->rooms = (char**)malloc(sizeof(char*) * l->nb_rooms + 1)) == NULL)
		return (-1);
	l->rooms[l->nb_rooms] = 0;
	if ((l->links = (char**)malloc(sizeof(char*) * l->nb_links + 1)) == NULL)
	{
		ft_free_tab(l->rooms);
		return (-1);
	}
	l->links[l->nb_links] = 0;
	return (0);
}

static char
	**ft_read_map(void)
{
	char		**map;
	char		**temp;
	char		*line;
	int			n;

	n = 1;
	map = NULL;
	while (get_next_line(g_fd, &line))
	{
		temp = (char**)malloc(sizeof(char*) * n + 1);
		if (n > 1)
		{
			ft_memcpy(temp, map, sizeof(char*) * n);
			temp[n] = NULL;
			free(map);
		}
		map = temp;
		map[n - 1] = (char*)malloc(sizeof(char) * ft_strlen(line) + 1);
		ft_memcpy(map[n - 1], line, sizeof(char) * ft_strlen(line) + 1);
		n++;
		free(line);
	}
	if (g_fd > 0)
		close(g_fd);
	return (map);
}

int
	main(int ac, char **av)
{
	t_lem_in	l;
	char		**map;

	g_option_v = 0;
	g_fd = 0;
	if (ac > 1)
		if (ft_options(ac, av) == -1)
			return (-1);
	if ((map = ft_read_map()) == NULL)
	{
		ft_dprintf(2, "ERROR\n");
		return (-1);
	}
	if (ft_init_struct(&l, map) == -1)
	{
		ft_dprintf(2, "ERROR\n");
		ft_free_tab(map);
		return (-1);
	}
	if (ft_parsing(map, &l) == -1 || ft_pathfinding(map, &l) == -1)
		ft_dprintf(2, "ERROR\n");
	ft_free_tab(map);
	ft_free_struct(&l);
	return (0);
}

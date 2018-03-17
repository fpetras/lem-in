/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 11:01:00 by fpetras           #+#    #+#             */
/*   Updated: 2018/03/17 08:41:40 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

size_t	ft_tablen(char **tab)
{
	size_t len;

	len = 0;
	while (tab[len])
		len++;
	return (len);
}

void	ft_print_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		ft_printf("%s\n", tab[i]);
		i++;
	}
}

int		li_get_nodes_index(t_node *rooms, t_lem_in *l, char *name)
{
	int i;

	i = 0;
	while (i < l->nb_rooms)
	{
		if (ft_strcmp(rooms[i].name, name) == 0)
			break ;
		i++;
	}
	return (rooms[i].index);
}

char	*li_get_nodes_name(t_node *rooms, t_lem_in *l, int index)
{
	int i;

	i = 0;
	while (i < l->nb_rooms)
	{
		if (rooms[i].index == index)
			break ;
		i++;
	}
	return (rooms[i].name);
}

void	fta_append_space(t_array *self, char *data)
{
	fta_append(self, data, ft_strlen(data));
	fta_append(self, " ", 1);
}

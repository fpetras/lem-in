/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 10:26:23 by fpetras           #+#    #+#             */
/*   Updated: 2018/03/22 11:05:09 by fpetras          ###   ########.fr       */
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

void	ft_print_solutions(t_array com, t_node *rooms, t_lem_in *l)
{
	int			i;
	int			j;
	char		**cmds[2];
	int			c;

	i = -1;
	if ((cmds[0] = ft_strsplit(((char*)com.data), '\n')) == NULL)
		return ;
	while (cmds[0][++i])
	{
		cmds[1] = ft_strsplit(cmds[0][i], ' ');
		j = -1;
		c = (i > 0) ? ft_printf("\n") : 0;
		while (++j < ft_wordcounter(cmds[0][i], ' '))
			if (get_prev_node(cmds[0], i, j, 1) != ft_atoi(cmds[1][j]) &&
				get_nodes_index(rooms, l, l->start) != ft_atoi(cmds[1][j]))
			{
				(c++ != 1) ? ft_printf(" ") : 0;
				ft_printf("L%d-%s", j + 1,
					get_nodes_name(rooms, l, ft_atoi(cmds[1][j])));
			}
		ft_strtab_free(cmds[1]);
	}
	ft_printf("\n");
	ft_strtab_free(cmds[0]);
}

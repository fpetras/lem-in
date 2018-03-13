/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 03:09:29 by rnugroho          #+#    #+#             */
/*   Updated: 2018/03/13 04:03:29 by rnugroho         ###   ########.fr       */
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
	pf_print_tab(int **tab)
{
	int i;
	int j;

	i = -1;
	while (++i < 8)
	{
		j = -1;
		while (++j < 8)
			ft_printf("%d ", tab[i][j]);
		ft_printf("\n");
	}	
}

void
	path_finder(int **routingtab)
{
	pf_print_tab(routingtab);
}

void
	path_finder_dummy()
{
	int	**routingtab;
	int	tab[8][8] = {
		{0, 3, 2, 2, 1, 2, 1, 2},
		{3, 0, 1, 1, 2, 2, 3, 2},
		{2, 1, 0, 2, 1, 1, 2, 1},
		{2, 1, 2, 0, 1, 1, 2, 2},
		{1, 2, 1, 1, 0, 2, 2, 1},
		{2, 2, 1, 1, 2, 0, 1, 2},
		{1, 3, 3, 3, 2, 1, 0, 1},
		{2, 2, 1, 2, 1, 2, 1, 0}
		};
	int i;
	int j;

	i = -1;
	routingtab = ft_init_tab(8);
	while (++i < 8)
	{
		j = -1;
		while (++j < 8)
			routingtab[i][j] = tab[i][j];
	}
	path_finder(routingtab);
}

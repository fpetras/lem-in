/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 03:09:29 by rnugroho          #+#    #+#             */
/*   Updated: 2018/03/13 06:07:49 by rnugroho         ###   ########.fr       */
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
	ft_printf("  ");
	while (i < col)
	{
		ft_printf("%*w%d%w ", RED, i);
		i++;
	}
	i = 0;
	ft_printf("\n");
	while (i < row)
	{
		j = -1;
		ft_printf("%*w%d%w ", RED, i);
		while (++j < col)
			ft_printf("%d ", tab[i][j]);
		ft_printf("\n");
		i++;
	}	
}

static void
	pf_print_solutions(t_solution *solutions)
{
	int i;

	i = 0;
	while (solutions[i].paths.data)
	{
		ft_printf("Solution %d: ", i);
		fta_printdata_int(solutions[i].paths);
		ft_printfln("(%d)", solutions[i].weight);
		i++;
	}	
}

int
	pf_solutions_len(t_solution *solutions)
{
	int len;

	len = 0;
	while (solutions[len].paths.data)
		len++;
	return (len);
}

int		pf_resize_solutiontab(t_solution **solutions, size_t new_size)
{
	t_solution	*tmp;

	tmp = (t_solution*)malloc(sizeof(t_solution) * new_size);
	if (tmp == NULL)
		return (1);
	ft_memcpy(tmp, &(**solutions), sizeof(t_solution) * new_size);
	*solutions = tmp;
	return (0);
}

void
	pf_add_solutiontab(t_solution **solutions, t_solution sol)
{
	int len;

	len = pf_solutions_len(*solutions) + 1;
	pf_resize_solutiontab(solutions, len + 1);
	(*solutions)[len - 1] = sol;
	(*solutions)[len] = (t_solution){NEW_ARRAY(int), 0};
}

void
	path_finder(int **routingtab, int size, int start, int end)
{
	t_solution	*solutions;
	t_solution	sol;
	int 		num;

	solutions = (t_solution*)malloc(sizeof(solutions) * 1);
	solutions[0] = (t_solution){NEW_ARRAY(int), 0};

	int row = start;
	int col = 0;
	while (col < size)
	{
		if (routingtab[row][col] == 1)
		{
			sol = (t_solution){NEW_ARRAY(int), 0};
			num = start;
			fta_append(&(sol.paths), &num, 1);
			num = col;
			sol.weight += 1;
			fta_append(&(sol.paths), &num, 1);
			pf_add_solutiontab(&solutions, sol);
		}
		col++;
	}
	pf_print_tab(routingtab, 8, 8);
	pf_print_solutions(solutions);

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
	path_finder(routingtab, 8, 1, 0);
}

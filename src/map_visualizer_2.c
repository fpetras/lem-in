/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_visualizer_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 21:14:17 by rnugroho          #+#    #+#             */
/*   Updated: 2018/03/15 21:15:46 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int
	scale_map_row(t_node *nodes, int size, int row)
{
	int		i;
	int		max_h;
	int		min_h;
	float	sc_row;

	i = 0;
	max_h = 0;
	min_h = nodes[0].row;
	while (i < size)
	{
		if (nodes[i].row > max_h)
			max_h = nodes[i].row;
		if (nodes[i].row < min_h)
			min_h = nodes[i].row;
		i++;
	}
	max_h -= min_h;
	sc_row = ((row - min_h) / (float)max_h) * H;
	return ((int)sc_row);
}

int
	scale_map_col(t_node *nodes, int size, int col)
{
	int		i;
	int		max_w;
	int		min_w;
	float	sc_col;

	i = 0;
	max_w = 0;
	min_w = nodes[0].col;
	while (i < size)
	{
		if (nodes[i].col > max_w)
			max_w = nodes[i].col;
		if (nodes[i].col < min_w)
			min_w = nodes[i].col;
		i++;
	}
	max_w -= min_w;
	sc_col = ((col - min_w) / (float)max_w) * W;
	return ((int)sc_col);
}

t_node
	*scale_map(t_node *nodes, int size)
{
	t_node	*d_nodes;
	int		i;

	d_nodes = (t_node*)malloc(sizeof(t_node) * size);
	ft_memcpy(d_nodes, nodes, sizeof(t_node) * size);
	i = 0;
	while (i < size)
	{
		nodes[i].col = scale_map_col(d_nodes, size, nodes[i].col);
		nodes[i].row = scale_map_row(d_nodes, size, nodes[i].row);
		i++;
	}
	free(d_nodes);
	return (nodes);
}


void
	print_line(t_node l1, t_node l2, int color)
{
	t_node	a;
	t_node	b;
	int		col;
	int		row;

	a = (l1.col >= l2.col ? l1 : l2);
	b = (l1.col < l2.col ? l1 : l2);
	col = b.col;
	if (a.col - b.col > 0)
		while (col < a.col)
		{
			row = b.row + (a.row - b.row) * (col - b.col) / (a.col - b.col);
			ft_printf("%*.*v%*w.%w", row, col++, color);
		}
	else
	{
		a = (l1.row >= l2.row ? l1 : l2);
		b = (l1.row < l2.row ? l1 : l2);
		row = b.row;
		while (row < a.row)
			ft_printf("%*.*v%*w.%w", row++, col, color);
	}
}

void
	print_map(t_node *nodes, int **routetab, int size)
{
	int i;
	int j;

	nodes = scale_map(nodes, size);
	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
			if (routetab[i][j] >= 1)
				print_line(nodes[i], nodes[j], routetab[i][j] - 1);
	}
	i = 0;
	while (i < size)
	{
		ft_printf("%*.*v%*W%s%w", nodes[i].row,nodes[i].col,
		GREEN, nodes[i].name);
		i++;
	}
	ft_printf("%*.*v", H + 1, 0);
}

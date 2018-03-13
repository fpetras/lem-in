/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_visualizer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 18:14:31 by rnugroho          #+#    #+#             */
/*   Updated: 2018/03/13 21:08:51 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#define W 100
#define H 30
#define gotoxy(x,y) ft_printf("\033[%d;%dH", (y), (x))
#define clear() ft_printf("\033[H\033[J")

void
	print_line(t_node l1, t_node l2, int color)
{
	t_node a;
	t_node b;
	int col;
	int row;

	a = (l1.col >= l2.col ? l1 : l2);
	b = (l1.col < l2.col ? l1 : l2);
	col = b.col;
	if (a.col - b.col > 0)
		while (col < a.col)
		{
			row = b.row + (a.row - b.row) * (col - b.col) / (a.col - b.col);
			gotoxy(col, row);
			ft_printf("%*w.%w", color);
			col++;
		}
	else
	{
		a = (l1.row >= l2.row ? l1 : l2);
		b = (l1.row < l2.row ? l1 : l2);
		row = b.row;
		while (row < a.row)
		{
			gotoxy(col, row);
			ft_printf("%*w.%w", color);
			row++;
		}
	}
}

int
	scale_map_row(t_node *nodes, int size, int row)
{
	int i;
	int max_h;
	int min_h;
	float sc_row;

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
	int i;
	int max_w;
	int min_w;
	float sc_col;

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
	*scale_map(t_node *nodes, size)
{
	t_node *d_nodes;
	int i;

	d_nodes = (t_node*)malloc(sizeof(t_node) * size);
	ft_memcpy(d_nodes, nodes, sizeof(t_node) * size);
	i = 0;
	while (i < size)
	{
		nodes[i].col = scale_map_col(d_nodes, size, nodes[i].col);
		nodes[i].row = scale_map_row(d_nodes, size, nodes[i].row);
		i++;
	}
	return (nodes);
}

void
	print_map(t_node *nodes, int **routetab, int size)
{
	int i;
	int j;

	nodes = scale_map(nodes, size);
	clear();
	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
			if (routetab[i][j] == 1)
				print_line(nodes[i], nodes[j], EOC);
	}
	i = 0;
	while (i < 8)
	{
		gotoxy(nodes[i].col, nodes[i].row);
		ft_printf("%*W%s%w", GREEN, nodes[i].name);
		i++;
	}
	gotoxy(W, H);
}

void
	print_map_dummy()
{
	t_node *nodes;
	int size;
	int	**routetab;
	int	tab[8][8] = {
		{0, 3, 2, 2, 1, 2, 1, 2},
		{3, 0, 1, 1, 2, 2, 3, 2},
		{2, 1, 0, 2, 1, 1, 2, 1},
		{2, 1, 2, 0, 1, 1, 2, 2},
		{1, 2, 1, 1, 0, 2, 2, 1},
		{2, 2, 1, 1, 2, 0, 1, 2},
		{1, 3, 3, 3, 2, 1, 0, 1},
		{2, 2, 1, 2, 1, 2, 1, 0}};
	int i;
	int j;

	size = 8;
	i = -1;
	routetab = ft_init_tab(8);
	while (++i < size)
	{
		j = -1;
		while (++j < size)
			routetab[i][j] = tab[i][j];
	}
	nodes = (t_node*)malloc(sizeof(t_node) * size);
	
	nodes[1] = (t_node){1, "1", 23, 3};
	nodes[2] = (t_node){2, "2", 16, 7};
	nodes[3] = (t_node){3, "3", 16, 3};
	nodes[4] = (t_node){4, "4", 16, 5};
	nodes[5] = (t_node){5, "5", 9, 3};
	nodes[6] = (t_node){6, "6", 1, 5};
	nodes[7] = (t_node){7, "7", 4, 8};
	nodes[0] = (t_node){0, "0", 9, 5};

	print_map(nodes, routetab, size);
}
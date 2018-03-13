/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_visualized.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 18:14:31 by rnugroho          #+#    #+#             */
/*   Updated: 2018/03/13 20:10:16 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#define W 100
#define H 30

void
	print_map(t_node *nodes)
{
	int row;
	int col;

	row = 0;
	while (row < H)
	{
		col = 0;
		while (col < W)
		{
			ft_printf(" ");
			col++;
		} 
		row++;
		ft_printf("\n");
	}
}

#define gotoxy(x,y) ft_printf("\033[%d;%dH", (y), (x))
#define clear() ft_printf("\033[H\033[J")

void
	print_line(t_node l1, t_node l2)
{
	t_node a;
	t_node b;

	a = (l1.col >= l2.col ? l1 : l2);
	b = (l1.col < l2.col ? l1 : l2);
	int dcol = a.col - b.col;
	int drow = a.row - b.row;
	int col = b.col;
	int row;
	if (dcol > 0)
		while (col < a.col)
		{
			row = b.row + drow * (col - b.col) / dcol;
			gotoxy(col, row);
			ft_printf(".");
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
			ft_printf(".");
			row++;
		}
	}
}

void
	print_map_dummy()
{
	t_node *nodes;

	nodes = (t_node*)malloc(sizeof(t_node) * 8);
	nodes[1] = (t_node){1, "1", 23, 3};
	nodes[2] = (t_node){2, "2", 16, 7};
	nodes[3] = (t_node){3, "3", 16, 3};
	nodes[4] = (t_node){4, "4", 16, 5};
	nodes[5] = (t_node){5, "5", 9, 3};
	nodes[6] = (t_node){6, "6", 1, 5};
	nodes[7] = (t_node){7, "7", 4, 8};
	nodes[0] = (t_node){0, "0", 9, 5};
	clear();
	print_map(nodes);
	int i;
	int max_w;
	int max_h;
	int min_w;
	int min_h;
	i = 0;
	max_w = 0;
	max_h = 0;
	min_w = nodes[0].col;
	min_h = nodes[0].row;
	while (i < 8)
	{
		if (nodes[i].col > max_w)
			max_w = nodes[i].col;
		if (nodes[i].row > max_h)
			max_h = nodes[i].row;
		if (nodes[i].col < min_w)
			min_w = nodes[i].col;
		if (nodes[i].row < min_h)
			min_h = nodes[i].row;
		i++;
	}
	i = 0;
	max_w -= min_w;
	max_h -= min_h;
	while (i < 8)
	{
		float sc_col = ((nodes[i].col - min_w) / (float)max_w) * W;
		float sc_row = ((nodes[i].row - min_h) / (float)max_h) * H;
		nodes[i].col = (int)sc_col;
		nodes[i].row = (int)sc_row;
		i++;
	}
	print_line(nodes[1], nodes[3]);
	print_line(nodes[1], nodes[2]);
	print_line(nodes[2], nodes[7]);
	print_line(nodes[2], nodes[4]);
	print_line(nodes[2], nodes[5]);
	print_line(nodes[3], nodes[4]);
	print_line(nodes[3], nodes[5]);
	print_line(nodes[4], nodes[0]);
	print_line(nodes[4], nodes[7]);
	print_line(nodes[5], nodes[6]);
	print_line(nodes[6], nodes[0]);
	print_line(nodes[6], nodes[7]);
	print_line(nodes[4], nodes[4]);
	i = 0;
	while (i < 8)
	{
		gotoxy(nodes[i].col, nodes[i].row);
		ft_printf("%*W%s%w", GREEN, nodes[i].name);
		i++;
	}
	gotoxy(W, H);
}
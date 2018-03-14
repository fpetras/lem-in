/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_visualizer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 18:14:31 by rnugroho          #+#    #+#             */
/*   Updated: 2018/03/14 01:40:52 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#define W 100
#define H 30

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
			ft_printf("%*.*v%*w.%w", row, col, color);
			col++;
		}
	else
	{
		a = (l1.row >= l2.row ? l1 : l2);
		b = (l1.row < l2.row ? l1 : l2);
		row = b.row;
		while (row < a.row)
		{
			ft_printf("%*.*v%*w.%w", row, col, color);
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
	*scale_map(t_node *nodes, int size)
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
	ft_printf("\033[H\033[J");
	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
			if (routetab[i][j] >= 1)
				print_line(nodes[i], nodes[j], routetab[i][j] - 1);
	}
	i = 0;
	while (i < 8)
	{
		ft_printf("%*.*v%*W%s%w", nodes[i].row, nodes[i].col, GREEN, nodes[i].name);
		i++;
	}
	ft_printf("%*.*v", H + 1, 0);
}

int
	mv_get_node(char *cmd)
{
	char 	*ptr;
	int		value;

	ptr = cmd;
	while (*ptr)
	{
		if (*ptr == '-')
			break ;
		ptr++;
	}
	ptr++;
	value = ft_atoi(ptr);
	return (value);
}

int
	mv_get_prev_node(char **cmd, int i, int start)
{
	if (i == 0)
		return (start);
	else
		return (mv_get_node(cmd[i - 1]));
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
	int c;
	int node1;
	int node2;
	char **cmds;

	size = 8;
	i = -1;
	routetab = ft_init_tab(8);
	while (++i < size)
	{
		j = -1;
		while (++j < size)
		if (tab[i][j] == 1)
			routetab[i][j] = tab[i][j];
		else
			routetab[i][j] = 0;
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

	cmds = (char**)malloc(sizeof(char*) * 4);
	cmds[0] = ft_strdup("L1-2");
	cmds[1] = ft_strdup("L1-4");
	cmds[2] = ft_strdup("L1-0");
	cmds[3] = NULL;
	c = 0;
	
	while(cmds[c])
	{
		node1 = mv_get_prev_node(cmds, c, 1);
		node2 = mv_get_node(cmds[c]);
		i = -1;
		while (++i < size)
		{
			j = -1;
			while (++j < size)
			{
				if ((i == node1 && j == node2) ||
					(i == node2 && j == node1))
					routetab[i][j] += 1;

				else	if (routetab[i][j] >= 1)
					 routetab[i][j] = 1;
			}
		}
		print_map(nodes, routetab, size);
		node1 = node2;
		c++;
		system("sleep 1");
	}
	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
		{
			if (routetab[i][j] >= 1)
				routetab[i][j] = 1;
		}
	}
	print_map(nodes, routetab, size);
}
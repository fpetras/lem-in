/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_visualizer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 18:14:31 by rnugroho          #+#    #+#             */
/*   Updated: 2018/03/15 21:10:28 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#define W 100
#define H 25

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

int
	mv_get_prev_node(char **cmd, int i, int j, int start)
{
	char 	**icmds;
	int		value;

	if (i == 0)
		return (start);
	else
	{
		icmds = ft_strsplit(cmd[i - 1], ' ');
		if (j >= ft_wordcounter(cmd[i - 1], ' '))
			j = 0;
		value = ft_atoi(icmds[j]);
		ft_strtab_free(icmds);
		return (value);
	}
}

void
	reset_map(int ***routetab, int size)
{
	int i;
	int j;

	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
		{
			if ((*routetab)[i][j] >= 1)
				(*routetab)[i][j] = 1;
		}
	}
}

void
	color_map(int ***routetab, int size, int node1, int node2)
{
	int i;
	int j;

	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
		{
			if ((i == node1 && j == node2) ||
				(i == node2 && j == node1))
			{
				(*routetab)[i][j] += 1;
				if ((*routetab)[i][j] > 3)
					(*routetab)[i][j] = 2;
			}
		}
	}
}

void
	run_print_map(int **routetab, int size, t_node *nodes, t_array a_cmds)
{
	int			i;
	int			j;
	int			node1;
	int			node2;
	char		**cmds;
	char		**icmds;

	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
			if (routetab[i][j] == 1 || routetab[j][i] == 1)
			{
				routetab[i][j] = 1;
				routetab[j][i] = 1;
			}
			else
				routetab[i][j] = 0;
	}
	i = 0;
	cmds = ft_strsplit(((char*)a_cmds.data), '\n');
	while (cmds[i])
	{
		icmds = ft_strsplit(cmds[i], ' ');
		j = 0;
		while (j < ft_wordcounter(cmds[i], ' '))
		{
			node1 = mv_get_prev_node(cmds, i, j, 1);
			node2 = ft_atoi(icmds[j]);
			color_map(&routetab, size, node1, node2);
			j++;
		}
		ft_strtab_free(icmds);
		ft_printf("\033[H\033[J");
		print_map(nodes, routetab, size);
		system("sleep 0.4");
		i++;
	}
	ft_strtab_free(cmds);
}

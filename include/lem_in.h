/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 09:32:55 by fpetras           #+#    #+#             */
/*   Updated: 2018/03/15 22:01:32 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

# define START	1
# define END	2
# define ROOM	1
# define LINK	2
# define W 100
# define H 25
# define ARRAY_DATA(D, I) ((int*)(D)->data)[I]

typedef struct		s_lem_in
{
	int				i;
	int				j;
	int				k;
	int				nb_ants;
	int				nb_rooms;
	int				nb_links;
	char			*start;
	char			*end;
	char			**rooms;
	char			**links;
}					t_lem_in;

typedef struct		s_node
{
	int				index;
	char			*name;
	int				col;
	int				row;
}					t_node;

int					ft_get_data(char **map, t_lem_in *l);

int					ft_check_empty_lines(char *file);
int					ft_count_rooms(char **map);
int					ft_count_links(char **map);
int					ft_count_spaces(char *line);
int					ft_check_coordinates(t_lem_in *l);
int					ft_check_identical_rooms(t_lem_in *l);
int					ft_check_first_link(t_lem_in *l);
int					ft_check_second_link(t_lem_in *l);
int					ft_check_second_link2(char *second_link, t_lem_in *l);
int					ft_check_link_to_same_room(t_lem_in *l);

int					ft_isroom(char *line);
int					ft_islink(char *line);
int					ft_isnumber(char *coord);

int					ft_pathfinding(t_lem_in *l);
void				ft_distance(int **routes, int size);

void				ft_remove_coordinates(t_lem_in *l);
void				ft_add_coordinates(char *room);
int					ft_1st_coord_index(char *room);
int					ft_2nd_coord_index(char *room);

size_t				ft_tablen(char **tab);
void				ft_print_tab(char **tab);
void				ft_free_tab(char **tab);
void				ft_free_int_tab(int **tab, int size);
void				ft_free_nodes(t_node *rooms, int size);
void				ft_free_struct(t_lem_in *l);
void				free_sols_cmds(t_array **sols, t_array cmds, int nb_sols);

int					**ft_init_table(t_lem_in *l);
t_node				*ft_init_rooms(t_lem_in *l);
int					li_get_nodes_index(t_node *rooms, t_lem_in *l, char *name);

void				path_finder_dummy();
void				print_map_dummy();
void				distance_calc_dummy();

int					**ft_init_tab(int size);
void				pf_print_tab(int **tab, int row, int col);

int					run_path_finder(int **routetab, int size, t_array ***sols, int start, int end);
void				solutions_to_cmds(t_array **sols, t_array *cmds, int nb_ants, int nb_sols);
void				run_print_map(int **routetab, int size, t_node *nodes, t_array a_cmds);

t_node				*scale_map(t_node *nodes, int size);
void				print_line(t_node l1, t_node l2, int color);
void				print_map(t_node *nodes, int **routetab, int size);

int					path_finder_1(int ***routetab, int size, t_array *sol, int end);
#endif

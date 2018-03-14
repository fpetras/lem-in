/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <rnugroho@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 09:32:55 by fpetras           #+#    #+#             */
/*   Updated: 2018/03/14 18:17:17 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

# define START	1
# define END	2
# define ROOM	1
# define LINK	2

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
void				ft_remove_coordinates(t_lem_in *l);
int					ft_check_identical_rooms(t_lem_in *l);
int					ft_check_first_link(t_lem_in *l);
int					ft_check_second_link(t_lem_in *l);
int					ft_check_second_link2(char *second_link, t_lem_in *l);
int					ft_check_link_to_same_room(t_lem_in *l);

int					ft_isroom(char *line);
int					ft_islink(char *line);
int					ft_isnumber(char *coord);

size_t				ft_tablen(char **tab);
void				ft_print_tab(char **tab);
void				ft_free_tab(char **tab);
void				ft_free_struct(t_lem_in *l);

void				path_finder_dummy();
void				print_map_dummy();
void				distance_calc_dummy();

int					**ft_init_tab(int size);
void				pf_print_tab(int **tab, int row, int col);
#endif

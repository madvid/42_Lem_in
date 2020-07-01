/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 15:49:34 by weilin            #+#    #+#             */
/*   Updated: 2020/06/29 19:56:27 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include <stdbool.h>

# define ONLY_SOLUTION	2
# define SHOW_PATH		4
# define L1 ((t_input *)(alst->content))->line
# define L2 ((t_input *)((*alst)->content))->line

typedef struct			s_room
{
	char				*name;
	int					x;
	int					y;
	int					s_t;
	int					path_id;
	int					new_path_id; //PATH
	int					ant_id;
	int					population;
	bool				deviation;//BFS route
	bool				visited;//BFS route
	bool				dead_end;
	t_list				*next;
	t_list				*new_next; //PATH
	t_list				*previous; //BFS route
	t_list				*links;
}						t_room;

typedef struct			s_antfarm
{
	int					ant_qty;
	unsigned long		rounds;
	unsigned int		options;
	int					id;
	t_list				*rooms;
	t_list				*start;
	t_list				*end;
	t_list				*ants;
}						t_antfarm;

typedef struct			s_link
{
	int					usage;
	t_list				*room;
}						t_link;

/*
** id = index to distinguish the different path 
** sent = number of ants which will take the path
** len = number of link/edge constituting the path
** complete = boolean var, 
** room
*/
typedef struct			s_path
{
	int					id;
	unsigned long		pending;
	int					len;
	bool				complete;
	t_list				*room;
}						t_path;

typedef struct			s_ant
{
	int					id;
	t_room				*at_room;
}						t_ant;

typedef struct			s_route
{
	t_list				*room;
}						t_route;

typedef struct			s_input
{
	char				*line;
}						t_input;


// pending to clean modifed/cleaned function left in header

/*
** ----------------------------- INIT ------------------------------------------
*/
int						get_antfarm(t_antfarm *atf, t_list *alst);
int						get_ant(t_antfarm *atf, t_list *alst, t_list *pth);
/*
** ------------------------------ ADD ------------------------------------------
*/
int						add_rooms(t_antfarm *atf, t_list **alst);
int						add_link(t_antfarm *atf, char *line);
/*
** ----------------------------- ALGO -----------------------------------------
*/
bool					get_path(t_antfarm *atf, t_list *start
						, t_list *end, t_list **pth);
bool					bfs_route(t_list *start, t_list *end, t_list **route);
int						finish_route(t_list *route, t_list *end);
bool					adj_part_of_path(t_list *current, t_list *adj_room);
bool					detour_src_of_adj(t_list *adj_room , t_list *end);
void					finish_path(t_list **pth);
unsigned long			solution_rounds(t_antfarm *atf, t_list *pth
						, unsigned int ant_qty);
void					print_path_reset_room(t_antfarm *atf, t_list **pth
												, unsigned long rounds);
void					set_links_usage(t_list *end, t_list **route);
bool					start_connected_to_end(t_list *start, t_list *end);
bool					init_unique_path(t_list **pth, t_antfarm *atf);

/*
** ---------------------------- DISPLAY ----------------------------------------
*/
void					print_all_paths(t_list *pth);
void					print_all_steps(t_list *steps);
void					print_ant_moves(t_antfarm *atf, t_list *pth);
void					print_antfarm(t_list *alst);

/*
** ---------------------------- TOOLS ------------------------------------------
*/
int						free_input_lst(t_list **lst, char *exit_msg);
int						print_free(t_antfarm *atf, t_list **alst
						, t_list **pth, char *msg);
int						read_input(t_list **alst);
void					delete_room(void *content, size_t size);
void					delete_input(void *content, size_t size);
int						is_comment(char *line);
int						is_start_end(char *line);
int						is_start(t_room *room);
int						is_visited(t_room *room);
int						is_in_path(t_room *room);
int						samepath(t_room *src, t_room *room);
int						go_link(t_list *link);

#endif
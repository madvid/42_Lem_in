/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_route2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 00:52:18 by weilin            #+#    #+#             */
/*   Updated: 2020/06/30 15:13:11 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		reset_room(t_room *room)
{
	room->visited = false;
	room->deviation = false;
	room->previous = NULL;
}

static void		reset_route(t_list *adj_room
		, t_list *src_of_adj, t_list *route, t_list *end_room)
{
	t_room	*room;

	while (route)
	{
		room = (t_room *)((t_route *)route->content)->room->content;
		reset_room(room);
		route = route->next;
	}
	reset_room((t_room *)adj_room->content);
	reset_room((t_room *)src_of_adj->content);
	reset_room((t_room *)end_room->content);
}

static t_list	*get_src_of_adj(t_list *link)
{
	while (link)
	{
		if (((t_link *)link->content)->usage == 1)
		{
			if (is_start((t_room *)((t_link *)link->content)->room->content))
				return (NULL);
			else
				return (((t_link *)link->content)->room);
		}
		link = link->next;
	}
	return (NULL);
}

/* //weib
** Description:
**	When adj_room is already part of other route, it will try to go to
**	src_of_adj , and see if there is another link in src_of_adj that can
**	go to end, so that adj itself will be available for curr
** Return:
**	True if:
**		src->deviation is false
**		+ go_link = 1
**		+ src->path_id different from dest->path_id
**		+ dest->path_id different from 0 ()
*/

bool			detour_src_of_adj(t_list *adj_room, t_list *end) //wei
{
	t_list	*src_of_adj;
	t_list	*links;
	t_list	*tmp_test_route;
	bool	ret;

	tmp_test_route = NULL;
	src_of_adj = NULL;
	ret = false;
	links = ((t_room *)adj_room->content)->links;
	if (!(src_of_adj = get_src_of_adj(links)))
		return (false);
	if (((t_room *)src_of_adj->content)->visited == false
		&& ((t_room *)adj_room->content)->dead_end == false)
	{
		((t_room *)src_of_adj->content)->visited = true;
		((t_room *)adj_room->content)->visited = true;
		ret = bfs_route(src_of_adj, end, &tmp_test_route);
		if (!ret)
			((t_room *)adj_room->content)->dead_end = true;
		reset_route(adj_room, src_of_adj, tmp_test_route, end);
		ft_lstdel(&tmp_test_route, ft_delcontent);
	}
	return (ret);
}

/*
** Description:
**	If adj_room is already part of other route, so current bfs_route:curr_adj
**	cannot be created from so go back to previous room
**	
**	by default src->deviation are initialized to false, not changed at first
** Return:
**	True if:
**		src->deviation is false
**		+ go_link = 1
**		+ src->path_id different from dest->path_id
**		+ dest->path_id different from 0 ()
*/

bool			adj_part_of_path(t_list *current, t_list *adj_room) //wei
{
	t_room	*curr;
	t_room	*adj;
	t_list	*link_of_adj;
	int		adj_taken_by_another_path;

	adj_taken_by_another_path = 0;
	curr = (t_room *)current->content;
	adj = (t_room *)adj_room->content;
	link_of_adj = adj->links;
	while (link_of_adj)
	{
		if (((t_link *)link_of_adj->content)->usage == 1)
		{
			adj_taken_by_another_path = 1;
			break ;
		}
		link_of_adj = link_of_adj->next;
	}
	return (!curr->deviation && is_in_path(adj) && !samepath(curr, adj) // not deviating yet + adjacent in a path already (one of it links used) + currend and adjacent not in the same path 
			&& adj_taken_by_another_path); // I'm wonder if the fact that adj is in a path and checking if one of the link of adjacent is 1 is not checking the same think finally
	return (!curr->deviation && is_in_path(adj) && !samepath(curr, adj));
}

bool			adj_part_of_path_v2(t_list *current, t_list *adj_room) //matthieu
{
	t_room	*curr;
	t_room	*adj;

	curr = (t_room *)current->content;
	adj = (t_room *)adj_room->content;

	return (!curr->deviation && is_in_path(adj) && !samepath(curr, adj));
}
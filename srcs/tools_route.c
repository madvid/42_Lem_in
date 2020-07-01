/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_route.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 22:30:47 by weilin            #+#    #+#             */
/*   Updated: 2020/06/30 14:31:53 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** ___Description___:
**	Check if adjacent (neighbor) room can be added in the queue (named route).
**	An adjacent room can be add if:
**		- The neighbor has not been visited during the current bfs,
**		- It is not the start room,
**		- The usage of the link between the current room and the adjacent
**		  room is not a part of a path already.
** ___Return___:
**	1: if the room can be add to the queue.
**	0: otherwise.
*/

static bool		room_viable(t_list *curr_link, t_room *adj)
{
	return (!is_visited(adj) && !go_link(curr_link) && !is_start(adj));
}

static bool		pending_detour(t_room *curr, int usage)
{
	return (curr->deviation && usage == 0);
}

/*
** ___Decription___:
**	The goal of the function is to check if a room will be added to the queue
**	|route or not.
**	There are several conditions to state if a room will be added to queue.
**	Most general case (in the last return):
**		If a the process is not in the middle of a detour (explained below),
**		Check of the avaibility of the adjacent room is performed, meaning:
**		  - The neighbor has not been visited yet,
**		  - It is not the start room,
**		  - The link between current and adjacent rooms not taken by a path.
**		This is checked by the function: room_viable.
**	The specific case: detour is ongoing !
**		
**
**
** if with the 1st return:
**	if usage != -1 => usage is 0/1 meaning either the link/edge not used yet
**  or going in opposite direction than a path taking this linke/edge
**	+ dst != 0 => room is not the end
**	+ curr->path_id != dst->path_id => curr and dst constituting the edge are
**	  from 2 differents paths and dst room are on a path
**	+ dst->path_id != 0            => either curr and dst are in 2 differents
**	  paths or curr not in any path and dst already in a path
**	+ !dst->visited => the dst room has not be visited yet
**	+ adj_part_of_path is TRUE = the link toward adj_room is 1, it means adj_room
**    is already part of other route, so now should deviate //wei
** ___Return___:
**	TRUE:  
**	FALSE: 
*/

static bool		route_viable(t_list *current, t_list *curr_link, t_list *end)
{
	t_list		*adj_room;
	t_room		*adj;
	t_room		*curr;
	int			usage;

	curr = (t_room *)current->content; // room from which links/edges will be inspect
	adj_room = ((t_link *)curr_link->content)->room; // catching the neighbor room of the edge encapsulate in t_list type
	adj = (t_room *)adj_room->content;
	usage = ((t_link *)curr_link->content)->usage;
	if (room_viable(curr_link, adj)	&& adj_part_of_path(current, adj_room))
		return (detour_src_of_adj(adj_room, end));
	return (room_viable(curr_link, adj)	&& !pending_detour(curr, usage)); //weib
}

/*
** ___Description___:
**	Append a new link containing the dst room into the route (BFS queue).
**	In the dst room are noted the origin room (from each room it comes from)
**	which will be usefull when the path will be reconstructed.
**	PLUS (important) flag visited is changed to TRUE, to not queued the room
**	twice.
** ___Return___:
**	1: If the room has been successfully added to the route/queue.
**	0: if memory allocation rising from the creation og the new link (lstnew).
*/

static int		add_to_route(t_list **route, t_list *target_room, t_list *current)
{
	t_route		new;
	t_list		*new_node;

	if (!(new_node = ft_lstnew(&new, sizeof(t_route))))
		return (0);
	((t_route *)new_node->content)->room = target_room;
	ft_lstappend(route, new_node);
	((t_room *)target_room->content)->previous = current;
	((t_room *)target_room->content)->visited = true;
	return (1);
}

/*
** ___Description___:
**	This function is the core of the queue construction needed for the BFS.
**	Neighbors of the current_room are investigated (via function route_viable)
**	to determine if they should be add to the queue or not (see route_viable
**	for futher details).
**	Function is ended if there is a memory allocation issue, end room is
**	encounter or all the neighbors of the current room is checked and added
**	or not into the queue.
** ___Return___:
**	1: if the room end is reached or if all of the neighbors of current_room
**	   are proceeded.
**	0: if add_route failed, meaning a memory allocation issue within this
**	   latter.
*/

int				finish_route(t_list *route, t_list *end)
{
	t_list	*link;
	t_list	*target_room;
	t_list	*current_room;

	current_room = ((t_route *)route->content)->room;
	link = ((t_room *)current_room->content)->links;
	while (link)
	{
		target_room = ((t_link *)link->content)->room;
		if (route_viable(current_room, link, end))
		{
			if (!add_to_route(&route, target_room, current_room))
				return (0);
			if (((t_room *)target_room->content)->s_t == 1)
				return (1);
			if (adj_part_of_path(current_room, target_room))
				((t_room *)target_room->content)->deviation = true;
		}
		link = link->next;
	}
	if (((t_room *)current_room->content)->deviation == true)
		((t_room *)current_room->content)->deviation = false;
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bfs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 18:02:10 by weilin            #+#    #+#             */
/*   Updated: 2020/06/30 13:45:12 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			print_path_reset_room(t_antfarm *atf, t_list **pth
										, unsigned long rounds)
{
	t_list	*room;
	t_room	*rm;

	room = atf->rooms;
	while (room)
	{
		rm = (t_room *)room->content;
		rm->next = rm->new_next;
		rm->path_id = rm->new_path_id;
		rm->previous = NULL;
		rm->visited = false;
		rm->deviation = false;
		rm->dead_end = false;
		rm->new_next = NULL;
		rm->new_path_id = 0;
		room = room->next;
	}
	ft_lstrev(pth);
	if (atf->options & SHOW_PATH)
		print_all_paths(*pth);
	atf->rounds = rounds;
}

static void		increase_ants_pending(t_list *path)
{
	while (path)
	{
		((t_path *)path->content)->pending++;
		path = path->next;
	}
}

t_list			*select_path_to_send_ants(t_list *path, unsigned int ant_qty)
{
	t_list			*head;
	unsigned int	path_capacity;
	int				head_path_len;
	
	if (!path->next)
		return (path);
	head = path;
	head_path_len = ((t_path *)path->content)->len;
	path_capacity = 0;
	path = path->next; // skip start_room
	while (path)
	{
		path_capacity += head_path_len - ((t_path *)path->content)->len + 1;
		path = path->next;
	}
	if (path_capacity >= ant_qty)
		return (select_path_to_send_ants(head->next, ant_qty));
	return (head);
}

unsigned long	solution_rounds(t_antfarm *atf, t_list *pth
				, unsigned int ant_qty)
{
	t_list			*used_path;
	unsigned long	rounds;

	rounds = 0;
	used_path = pth;
	while (ant_qty > 0)
	{
		used_path = select_path_to_send_ants(used_path, ant_qty);
		increase_ants_pending(used_path);
		ant_qty -= ft_lstlen(used_path);
		rounds++;
	}
	rounds += ((t_path *)used_path->content)->len - 1;
	if (atf->options & SHOW_PATH)
		ft_printf("This solution would take %ld rounds\n", rounds);
	return (rounds);
}

/*
** ___Description___:
**	Function is the core part of the BFS, the queue (route) is constructed
**	fisrt and start is placed.
**	Then, the queue is extended by putting the available neighbors of the
**	current room (elem) into the queue (function finish_route).
**	See the corresponding function to know the criteria of avaibility of a
**	room.
**	If end room is reached, bfs is finished (find_new_route is set to true).
** ___Remarks___:
**	Unlike a classic queue, the 1st entry room is not really poped from the
**	queue but, when it is proceeded, the function jump onto the next one
**	without withdrawing any rooms from the queue (route).
** ___Return___:
**	TRUE  : if a new path/route is found
**	FALSE : if memory allocation issue or if no new path/route is founded
*/

bool			bfs_route(t_list *start, t_list *end, t_list **route)
{
	t_list		*elem;
	t_route		new_route;
	bool		found_new_route;

	found_new_route = false;
	if (!(*route = ft_lstnew(&new_route, sizeof(t_route))))
		return (false);
	else
		((t_route *)(*route)->content)->room = start;
	((t_room *)start->content)->visited = true;
	elem = *route;
	while (elem)
	{
		if (!finish_route(elem, end))
			return (false);
		if (((t_room *)end->content)->visited)
		{
			found_new_route = true;
			break ;
		}
		elem = elem->next;
	}
	return (found_new_route);
}

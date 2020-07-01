/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 18:02:10 by weilin            #+#    #+#             */
/*   Updated: 2020/06/30 11:24:34 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** ___Description___:
**	Function explore the list of link of the source room to find the link
**	going to the dest room.
** ___Return___:
**	link: the link from the src room to dest room
**	NULL: if no link between src room and dest room is found
*/

static t_list	*get_link(t_list *src, t_list *dest)
{
	t_list	*link;
	t_list	*room;

	link = ((t_room *)src->content)->links;
	while (link)
	{
		room = ((t_link *)link->content)->room;
		if (room == dest)
			return (link);
		link = link->next;
	}
	return (NULL);
}

/*
** ___Description___:
**	Depending on value of is_previous (true if the previous room is src,
**	false otherwise), the usage of the link between src and dest is set
**	to -1|1 if usage was 0.
**	If initially usage is -1|1, the usage is reset to 0 (occurs when a
**	deviation took place via this link).
** ___Remarks___:
**	The usage allows to know which link was used to go from start to end.
**	As mentionned, when a link was already used for a path and a deviation
**	via this link is allowed, the usage is reset to 0. It is a trick the
**	process of reconstruction of the augmented path (the different paths).
*/

static void		set_link_usage(t_list *src, t_list *dest, bool is_previous)
{
	t_list	*link;

	if (!(link = get_link(src, dest)))
		return ;
	if (((t_link *)link->content)->usage == 0 && is_previous)
		((t_link *)link->content)->usage = -1;
	else if (((t_link *)link->content)->usage == 0 && !is_previous)
		((t_link *)link->content)->usage = 1;
	else
		((t_link *)link->content)->usage = 0;
}

/*
** ___Description___:
**	After a successful BFS, route (queue of rooms) is free/destroyed here,
**	plus the function update the usage of the links of the rooms constituting
**	the path:
**		- usage of the link is set to -1 in the direction "start -> end",
**		- usage of the link is set to -1 in the direction "end -> start".
*/

void			set_links_usage(t_list *end, t_list **route)
{
	t_list	*room;
	t_list	*previous;

	ft_lstdel(route, ft_delcontent);
	room = end;
	while (room)
	{
		previous = ((t_room *)room->content)->previous;
		if (previous)
		{
			set_link_usage(previous, room, true);
			set_link_usage(room, previous, false);
		}
		room = ((t_room *)room->content)->previous;
	}
}

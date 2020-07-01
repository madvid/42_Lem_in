/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 19:31:08 by weilin            #+#    #+#             */
/*   Updated: 2020/06/29 19:55:38 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"


/*
** Description:
**	The function check if the room start has the room end as a neighbor.
** Return:
**	TRUE  : start and end are connnected
**	FALSE : end is not a neighbor of start
*/

bool			start_connected_to_end(t_list *start, t_list *end)
{
	t_list	*link;
	t_list	*dest_room;

	link = ((t_room *)start->content)->links;
	while (link)
	{
		dest_room = ((t_link *)link->content)->room;
		if (dest_room == end)
			return (true);
		link = link->next;
	}
	return (false);
}

/*
** Description:
**	Initialized the link path corresponding to the path between start and end
** Return:
**	TRUE  : If no mem allocation during the path initialization
**	FALSE : memory allocation issue (lstnew)
*/

bool			init_unique_path(t_list **pth, t_antfarm *atf)
{
	t_path	path;
	t_list	*new_path;

	path.id = 1;
	path.len = 1;
	path.room = atf->end;
	path.pending = atf->ant_qty;
	path.complete = true;
	atf->rounds = 1;
	if (!(new_path = ft_lstnew(&path, sizeof(t_path))))
		return (false);
	if (atf->options & SHOW_PATH)
	{
		ft_printf("Initialized 1 path:\n");
		ft_printf("# 1: End\n");
	}
	ft_lstprepend(pth, new_path);
	return (true);
}

static void		elem_finish_path(t_list *path, t_list *room) // reconstruction of path based on usage of link (follow the -1)
{
	t_list	*link;
	t_list	*next_room;
	int		path_id;

	path_id = ((t_path *)path->content)->id;
	link = ((t_room *)room->content)->links;
	if (((t_room *)room->content)->s_t == 1)
		((t_path *)path->content)->complete = true;
	while (link)
	{
		if (((t_link *)link->content)->usage == -1)
		{
			((t_path *)path->content)->len++;
			next_room = ((t_link *)link->content)->room;
			((t_room *)room->content)->new_next = next_room;
			((t_room *)room->content)->new_path_id = path_id;
			elem_finish_path(path, next_room);
			return ;
		}
		link = link->next;
	}
}

static int		sort_by_pathlen(void *a, void *b)
{
	t_path	*path1;
	t_path	*path2;

	path1 = (t_path *)a;
	path2 = (t_path *)b;
	return (path1->len < path2->len);
}

void			finish_path(t_list **pth)
{
	t_list	*room;
	t_list	*elem;

	elem = *pth; // pointer on pth list
	while (elem)
	{
		room = ((t_path *)elem->content)->room; // catching the first room of the path under processing
		elem_finish_path(elem, room);
		elem = elem->next;
	}
	ft_lst_mergesort(pth, sort_by_pathlen);
}

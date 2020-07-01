/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_room.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 22:53:36 by weilin            #+#    #+#             */
/*   Updated: 2020/06/30 09:53:24 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		go_link(t_list *link)
{
	return (((t_link *)link->content)->usage == -1);
}

int		is_start(t_room *room)
{
	return (room->s_t == 0);
}

/*
** ___Description___:
**	Check if the path_id of src room and dest room are identical
** ___Return___:
**	1: if both src room and dest room are on the same path
**	0: otherwise
*/

int		samepath(t_room *src, t_room *room)
{
	return (src->path_id == room->path_id);
}

/*
** ___Description___:
**	Check if the room has been already visited during the bfs.
** ___Return___:
**	1: if the room has been visited
**	0: otherwise
*/

int		is_visited(t_room *room)
{
	return (room->visited);
}

/*
** ___Description___:
**	Check if the room (actually the adjacent room) is already
**	in a path.
** ___Return___:
**	1: if path_id is different from 0
**	0: if path_id is 0
*/

int		is_in_path(t_room *room)
{
	return (room->path_id != 0);
}

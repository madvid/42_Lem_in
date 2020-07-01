/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_rooms.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 03:08:07 by weilin            #+#    #+#             */
/*   Updated: 2020/06/25 19:05:24 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** ___Description___:
**	Check if the room where the inner variables values have just being set does not
**	already exist. name and couple of coordinates are inspected.
** ___Return___:
**	1: the room is not already present in the list of rooms (atf->rooms)
**	0: if the room is repeated.
*/

static int		room_repeat(t_antfarm *atf, char **tab)
{
	t_list	*elem;
	t_room	*tmp;

	elem = atf->rooms;
	while (elem)
	{
		tmp = (t_room *)elem->content;
		if ((ft_atoi(tab[1]) == tmp->x && ft_atoi(tab[2]) == tmp->y)
			|| ft_strequ(tmp->name, tab[0]))
			return (0);
		elem = elem->next;
	}
	return (1);
}

/*
** ___Description___:
**	Function detects the commands "##start" and "##end".
**	The commands '##start' and '##end' have to be given once, otherwise error
**	is risen
** ___Return___:
**	1 : the list of input is not finished
**	0 : if command start/end has been already encounter or if end of list
**		reached after the specification of command "#start"/"#end"
*/

static int		mark_start_end(t_room *room, t_list **alst)
{
	static int		t[2] = {0, 0};

	if (ft_strequ(L2, "##start"))
	{
		if (t[0] == 1)
			return (0);
		else
		{
			t[0] = 1;
			room->s_t = 0;
			*alst = (*alst)->next;
		}
	}
	else if (ft_strequ(L2, "##end"))
	{
		if (t[1] == 1)
			return (0);
		else
		{
			t[1] = 1;
			room->s_t = 1;
			*alst = (*alst)->next;
		}
	}
	return (*alst != NULL);
}

/*
** ___Description___:
**	Set the value of the pointers atf->start/end: if the current room is
**	start/end, the pointer atf->start/end is pointing directly on the room
**	beeing start/end, this guaranty a direct access to these 2 rooms.
*/

static void		init_start_end(t_antfarm *atf, t_list *lst, int end)
{
	if (end == 0)
		// atf->start = lst;
	{
		atf->start = lst;
		((t_room *)atf->start->content)->population = atf->ant_qty;
		((t_room *)atf->start->content)->ant_id = 1;
	}
	else
		atf->end = lst;
}

/*
** ___Description___:
**	Check if the 2 last entries of tab are integers
**	if the 2 entries are valid formated coordinates, then they are stocked in room.x/y
**	The function also initialized all the other inner variables.
** ___Return___:
**	1: if coordinates are valid and if no issue during mem allocation for name
**	0: if coordinates are not integer, or if memory allocation for room->name
*/

static int		set_room_val(t_room *room, char **tab)
{
	if (!ft_atoi_int(tab[1], &room->x) || !ft_atoi_int(tab[2], &room->y))
		return (0);
	if (!(room->name = ft_strdup(tab[0])))
		return (0);
	room->links = NULL;
	room->next = NULL;
	room->previous = NULL;
	room->new_next = NULL;
	room->visited = false;
	room->deviation = false;
	room->path_id = 0;
	room->new_path_id = 0;
	room->dead_end = false;
	room->population = 0;
	room->ant_id = 0;
	return (1);
}

/*
** ___Description___:
**	Creation and initialization of room:
**	  - s_t: {-1;0;1} for {common room;start room;end room}
**	  - line has to be made of 3 words corresponding to the name and coord
**		of the room (room.name, room.x and room.y)
**	  - all the inner variables of room are initialized
**	  - Check if the room is already present within atf->rooms
**	  - set pointer atf->start and atf->end if room is start/end
** ___Return___:
**	1: if the room is correct, fully initialized and has been add to atf->rooms
**		or if the line is a comment or not ignored command.
**	0: otherwise
*/

int				add_rooms(t_antfarm *atf, t_list **alst)
{
	char			**tab;
	t_room			room;
	t_list			*new_list;

	room.s_t = -1;
	if (!mark_start_end(&room, alst))
		return (0);
	else if ((L2)[0] == '#')
		return (1);
	if (!(tab = ft_split_whitespaces(L2, (ft_wd(L2) == 3) ? 3 : 0)))
		return (0);
	if (!(tab[0] && tab[1] && tab[2] && !tab[3]) || !set_room_val(&room, tab))
		return (ret_strtab_free(tab, 0));
	if (!room_repeat(atf, tab) || !(new_list = ft_lstnew(&room, sizeof(t_room))))
	{
		ft_strdel(&room.name);
		return (ret_strtab_free(tab, 0));
	}
	(room.s_t != -1) ? init_start_end(atf, new_list, room.s_t) : 0;
	ft_lstappend(&atf->rooms, new_list);
	return (ret_strtab_free(tab, 1));
}

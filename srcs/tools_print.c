/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 16:23:18 by weilin            #+#    #+#             */
/*   Updated: 2020/06/26 19:06:42 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** ___Description___:
**	Function print on the standard input the content of each link of the linked
**	list, which correspond to the description of the antfarm:
**	  - number of ants,
**	  - comments and commands,
**	  - description of the rooms (name and coordinates),
**	  - description of the links/edges between rooms.
*/

void			print_antfarm(t_list *alst)
{
	while (alst)
	{
		ft_putendl(L1);
		alst = alst->next;
	}
}

void			print_all_steps(t_list *room)
{
	ft_printf("# %2d: ", ((t_room *)room->content)->path_id);
	while (room)
	{
		ft_printf("%s%c"
		, ((t_room *)room->content)->name
		, ((t_room *)room->content)->next ? '-' : '\n');
		room = ((t_room *)room->content)->next;
	}
}

void			print_all_paths(t_list *path)
{
	t_list	*room;

	while (path)
	{
		room = ((t_path *)path->content)->room;
		print_all_steps(room);
		path = path->next;
	}
}

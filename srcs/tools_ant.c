/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_ant.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 18:37:25 by weilin            #+#    #+#             */
/*   Updated: 2020/06/30 00:35:53 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** ___Description___:
**	It moves 1 ant from current room to the dst room asssigned and sets the
**	population and ant_id accordingly.
*/

static void		move_ant_one_step(t_room *curr, t_room *dst)
{
	curr->population--;
	dst->population++;
	dst->ant_id = curr->ant_id;
}

/*
** ___Description___:
**	It moves all ants from Start_room to End_room at once and sets End_room
**	population to atf->ant_qty, then the ant movement ends.
*/

static void		move_all_ants_at_once(t_antfarm *atf)
{
	int		i;
	t_room	*end;

	i = 0;
	end = (t_room *)atf->end->content;
	while (i < atf->ant_qty)
	{
		i++;
		ft_printf("L%d-%s%s", i, end->name, i < atf->ant_qty ? " " : "\n");
	}
	end->population += i;
	((t_room *)atf->start->content)->population -= i;
}

/*
** ___Parameters___:
**	t_path *path: the path of which the current ant will be dispatched to
**	t_room *dst: the room that the current ant is going to in this round
**	bool eol: before reaching the end of ant list, it prints a space in between
**
** ___Description___:
**	In each round it dispatches 1 ant from Start_room for each path until there
**	is no ant pending to be dispatched in the path, when all paths are already
**	dispatched with 1 ant respectively, it stops and prints a line break.
*/

static void		move_ant_from_start(t_list *ant, t_room *start, t_list *pth)
{
	bool	eol;
	t_room	*dst;
	t_path	*path;

	while (ant && pth && (path = (t_path *)pth->content)->pending > 0)
	{
		eol = false;
		dst = (t_room *)path->room->content;
		move_ant_one_step(start, dst);
		start->ant_id++;
		if (!pth->next || !((t_path *)pth->next->content)->pending)
			eol = true;
		ft_printf("L%d-%s%s", dst->ant_id, dst->name, eol ? "" : " ");
		((t_ant *)ant->content)->at_room = dst;
		path->pending--;
		pth = pth->next;
		ant = ant->next;
	}
	ft_putchar('\n');
}

/*
** ___Parameters___:
**	t_room *curr: the room where the ant currectly is
**	t_room *next: the next room in the path
**	bool eol: before reaching the end of ant list, it prints a space in between
**
** ___Description___:
**	It moves all the ants previously dispatched who are not in Start_room now
**	and still on their way to End_room, for the first round it won't work due
**	to the fact there isn't any ant dispatched from Start_room yet
*/

static t_list	*move_ant_on_the_way(t_list *ant)
{
	bool	eol;
	t_room	*curr;
	t_room	*next;

	while (ant && !is_start(((t_ant *)ant->content)->at_room))
	{
		curr = ((t_ant *)ant->content)->at_room;
		next = curr->next ? (t_room *)curr->next->content : NULL;
		eol = false;
		if (curr && next)
		{
			move_ant_one_step(curr, next);
			if (!ant->next)
				eol = true;
			ft_printf("L%d-%s%s", curr->ant_id,	next->name, eol ? "" : " ");
			curr->ant_id = 0;
			((t_ant *)ant->content)->at_room = next;
		}
		ant = ant->next;
	}
	return (ant);
}

/*
** ___Description___:
**	If a direct link between Start_room and End_room exists, it will move all
**	ants at once,
**	else it will loop in moving ants from Start_room to End_room by moving ants
**	who are already on the way first, and then dispatches ants who are still in
**	Start_room, with initial population set of atf->ant_qty, one loop time is a
**	round.
*/

void			print_ant_moves(t_antfarm *atf, t_list *pth)
{
	t_list	*ant;
	t_room	*start_room;

	start_room = (t_room *)atf->start->content;
	start_room->ant_id = 1;
	start_room->population = atf->ant_qty;
	if (!(atf->options & ONLY_SOLUTION))
		ft_putchar('\n');
	if (ft_lstlen(pth) == 1 && ((t_path *)pth->content)->len == 1)
		move_all_ants_at_once(atf);
	else
		while (((t_room *)atf->end->content)->population < atf->ant_qty)
		{
			ant = move_ant_on_the_way(atf->ants);
			move_ant_from_start(ant, start_room, pth);
		}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_antfarm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 02:45:37 by weilin            #+#    #+#             */
/*   Updated: 2020/06/30 13:34:07 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** ___Description___:
**	Function skip the link in the list input(alst) that are comments.
**	When the content of the link is not a comment, it is supposedly a number
**	(for the number of ants). Thus we stock the number in ant_qty. If this is
**	not a number, nothing is stock in ant_qty and error (0) is returned.
** ___Return___:
**	1:  the input line correponding to the number of ants is only preceded by
**		 comments and ant_qty is a positive int.
**	0: otherwise
*/

static int		get_ant_qty(t_antfarm *atf, t_list **alst)
{
	while (*alst && is_comment(L2))
		*alst = (*alst)->next;
	if (*alst && ft_isnumber(L2) == 1)
	{
		if (!ft_atoi_int(L2, &atf->ant_qty))
			return (0);
		*alst = (*alst)->next;
		return ((atf->ant_qty > 0) && *alst);
	}
	return (0);
}

/*
** ___Description___:
**	Check if the line (content of the input list) is either a comment or
**	command. If it is not a comment/command function check if there is
**	a '-' within the line, if there is, error (0) is risen (because room
**	definition is expected).
** ___Return___:
**	0: if the line is a possible link/edge description or a wrong formated line
**	1: otherwise (a room, a command or a comment)
*/

static int		the_rooms(char *line)
{
	if (line[0] == '#')
		return (1);
	else if (ft_strchr(line, '-'))
		return (0);
	return (1);
}

/*
** ___Description___:
**	Function process the links encounter in the input lines stocked in the
**	parsing structure.
**	It creates 2 single direction links for each pair of rooms that has link
**	connecting to each other
**	___Return___:
**	1: if all the remaining lines in alst were well formatted links or comments
**	   and if all links can be created successfully
**	0: if any of the input lines is badly formatted or add_link failed (mem
**	   allocation issue)
*/

static int		init_links(t_antfarm *atf, t_list *alst)
{
	if (!alst || !add_link(atf, L1))
		return (0);
	alst = alst->next;
	while (alst)
	{
		if (is_start_end(L1) || (!is_comment(L1) && !add_link(atf, L1)))
			return (0);
		alst = alst->next;
	}
	return (1);
}

/*
** ___Parameters___:
**	t_antfarm *atf: struct variable representing the graph
**	t_list *alst: list where each link content is a string/line from stdin
** ___Description___:
**	Initialization of t_antfarm *atf.
**	The list of input is roamed one time, comments are always skipped, after
**	possible commands (start/end) a positive integer is expected and stock in
**	ant_qty
**	Then rooms, commands and comments are expected (rooms are stocked in
**	atf->rooms), pointers atf->start/end are set.
**	Comments and commands others than start/end are ignored.
** ___Return___:
**	1:  if start/end room both exist and links can be created successfully
**	0:  if any of the input lines is badly formatted or either the room start
**		or end does not existed
*/

int				get_antfarm(t_antfarm *atf, t_list *alst)
{
	if (!get_ant_qty(atf, &alst))
		return (0);
	while (atf->ant_qty && alst && the_rooms(L1))
	{
		if (!add_rooms(atf, &alst))
			return (0);
		alst = alst->next;
	}
	return ((!atf->start || !atf->end) ? 0 : init_links(atf, alst));
}

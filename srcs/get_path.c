/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 22:25:22 by weilin            #+#    #+#             */
/*   Updated: 2020/06/25 18:06:49 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** ___Description___:
**	Initialization of a path, all inner variable are set, and this new path
**	is append in the list pth (the augmented path).
**	Notice that only the 1st link (the 1st room after start) is allocated,
**	each paths will be constructed in the function finish_path.
** ___Remarks___:
**	The id of paths change every times the function init_path is called,
**	thus the id of the same path will change every time the augmented path
**	is update.
** ___Return___:
**	1: if the initialization is successfully performed.
**	0: if memory allocation issue
*/

static int		init_path_sub(t_list **pth, t_list *room)
{
	t_list		*new_path;
	t_path		path;
	static int	path_id = 0;

	path.len = 1;
	path.id = ++path_id;
	path.pending = 0;
	path.room = NULL;
	path.complete = false;
	if (!(new_path = ft_lstnew(&path, sizeof(t_path))))
		return (0);
	((t_path *)new_path->content)->room = room;
	ft_lstprepend(pth, new_path);
	return (1);
}

/*
** ___Description___:
**	Function is called after reaching the room end in BFS process.
**	The 1st action performed is the update of the usage of the links
**	constituting the last path found by the bfs process (last path because
**	the usage are update based on the inner variable previous of each room
**	visited in reversed order from end).
**	Next, the list of paths (called augmented path in the graph theory) is
**	initialized first (init_path_sub) and constructed (finish_path).
** ___Remarks___:
**	Notice that as deviation can occured, it is here, during set_links_usage
**	and finish_path that 2 paths crossing each other are reconstruted.
** ___Return___:
**	1: if the augmented paths is fully constructed.
**	0: if memory allocation issue
*/

static int		init_path(t_antfarm *atf, t_list **pth, t_list **route)
{
	t_list		*link;

	set_links_usage(atf->end, route);
	link = ((t_room *)(atf->start->content))->links;
	while (link)
	{
		if (((t_link *)link->content)->usage == -1)
			if (!init_path_sub(pth, ((t_link *)link->content)->room))
				return (0);
		link = link->next;
	}
	if (atf->options & SHOW_PATH)
		ft_printf("Initialized %lu path%s", ft_lstlen(*pth),
					ft_lstlen(*pth) > 1 ? "s:\n" : ":\n");
	finish_path(pth);
	return (1);
}

/*
** ___Parameters___:
**	*atf: pointer on the struct variable t_antfarm, containing full
**		  description of the antfarm.
**	**pth: adress of pointer on t_list struct variable, being list
**		   of the differents pth and descriptive variable within.
** ___Remarks___:
**	As pth is a list, the t_path inner variable is at content:
**	pth: [cnt:path1 & next->]--[cnt:path2 & next->]--{...}--[NULL]
** ___Description___:
**	Function manages the BFS algo, followed by the step of path construction
**	and calculate the number of ants per pth and evaluate the performance
**	(in how many rounds all the ants will reach the END)
** ___Return___:
**	TRUE  : if a solution is found i.e. there is/are path(s) connecting start
**			to end.
**	FALSE : if rounds != LONG_MAX(initialization value) || ret = 0 or memory
**			allocation issue.
*/

static bool		find_path(t_antfarm *atf, t_list **pth)
{
	unsigned long	ret;
	t_list			*route;
	t_list			*previous_pth;

	route = NULL;
	while (bfs_route(atf->start, atf->end, &route))
	{
		previous_pth = *pth;
		*pth = NULL;
		if (!init_path(atf, pth, &route))
			return (false);
		ret = solution_rounds(atf, *pth, atf->ant_qty);
		if (ret >= atf->rounds || ret == 0)
		{
			ft_lstdel(pth, ft_delcontent);
			*pth = previous_pth;
			break ;
		}
		print_path_reset_room(atf, pth, ret);
		ft_lstdel(&previous_pth, ft_delcontent);
	}
	ft_lstdel(&route, ft_delcontent);
	return (atf->rounds != LONG_MAX && ret != 0);
}

/*
** ___Description___:
**	Function looks for path(s) connecting the rooms start and end.
**	Two cases are treated:
**	  - if the room start and end are directly connected,
**	  - if they are not.
**	In the 1st case, only one path is constructed, in the latter case
**	the algo of paths finding based on BFS is used.
** ___Return___:
**	TRUE  : if no mem allocation issue or if there is at least one
**			path found during BFS.
**	FLASE : if mem allocation in any functions encounter in init_unique_path
**			or in find_path.
*/

bool			get_path(t_antfarm *atf, t_list *start, t_list *end
			, t_list **pth)
{
	if (start_connected_to_end(start, end))
		return (init_unique_path(pth, atf));
	return (find_path(atf, pth));
}

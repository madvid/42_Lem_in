/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 02:57:28 by weilin            #+#    #+#             */
/*   Updated: 2020/06/28 22:47:51 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		delete_room(void *content, size_t size)
{
	t_room	*room;

	room = (t_room *)content;
	if (content && size)
	{
		ft_strdel(&room->name);
		ft_lstdel(&room->links, ft_delcontent);
		free(content);
	}
}

void		delete_input(void *content, size_t size)
{
	t_input		*input;

	input = (t_input *)content;
	if (content && size)
	{
		ft_strdel(&input->line);
		free(content);
	}
}

int			free_input_lst(t_list **alst, char *exit_msg)
{
	ft_lstdel(alst, delete_input);
	if (exit_msg)
	{
		write(2, exit_msg, ft_strlen(exit_msg));
		ft_putchar('\n');
	}
	return (exit_msg ? -1 : 0);
}

int			print_free(t_antfarm *atf, t_list **input
			, t_list **pth, char *msg)
{
	if (atf->rooms)
		ft_lstdel(&atf->rooms, delete_room);
	if (atf->ants)
		ft_lstdel(&atf->ants, ft_delcontent);
	ft_lstdel(pth, ft_delcontent);
	return (free_input_lst(input, msg));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 16:24:56 by weilin            #+#    #+#             */
/*   Updated: 2020/06/30 00:29:01 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** ___Description___:
**	Initialization of all the inner variables of t_antfarm struct var
**	except ant_qty which is initialized by another function in get_antfarm
*/

static void		init_atf_values(t_antfarm *atf)
{
	atf->rooms = NULL;
	atf->start = NULL;
	atf->end = NULL;
	atf->rounds = LONG_MAX;
	atf->options = 0;
	atf->ants = NULL;
}

/*
** ___Description___:
**	Managing the options available:
**	  - '--paths' to print when selecting paths solution of the minimum rounds
**	  - '--solution' to print ant moves without the antfarm
**	 if any of the two options is specified, antfarm map won't be printed.
*/

static int		get_options(t_antfarm *atf, int ac, char **av)
{
	int i;
	
	init_atf_values(atf);
	i = 1;
	if (ac > 1)
	{
		while (i < ac)
		{
			if (ft_strequ(av[i], "--paths"))
				atf->options |= SHOW_PATH;
			else if (ft_strequ(av[i], "--solution"))
				atf->options |= ONLY_SOLUTION;
			i++;
		}
		if(!atf->options)
		{
			ft_putendl("Usage: ./lem-in [--paths] [--solution] < antfarm_map");
			return(0);
		}
	}
	return (1);
}

/*
** ___Description___:
**	get_options		: parsing program options and return usage if needed
**	read_input		: parsing with basic tests on the format of input
**	get_antfarm		: construction of struct variable which containing graph
**	get_path		: algorithm of multi-paths finding based on BFS
**	get_ant			: prepare the ant troops and print ant moves in stdout
*/

int				main(int ac, char **av)
{
	t_antfarm	atf;
	t_list		*alst;
	t_list		*pth;

	alst = NULL;
	pth = NULL;
	if (!get_options(&atf, ac, av))
		return (0);
	if (!read_input(&alst))
		return (free_input_lst(&alst, "ERROR"));
	if (!get_antfarm(&atf, alst))
		return (print_free(&atf, &alst, &pth, "ERROR"));
	if (!(get_path(&atf, atf.start, atf.end, &pth)))
		return (print_free(&atf, &alst, &pth, "ERROR"));
	if (!get_ant(&atf, alst, pth))
		return (print_free(&atf, &alst, &pth, "ERROR"));
	return (print_free(&atf, &alst, &pth, NULL));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 15:23:20 by mdavid            #+#    #+#             */
/*   Updated: 2020/06/24 15:34:54 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# ifndef LIBFT_H
#  define LIBFT_H
#  include "libft.h"
# endif

/*
** structure description:
**	nb_ants: the number of ants catch during parsing
**	input: list of the 
*/

typedef struct		s_parse
{
	int				nb_ants;
	t_list			*input;
	int				stat_se;
	static int		prev_is_se[2] = {0, 0};
}					t_parse;

typedef struct lem_in
{
	/* data */
};

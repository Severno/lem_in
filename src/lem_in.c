/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sapril <sapril@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 14:17:21 by sapril            #+#    #+#             */
/*   Updated: 2020/01/28 14:34:40 by sapril           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"
//
//t_lem		*create_lem_in()
//{
//	t_lem *new_lem;
//
//	new_lem = ft_memalloc(sizeof(t_lem));
////	new_lem->ants = get_ants();
//}

int			main(int argc, char *argv[])
{
	t_lem *lem;

//	lem = create_lem_in();
	lem = ft_memalloc(sizeof(t_lem));
	get_lines(lem, "../maps/test.map");
}
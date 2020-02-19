/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sapril <sapril@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 08:34:20 by sapril            #+#    #+#             */
/*   Updated: 2020/02/19 11:49:38 by sapril           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_room *create_room(char **name, int x, int y)
{
	t_room	*new_room;
	int i;

	i = 0;
	new_room = ft_memalloc(sizeof(t_room));
	new_room->name = ft_strnew(ft_strlen(*name));
	new_room->name = ft_strcpy(new_room->name, *name);
	new_room->coord_x = x;
	new_room->coord_y = y;
	new_room->start = NULL;
	new_room->end = NULL;
	new_room->next = NULL;
	new_room->in_degree = 0;
	new_room->out_degree = 0;
	new_room->bfs_lvl = -1;
	new_room->ant_number = -1;
	new_room->visited = 0;
	new_room->in_link = ft_memalloc(sizeof(char *) * MIN_LINKS);
	new_room->out_link = ft_memalloc(sizeof(char *) * MIN_LINKS);
	while (i < MIN_LINKS)
		new_room->out_link[i++] = ft_memalloc(sizeof(char) * 100);
	i = 0;
	while (i < MIN_LINKS)
		new_room->in_link[i++] = ft_memalloc(sizeof(char) * 100);
	return (new_room);
}

t_lem		*create_lem_in()
{
	t_lem *new_lem;

	new_lem = ft_memalloc(sizeof(t_lem));
	new_lem->concat_lines = ft_strnew(LINE_SIZE);
	new_lem->ht = ht_create();
	new_lem->start = NULL;
	new_lem->end = NULL;
	new_lem->names = NULL;
	new_lem->ants = -1;
	new_lem->fd = -1;
	new_lem->rooms_cap = 0;
	new_lem->start_end_flag = 0;
	new_lem->ants_finished = 0;
	new_lem->fd = 0;
	new_lem->errors = 0;
	new_lem->concat_mult = 1;
	new_lem->concat_bytes = 0;
	return (new_lem);
}
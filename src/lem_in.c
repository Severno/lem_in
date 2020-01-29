/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sapril <sapril@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 14:17:21 by sapril            #+#    #+#             */
/*   Updated: 2020/01/29 18:31:32 by sapril           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"
//
t_lem		*create_lem_in()
{
	t_lem *new_lem;

	new_lem = ft_memalloc(sizeof(t_lem));
	new_lem->ht = ht_create();
	new_lem->start = NULL;
	new_lem->end = NULL;
	new_lem->fd = -1;
	new_lem->ants = -1;
	new_lem->names = NULL;
//	new_lem->ants = get_ants();
	return (new_lem);
}

t_room *create_room( char **name, int x, int y)
{
	t_room	*new_room;
	int		i;

	i = 0;
	new_room = ft_memalloc(sizeof(t_room));
	new_room->bfs_lvl = -1;
	new_room->coord_x = x;
	new_room->coord_y = y;
	new_room->in_degree = 0;
	new_room->out_degree = 0;
	new_room->out_links = ft_memalloc(sizeof(t_room *) * 10);
	new_room->in_links = ft_memalloc(sizeof(t_room *) * 10);
	while (i < MIN_LINKS)
		new_room->out_links[i++] = ft_memalloc(sizeof(t_room *));
	i = 0;
	while (i < MIN_LINKS)
		new_room->in_links[i++] = ft_memalloc(sizeof(t_room *));
	new_room->visited = 0;
	new_room->name = ft_strnew(ft_strlen(*name));
	new_room->name = ft_strcpy(new_room->name, *name);
	return (new_room);
}


void print_rooms(t_lem *lem, t_room *start, int cur_out_degree)
{
	int in_degree;
	int out_degree;

	if (cur_out_degree >= start->out_degree)
		return;
	in_degree = 0;
	out_degree = 0;
	ft_printf("Root name = %s, x = %d, y = %d", start->name, start->coord_x, start->coord_y);
	while (in_degree < start->in_degree)
	{
		ft_printf("In link name = %s, x = %d, y = %d, link num = %d\n", start->in_links[in_degree]->name,
				start->in_links[in_degree]->coord_x, start->in_links[in_degree]->coord_y, in_degree + 1);
		in_degree++;
	}
	while (out_degree < start->out_degree)
	{
		ft_printf("Out link name = %s, x = %d, y = %d, link num = %d\n", start->out_links[out_degree]->name,
				start->out_links[out_degree]->coord_x, start->out_links[out_degree]->coord_y, out_degree + 1);
		out_degree++;
	}
	print_rooms(lem, start->out_links[cur_out_degree], cur_out_degree + 1);
}

int			main(int argc, char *argv[])
{
	t_lem *lem;

	lem = create_lem_in();
	lem->fd = open("../maps/test.map", O_RDONLY);
	get_lines(lem, "../maps/test.map");
	ft_putstr(lem->names);
	ht_print(lem->ht);
	ft_printf("start = %s\n", lem->start);
	ft_printf("end = %s\n", lem->end);
	print_rooms(lem, ht_get(lem->ht, lem->start), 0);
	free_data(&lem);
	return (0);
}
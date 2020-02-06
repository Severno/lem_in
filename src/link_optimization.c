/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_optimization.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sapril <sapril@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 19:57:55 by sapril            #+#    #+#             */
/*   Updated: 2020/02/05 20:08:26 by sapril           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int get_pos_link_out(char **out_links, char *in_link, int out_degree)
{
	int i;

	i = 0;
	while (i < out_degree)
	{
		if (ft_strequ(out_links[i], in_link))
			return (i);
		i++;
	}
	return (-1);
}

void remove_dead_link(t_lem *lem, t_room *dead_room)
{
	t_room	*out_link;
	int		in_degr;
	int		pos_out_link;

	in_degr = 0;
	while (in_degr < dead_room->in_degree)
	{
		if (dead_room->in_link[in_degr])
		{
			out_link = ht_get(lem->ht, dead_room->in_link[in_degr]);
			pos_out_link = get_pos_link_out(out_link->out_link, dead_room->name, out_link->out_degree);
			free(out_link->out_link[pos_out_link]);
			out_link->out_link[pos_out_link] = NULL;
			free(dead_room->in_link[in_degr]);
			dead_room->in_link[in_degr] = NULL;
		}
		in_degr++;
	}
}

int get_pos_link_in(char **in_links, char *out_link, int in_degree)
{
	int i;

	i = 0;
	if (in_links && *in_links && out_link)
	{
		while (i < in_degree)
		{
			if (ft_strequ(in_links[i], out_link))
				return (i);
			i++;
		}
	}
	return (-1);
}

void delete_current_link(t_room *from, t_room *to, int out_pos, int in_pos)
{
	free(from->out_link[out_pos]);
	from->out_link[out_pos] = NULL;
	free(to->in_link[in_pos]);
	to->in_link[in_pos] = NULL;

}

void	delete_useless_links(t_lem *lem, t_room *start)
{
	t_ht	*seen;
	t_queue	*queue;
	t_qnode *current;
	int		out_degree;

	out_degree = 0;
	seen = create_seen();
	queue = queue_create();
	enqueue(queue, start);
	start->bfs_lvl = 0;
	while (queue->front)
	{
		print_queue(queue);
		print_ht_seen(seen);
		current = dequeue(queue);
		if (!current || !current->room)
			continue;
		print_queue(queue);
		print_ht_seen(seen);
		ft_printf(BLUE"Current working %s \n"RESET, current->room->name);
		if (!ht_get(seen, current->room->name)) // проверяем есть ли в просмотренных
		{
			ht_set(seen, current->room->name, &current->room); // если нет, добавляем в просмотренные
			ft_printf("Current node = %s, bfs_lvl = %d\n", current->room->name, current->room->bfs_lvl);
			while (out_degree < current->room->out_degree) // смотрим все исходящие ссылки из текущий комнаты
			{
				if (current->room->bfs_lvl == ht_get(lem->ht, current->room->out_link[out_degree])->bfs_lvl) // удаляет элементы которые ссылаются на один и тот же BFS уровень
				{
					delete_current_link(
							current->room,
							ht_get(lem->ht, current->room->out_link[out_degree]),
							out_degree,
							get_pos_link_in(
									ht_get(lem->ht, current->room->out_link[out_degree])->in_link,
									current->room->name,
									ht_get(lem->ht, current->room->out_link[out_degree])->in_degree
							)
					);
				}
				if (!ht_get(seen, current->room->out_link[out_degree]))
					enqueue(queue, ht_get(lem->ht, current->room->out_link[out_degree]));
//				print_queue(queue);
//				print_ht_seen(seen);
				if (current->room->out_link[out_degree])
					ft_printf("Current node = %s, bfs_lvl = %d\n", current->room->out_link[out_degree], ht_get(lem->ht, current->room->out_link[out_degree])->bfs_lvl);
				out_degree++;
//				if (current->room->out_degree == 0 && current->room->bfs_lvl != MAX_INTEGER)
//					remove_dead_link(lem, current->room);
			}
//			if (ht_get(lem->ht, current->room->out_link[out_degree])->out_degree == 0  && current->room->bfs_lvl != MAX_INTEGER)
//				remove_dead_link(lem, current->room);
			if (current->room->out_degree == 0 && current->room->bfs_lvl != MAX_INTEGER)
				remove_dead_link(lem, current->room);
		}
//		print_queue(queue);
//		print_ht_seen(seen);
		free(current);
		out_degree = 0;
	}
	free(queue);
	free_seen(&seen);
//	ft_printf("Malloc entries %d\n", malloc_entries);
//	ft_printf("Freed entries %d\n", freed_entries);
}
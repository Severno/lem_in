/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sapril <sapril@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 20:05:00 by sapril            #+#    #+#             */
/*   Updated: 2020/02/13 13:28:31 by sapril           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/lem_in.h"

void print_ht_seen(t_ht *seen)
{
	int i;

	i = 0;

	ft_printf("Already seen ");
	while (i < TABLE_SIZE)
	{
		if (seen->entries[i]->value)
			ft_printf("%s ", seen->entries[i]->value->name);
		i++;
	}
	ft_putchar('\n');
}

void print_links(t_lem *lem)
{
	int i;
	int in_degr;
	int out_degr;

	i = 0;
	in_degr = 0;
	out_degr = 0;
	while (i < TABLE_SIZE)
	{
		if (lem->ht->entries[i])
		{
			while (in_degr < lem->ht->entries[i]->value->in_degree)
			{
				ft_printf("Name = %s, In link %s \n",lem->ht->entries[i]->value->name, lem->ht->entries[i]->value->in_link[in_degr]);
				in_degr++;
			}
			ft_printf("\n");
			while (out_degr < lem->ht->entries[i]->value->out_degree)
			{
				ft_printf("Name = %s, Out link %s \n",lem->ht->entries[i]->value->name, lem->ht->entries[i]->value->out_link[out_degr]);
				out_degr++;
			}
		}
		i++;
	}
}

void print_rooms(t_lem *lem)
{
	int in_degree;
	int out_degree;
	int rooms;
	int i;

	rooms = 49;
	in_degree = 0;
	out_degree = 0;
	i = 0;
	while (i < TABLE_SIZE)
	{
		if (lem->ht->entries[i])
		{
			ft_printf(RED"----Root NAME = %s, X = %d, Y = %d ----\n"RESET, lem->ht->entries[i]->value->name, lem->ht->entries[i]->value->coord_x, lem->ht->entries[i]->value->coord_y);
			while (out_degree < lem->ht->entries[i]->value->out_degree)
			{
				ft_printf(BLUE"Out link = %s\n"RESET, lem->ht->entries[i]->value->out_link[out_degree]);
				out_degree++;
			}
			while (in_degree < lem->ht->entries[i]->value->in_degree)
			{
				ft_printf(BLUE"In link = %s\n"RESET, lem->ht->entries[i]->value->in_link[in_degree]);
				in_degree++;
			}
			in_degree = 0;
			out_degree = 0;
			rooms++;
			ft_putchar('\n');
		}
		i++;
	}
}

void next_search(t_lem *lem, t_room *curr_room)
{
	int out_degr_cur;
//	int out_degr_work;
//	int path_count;

	out_degr_cur = 0;
	if (ft_strequ(curr_room->name, lem->end))
	{
		ft_printf(" -> %s", curr_room->name);
		return;
	}
	while (out_degr_cur < curr_room->out_degree)
	{
		if (curr_room->out_link[out_degr_cur] != NULL && curr_room->out_link[out_degr_cur][0] != '\0')
		{
			ft_printf(" -> %s", curr_room->name);
			next_search(lem, ht_get(lem->ht, curr_room->out_link[out_degr_cur]));
		}
//		next_search(lem, ht_get(lem->ht, curr_room->out_link[out_degr_cur]));
		out_degr_cur++;
	}
}

void print_paths(t_lem *lem, t_room *start)
{
	int out_degr_cur;
//	int out_degr_work;
	int path_count;
	t_room *cur_room;

	out_degr_cur = 0;
//	out_degr_work= 0;
	path_count = 1;
	ft_printf(RED"Start\n"RESET);
	while (out_degr_cur < start->out_degree)
	{
		cur_room = ht_get(lem->ht, start->out_link[out_degr_cur]);
		ft_printf("Path %d. %s", path_count, start->name);
		next_search(lem, cur_room);
		ft_putchar('\n');
		out_degr_cur++;
//		out_degr_work = 0;
		path_count++;
	}
}

void next_search_linked_list(t_room *cur_room)
{
	while (cur_room)
	{
		ft_printf(" -> %s", cur_room->name);
		cur_room = cur_room->next;
	}
}

void print_paths_linked_list(t_lem *lem, t_room *start)
{
	int out_degr_cur;
//	int out_degr_work;
	int path_count;
	t_room *cur_room;

	out_degr_cur = 0;
//	out_degr_work= 0;
	path_count = 1;
	ft_printf(RED"Start\n"RESET);
	while (out_degr_cur < start->out_degree)
	{
		cur_room = ht_get(lem->ht, start->out_link[out_degr_cur]);
		ft_printf("Path %d. %s", path_count, start->name);
		next_search_linked_list(cur_room);
		ft_putchar('\n');
		out_degr_cur++;
//		out_degr_work = 0;
		path_count++;
	}
}

void print_current_room_state(t_lem *lem, t_room *start, int bfs_level, int ants)
{
	t_ht	*seen;
	t_queue	*queue;
	t_qnode *current;
	int		out_degree;
	t_room	*deciding_room;

	out_degree = 0;
	seen = create_seen();
	queue = queue_create();
	enqueue(queue, start);
	while (queue->front && bfs_level-- >= 0)
	{
		current = dequeue(queue);
		if (current == NULL || current->room == NULL)
			continue;
		if (!current->room->name)
			continue;
		if (!ht_get(seen, current->room->name)) // проверяем есть ли в просмотренных
		{
			ht_set(seen, current->room->name, &current->room); // если нет, добавляем в просмотренные
			while (out_degree < current->room->out_degree) // смотрим все исходящие ссылки из текущий комнаты
			{
				deciding_room = ht_get(lem->ht, current->room->out_link[out_degree]);
				if (deciding_room && deciding_room->name && deciding_room->name[0] != '\0')
					ft_printf("L%d-%s ", ants, deciding_room->name);
				if (!ht_get(seen, current->room->out_link[out_degree])) // если его нет в просмотренном добавляем в очередь
					enqueue(queue, ht_get(lem->ht, current->room->out_link[out_degree]));
				out_degree++;
			}
		}
		free(current);
		out_degree = 0;
	}
	ft_printf("\n");
	free(queue);
	free_seen(&seen);
}
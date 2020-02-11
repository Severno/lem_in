/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sapril <sapril@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 12:49:16 by sapril            #+#    #+#             */
/*   Updated: 2020/02/11 16:48:57 by sapril           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"
// Здесь нужно добавить полное смещение муравьев, каждый раз на один. То есть нужно пробегаться и двигать их до тех пор пока конечный элемент на станет END
void run_push_path(t_room *curr_room, t_ht *ants_and_rooms, int launched_ants)
{
	while (curr_room)
	{
		if (curr_room->next && curr_room->next->ant_number == -1)
		{
			ht_set(ants_and_rooms, ft_itoa(curr_room->ant_number), &curr_room->next);
//			ht_set(ants_and_rooms, "-1", &curr_room);
			curr_room->next->ant_number = curr_room->ant_number;
			curr_room->ant_number = -1;
			if (curr_room->prev && curr_room->prev->ant_number == -1)
				break;
		}
		curr_room = curr_room->next;
	}
}

void push_path(t_lem *lem, t_room *start, int launched_ants)
{
	int out_degr_cur;
	t_room *curr_room;

	out_degr_cur = 0;
	while (out_degr_cur < start->out_degree)
	{
		curr_room = ht_get(lem->ht, start->out_link[out_degr_cur]);
		if (curr_room->name != NULL && curr_room->name[0] != '\0')
		{
			run_push_path(curr_room, launched_ants);
		}
		out_degr_cur++;
	}
	ft_putchar('\n');
}

//void print_from_the_end(t_lem *lem, t_room *end_prev, t_room *start_prev)
//{
//	while (end)
//	{
//		end
//	}
//}

void run_path(t_lem *lem, t_room *curr_room, int launched_ants, int *bfs_lvl)
{
	int out_degr;

	out_degr = 0;

	if (curr_room->ant_number == -1)
		curr_room->ant_number = launched_ants;
	while (curr_room)
	{
		if (curr_room->ant_number != -1)
			ft_printf("L%d-%s ", curr_room->ant_number, curr_room->name);
		curr_room = curr_room->next;
	}
//	print_current_room_state(lem, ht_get(lem->ht, lem->start), *bfs_lvl, launched_ants);
}

void launch_ants(t_lem *lem, t_room *start, int ants)
{
	t_ht	*ants_and_rooms;
	int out_degr_cur;
	t_room *curr_room;
	int launched_ants;
	int bfs_lvl;

	launched_ants = 1;
	out_degr_cur = 0;
	bfs_lvl = 0;
	ants_and_rooms = ht_create();
	while (launched_ants < ants)
	{
		while (out_degr_cur < start->out_degree)
		{
			curr_room = ht_get(lem->ht, start->out_link[out_degr_cur]);
			if (curr_room->name != NULL && curr_room->name[0] != '\0')
			{
				ht_set(ants_and_rooms, ft_itoa(launched_ants), &curr_room);
				run_path(lem, curr_room, launched_ants++, &bfs_lvl);
				bfs_lvl++;
			}
			out_degr_cur++;
		}
		push_path(lem, start, launched_ants);
//		ft_putchar('\n');
		out_degr_cur = 0;
	}
}
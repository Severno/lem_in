/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sapril <sapril@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 12:49:16 by sapril            #+#    #+#             */
/*   Updated: 2020/02/15 10:24:07 by sapril           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void print_current_ants_position(t_ht *ants_and_rooms, int curr_ant, t_lem *lem)
{
	int tmp_ants;
	t_room *curr_room;

	tmp_ants = 1;
	while (tmp_ants < curr_ant)
	{
		curr_room = ht_get(ants_and_rooms, ft_itoa(tmp_ants));
		if (!curr_room)
		{
			tmp_ants++;
			continue;
		}
		if (!ft_strequ(curr_room->name, lem->end))
			ft_printf("L%d-%s ", tmp_ants, curr_room->name);
		tmp_ants++;
	}
	ft_putchar('\n');
}


void push_all_ants(t_ht *ants_and_rooms, t_lem *lem, t_room *curr_room, int curr_ant)
{
	int tmp_ants;
	t_room *working_room;

	tmp_ants = 1;
	while (tmp_ants < curr_ant)
	{
		working_room = ht_get(ants_and_rooms, ft_itoa(tmp_ants));
		if (working_room)
		{

		}
		tmp_ants++;
	}
}

void run_current_lvl(t_ht *ants_and_rooms, int curr_ant, t_lem *lem)
{
	int tmp_ants;
	char *curr_ant_key;
	t_room *curr_ant_room;

	tmp_ants = 1;
	print_current_ants_position(ants_and_rooms, curr_ant, lem);
	while (tmp_ants < curr_ant)
	{
		curr_ant_key = ft_itoa(tmp_ants);
		curr_ant_room = ht_get(ants_and_rooms, curr_ant_key);
		if (curr_ant_room && curr_ant_room->next)
			ht_set(ants_and_rooms, curr_ant_key, &curr_ant_room->next);
		if (curr_ant_room == ht_get(lem->ht, lem->end))
		{
			ants_and_rooms->entries[hash(curr_ant_key)] = NULL;
			lem->ants_finished++;
		}
		tmp_ants++;
	}
}

// Здесь нужно добавить полное смещение муравьев, каждый раз на один. То есть нужно пробегаться и двигать их до тех пор пока конечный элемент на станет END
void run_push_path(t_lem *lem, t_room *curr_room, int launched_ants, int prev_ant)
{
//	int tmp_ant;
//	(void)launched_ants;
//	if (!ft_strequ(curr_room->next->name, lem->end) && curr_room->ant_number != -1)
//	{
//		tmp_ant = curr_room->ant_number;
//		curr_room->ant_number = launched_ants;
////		ft_printf("L%d-%s ", curr_room->ant_number, curr_room->name);
//		run_push_path(lem, curr_room->next, launched_ants, tmp_ant);
//	}
//	ft_printf("L%d-%s ", curr_room->ant_number, curr_room->name);
//
//	if (curr_room->next && ft_strequ(curr_room->next->name, lem->end))
//	{
//		curr_room->next->ant_number = curr_room->ant_number;
//		curr_room->ant_number = prev_ant;
//		ft_printf("L%d-%s ", curr_room->ant_number, curr_room->name);
//		return;
//	}
//	else if (curr_room->next && curr_room->ant_number == -1 && curr_room->next->ant_number == -1)
//	{
//		curr_room->ant_number = launched_ants;
//		ft_printf("L%d-%s ", curr_room->ant_number, curr_room->name);
//		return;
//	}
//	else if (curr_room->next && curr_room->ant_number != -1 && curr_room->next->ant_number == -1)
//	{
//		tmp_ant = curr_room->ant_number;
//		curr_room->ant_number = launched_ants;
//		curr_room->next->ant_number = tmp_ant;
//		ft_printf("L%d-%s ", curr_room->ant_number, curr_room->name);
////		run_push_path(lem, curr_room->next, launched_ants, tmp_ant);
//	}
//	else if (curr_room->next && curr_room->next->ant_number != -1 && curr_room->ant_number != -1)
//	{
//		tmp_ant = curr_room->ant_number;
//		curr_room->ant_number = launched_ants;
//		ft_printf("L%d-%s ", curr_room->ant_number, curr_room->name);
//		run_push_path(lem, curr_room->next, launched_ants, tmp_ant);
//	}
}

void push_path(t_lem *lem, t_room *start, int launched_ants)
{
	(void)launched_ants;
	int out_degr_cur;
	t_room *curr_room;

	out_degr_cur = 0;
	while (out_degr_cur < start->out_degree)
	{
		curr_room = ht_get(lem->ht, start->out_link[out_degr_cur]);
		if (curr_room && curr_room->name != NULL && curr_room->name[0] != '\0')
		{
			run_push_path(lem, curr_room, launched_ants, launched_ants);
		}
		out_degr_cur++;
	}
	ft_putchar('\n');
}

void run_path(t_lem *lem, t_room *curr_room, int launched_ants, int *bfs_lvl)
{
	(void)bfs_lvl;
	(void)lem;
	if (curr_room->ant_number == -1)
		curr_room->ant_number = launched_ants;
	while (curr_room)
	{
		if (curr_room->ant_number != -1)
			ft_printf("L%d-%s ", curr_room->ant_number, curr_room->name);
//		if (curr_room->ant_number == -1)
//			curr_room->ant_number = launched_ants;
		curr_room = curr_room->next;
	}
	ft_putchar('\n');
//	print_current_room_state(lem, ht_get(lem->ht, lem->start), *bfs_lvl, launched_ants);
}

void free_ants_and_rooms(t_ht **ants_and_rooms)
{
	t_entry	*entry;
	char	**in_links;
	char	**out_links;
	int i;

	i = 0;
	while (i < TABLE_SIZE)
	{
		if ((*ants_and_rooms)->entries[i])
		{
			entry = (*ants_and_rooms)->entries[i];
			if (entry->value)
			{
				in_links = entry->value->in_link;
				out_links = entry->value->out_link;
				free_str_links(&in_links, &out_links);
				free_entry(&entry);
//			ft_printf("freed rooms = %d\n", ++freed_rooms);
			}
		}
		free((*ants_and_rooms)->entries[i]);
		(*ants_and_rooms)->entries[i] = NULL;
		i++;
	}

}

void launch_ants(t_lem *lem, t_room *start, int ants)
{
	t_ht	*ants_and_rooms;
	int out_degr_cur;
	t_room *curr_room;
	int curr_ant;
	int bfs_lvl;
	int i;

	i = 0;
	curr_ant = 1;
	out_degr_cur = 0;
	bfs_lvl = 0;
	ants_and_rooms = ht_create();
	while (lem->ants_finished < ants)
	{
		while (out_degr_cur < start->out_degree)
		{
			curr_room = ht_get(lem->ht, start->out_link[out_degr_cur]);
			if (curr_ant <= ants && curr_room && curr_room->name != NULL && curr_room->name[0] != '\0')
			{
				ht_set(ants_and_rooms, ft_itoa(curr_ant++), &curr_room);
				bfs_lvl++;
			}
			out_degr_cur++;
		}
		run_current_lvl(ants_and_rooms, curr_ant, lem);
//		ft_putchar('\n');
		out_degr_cur = 0;
	}
	print_current_ants_position(ants_and_rooms, curr_ant, lem);
//	free_ants_and_rooms(&ants_and_rooms);
//	free(ants_and_rooms);
	ants_and_rooms = NULL;
}
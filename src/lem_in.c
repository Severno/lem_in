/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sapril <sapril@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 14:17:21 by sapril            #+#    #+#             */
/*   Updated: 2020/02/17 15:55:04 by sapril           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"
//

int out_links_created = 0;
int in_links_created = 0;
int rooms_created;
t_lem		*create_lem_in()
{
	t_lem *new_lem;

	new_lem = ft_memalloc(sizeof(t_lem));
	new_lem->ht = ht_create();
	new_lem->start = NULL;
	new_lem->end = NULL;
	new_lem->names = NULL;
	new_lem->ants = -1;
	new_lem->rooms_cap = 0;
	new_lem->fd = -1;
	new_lem->start_end_flag = 0;
	new_lem->ants_finished = 0;
	new_lem->fd = 0;
	new_lem->errors = 0;
//	new_lem->queue = create_queue();
//	new_lem->ants = get_ants();
	return (new_lem);
}

t_room *init_link()
{
	t_room *new_room;

	new_room = ft_memalloc(sizeof(t_room));
	new_room->name = NULL;
	new_room->bfs_lvl = -1;
	new_room->coord_x = -1;
	new_room->coord_y = -1;
	new_room->in_degree = 0;
	new_room->out_degree = 0;
	return (new_room);
}

t_room *create_room(char **name, int x, int y)
{
	t_room	*new_room;
	int i;

	i = 0;
	rooms_created++;
//	ft_printf("Create name = %s, room num = %d\n", *name, rooms_created);
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
	new_room->in_link = ft_memalloc(sizeof(char *) * MIN_LINKS);
	new_room->out_link = ft_memalloc(sizeof(char *) * MIN_LINKS);
	while (i < MIN_LINKS)
	{
		new_room->out_link[i++] = ft_memalloc(sizeof(char) * 50);
		out_links_created++;
	}
	i = 0;
	while (i < MIN_LINKS)
	{
		new_room->in_link[i++] = ft_memalloc(sizeof(char) * 50);
		in_links_created++;
	}
	return (new_room);
}

int next_path(t_lem *lem, t_room *curr_room)
{
	int out_degr_cur;
	int is_valid_path;

	out_degr_cur = 0;
	is_valid_path = 0;
	if (ft_strequ(curr_room->name, lem->end))
	{
		curr_room->next = NULL;
		return (1);
	}
	while (out_degr_cur < curr_room->out_degree)
	{
		if ((get_real_out_links(curr_room)) == 0)
		{
			out_degr_cur++;
			return (-1);
		}
		if (curr_room->out_link[out_degr_cur] != NULL && curr_room->out_link[out_degr_cur][0] != '\0')
		{
			curr_room->next = ht_get(lem->ht, curr_room->out_link[out_degr_cur]);
			is_valid_path = next_path(lem, ht_get(lem->ht, curr_room->out_link[out_degr_cur]));
			if (is_valid_path == -1)
				return (-1);
		}
//		next_search(lem, ht_get(lem->ht, curr_room->out_link[out_degr_cur]));
		out_degr_cur++;
	}
	if ((get_real_out_links(curr_room)) == 0)
		return (-1);
	return (is_valid_path);
}

void form_paths(t_lem *lem, t_room *start)
{
	int out_degr_cur;
	int is_valid_path;
	int path_count;
	t_room *cur_room;

	out_degr_cur = 0;
//	out_degr_work= 0;
	path_count = 1;
	is_valid_path = 0;
	ft_printf(RED"Start\n"RESET);
	while (out_degr_cur < start->out_degree)
	{
		cur_room = ht_get(lem->ht, start->out_link[out_degr_cur]);
		if (!cur_room)
		{
			out_degr_cur++;
			continue;
		}
		is_valid_path = next_path(lem, cur_room);
		if (is_valid_path == -1)
		{
			free(start->out_link[out_degr_cur]);
			start->out_link[out_degr_cur] = NULL;
		}
		ft_putchar('\n');
//		out_degr_work = 0;
		out_degr_cur++;
		path_count++;
	}
}

int handle_errors(t_lem *lem)
{
	if (lem->ants < 0)
		exit(free_data(&lem));
	if (lem->end == NULL || lem->start == NULL)
		exit(free_data(&lem));
	if (lem->rooms_cap == 0)
		exit(free_data(&lem));
	return (0);
}

int is_path(t_lem *lem, t_room *start)
{
	int out_degr;
	int path_cap;
	t_room *curr_room;


	out_degr = 0;
	path_cap = 0;
	while (out_degr < start->out_degree)
	{
		curr_room = ht_get(lem->ht, start->out_link[out_degr]);
		if ((get_real_out_links(curr_room)) == 0)
		{
			out_degr++;
			continue;
		}
		while (curr_room)
		{
			if (ft_strequ(curr_room->name, lem->end))
				path_cap++;
			curr_room = curr_room->next;
		}
		out_degr++;
	}
	return path_cap;
}

// ----MAIN LEM_IN----
int			main(int argc, char *argv[])
{
	t_lem *lem;
	t_room *start;

	(void)argc;
	(void)argv;
	lem = create_lem_in();
	get_info(lem, argv[1]);

	start = ht_get(lem->ht, lem->start);
	handle_errors(lem);
//	ft_putstr(lem->names);
//	ht_print(lem->ht);
//	ft_printf("start = %s\n", lem->start);
//	ft_printf("end = %s\n", lem->end);
//	ft_putstr(lem->names);
	ft_printf("In links created = %d\n", in_links_created);
	ft_printf("Out links created = %d\n", out_links_created);
//	ft_printf("Rooms created = %d\n", rooms_created);
//	print_rooms(lem);
	bfs_set_lvl(lem, start, lem->end);
	delete_useless_links(lem, start);
//	print_rooms(lem);
	delete_input_links(lem, start);
//	print_rooms(lem);
	delete_output_links(lem, start);
	print_rooms(lem);
	if (get_real_out_links(start) == 0) // проверка если нет исходящих путей из старта
		exit(free_data(&lem));
	form_paths(lem, start);
	if (!is_path(lem, start))
		exit(free_data(&lem));
//	print_rooms(lem);
	bfs_set_lvl(lem, start, lem->end);
	print_paths_linked_list(lem, start);
//	sleep(100);
	launch_ants(lem,  ht_get(lem->ht, lem->start), lem->ants);
//	print_links(lem);
	close(lem->fd);
	free_data(&lem);
	return (0);
}
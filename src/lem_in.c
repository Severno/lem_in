/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sapril <sapril@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 14:17:21 by sapril            #+#    #+#             */
/*   Updated: 2020/02/04 18:20:23 by sapril           ###   ########.fr       */
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
	new_lem->start_end_flag = 0;
	new_lem->rooms_cap = 0;
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
	new_room = ft_memalloc(sizeof(t_room));
	new_room->bfs_lvl = -1;
	new_room->coord_x = x;
	new_room->coord_y = y;
	new_room->in_degree = 0;
	new_room->out_degree = 0;
	new_room->out_links = ft_memalloc(sizeof(t_room *) * 10);
	new_room->in_links = ft_memalloc(sizeof(t_room *) * 10);
	while (i < MIN_LINKS)
		new_room->out_links[i++] = init_link();
	i = 0;
	while (i < MIN_LINKS)
		new_room->in_links[i++] = init_link();
	new_room->visited = 0;
	new_room->name = ft_strnew(ft_strlen(*name));
	new_room->name = ft_strcpy(new_room->name, *name);
	return (new_room);
}


void print_rooms(t_lem *lem)
{
	int in_degree;
	int out_degree;
	int rooms;

	rooms = 49;
	in_degree = 0;
	out_degree = 0;
	while (rooms < 56)
	{
		ft_printf(RED"----Root NAME = %s, X = %d, Y = %d ----\n"RESET, lem->ht->entries[rooms]->value->name, lem->ht->entries[rooms]->value->coord_x, lem->ht->entries[rooms]->value->coord_y);
		while (out_degree < lem->ht->entries[rooms]->value->out_degree)
		{
			ft_printf(BLUE"Out link NAME = %s, X = %d, Y = %d, link num = %d\n"RESET, lem->ht->entries[rooms]->value->out_links[out_degree]->name,
					  lem->ht->entries[rooms]->value->out_links[out_degree]->coord_x, lem->ht->entries[rooms]->value->out_links[out_degree]->coord_y, out_degree + 1);
			out_degree++;
		}
		while (in_degree < lem->ht->entries[rooms]->value->in_degree)
		{
			ft_printf(MAGENTA"In link NAME = %s, X = %d, Y = %d, link num = %d\n"RESET, lem->ht->entries[rooms]->value->in_links[in_degree]->name,
					  lem->ht->entries[rooms]->value->in_links[in_degree]->coord_x, lem->ht->entries[rooms]->value->in_links[in_degree]->coord_y, in_degree + 1);
			in_degree++;
		}
		in_degree = 0;
		out_degree = 0;
		rooms++;
		ft_putchar('\n');
	}

}


// ----TEST QUEUE---- IT WORKS
//int			main(int argc, char *argv[])
//{
//	t_queue *queue;
//	t_room *room1;
//	t_room *room2;
//	t_room *room3;
//	t_room *room4;
//	t_room *room5;
//	t_room *room6;
//
//	queue = create_queue();
//
//	room1 = ft_memalloc(sizeof(t_room));
//	room1->name = "Hello";
//	room1->coord_x = 1;
//	room1->coord_y = 2;
//	room2 = ft_memalloc(sizeof(t_room));
//	room2->name = "World";
//	room2->coord_x = 3;
//	room2->coord_y = 4;
//	room3 = ft_memalloc(sizeof(t_room));
//	room3->name = "Yes";
//	room3->coord_x = 5;
//	room3->coord_y = 6;
//	room4 = ft_memalloc(sizeof(t_room));
//	room4->name = "This";
//	room4->coord_x = 7;
//	room4->coord_y = 8;
//	room5 = ft_memalloc(sizeof(t_room));
//	room5->name = "is";
//	room5->coord_x = 9;
//	room5->coord_y = 10;
//	room6 = ft_memalloc(sizeof(t_room));
//	room6->name = "Dog";
//	room6->coord_x = 11;
//	room6->coord_y = 12;
//
//	enqueue(queue, room1);
//	enqueue(queue, room2);
//	enqueue(queue, room3);
//	enqueue(queue, room4);
//	enqueue(queue, room5);
//	enqueue(queue, room6);
//
//	display(queue);
//	ft_putchar('\n');
//	dequeue(queue);
//	dequeue(queue);
//	dequeue(queue);
//	ft_putchar('\n');
//	display(queue);
//
//	return (0);
//}

// ---------------------------------

// ----MAIN LEM_IN----
int			main(int argc, char *argv[])
{
	t_lem *lem;
	t_queue *queue;
//	int n;
//
//	n = 0;
//	n = n ^ 1;
//	n = n ^ 2;
//	if (n)
//		printf("%d\n", n);
	(void)argc;
	(void)argv;
	lem = create_lem_in();
	lem->fd = open("../maps/test.map", O_RDONLY);
	get_info(lem, "../maps/test.map");
	ft_putstr(lem->names);
	ht_print(lem->ht);
	ft_printf("start = %s\n", lem->start);
	ft_printf("end = %s\n", lem->end);
	ft_putstr(lem->names);
//	print_rooms(lem);
//	bfs_set_lvl(lem, ht_get(lem->ht, lem->start));
	free_data(&lem);
	return (0);
}
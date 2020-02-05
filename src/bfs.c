#include "../includes/lem_in.h"

int malloc_entries = 0;
int freed_entries = 0;

t_ht		*create_seen()
{
	t_ht *new_ht;
	int i;

	if (!(new_ht = ft_memalloc(sizeof(t_ht))))
		return (NULL);
	if (!(new_ht->entries = ft_memalloc(sizeof(t_entry *) * (TABLE_SIZE))))
		return (NULL);
	i = 0;
	while (i < TABLE_SIZE)
	{
		new_ht->entries[i++] = ft_memalloc(sizeof(t_entry));
		malloc_entries++;
	}
	return (new_ht);
}

void set_bfs_lvl(t_lem *lem, t_qnode *current, int	out_degree, t_ht *ht)
{
	t_room *curr_room;

	curr_room = ht_get(lem->ht, current->room->out_link[out_degree]);
	if (ft_strequ(curr_room->name, lem->end))
		curr_room->bfs_lvl = MAX_INTEGER;
	if (curr_room->bfs_lvl == -1)
		curr_room->bfs_lvl = current->room->bfs_lvl + 1;

}


void		bfs_set_lvl(t_lem *lem, t_room *start)
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
//		print_queue(queue);
//		print_ht_seen(seen);
		current = dequeue(queue);
		if (!current || !current->room->name)
			continue;
//		print_queue(queue);
//		print_ht_seen(seen);
//		ft_printf(BLUE"Current working %s \n"RESET, current->room->name);
		if (!ht_get(seen, current->room->name)) // проверяем есть ли в просмотренных
		{
			ht_set(seen, current->room->name, &current->room); // если нет, добавляем в просмотренные
			ft_printf("Current node = %s, bfs_lvl = %d\n", current->room->name, current->room->bfs_lvl);
			while (out_degree < current->room->out_degree) // смотрим все исходящие ссылки из текущий комнаты
			{
				set_bfs_lvl(lem, current, out_degree, lem->ht);
				if (!ht_get(seen, current->room->out_link[out_degree])) // если его нет в просмотренном добавляем в очередь
					enqueue(queue, ht_get(lem->ht, current->room->out_link[out_degree]));
//				print_queue(queue);
//				print_ht_seen(seen);
				ft_printf("Current node = %s, bfs_lvl = %d\n", current->room->out_link[out_degree], ht_get(lem->ht, current->room->out_link[out_degree])->bfs_lvl);
				out_degree++;
			}
		}
//		print_queue(queue);
//		print_ht_seen(seen);
		free(current);
		out_degree = 0;
	}
	free(queue);
	free_seen(&lem, &seen);
	ft_printf("Malloc entries %d\n", malloc_entries);
	ft_printf("Freed entries %d\n", freed_entries);
	delete_useless_links(lem, start);
}

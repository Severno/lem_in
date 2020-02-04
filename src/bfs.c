#include "../includes/lem_in.h"

void free_seen(t_lem *lem, t_ht *seen)
{
	int i;

	i = 0;
	while (i < lem->rooms_cap)
		free(seen->entries[i++]);
	free(seen->entries);
}

t_ht		*create_seen(int size)
{
	t_ht *new_ht;
	int i;

	if (!(new_ht = ft_memalloc(sizeof(t_ht))))
		return (NULL);
	if (!(new_ht->entries = ft_memalloc(sizeof(t_entry *) * size + 20)))
		return (NULL);
	i = 0;
	while (i < size + 20)
		new_ht->entries[i++] = ft_memalloc(sizeof(t_entry));
	return (new_ht);
}

void set_bfs_lvl(t_lem *lem, t_qnode *current, int	out_degree)
{
	int in_degree;
	int min_bfs_level;

	in_degree = 0;
	min_bfs_level = -1;
	if (ft_strequ(current->room->out_links[out_degree]->name, lem->end))
		current->room->out_links[out_degree]->bfs_lvl = MAX_INTEGER;
	if (current->room->out_links[out_degree]->bfs_lvl == -1
		&& current->room->out_links[out_degree]->in_links)
		current->room->out_links[out_degree]->bfs_lvl = current->room->bfs_lvl + 1;

}

void		bfs_set_lvl(t_lem *lem, t_room *start)
{
	t_ht	*seen;
	t_queue	*queue;
	t_qnode *current;
	int		out_degree;
	int		bfs_lvl;

	out_degree = 0;
	bfs_lvl = 1;
	seen = create_seen(lem->rooms_cap);
	queue = queue_create();
	enqueue(queue, start);
	start->bfs_lvl = 0;
	while (queue->front)
	{
		current = queue_get_front(&queue);
		if (!ht_get(seen, current->room->name))
		{
			ht_set(seen, current->room->name, &current->room);
			ft_printf("Current node = %s, bfs_lvl = %d\n", current->room->name, current->room->bfs_lvl);
			while (current->room->out_links[out_degree]->name != NULL)
			{
				set_bfs_lvl(lem, current, out_degree);
				if (!ht_get(seen, current->room->out_links[out_degree]->name))
					enqueue(queue, current->room->out_links[out_degree]);
				ft_printf("Current node = %s, bfs_lvl = %d\n", current->room->out_links[out_degree]->name, current->room->out_links[out_degree]->bfs_lvl);
				out_degree++;
			}
		}
		out_degree = 0;
	}
	free_seen(lem, seen);
}

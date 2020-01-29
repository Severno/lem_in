/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sapril <sapril@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 11:16:29 by sapril            #+#    #+#             */
/*   Updated: 2020/01/29 19:09:10 by sapril           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void			free_room_links(t_room **room)
{
	int in_count;
	int out_count;

	in_count = 0;
	out_count = 0;
	while (in_count < (*room)->in_degree)
	{
		free((*room)->in_links[in_count]);
		in_count++;
	}
	while (out_count < (*room)->out_degree)
	{
		free((*room)->out_links[out_count]);
		out_count++;
	}
}

void			free_hash_table_entries(t_lem **lem, t_room *check_room, unsigned long slot)
{
	int j;

	j = 0;
	while (j < MIN_LINKS)
	{
		if (check_room)
		{
			if ((*lem)->ht->entries[slot]->value->out_links[j] != (*lem)->ht->entries[slot]->value->in_links[j])
			{
				free((*lem)->ht->entries[slot]->value->out_links[j]);
				(*lem)->ht->entries[slot]->value->out_links[j] = NULL;
				free((*lem)->ht->entries[slot]->value->in_links[j]);
				(*lem)->ht->entries[slot]->value->in_links[j] = NULL;
			}
		}
		j++;
	}
}

void				free_hash_table_main(unsigned long slot, t_lem **lem)
{
	free((*lem)->ht->entries[slot]->value->out_links);
	free((*lem)->ht->entries[slot]->value->in_links);
	free((*lem)->ht->entries[slot]->value->name);
	free((*lem)->ht->entries[slot]->value);
	free((*lem)->ht->entries[slot]->key);
	free((*lem)->ht->entries[slot]);
}

void				free_hash_table(t_lem **lem)
{
	char			**split_names;
	t_room			*check_room;
	unsigned long	slot;
	int				i;

	i = 0;
	split_names = ft_strsplit((*lem)->names, '\n');
	while (split_names[i])
	{
		slot = hash(split_names[i]);
		check_room = ht_get((*lem)->ht, split_names[i]);
		free_room_links(&(*lem)->ht->entries[slot]->value);
		free_hash_table_entries(lem, check_room, slot);
		free_hash_table_main(slot, lem);
		i++;
	}
	free((*lem)->ht->entries);
	free((*lem)->ht);
	free_split_str(&split_names);
}

void				free_data(t_lem **lem)
{
	if ((*lem)->ht)
		free_hash_table(lem);
	if (*lem)
	{
		(*lem)->names ? free((*lem)->names) : 0;
		(*lem)->start ? free((*lem)->start) : 0;
		(*lem)->end ? free((*lem)->end) : 0;
		free(*lem);
	}
}

void				free_split_str(char ***tab)
{
	int		i;

	i = 0;
	while ((*tab)[i])
	{
		if ((*tab)[i] != NULL)
			free((*tab)[i]);
		i++;
	}
	free(*tab);
	*tab = 0;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sapril <sapril@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 11:16:29 by sapril            #+#    #+#             */
/*   Updated: 2020/02/05 13:00:03 by sapril           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int freed_in = 0;
int freed_out = 0;
int freed_rooms = 0;

int				free_data(t_lem **lem)
{
	int i;

	i = 0;
	while (i < TABLE_SIZE)
		free_entries(lem, i++);
	free_lem(lem);
	return (1);
}

void 			free_entries(t_lem **lem, int i)
{
	t_entry	*entry;
	char	**in_links;
	char	**out_links;

	if ((*lem)->ht->entries[i])
	{
		entry = (*lem)->ht->entries[i];
		if (entry->value)
		{
			in_links = entry->value->in_link;
			out_links = entry->value->out_link;
			free_str_links(&in_links, &out_links);
			free_entry(&entry);
//			ft_printf("freed rooms = %d\n", ++freed_rooms);
		}
	}
	free((*lem)->ht->entries[i]);
	(*lem)->ht->entries[i] = NULL;
}

void			free_entry(t_entry **entry)
{
	free((*entry)->value->name);
	free((*entry)->value);
	free((*entry)->key);
}

void			free_lem(t_lem **lem)
{
	free((*lem)->ht->entries);
	free((*lem)->ht);
	free((*lem)->names);
	free((*lem)->end);
	free((*lem)->start);
	free((*lem));
}

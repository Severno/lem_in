/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sapril <sapril@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 09:15:32 by sapril            #+#    #+#             */
/*   Updated: 2020/01/29 17:07:55 by sapril           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

unsigned long		hash(const char *key)
{
	unsigned int	i;
	unsigned int	key_len;
	unsigned long	value;

	i = 0;
	key_len = ft_strlen(key);
	value = 0;
	while (i < key_len)
		value = (value * NICE_PRIME_NUMBER) + key[i++];
	value = value % TABLE_SIZE;
	return (value);
}

t_ht				*ht_create(void)
{
	t_ht			*hash_table;
	unsigned long	i;

	i = 0;
	hash_table = ft_memalloc(sizeof(t_ht));
	hash_table->entries = ft_memalloc(sizeof(t_entry *) * TABLE_SIZE);
	while (i < TABLE_SIZE)
		hash_table->entries[i++] = NULL;

	return (hash_table);
}

t_entry				*ht_pair(const char *key, t_room **value)
{
	t_entry *entry;

	entry = ft_memalloc(sizeof(t_entry));
	entry->key = ft_strnew(sizeof(ft_strlen(key)));
	entry->key = ft_strcpy(entry->key, key);
	entry->value = *value;
	entry->next = NULL;
	return (entry);
}

void				ht_set(t_ht *hashtable, const char *key, t_room **value)
{
	unsigned long	slot;
	t_entry			*entry;
	t_entry			*prev;

	slot = hash(key);
	entry = hashtable->entries[slot];
	if (entry == NULL)
	{
		hashtable->entries[slot] = ht_pair(key, value);
		return ;
	}

	while (entry)
	{
		if (ft_strcmp(entry->key, key) == 0)
		{
			free(entry->value);
			entry->value = *value;
			return;
		}
		prev = entry;
		entry = prev->next;
//		prev->next = entry;
	}
	prev->next = ht_pair(key, value);
}

t_room		*ht_get(t_ht *hashtable, const char *key)
{
	unsigned long	slot;
	t_entry 		*entry;

	slot = hash(key);
	entry = hashtable->entries[slot];
	if (entry == NULL)
		return (NULL);
	while (entry != NULL)
	{
		if (ft_strcmp(entry->key, key) == 0)
			return (entry->value);
		entry = entry->next;
	}
	return (NULL);
}

void	ht_print(t_ht *hashtable)
{
	unsigned long	i;
	unsigned long	elems;
	t_entry			*entry;

	i = 0;
	elems = 1;
	while (i < TABLE_SIZE)
	{
		entry = hashtable->entries[i];
		if (entry == NULL)
		{
			i++;
			continue;
		}

		ft_printf("slot[%4d]: ", i);
		while (1)
		{
			ft_printf(CYAN" el: %lu"RESET" - %s = x - %d, y - %d ", elems, entry->key, entry->value->coord_x, entry->value->coord_y);
			if (entry->next == NULL)
				break;
			ft_putstr(RED"/"RESET);
			entry = entry->next;
			elems++;
		}
		elems = 1;
		ft_putchar('\n');
		i++;
	}
}

//int main()
//{
//	t_ht *ht = ht_create();
//	int arr[2] = {1,2};
//	int arr1[2] = {112233,99};
//	int arr2[2] = {0,212321};
//	int arr3[2] = {123,222};
//	int arr4[2] = {10,20};
//	int arr5[2] = {42,33};
//	ht_set(ht, "name1", arr);
//	ht_set(ht, "name2", arr1);
//	ht_set(ht, "name3", arr2);
//	ht_set(ht, "name4", arr3);
//	ht_set(ht, "name5", arr4);
//	ht_set(ht, "name6", arr5);
//	ht_print(ht);
//	return (0);
//}
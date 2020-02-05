/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sapril <sapril@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 20:05:00 by sapril            #+#    #+#             */
/*   Updated: 2020/02/05 20:05:08 by sapril           ###   ########.fr       */
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
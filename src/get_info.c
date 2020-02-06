/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sapril <sapril@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 09:50:58 by sapril            #+#    #+#             */
/*   Updated: 2020/02/06 17:25:17 by sapril           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

// VALIDATION

//Map must have a valid number of ants: 1 <= number of ants <= INT_MAX.
//
//Map must have the start and the end rooms.
//
//Map must have no rooms with the same names. Each room name must be unique.
//
//Map must have no rooms with the same coordinates.
//
//Map must have one or more links.
//
//Each link must have valid names of the start and the end rooms. It means that rooms with these names are present in map file.
//
//Map must have no duplicates of links. There are no links that connect the same points.

void			add_link(t_lem *lem, char *lines, char **split_str)
{
	t_room 	*from;
	t_room	*to;
	char	*tmp;
	char	**split_connections;

	free_split_str(&split_str);
	split_connections = ft_strsplit(lines, '-');
	free(lines);
	lines = NULL;
	if (is_connection(lem, split_connections))
	{
		from = ht_get(lem->ht, split_connections[0]);
		to = ht_get(lem->ht, split_connections[1]);
		if (from->out_link[from->out_degree] == NULL)
		{
			from->out_link[from->out_degree] = ft_strnew(ft_strlen(to->name) + 1);
			from->out_link[from->out_degree] = ft_strcpy(from->out_link[from->out_degree], to->name);
		}
		else
		{
			tmp = from->out_link[from->out_degree];
			from->out_link[from->out_degree] = ft_strjoin(from->out_link[from->out_degree], to->name);
			free(tmp);
		}
		from->out_degree++;
		if (to->in_link[to->in_degree] == NULL)
		{
			to->in_link[to->in_degree] = ft_strnew(ft_strlen(from->name) + 1);
			to->in_link[to->in_degree] = ft_strcpy(to->in_link[to->in_degree], from->name);
		}
		else
		{
			tmp = to->in_link[to->in_degree];
			to->in_link[to->in_degree] = ft_strjoin(to->in_link[to->in_degree] , from->name);
			free(tmp);
		}
		to->in_degree++;
	}
	free_split_str(&split_connections);
}

void			add_el_to_hash_map(t_lem *lem, char **lines, char **split_str)
{
	t_room	*new_room;

	new_room = create_room(&split_str[0], ft_atoi(split_str[1]), ft_atoi(split_str[2]));
	ht_set(lem->ht, split_str[0], &new_room);
	lem->rooms_cap++;
	free_split_str(&split_str);
	free(*lines);
	*lines = NULL;
}

void			add_start_or_end(t_lem *lem, char **split_str, char **lines)
{
	char	*tmp_dest;
	t_room	*new_room;

	tmp_dest = ft_strdup(*lines);
	free(*lines);
	(*lines) = NULL;
	free_split_str(&split_str);
	get_next_line(lem->fd, lines);
	split_str = ft_strsplit(*lines, ' ');
	if (ft_strequ(tmp_dest, "##end") && !(lem->start_end_flag & 1)) {
		lem->start_end_flag ^= 1;
		lem->end = ft_strdup(split_str[0]);
	}
	if (ft_strequ(tmp_dest, "##start") && !(lem->start_end_flag & 2))
	{
		lem->start_end_flag ^= 2;
		lem->start = ft_strdup(split_str[0]);
	}
	new_room = create_room(&split_str[0], ft_atoi(split_str[1]), ft_atoi(split_str[2]));
	ht_set(lem->ht, split_str[0], &new_room);
	lem->rooms_cap++;
	free_split_str(&split_str);
	free(*lines);
	*lines = NULL;
	free(tmp_dest);
}

int check_coord_valid(char *x, char *y)
{
	if (ft_str_is_numeric_no_spaces(x)
		&& ft_strlen(x) <= 10
		&& ft_str_is_numeric_no_spaces(y)
		&& ft_strlen(y) <= 10)
		return (1);
	return (0);
}

void		get_info(t_lem *lem, char *file_name)
{
	char	*lines;
	char	**split_str;
	
	(void)file_name;

	while (get_next_line(lem->fd, &lines) > 0)
	{
		split_str = ft_strsplit(lines, ' ');
		if (is_comment(lines))
		{
			free_split_str(&split_str);
			free(lines);
			lines = NULL;
			continue;
		}
		else if (is_ant(lines, split_str))
		{
			lem->ants = ft_atoi(split_str[0]);
			free_split_str(&split_str);
			free(lines);
			lines = NULL;
		}
		else if (is_end_or_start(lem, split_str))
			add_start_or_end(lem, split_str, &lines);
		else if (is_room(split_str, &lines))
			add_el_to_hash_map(lem, &lines, split_str);
		else if (ft_strchr(lines, '-'))
			add_link(lem, lines, split_str);
		else
		{
			free_split_str(&split_str);
			free(lines);
			lines = NULL;
		}
	}
}

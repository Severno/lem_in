/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sapril <sapril@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 09:50:58 by sapril            #+#    #+#             */
/*   Updated: 2020/01/29 19:01:14 by sapril           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void			add_special_el(t_lem *lem, char **dest, char **lines, char **split_str)
{
	int		arr[2];
	char	*tmp;
	t_room 	*new_room;

	free_split_str(&split_str);
	free(*lines);
	get_next_line(lem->fd, lines);
	split_str = ft_strsplit(*lines, ' ');
	free(*lines);
	tmp = lem->names;
	lem->names = ft_strjoin(lem->names, split_str[0]);
	free(tmp);
	tmp = lem->names;
	lem->names = ft_strjoin(lem->names, "\n");
	free(tmp);
	*dest = ft_strnew(sizeof(char) * ft_strlen(split_str[0]));
	*dest = ft_strcpy(*dest, split_str[0]);
	if (ft_str_is_numeric_no_spaces(split_str[1])
		&& ft_strlen(split_str[1]) <= 10
		&& ft_str_is_numeric_no_spaces(split_str[2])
		&& ft_strlen(split_str[2]) <= 10)
	{
		arr[0] = ft_atoi(split_str[1]);
		arr[1] = ft_atoi(split_str[2]);
	}
	new_room = create_room(&split_str[0], arr[0], arr[1]);
	ht_set(lem->ht, split_str[0], &new_room);
	free_split_str(&split_str);
}

void			add_el(t_lem *lem, char **lines, char **split_str)
{
	int		arr[2];
	char	*tmp;
	t_room 	*new_room;

	free_split_str(&split_str);
	split_str = ft_strsplit(*lines, ' ');
	free(*lines);
	tmp = lem->names;
	lem->names = ft_strjoin(lem->names, split_str[0]);
	free(tmp);
	tmp = lem->names;
	lem->names = ft_strjoin(lem->names, "\n");
	free(tmp);
	if (ft_str_is_numeric_no_spaces(split_str[1])
		&& ft_strlen(split_str[1]) <= 10
		&& ft_str_is_numeric_no_spaces(split_str[2])
		&& ft_strlen(split_str[2]) <= 10)
	{
		arr[0] = ft_atoi(split_str[1]);
		arr[1] = ft_atoi(split_str[2]);
	}
	new_room = create_room(&split_str[0], arr[0], arr[1]);
	ht_set(lem->ht, split_str[0], &new_room);
	free_split_str(&split_str);
}

void		get_lines(t_lem *lem, char *file_name)
{
	int		fd;
	char	*lines;
	char	**split_str;
	char	**split_connections;
	t_room	*from;
	t_room	*to;
	int		arr[2];

	while (get_next_line(lem->fd, &lines) > 0)
	{
		split_str = ft_strsplit(lines, ' ');
		if (lines[0] == '#' && lines[1] != '#')
		{
			free_split_str(&split_str);
			free(lines);
			continue;
		}
		else if (ft_str_is_numeric_no_spaces(split_str[0]) && split_str[1] == NULL && !ft_strchr(lines, '-'))
		{
			lem->ants = ft_atoi(split_str[0]);
			free(lines);
			free_split_str(&split_str);
		}
		else if (ft_strequ(lines, "##start") && lem->start == NULL)
			add_special_el(lem, &lem->start, &lines, split_str);
		else if (ft_strequ(lines, "##end") && lem->end == NULL)
			add_special_el(lem, &lem->end, &lines, split_str);
		else if (!ft_strchr(lines, '-') && split_str[0]
		&& ft_str_is_numeric_no_spaces(split_str[1])
		&& ft_str_is_numeric_no_spaces(split_str[2]))
			add_el(lem, &lines, split_str);
		else if (ft_strchr(lines, '-'))
		{
			free_split_str(&split_str);
			split_connections = ft_strsplit(lines, '-');
			free(lines);
			if (ht_get(lem->ht, split_connections[0]) && ht_get(lem->ht, split_connections[1]))
			{
				from = ht_get(lem->ht, split_connections[0]);
				to = ht_get(lem->ht, split_connections[1]);
				from->out_links[from->out_degree++] = to->in_links[to->in_degree++];
			}
			free_split_str(&split_connections);
		}
		else
		{
			free(lines);
			free_split_str(&split_str);
		}

//		if (ft_strchr(lines, '-'))
//		{
//			split_connections = ft_strsplit(lines, '-');
//			if ()
//		}
//		printf("%s\n", lines);
	}
}

void		get_ants(t_lem *lem)
{

}

void		get_rooms(t_lem *lem)
{

}

void		get_connections(t_lem *lem)
{

}

void		get_comments(t_lem *lem)
{

}

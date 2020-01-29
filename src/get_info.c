/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sapril <sapril@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 09:50:58 by sapril            #+#    #+#             */
/*   Updated: 2020/01/28 15:21:18 by sapril           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void		get_lines(t_lem *lem, char *file_name)
{
	int		fd;
	char	*lines;

	lem->fd = open(file_name, O_RDONLY);
	while (get_next_line(lem->fd, &lines))
	{
		if (lines[0] != '#' && ft_str_is_numeric_no_spaces(lines))
			lem->ants = ft_atoi(lines);
		if (ft_strequ(lines, "##start"))
		{
			get_next_line(lem->fd, &lines);

		}
			get_rooms(lem);
//		printf("%s\n", lines);
	}
}

void		get_ants(t_lem *lem)
{

}

void		get_rooms(t_lem *lem)
{
	char	*lines;
	char	**str_split;

	while (get_next_line(lem->fd, &lines))
	{
		if (ft_strequ(lines, "##end"))
		{
			get_next_line(lem->fd, &lines);
			break;
		}
		if (lines[0] == '#' && lines[1] != '#')
			continue;
		str_split = ft_strsplit(lines, ' ');
		printf("%s\n", lines);
	}
}

void		get_connections(t_lem *lem)
{

}

void		get_comments(t_lem *lem)
{

}

t_room		*create_room(char *name, char *coord_x, char *coord_y)
{
	t_room *new_room;

	new_room = ft_memalloc(sizeof(t_room));
	new_room->name = ft_strcpy(new_room->name, name);
	new_room->coord_x = ft_atoi(coord_x);
	new_room->coord_y = ft_atoi(coord_y);
	return (new_room);
}

int			get_rooms
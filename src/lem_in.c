/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sapril <sapril@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 14:17:21 by sapril            #+#    #+#             */
/*   Updated: 2020/02/19 13:29:09 by sapril           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

// ----MAIN LEM_IN----
int			main(int argc, char *argv[])
{
	t_lem *lem;
	t_room *start;

	(void)argc;
	(void)argv;
	lem = create_lem_in();
//	if (!is_valid_map(lem))
//		return (0);
	get_info(lem, argv[1]);
	start = ht_get(lem->ht, lem->start);
	handle_errors(lem);
//	ft_putstr(lem->names);
//	ht_print(lem->ht);
//	ft_printf("start = %s\n", lem->start);
//	ft_printf("end = %s\n", lem->end);
//	ft_putstr(lem->names);
//	ft_printf("In links created = %d\n", in_links_created);
//	ft_printf("Out links created = %d\n", out_links_created);
//	ft_printf("Rooms created = %d\n", rooms_created);
//	print_rooms(lem);
	print_lines(lem->concat_lines);
	bfs_set_lvl(lem, start, lem->end);
	delete_useless_links(lem, start);
//	print_rooms(lem);
//	print_rooms(lem);
	delete_input_links(lem, start);
	delete_output_links(lem, start);
//	print_rooms(lem);
//	print_rooms(lem);
	print_rooms(lem);
	if (get_real_out_links(start) == 0) // проверка если нет исходящих путей из старта
		exit(free_data(&lem));
	form_paths(lem, start);
//	if (!is_path(lem, start))
//		exit(free_data(&lem));
//	print_rooms(lem);
//	bfs_set_lvl(lem, start, lem->end);
//	sleep(1000);
//	print_rooms(lem);
	print_paths_linked_list(lem, start);
//	sleep(1000);
	launch_ants(lem,  ht_get(lem->ht, lem->start), lem->ants);
//	print_links(lem);
	close(lem->fd);
	free_data(&lem);
	return (0);
}
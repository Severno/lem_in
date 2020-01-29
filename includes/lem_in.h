#ifndef LEM_IN_H
# define LEM_IN_H
# include "../libft/includes/libft.h"
typedef struct		s_room
{
	char			*name;
	int				visited;
	int				coord_x;
	int				coord_y;
	int				start;
	int				end;
	int				in_links;
	int				out_links;
	int				bfs_lvl;
}					t_room;

typedef struct		s_lem
{
	int				ants;
	char			**lines;
	char			*start;
	char			*end;
	int				fd;

}					t_lem;

// get_info
void				get_ants();
void				get_rooms();
void				get_connections();
void				get_comments();
void				get_lines(t_lem *lem, char *file_name);

#endif

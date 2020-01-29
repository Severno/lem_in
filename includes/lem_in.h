#ifndef LEM_IN_H
# define LEM_IN_H
# include "../libft/includes/libft.h"
# define TABLE_SIZE 100000
# define NICE_PRIME_NUMBER 37
# define MIN_LINKS 10
# define X 0
# define Y 1
# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define BLUE    "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN    "\x1b[36m"
# define RESET   "\x1b[0m"
# define CLR "\e[1;1H\e[2J"
# define WHITE   "\x1B[37m"

typedef struct		s_room
{
	char			*name;
	int				visited;
	int				coord_x;
	int				coord_y;
	char			*start;
	char			*end;
	int				in_degree;
	int				out_degree;
	struct s_room	**in_links;
	struct s_room	**out_links;
	int				bfs_lvl;
}					t_room;

typedef struct		s_entry
{
	char			*key;
	t_room			*value;
	struct			s_entry *next;
}					t_entry;

typedef struct		s_hash_table
{
	t_entry			**entries;
}					t_ht;

typedef struct		s_lem
{
	int				ants;
	char			**lines;
	char			*names;
	t_ht			*ht;
	char			*start;
	char			*end;
	int				fd;

}					t_lem;

// hashmap
unsigned long		hash(const char *key);
t_ht				*ht_create(void);
t_entry				*ht_pair(const char *key, t_room **value);
void				ht_set(t_ht *hashtable, const char *key, t_room **value);
t_room				*ht_get(t_ht *hashtable, const char *key);
void				ht_print(t_ht *hashtable);

//lemin
t_room				*create_room(char **name, int x, int y);

// get_info
void				get_ants();
void				get_rooms();
void				get_connections();
void				get_comments();
void				get_lines(t_lem *lem, char *file_name);
void				add_special_el(t_lem *lem, char **dest, char **lines, char **split_str);

// free data
void				free_hash_table_entries(t_lem **lem, t_room *check_room, unsigned long slot);
void				free_hash_table_main(unsigned long slot, t_lem **lem);
void				free_hash_table(t_lem **lem);
void				free_data(t_lem **lem);
void				free_split_str(char ***tab);

#endif

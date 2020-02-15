#ifndef LEM_IN_H
# define LEM_IN_H
# include "../libft/includes/libft.h"
# define TABLE_SIZE 100000
# define NICE_PRIME_NUMBER 37
# define MIN_LINKS 30
# define QUEUE_SIZE 5000
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

struct		s_room;
struct		s_entry;
struct		s_hash_table;
struct		s_qnode;
struct		s_queue;
struct		s_lem;

typedef struct		s_room
{
	char			*name;
	int				coord_x;
	int				coord_y;
	char			*start;
	char			*end;
	int				in_degree;
	int				out_degree;
	char			**in_link;
	char			**out_link;
	int				bfs_lvl;
	struct s_room	*next;
	int				ant_number;
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

//typedef struct		s_queue
//{
//	t_room 			**a;
//	int				front;
//	int				back;
//}					t_queue;

typedef struct			s_qnode
{
	t_room				*room;
	struct s_qnode		*next;
}						t_qnode;

typedef struct			s_queue
{
	t_qnode				*front;
	t_qnode				*rear;
}						t_queue;

typedef struct		s_lem
{
	int				ants;
	int				rooms_cap;
//	char			**lines;
	char			*names;
	t_ht			*ht;
	char			*start;
	char			*end;
	int				fd;
	char			start_end_flag;
	int				ants_finished;
//	t_queue			*queue;
}					t_lem;

// hashmap
unsigned long		hash(const char *key);
t_ht				*ht_create(void);
t_entry				*ht_pair(const char *key, t_room **value);
void				ht_set(t_ht *hashtable, const char *key, t_room **value);
t_room				*ht_get(t_ht *hashtable, const char *key);
void				ht_print(t_ht *hashtable);
void				ht_print(t_ht *hashtable);

// queue
//t_queue				*create_queue();
//void				enqueue(t_queue *queue, t_room *room);
//t_room				*dequeue(t_queue *queue);
//void				display(t_queue *queue);

// queue linked list
t_queue				*queue_create();
t_qnode				*queue_new_node(t_room *room);
void				enqueue(t_queue *queue, t_room *room);
t_qnode				*dequeue(t_queue *queue);
t_qnode				*queue_get_front(t_queue **queue);
void				print_queue(t_queue *queue);

// bfs
t_ht				*create_seen();
void				bfs_set_lvl(t_lem *lem, t_room *start, char *end);
void				reverse_set_bfs_lvl(t_lem *lem, t_qnode *current, int	in_degree, char *end);
void				reverse_bfs_set_lel(t_lem *lem, t_room *start, char *end);
/*
	link_optimization
*/
int					get_pos_link_out(char **out_links, char *in_link, int out_degree);
void				remove_dead_link(t_lem *lem, t_room *dead_room);
int					get_pos_link_in(char **in_links, char *out_link, int in_degree);
void				delete_current_link(t_room *from, t_room *to, int out_pos, int in_pos);
void				delete_useless_links(t_lem *lem, t_room *start);
void				delete_input_links(t_lem *lem, t_room *start);
void				delete_cur_output_link(t_room *curr_room, t_lem *lem);
void				delete_output_links(t_lem *lem, t_room *start);
/*
	printing
*/
void 				print_ht_seen(t_ht *seen);
void 				print_links(t_lem *lem);
void 				print_rooms(t_lem *lem);
void 				print_paths_linked_list(t_lem *lem, t_room *start);
void 				print_current_ants_position(t_ht *ants_and_rooms, int curr_ant, t_lem *lem);

//lemin
t_room				*create_room(char **name, int x, int y);

// get_info
void				get_info(t_lem *lem, char *file_name);
void				add_link(t_lem *lem, char *lines, char **split_str);
void				add_el_to_hash_map(t_lem *lem, char **lines, char **split_str);
void				add_start_or_end(t_lem *lem, char **split_str, char **lines);
int					check_coord_valid(char *x, char *y);

// free data
int					free_data(t_lem **lem);
void 				free_entries(t_lem **lem, int i);
void				free_lem(t_lem **lem);
void				free_entry(t_entry **entry);

// free data2
void				free_seen(t_ht **seen);
void				free_str_links(char ***in_links, char ***out_links);
void				free_split_str(char ***tab);

// validation
int					is_end_or_start(t_lem *lem, char **split_str);
int					is_room(char **split_str, char **lines);
int					is_connection(t_lem *lem, char **split_connections);
int					is_ant(const char *lines, char **split_str);
int					is_comment(const char *lines);

// room_utils
int					get_real_out_links(t_room *curr_room);
int					get_real_in_links(t_room *curr_room);

// Ants
void				run_path(t_lem *lem, t_room *curr_room, int launched_ants, int *bfs_lvl);
void				launch_ants(t_lem *lem, t_room *start, int ants);
#endif

#include "../includes/ft_select.h"

t_file *init_file_list()
{
	t_file *file_list;

	file_list = (t_file*)malloc(sizeof(t_file));
	file_list->next = NULL;
	file_list->name = NULL;
	file_list->len = 0;
	file_list->type = 0;
	return (file_list);
}
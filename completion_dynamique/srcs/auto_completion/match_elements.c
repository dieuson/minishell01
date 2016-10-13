#include "../../includes/ft_select.h"

static t_file 	*get_values(t_file *match_files)
{
	FT_INIT(t_file*, head, match_files);
	FT_INIT(int, nb_elem, 0);
	FT_INIT(int, len_str, 0);
	if (!match_files)
		return (NULL);
	while (match_files)
	{
		nb_elem++;
		len_str = match_files->len > len_str ? match_files->len : len_str;
		match_files = match_files->next;
	}
	head->len = len_str;
	head->nb_elem = nb_elem;
	return (head);
}

t_file 			*compare_list_sentence(t_file *files, char *sentence)
{
	FT_INIT(t_file*, match_files, NULL);
	FT_INIT(t_file*, head, NULL);
	while (files)
	{
		if (files && !ft_strncmp(files->name, sentence, ft_strlen(sentence)))
		{
			if ((files->name)[0] == '.' && !ft_strcmp(sentence, ""))
				;
			else
			{
				if (!match_files)
					MULTI(head, match_files, files);
				else
				{
					match_files->next = files;
					match_files = match_files->next;
				}
			}
		}
		files = files->next;
	}
	if (match_files)
		match_files->next = NULL;
	head = get_values(head);
	return (head);
}
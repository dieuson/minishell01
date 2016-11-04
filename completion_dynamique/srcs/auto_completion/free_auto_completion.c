#include "../../includes/ft_select.h"

void 			free_lists(t_file *match_files)
{
	FT_INIT(t_file*, tmp, NULL);
	
	if (!match_files)
		return ;
	while(match_files)
	{
		ft_strdel(&(match_files->name));
		ft_strdel(&(match_files->absolute_path));
		tmp = match_files;
		match_files = match_files->next;
		free(tmp);
	}
}


void 			free_files(t_file **files_list)
{
	FT_INIT(t_file*, tmp, NULL);
	
	if (!(*files_list))
		return ;
	ft_putstr("START DELETE FILES_LIST\n\n\n");
	while((*files_list))
	{
		ft_putendl((*files_list)->name);
		ft_strdel(&((*files_list)->name));
		ft_strdel(&((*files_list)->absolute_path));
		tmp = (*files_list);
		(*files_list) = (*files_list)->next;
		free(tmp);
	}
}

void		free_auto_tab(char **table)
{
	int		colonne;

	colonne = 0;
	while ((table) && (table)[colonne])
	{
		free((table)[colonne]);
		(table)[colonne] = NULL;
		colonne++;
	}
	free(table);
}


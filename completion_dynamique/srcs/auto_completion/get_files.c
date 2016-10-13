#include "../../includes/ft_select.h"

static int 			compare(char *str1, char *str2)
{
	FT_INIT(int, diff, 0);
	FT_INIT(char*, s1, ft_strtolower(ft_strdup(str1)));
	FT_INIT(char*, s2, ft_strtolower(ft_strdup(str2)));
	diff = ft_strcmp(s1, s2);
	ft_strdel(&s1);
	ft_strdel(&s2);
	return (diff);
}

static t_file		*sort_list(t_file *files)
{
	FT_INIT(t_file*, after, files);
	FT_INIT(t_file*, before, files);
	FT_INIT(t_file*, tmp, NULL);
	while (after && after->next)
	{
		if (compare(after->name, (after->next)->name) > 0)
		{
			files = (after == files) ? after->next : files;
			before->next = after->next;
			tmp = (after->next)->next;
			(after->next)->next = after;
			after->next = tmp;
			MULTI(after, before, files);
		}
		else
		{
			before = after;
			after = after->next;
		}
	}
	return (files);
}

static t_file 		*create_cell(char *name, int dir)
{
	t_file 			*new_cell;

	new_cell = (t_file *)malloc(sizeof(t_file));
	new_cell->name = ft_strdup(name);
	new_cell->type = dir ? 1 : 0;
	new_cell->len = ft_strlen(new_cell->name);
	new_cell->next = NULL;
	new_cell->nb_elem = 0;
	return (new_cell);
}



t_file 				*store_files_dirs(DIR *rep, t_file *files, char *path)
{
	struct dirent 	*fd;
	struct stat		infos;

	FT_INIT(t_file *, start, NULL);
	FT_INIT(char*, path_file, NULL);
	while ((fd = readdir(rep)))
	{
		path_file = ft_strjoin(path, fd->d_name);
		lstat(path_file, &infos);
		ft_strdel(&path_file);
		if (!files)
			MULTI(start, files, create_cell(fd->d_name, 
				S_ISDIR(infos.st_mode)));
		else
		{
			files->next = create_cell(fd->d_name, S_ISDIR(infos.st_mode));
			files = files->next;
		}
	}
	closedir(rep);
	files = sort_list(start);
	return (files);
}
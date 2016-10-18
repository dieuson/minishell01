#include "../../includes/ft_select.h"

static char		*str_to_search(char *sentence)
{
	FT_INIT(char*, new_sentence, NULL);
	if (ft_strchr(sentence, ' '))
		sentence = ft_strrchr(sentence, ' ') + 1;
	if (ft_strrchr(sentence, '/'))
	{
		new_sentence = ft_strrchr(sentence, '/') + 1;
		if (ft_strlen(new_sentence))
			return (new_sentence);
		else
			return ("");
	}
	else
		new_sentence = sentence;
	return (new_sentence);
}

static t_file 			*get_file_path(char *path, char *sentence)
{
	DIR 		*rep;
	
	FT_INIT(t_file*, files, NULL);
	if (!path || !sentence)
		return (NULL);
	rep  = opendir(path);
	if (rep && !ft_strchr(sentence, ' ') && sentence[0] != '/' && 
		getenv("PATH"))
		files = store_files_dirs(rep, files, path, str_to_search(sentence));
	else if (rep && path && sentence[ft_strlen(sentence)] != ' ')
		files = store_files_dirs(rep, files, path, str_to_search(sentence));
	else
	{
		rep =  opendir(".");
		files = store_files_dirs(rep, files, path, str_to_search(sentence));
	}
	ft_strdel(&path);
	return (files);
}

int 			len_tab(char **tab_m)
{
	FT_INIT(int, i, 0);
	if (!tab_m)
		return (0);
	while (tab_m[i])
		i++;
	return (i);
}

t_file 			*files_list(char **sentence)
{
	FT_INIT(char**, path, NULL);
	FT_INIT(t_file*, files, NULL);
	FT_INIT(t_file*, head, NULL);
	*sentence = default_sentence(*sentence);
	if (!ft_strchr(*sentence, ' ') && *sentence[0] != '/' && getenv("PATH"))
		path = ft_strsplit(getenv("PATH"), ':');
	else
	{
		*sentence += ft_strlen(ft_strrchr(*sentence, ' ')) + 1;
		path = ft_strsplit(set_path(sentence, 
			getenv("HOME"), getenv("PWD")), '\n');
	}
	ft_printf("path =%s,\n", path[0]);
	while (path && *path)
	{
		if (!files)
			MULTI(head, files, get_file_path(*path, *sentence));
		else
			files->next = get_file_path(*path, *sentence);
		while (files && files->next)
			files = files->next;
		path++;
	}
	head = sort_list(head);
	return (head);
}

{
	char					*name;
	int 					type;
	int 					len;
	char 					*absolute_path;
	int 					nb_elem;
	struct s_file			*next;


void 			free_lists(t_file *match_files)
{
	FT_INIT(t_file*, col, NULL);
	FT_INIT(t_file*, tmp, NULL);
	
	if (!match_files)
		return ;
	while(match_files)
	{
		col = match_files->elem;
		while(col)
		{
			ft_strdel(&(col->name));
			ft_strdel(&(col->absolute_path));
			tmp = col;
			col = col->next;
			free(tmp);
		}
	}
}

char			*detect_auto_comletion(char *sentence)
{
	FT_INIT(t_file*, files, NULL);
	FT_INIT(t_file*, match_files, NULL);
	FT_INIT(char*, new_sentence, NULL);
	FT_INIT(char*, start_sentence, ft_strdup(sentence));
	FT_INIT(char*, to_search, NULL);
	if (!sentence || !ft_strlen(sentence))
	{
		ft_printf("Error sentence :exist? :%s, sentence_len =%d\n", sentence, ft_strlen(sentence));
		return (sentence);
	}
	files = files_list(&sentence);
	ft_putstr("test1\n");
	to_search = str_to_search(sentence);
	ft_putstr("test2\n");
	ft_printf("to_search =%s, sentence =%s,\n", to_search, start_sentence);
	if ((match_files =  compare_list_sentence(files, to_search)) != NULL)
		new_sentence = similarity(match_files, to_search);
	ft_putstr("test3\n");
	if (new_sentence && ft_strlen(new_sentence))
	{
		ft_printf("sentence =%s,\n", sentence);	
		ft_strdel(&sentence);
		free_lists(match_files);
		return (ft_strjoin(start_sentence, new_sentence));
	}
	free_lists(match_files);
	ft_putstr("test4\n");
//	return ("");
//	display_completion(sentence, match_files);
//	ft_strdel(&sentence);
	ft_putstr("test5\n");
	return (start_sentence);
}
#include "../../includes/ft_select.h"

static char		*str_to_search(char *sentence)
{
	FT_INIT(char*, new_sentence, NULL);
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
	{
//		ft_printf("get_file_path bin file\n");
		files = store_files_dirs(rep, files, path, str_to_search(sentence));
	}
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

t_file 			*files_list(char *sentence)
{
	FT_INIT(char**, path, NULL);
	FT_INIT(t_file*, files, NULL);
	FT_INIT(t_file*, head, NULL);
	FT_INIT(char *, tmp, sentence);
	sentence = default_sentence(sentence);
	if (!ft_strchr(sentence, ' ') && sentence[0] != '/' && getenv("PATH"))
	{
//		ft_printf("bin file\n");		
		path = ft_strsplit(getenv("PATH"), ':');
	}
	else
	{
//		ft_printf("simple file\n");
		tmp = ft_strrchr(sentence, ' ') + 1;
		path = ft_strsplit(set_path(tmp, getenv("HOME"), getenv("PWD")), '\n');
	}
	if (ft_strrchr(sentence, ' '))
		sentence = ft_strrchr(sentence, ' ');
//	ft_printf("tmp =%s,\n", tmp);
//	ft_printf("sentence =%s,\n", sentence);
	while (path && *path)
	{
//		ft_printf("path =%s,\n", path[0]);
		if (!files)
			files = get_file_path(*path, sentence);
		else
			files->next = get_file_path(*path, sentence);
		if (!head)
			head = files;
		while (files->next)
		{
//			ft_printf("file_name =%s,\n", files->name);
			files = files->next;
		}
		path++;
	}
	files->next = NULL;
	head = sort_list(head);
//	while (head)
//	{
//		ft_printf("file_name =%s,\n", head->name);
//		head = head->next;
//	}

//	free(path);
	return (head);
}


char			*detect_auto_comletion(char *sentence)
{
	FT_INIT(t_file*, files, NULL);
	FT_INIT(t_file*, match_files, NULL);
	FT_INIT(char*, new_sentence, NULL);
	FT_INIT(char*, to_search, NULL);
	if (!sentence || !ft_strlen(sentence))
	{
		ft_printf("Error sentence :exist? :%s, sentence_len =%d\n", sentence, ft_strlen(sentence));
		return (sentence);
	}
	files = files_list(sentence);
/*	while (files)
	{
		ft_putendl(files->name);
		files = files->next;
	}*/
	to_search = str_to_search(sentence);
	if ((match_files =  compare_list_sentence(files, to_search)) != NULL)
		new_sentence = similarity(match_files, to_search);
	if (new_sentence && ft_strlen(new_sentence))
		return (ft_strjoin(sentence, new_sentence));
	display_completion(sentence, match_files);
	return ("");
	return (sentence);
}
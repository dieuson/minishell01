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

t_file 			*get_file_path(char *path, char *sentence)
{
	DIR 		*rep;
	
	FT_INIT(t_file*, files, NULL);
	if (!path || !sentence)
		return (NULL);
	ft_putstr("get_file_path start1\n");
	ft_printf("get_file_path =%s,\n", path);
	rep  = opendir(path);
	ft_putstr("get_file_path start35\n");
	if (rep && !ft_strchr(sentence, ' ') && sentence[0] != '/' && 
		getenv("PATH"))
		files = store_files_dirs(rep, files, path, str_to_search(sentence));
	else if (rep && path && sentence[ft_strlen(sentence)] != ' ')
		files = store_files_dirs(rep, files, path, str_to_search(sentence));
	else
	{
		closedir(rep);
		rep =  opendir(".");
		files = store_files_dirs(rep, files, path, str_to_search(sentence));
	}
	closedir(rep);
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
	FT_INIT(int, i, 0);
	ft_putstr("Test0\n");
	*sentence = default_sentence(*sentence);
	ft_putstr("Test1\n");
	path = set_path(sentence, getenv("HOME"), getenv("PWD"));
	ft_putstr("Test2\n");
	ft_printf("path =%s,\n", path[0]);
	while (path && path[i])
	{
		if (!files)
			MULTI(head, files, get_file_path(path[i], *sentence));
		else
			files->next = get_file_path(path[i], *sentence);
		while (files && files->next)
			files = files->next;
		i++;
	}
	ft_putstr("test end files_list\n");
	free_auto_tab(path);
	head = sort_list(head);
//	free_auto_tab(path);
	return (head);
}

void 			free_files(t_file **files_list)
{
	FT_INIT(t_file*, tmp, NULL);
	
	if (!(*files_list))
		return ;
	while((*files_list))
	{
		ft_strdel(&((*files_list)->name));
		ft_strdel(&((*files_list)->absolute_path));
		tmp = (*files_list);
		(*files_list) = (*files_list)->next;
		free(tmp);
	}
}

char			*detect_auto_comletion(char *sentence)
{
	FT_INIT(t_file*, files, NULL);
	FT_INIT(t_file*, match_files, NULL);
	FT_INIT(char*, new_sentence, NULL);
	ft_putstr("test1\n");
	FT_INIT(char*, start_sentence, ft_strdup(sentence));
	FT_INIT(char*, to_search, NULL);
	ft_putstr("test1\n");
	if (!sentence || !ft_strlen(sentence))
	{
		ft_printf("Error sentence :exist? :%s, sentence_len =%d\n", sentence, ft_strlen(sentence));
		return (sentence);
	}
//	ft_putstr("test10\n");
	files = files_list(&sentence);
	ft_putstr("test10\n");
	to_search = str_to_search(sentence);
	ft_putstr("test2\n");
//	ft_printf("to_search =%s, sentence =%s,\n", to_search, start_sentence);
	if ((match_files =  compare_list_sentence(files, to_search)))
		new_sentence = similarity(match_files, to_search);
//	ft_putstr("test3\n");
//	ft_strdel(&sentence);
	if (new_sentence && start_sentence && ft_strlen(new_sentence))
	{
//		ft_printf("sentence =%s,\n", sentence);	
//		if (sentence)
		ft_strdel(&sentence);
//		free_lists(match_files);
		free_files(&files);
		sentence = ft_strjoin(start_sentence, new_sentence);
		ft_strdel(&start_sentence);
		ft_strdel(&new_sentence);
		return (sentence);
	}
//	return (NULL);
	//ft_putstr("test4\n");
	if (new_sentence)
		ft_strdel(&new_sentence);
	display_completion(sentence, match_files);
	ft_strdel(&sentence);
	free_files(&files);
//	free_lists(match_files);
	//ft_putstr("test5\n");
	return (start_sentence);
}
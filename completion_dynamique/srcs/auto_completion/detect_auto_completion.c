#include "../../includes/ft_select.h"

char 			*set_sentence(char *sentence)
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

char 			*add_characes

char			*detect_auto_comletion(char *sentence)
{
	FT_INIT(char*, path, NULL);
	FT_INIT(t_file*, files, NULL);
	FT_INIT(t_file*, match_files, NULL);
	DIR 		*rep;
	
	if (!sentence)
		return (0);
	if (ft_strrchr(sentence, ' '))
		sentence = ft_strrchr(sentence, ' ') + 1;
	path = set_path(sentence, getenv("HOME"), getenv("PWD"));
	rep = opendir(path);
	if (rep && path && sentence[ft_strlen(sentence)] != ' ')
		files = store_files_dirs(rep, files, path);
	else
	{
		rep =  opendir(".");
		files = store_files_dirs(rep, files, path);
	}
	sentence = set_sentence(sentence);
	match_files =  compare_list_sentence(files, sentence);
	display_completion(&sentence, match_files);
	ft_strdel(&path);
	return (sentence);
}
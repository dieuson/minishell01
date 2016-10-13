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

static int 		verif_matchs(t_file *files, size_t len_cmp, int nb_args)
{
	FT_INIT(t_file*, before, files);
	FT_INIT(t_file*, after, before->next);
	FT_INIT(int, i, 1);
	if (nb_args == 1 && len_cmp < ft_strlen(files->name))
		return (1);
	while (before && before->next)
	{
		if (!ft_strncmp(before->name, after->name, len_cmp))
			i++;
		else
			break ;
		before = before->next;
		after = before->next;
	}
	if (i == nb_args)
		return (1);
	return (0);
}


static char 	*similarity(t_file *match_files, char *sentence)
{
	FT_INIT(int, len_cmp, ft_strlen(sentence));
	FT_INIT(char*, similarity, ft_strnew(match_files->len * 2));
	FT_INIT(int, nb_args, match_files->nb_elem);
	FT_INIT(int, verif, nb_args);

	while (verif && len_cmp <= match_files->len)
	{
		verif = verif_matchs(match_files, len_cmp, nb_args);
		if (verif)
			ft_strncpy(similarity, match_files->name, len_cmp);
		len_cmp++;
	}
	if (similarity && ft_strlen(similarity))
	{
		if (nb_args == 1 && match_files->type)
			ft_strcat(similarity, "/");
		ft_putstr(similarity += ft_strlen(sentence));
	}
	else
		similarity = NULL;
	return (similarity);
}

char			*detect_auto_comletion(char *sentence)
{
	FT_INIT(char*, path, NULL);
	FT_INIT(t_file*, files, NULL);
	FT_INIT(t_file*, match_files, NULL);
	DIR 		*rep;
	
	if (!sentence || !ft_strlen(sentence))
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
	if (match_files && !(sentence = similarity(match_files, sentence)))
		return (sentence);
	display_completion(&sentence, match_files);
	ft_strdel(&path);
/*
printf("\033[XA"); // Move up X lines;
printf("\033[XB"); // Move down X lines;
printf("\033[XC"); // Move right X column;
printf("\033[XD"); // Move left X column;
printf("\033[2J"); // Clear screen
printf("\033[8;5Hhello"); // Move to (8, 5) and output hello
*/
	return (sentence);
}
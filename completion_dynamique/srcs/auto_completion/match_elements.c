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

char 			*similarity(t_file *match_files, char *sentence)
{
	FT_INIT(int, len_cmp, ft_strlen(sentence));
	//ft_putstr("test2\n");
	FT_INIT(char*, tmp, NULL);
	FT_INIT(char*, similarity, ft_strnew(match_files->len * 2));
	//ft_putstr("test2\n");
	FT_INIT(int, nb_args, match_files->nb_elem);
	//ft_putstr("test2\n");
	FT_INIT(int, verif, nb_args);

	//ft_putstr("test2\n");
	while (verif && len_cmp <= match_files->len)
	{
		verif = verif_matchs(match_files, len_cmp, nb_args);
		if (verif)
			ft_strncpy(similarity, match_files->name, len_cmp);
		len_cmp++;
	}
	//ft_putstr("test3\n");
	if (similarity && ft_strlen(similarity))
	{
		if (nb_args == 1 && match_files->type)
			ft_strcat(similarity, "/");
		tmp = similarity;
		similarity = ft_strdup(similarity + ft_strlen(sentence));
		ft_strdel(&tmp);
		if (similarity && sentence && !ft_strcmp(similarity, sentence))
		{
			ft_strdel(&similarity);
			return (NULL);
		}
		ft_putstr(similarity);
	}
	else
	{
		ft_strdel(&similarity);
		similarity = ft_strdup(sentence);
	}
	//ft_putstr("test4\n");
	return (similarity);
}

t_file 			*compare_list_sentence(t_file *files, char *sentence)
{
	FT_INIT(t_file*, match_files, NULL);
	FT_INIT(t_file*, head, NULL);
	while (files)
	{
		if (files && ft_strlen(sentence) <= ft_strlen(files->name) &&
			!ft_strncmp(files->name, sentence, ft_strlen(sentence)))
		{
			if ((files->name)[0] != '.' || ft_strcmp(sentence, ""))
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
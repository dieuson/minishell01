#include "../../includes/ft_select.h"

void		free_simple_tab(char ***tab_to_del)
{
	int		colonne;

	colonne = 0;
	while ((*tab_to_del) && (*tab_to_del)[colonne])
	{
		free((*tab_to_del)[colonne]);
		(*tab_to_del)[colonne] = NULL;
		colonne++;
	}
	free(*tab_to_del);
	*tab_to_del = NULL;
}

char 			*default_sentence(char *sentence)
{
	FT_INIT(char **, path, NULL);
	FT_INIT(int, i, 0);
	FT_INIT(char*, tmp, NULL);
	FT_INIT(char*, str, ft_strdup(""));
	if (!ft_strchr(sentence, ' '))
		return (sentence);
	path = ft_strsplit(sentence, ' ');
	while (path && path[i])
	{
		tmp = str;
		str = ft_strjoin(str, path[i]);
		if (tmp)
			ft_strdel(&tmp);
		if (path[i + 1] && str && ft_strlen(str))
		{
			tmp = str;
			str = ft_strjoin(str, " ");
			if (tmp)
				ft_strdel(&tmp);	
		}
		i++;
	}
	free_simple_tab(&path);
	return (str);
}
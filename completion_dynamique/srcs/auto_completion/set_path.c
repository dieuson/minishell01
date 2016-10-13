#include "../../includes/ft_select.h"

char 			*set_begining(char *sentence, char *home, char *current_path)
{
	FT_INIT(char*, new_path, ft_strnew(ft_strlen(sentence) + 100));
	if (ft_strlen(sentence) >= 2 && !ft_strncmp(sentence, "./", 2))
	{
		ft_strcpy(new_path, current_path);
		ft_strcat(new_path, sentence + 1);
	}
	else if (sentence[0] == '~')
	{
		ft_strcpy(new_path, home);
		ft_strcat(new_path, sentence + 1);
	}
	else if (!ft_strcmp(sentence, ".."))
	{
		ft_strncpy(new_path, current_path, ft_strlen(current_path) - ft_strlen(ft_strrchr(current_path, '/')));
		ft_strcat(new_path, "/");	
	}
	else
	{
		ft_strcpy(new_path, current_path);
		ft_strcat(new_path, "/");	
		ft_strcat(new_path, sentence);
	}
	return (new_path);
}

void 			remove_char(char **str, char c)
{
	if (!str || !c)
		return ;
	FT_INIT(int, i, ft_strlen(*str) - 1);
	while ((*str)[i] && (*str)[i] == c)
	{
		(*str)[i] = '\0';
		i--;
	}
}

char 			*parse_dirs(char **dirs, char *new_path, char *home)
{
	while (dirs && *dirs)
	{
		if (!ft_strcmp(*dirs, "~"))
			ft_strcat(new_path, home);
		else if (!ft_strcmp(*dirs, ".."))
		{
			remove_char(&new_path, '/');
			ft_bzero((void*)(new_path +  (ft_strlen(new_path) - 
			ft_strlen(ft_strrchr(new_path, '/')))) , ft_strlen(new_path));
			if (!ft_strlen(new_path))
				ft_strcpy(new_path, "/");
		}
		else if (!ft_strcmp(*dirs, "."))
			;
		else
		{
			if (new_path[ft_strlen(new_path) - 1] != '/')
				ft_strcat(new_path, "/");
			ft_strcat(new_path, *dirs);
		}
		if ((*(dirs + 1) && new_path[ft_strlen(new_path) - 1] != '/'))
			ft_strcat(new_path, "/");
		(dirs)++;
	}
	return (new_path);
}

char 			*set_path(char *sentence, char *home, char *current_path)
{
	FT_INIT(char*, new_path, NULL);
	FT_INIT(char**, dirs, NULL);
	FT_INIT(int, i, 0);
	new_path = set_begining(sentence, home, sentence[0] == '/' ? ""
		: current_path);
	sentence = ft_strdup(new_path);
	ft_bzero((void*)new_path, ft_strlen(new_path));
	dirs = ft_strsplit(sentence, '/');
	ft_strcat(new_path, "/");
	new_path = parse_dirs(dirs, new_path, home);
	while (dirs && dirs[i])
	{	
		free(dirs[i]);
		i++;
	}
	free(dirs);
	return (new_path);
}
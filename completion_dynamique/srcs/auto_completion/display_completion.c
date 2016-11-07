#include "../../includes/ft_select.h"

static char		*set_sentence(char *str, int len_str, char *name)
{
	FT_INIT(char*, tmp, ft_itoa(len_str + 2));
	str = ft_strcat(str, "%-");
	str = ft_strcat(str, tmp);
	str = ft_strcat(str, "s");
	ft_printf(str, name);
	ft_bzero(str, ft_strlen(str));
	ft_strdel(&tmp);
	return (str);
}

void 			reset_cursor_pos(int len_str, int nb_colonnes, int nb_elem, char *sentence)
{
	FT_INIT(int, nb_col, 0);
	FT_INIT(int, nb_line, 0);
	if (!nb_elem)
		return ;
	ft_putstr("\033[32m|\033[0m");
	nb_colonnes = nb_elem <= nb_colonnes ? nb_elem : nb_colonnes;
	nb_col = (len_str + 2) * nb_colonnes - 1 - ft_strlen(sentence);
	nb_line = nb_elem / nb_colonnes;
	while (nb_col)
	{
		ft_printf("\033[1D");
		nb_col--;
	}
	while (nb_line > 0)
	{
		ft_printf("\033[1A");
		nb_line--;
	}
}

static void		display_form(t_completion *all_col, int nb_elem, int len_str, int nb_col)
{
	FT_INIT(t_file *, col, all_col->elem);
	FT_INIT(t_file *, tmp_col, col);
	FT_INIT(t_completion *, head, all_col);
	FT_INIT(char *, tmp, NULL);
	FT_INIT(int, ref_col, 0);
	tmp = ft_strnew(ft_strlen(col->name) + 4096);
	while (all_col && nb_elem)
	{
		if (!ref_col)
			head = all_col;
		col = all_col->elem;
		if (col)
		{
			tmp = set_sentence(tmp, len_str, col->name);
			tmp_col = col;
			col = col->next;

			ft_strdel(&(tmp_col)->name);
			ft_strdel(&(tmp_col)->absolute_path);
			free(tmp_col);

			nb_elem--;
			all_col->elem = col;
		}
		if (ref_col >= nb_col - 1)
		{
			ft_putendl("");
			ref_col = 0;
			all_col = head;
		}
		else
		{
			ref_col++;
			all_col = all_col->next;
		}
	}
	ft_strdel(&tmp);
}

int 			arrondi(float val)
{
	FT_INIT(int, val2, val);
	FT_INIT(float, result, val - val2);
	if (result >= 0.5)
		return (val2 + 1);
	return (val2);
}

int 			ft_nb_elem_lst(int nb_elem, int nb_col)
{
	FT_INIT(float, result, 0);
	while (result * nb_col < nb_elem)
		result++;
	return (result);
}

void 			display_completion(char *sentence, t_file *match_files)
{
	struct winsize ws;

	if (!sentence || !match_files)
		return ;
	ft_putstr("\n");
	FT_INIT(t_completion *, lst_lst, NULL);
	FT_INIT(t_completion*, tmp_lst, NULL);
	FT_INIT(float, nb_elem, (float)match_files->nb_elem);
	FT_INIT(float, len_str, (float)match_files->len);
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
	FT_INIT(float, nb_col, arrondi(ws.ws_col / (len_str + 2)));
	FT_INIT(float, nb_line, ws.ws_row);
	FT_INIT(float, nb_elem_lst, ft_nb_elem_lst(nb_elem, nb_col));
//	printf("\nnb elem =%f, nb_elem_lst =%f, nb_col =%f, nb_line =%f\n", nb_elem, nb_elem_lst, nb_col, nb_line);
//	ft_printf("display nb_col =%d, len_str =%d,\n", ws.ws_col, (len_str + 2));
	lst_lst = build_lst_lst(match_files, (nb_elem_lst == 0 ? 1 : nb_elem_lst), nb_col);
	tmp_lst = lst_lst;
	display_form(lst_lst, nb_elem, len_str, nb_col);
	lst_lst = tmp_lst;
	while (lst_lst->next)
	{
//		ft_putendl("LOOP DELETE\n");
		tmp_lst = lst_lst;
		lst_lst = lst_lst->next;
		free(tmp_lst);
	}
	free(lst_lst);
	ft_printf("\n%s", sentence);
	if (nb_elem || len_str || nb_col || nb_line || nb_elem_lst || lst_lst)
		return ;
}
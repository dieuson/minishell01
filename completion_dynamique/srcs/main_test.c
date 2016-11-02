/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvirgile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 15:11:31 by dvirgile          #+#    #+#             */
/*   Updated: 2016/09/27 15:15:57 by dvirgile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

int main()
{
	FT_INIT(int, val, 0);
	FT_INIT(int, fd_test, 0);
	FT_INIT(int, fd_result, 0);
	FT_INIT(char*, test, NULL);
	FT_INIT(char*, result, NULL);

	FT_INIT(int, i, 1);
	FT_INIT(char*, inputs, "");

 	fd_result = open("/home/dieuson/minishell01/completion_dynamique/srcs/result.txt",  O_RDONLY);
 	fd_test = open("/home/dieuson/minishell01/completion_dynamique/srcs/test.txt",  O_RDONLY);
 	while (get_next_line(fd_test, &test))
 	{
		inputs = test;
		ft_printf("inputs =%s,\n", test);
		inputs = detect_auto_comletion(inputs);
		get_next_line(fd_result, &result);
		if (inputs)
			ft_printf("output =%s,\n", inputs);
		else
			ft_printf("NO INPUTS\n");
		if (result)
			ft_printf("result =%s,\n", result);
		else
			ft_printf("NO LINE\n");
		if (result && inputs && !ft_strcmp(result, inputs))
		{
			val++;
			ft_putstr("\033[32mOK\033[0m\n");
		}
		else
			ft_putstr("\033[31mKO\033[0m\n");
 		ft_strdel(&inputs);
 		ft_strdel(&test);
 		ft_strdel(&result);
 		i++;
 		if (i > 2)
 			break;
 	}
 	i--;
 	ft_strdel(&test);
 	ft_printf("Results => OK: %d, KO: %d\n", val, i - val);
 	close(fd_result);
 	close(fd_test);

	return (0);
}

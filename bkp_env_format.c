/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bkp_env_format.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/31 15:26:04 by sgaudin           #+#    #+#             */
/*   Updated: 2016/08/31 15:26:23 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		env_format(char *var)
{
	FT_INIT(int, i, ft_strlen(var) - ft_strlen(ft_strchr(var, '=')));
	FT_INIT(int, j, ft_strlen(ft_strchr(var, '=') + 1));
	if (ft_strchr(var, '=') == NULL)
		return (0);
	FT_INIT(char *, name, ft_strnew(i));
	FT_INIT(char *, value, ft_strnew(j));
	name = ft_strncpy(name, var, i);
	ft_strcpy(value, ft_strchr(var, '=') + 1);
	FT_MULTI3(i, j, 0);
	if (ft_strchr(value, '='))
	{
		free_la_flemme(&name, &value);
		return (0);
	}
	while (name[i])
	{
		if (name[i] < 'A' || name[i] > 'Z')
			if (name[i] != '_')
			{
				free_la_flemme(&name, &value);
				return (0);
			}
		i++;
	}
	free_la_flemme(&name, &value);
	return (1);
}

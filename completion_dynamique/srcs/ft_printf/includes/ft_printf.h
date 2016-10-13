/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvirgile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 19:23:14 by dvirgile          #+#    #+#             */
/*   Updated: 2016/03/12 19:23:17 by dvirgile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# ifndef FT_INIT
#  define FT_INIT(t, n, v) t n = v
# endif

# ifndef MULTI
#  define MULTI(a, b, c) a = b = c
# endif
# define TER(si,alors,sinon)			si ? alors : sinon

# include "../libft/includes/libft.h"
# include <stdarg.h>
# include <wchar.h>
# include <stdint.h>

typedef struct		s_docker
{
	int				result;
	int				i;
	int				len;
	int				(*fct[256])(const char *, va_list, struct s_docker *);
	int				dieze;
	int				zero;
	int				less;
	int				more;
	int				space;
	int				dot;
	int				width;
	int				precision;
	char			type;
	int				choice;
	int				length;
	int				wide_width;
	enum {
		z = 1,
		j,
		ll,
		l,
		hh,
		h
	}				enum_length;
}					t_docker;

int					ft_printf(const char *format, ...);

int					longueur_nb(int64_t nb);
int					len_base(uintmax_t nb, uint32_t base);
int					ft_add_spaces(int nb_spaces, int len, char c);

void				ft_detect_flags(const char *str, t_docker *data);
void				ft_detect_width(const char *str, t_docker *data, int who);
int					distrib_putbase(t_docker *data, uintmax_t result, int base
									, uint8_t flag);

int					ftp_putbase(uintmax_t n, uint32_t base, uint8_t flag,
								t_docker *data);
int					ftp_octal(uint32_t nb, va_list args, t_docker *data);
int					ftp_putchar(uint32_t c);
int					ftp_putstr(uint8_t *str);
int					ftp_strlen(uint8_t *str);
int					ftp_putnbr(int64_t n, t_docker *data);
int					ftp_putnbr_long(int64_t n, t_docker *data);
int					ftp_putbase_long(uintmax_t n, uint32_t base, uint8_t flag,
									t_docker *data);

int					call_putstr(const char *str, va_list args, t_docker *data);
int					call_putchar(const char *str, va_list args, t_docker *data);
int					call_putnbr(const char *str, va_list args, t_docker *data);
int					call_putbase(const char *str, va_list args, t_docker *data);
int					call_putbase_long(const char *str, va_list args,
									t_docker *data);
int					call_putnbr_long(const char *str, va_list args,
									t_docker *data);
int					call_putwchar(const char *str, va_list args,
									t_docker *data);
int					call_putwstr(const char *str, va_list args, t_docker *data);
int					call_putadress(const char *str, va_list args,
									t_docker *data);
int					call_purcent(const char *str, va_list args, t_docker *data);

t_docker			init_tabptr(void);
void				detect_conversion(const char *str, t_docker *data);
uintmax_t			unsigned_conversion(t_docker *data, va_list args);
intmax_t			signed_conversion(t_docker *data, va_list args);
int					ft_check_valid(const char *str, t_docker *data);
int					detect(const char *s, t_docker *data);

#endif

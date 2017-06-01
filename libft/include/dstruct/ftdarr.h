/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftdarr.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 23:52:49 by bmontoya          #+#    #+#             */
/*   Updated: 2017/06/01 13:38:25 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTDARR_H
# define FTDARR_H
# include <stddef.h>

typedef struct	s_darr
{
	char		*arr;
	size_t		size;
	size_t		space;
	size_t		len;
}				t_darr;

t_darr			*ft_darrnew(size_t space, size_t size);
void			ft_darradd(t_darr *darr, void *data);
void			ft_darrdel(t_darr *darr);
#endif

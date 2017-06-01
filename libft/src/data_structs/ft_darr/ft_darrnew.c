/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_darrnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 23:53:38 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/28 02:22:21 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dstruct/ftdarr.h>
#include <stdlib.h>
#include <ftstring.h>

/*
** Size- Amount of memory needed per object
** Space- The space to initially malloc
** Will be null terminated
*/

t_darr	*ft_darrnew(size_t space, size_t size)
{
	t_darr	*new;

	if (!size || !(new = malloc(sizeof(*new))))
		return (NULL);
	new->size = size;
	new->len = 0;
	new->space = (space > 1) ? space : 2;
	new->arr = ft_memalloc(new->space * new->size);
	return (new);
}

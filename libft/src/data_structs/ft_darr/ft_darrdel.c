/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_darrdel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/28 02:27:54 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/28 02:29:04 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dstruct/ftdarr.h>
#include <stdlib.h>

void	ft_darrdel(t_darr *darr)
{
	free(darr->arr);
	free(darr);
}

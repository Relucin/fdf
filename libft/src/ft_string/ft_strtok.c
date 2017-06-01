/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 15:16:37 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/25 16:26:53 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftstring.h>

char	*ft_strtok(char *str, const char *delimiters)
{
	static char	*tstr = 0;
	char		*ret;

	if (str)
		tstr = str;
	while (*tstr)
	{
		if (ft_strchr(delimiters, *tstr))
			++tstr;
		else
			break ;
	}
	ret = tstr;
	while (*tstr)
		if (ft_strchr(delimiters, *++tstr))
			break ;
	if (*tstr)
		*tstr++ = '\0';
	return (*ret) ? ret : NULL;
}

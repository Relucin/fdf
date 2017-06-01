/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 23:21:21 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/23 16:47:29 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftstdio.h>
#include <dstruct/ftlist.h>
#include <ftstring.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

t_list		*check_data(t_list **arr, int fd)
{
	t_file file;
	t_list *tmp;

	file.fd = fd;
	file.rd = 0;
	file.f = 0;
	if (!*arr)
	{
		file.of = ft_strnew(1);
		*arr = ft_lstnew(&file, sizeof(file));
		return (*arr);
	}
	tmp = *arr;
	while (((t_file*)tmp->content)->fd != fd)
	{
		tmp = tmp->next;
		if (tmp)
			continue;
		file.of = ft_strnew(1);
		ft_lstadd(arr, ft_lstnew(&file, sizeof(file)));
		return (*arr);
	}
	return (tmp);
}

void		set_line(t_list *node, char **line)
{
	int		nloc;
	t_file	*file;
	char	*tmpof;

	nloc = -1;
	file = (t_file*)node->content;
	while (file->of[++nloc])
		if (file->of[nloc] == 0x0a)
			break ;
	if (file->f && !file->of[nloc])
	{
		*line = ft_strdup(file->of);
		file->rd = 0;
	}
	else
	{
		tmpof = file->of;
		*line = ft_strsub(tmpof, 0, nloc);
		file->of = ft_strsub(tmpof, nloc + 1, ft_strlen(tmpof) - (nloc + 1));
		file->rd -= nloc + 1;
		free(tmpof);
	}
}

int			read_file(t_list *node, int fd)
{
	char	buf[BUFF_SIZE + 1];
	t_file	*file;
	int		rd;
	char	*tmpof;

	file = (t_file*)node->content;
	rd = read(fd, buf, BUFF_SIZE);
	if (file->f || rd == -1)
	{
		free(file->of);
		free(file);
		return (rd == -1) ? -1 : 0;
	}
	buf[rd] = '\0';
	if (rd < BUFF_SIZE)
		file->f = 1;
	file->rd += rd;
	tmpof = file->of;
	file->of = ft_strjoin(file->of, buf);
	free(tmpof);
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	static t_list	*head = 0;
	t_list			*node;
	t_file			*f_node;
	int				ret;

	if (!line)
		return (-1);
	*line = 0;
	node = check_data(&head, fd);
	f_node = (t_file*)node->content;
	while (!*line)
	{
		if (f_node->rd && (ft_strchr(f_node->of, 0x0a) || f_node->f))
			set_line(node, line);
		else
		{
			if ((ret = read_file(node, fd)) < 1)
			{
				ft_lstdelnode(&head, node);
				return (ret);
			}
		}
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_env_build.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/28 16:32:14 by bmontoya          #+#    #+#             */
/*   Updated: 2017/06/01 13:29:56 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <ftstdlib.h>
#include <ftstring.h>
#include <stdlib.h>
#include <unistd.h>
#include <ftstdio.h>
#include <fcntl.h>
#include <math.h>

static void			fdf_translate_darr(t_env *env, t_darr **tmap)
{
	t_point	**map;
	size_t	x;

	map = env->map;
	env->xlen = (*tmap)->len;
	while (*tmap)
	{
		x = 0;
		*map = (t_point *)(*tmap)->arr;
		while (x < env->xlen)
		{
			if ((*map)[x].z)
			{
				(*map)[x].color ^= (0xFF & ((int)(0xE0 *
					((double)(*map)[x].z / env->maxz)))) << 16;
				(*map)[x].color ^= (0xFF & ((int)(0xE0 *
					((double)(*map)[x].z / env->maxz)))) << 8;
			}
			++x;
		}
		++map;
		free(*tmap++);
	}
	*map = 0;
}

static void			fdf_fill_row(t_darr *map, char *line, t_env *env)
{
	t_point			point;
	t_darr			*row;
	char			*pdata;

	row = ft_darrnew(256, sizeof(point));
	point.z = ft_atoi(ft_strtok(line, " "));
	point.color = 0xFFFFB0;
	if (fabs((double)point.z) > env->maxz)
		env->maxz = point.z;
	ft_darradd(row, &point);
	while ((pdata = ft_strtok(NULL, " ")))
	{
		point.z = ft_atoi(pdata);
		if (fabs((double)point.z) > env->maxz)
			env->maxz = point.z;
		ft_darradd(row, &point);
	}
	ft_darradd(map, &row);
}

inline static void	fdf_calc_map(t_env *env)
{
	int	xmid;
	int	ymid;

	xmid = env->xlen / 2;
	ymid = env->ylen / 2;
	env->xscale = env->width / (env->xlen * 2);
	env->yscale = env->height / (env->ylen * 2);
	env->zscale = env->maxz / (env->xscale + env->yscale);
	if (!env->zscale && env->maxz)
		env->zscale = (env->xscale + env->yscale) / env->maxz;
	while (env->zscale / (env->xscale + env->yscale) > 2)
		env->zscale /= 2;
	env->zinc = env->zscale;
	fdf_calc_point(env, env->map[ymid] + xmid, xmid, ymid);
	env->xoffset = (env->width / 2) - env->map[ymid][xmid].tx;
	env->yoffset = (env->height / 2) - env->map[ymid][xmid].ty;
}

int					fdf_init_map(t_env *env, char *file)
{
	t_darr	*tmap;
	char	*line;
	int		fd;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (0);
	tmap = ft_darrnew(64, sizeof(t_darr *));
	while (get_next_line(fd, &line) > 0)
	{
		fdf_fill_row(tmap, line, env);
		free(line);
	}
	close(fd);
	if (!tmap->len)
	{
		ft_darrdel(tmap);
		return (0);
	}
	env->map = malloc(sizeof(t_point *) * (tmap->len + 1));
	env->ylen = tmap->len;
	fdf_translate_darr(env, (t_darr **)tmap->arr);
	fdf_calc_map(env);
	ft_darrdel(tmap);
	return (1);
}

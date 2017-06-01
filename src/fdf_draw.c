/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/28 03:37:40 by bmontoya          #+#    #+#             */
/*   Updated: 2017/06/01 13:29:59 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <mlx.h>
#include <math.h>
#include <unistd.h>

inline static void	fdf_put_pixel(t_point *p, t_env *e)
{
	int calc;

	calc = p->tx + p->ty * e->height;
	if (p->tx > 0 && p->ty > 0 && calc > 0 &&
		p->tx < e->width && p->ty < e->height && calc < e->area)
	{
		e->imgp[calc] = p->color;
	}
}

inline static void	fdf_draw(t_draw *d, t_point *p1, t_point *p2)
{
	int dcolor;
	int	cc;

	d->dzx = 0;
	d->dzy = 0;
	d->dx = fabs((double)(p2->tx - p1->tx));
	d->dy = -1 * fabs((double)(p2->ty - p1->ty));
	d->cx = (p2->tx > p1->tx) ? 1 : -1;
	d->cy = (p2->ty > p1->ty) ? 1 : -1;
	d->err = d->dx + d->dy;
	dcolor = fabs((double)(p2->color >> 16) - (p1->color >> 16));
	cc = (p2->color > p1->color) ? -1 : 1;
	if (d->dx && !d->dy)
	{
		dcolor /= d->dx;
		d->dzx = ((dcolor << 16) + (dcolor << 8)) * -cc;
	}
	else if (d->dy)
	{
		dcolor /= d->dy;
		d->dzy = ((dcolor << 16) + (dcolor << 8)) * cc;
	}
}

inline static void	fdf_draw_line(t_env *env, t_point p1, t_point p2)
{
	t_draw	draw;

	fdf_draw(&draw, &p1, &p2);
	while (1)
	{
		fdf_put_pixel(&p1, env);
		if (p1.tx == p2.tx && p1.ty == p2.ty)
			break ;
		draw.err2 = draw.err << 1;
		if (draw.err2 >= draw.dy)
		{
			draw.err += draw.dy;
			p1.color += (draw.dzx);
			p1.tx += draw.cx;
		}
		if (draw.err2 <= draw.dx)
		{
			draw.err += draw.dx;
			p1.color += (draw.dzy);
			p1.ty += draw.cy;
		}
	}
}

inline static void	fdf_draw_x(t_env *env, int y)
{
	size_t	x;

	x = 0;
	fdf_calc_point(env, env->map[y] + x, x, y);
	if (env->xlen == 1)
		fdf_draw_line(env, env->map[y][x], env->map[y][x]);
	while (x + 1 < env->xlen)
	{
		fdf_calc_point(env, env->map[y] + x + 1, x + 1, y);
		fdf_draw_line(env, env->map[y][x], env->map[y][x + 1]);
		++x;
	}
}

void				fdf_draw_map(t_env *env)
{
	int		y;
	size_t	x;

	y = 0;
	while (1)
	{
		fdf_draw_x(env, y);
		if (env->map[++y])
		{
			x = 0;
			fdf_draw_x(env, y);
			while (x < env->xlen)
			{
				fdf_draw_line(env, env->map[y - 1][x], env->map[y][x]);
				++x;
			}
		}
		else
			break ;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 20:26:18 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/31 20:30:46 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <dstruct/ftdarr.h>

typedef void * t_win;
typedef void * t_mlx;
typedef void * t_img;
typedef int * t_img_p;

typedef struct	s_draw
{
	int			dx;
	int			dy;
	int			dzx;
	int			dzy;
	int			cx;
	int			cy;
	int			err;
	int			err2;
}				t_draw;

typedef struct	s_point
{
	int			tx;
	int			ty;
	int			z;
	int			color;
}				t_point;

typedef struct	s_env
{
	t_win		window;
	t_mlx		mlx;
	t_img		image;
	t_img_p		imgp;
	int			maxz;
	int			bpp;
	int			size;
	int			area;
	int			endian;
	int			width;
	int			height;
	float		rx;
	float		ry;
	float		rz;
	t_point		**map;
	size_t		xlen;
	size_t		ylen;
	int			xscale;
	int			yscale;
	int			zscale;
	int			zinc;
	int			xoffset;
	int			yoffset;
}				t_env;
void			fdf_draw_row(t_env *env, t_point *r1, t_point *r2);
void			fdf_draw_map(t_env *env);
int				fdf_init_map(t_env *env, char *file);
void			fdf_calc_point(t_env *env, t_point *point, int x, int y);
int				fdf_expose_hook(t_env *env);
int				fdf_key_hook(int button, t_env *env);
int				fdf_mouse_hook(int button, int x, int y, t_env *env);
#endif

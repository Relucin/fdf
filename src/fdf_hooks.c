/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 20:29:21 by bmontoya          #+#    #+#             */
/*   Updated: 2017/06/01 13:29:58 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <fdf.h>
#include <stdlib.h>

int			fdf_expose_hook(t_env *env)
{
	env->image = mlx_new_image(env->mlx, env->width, env->height);
	env->imgp = (int *)mlx_get_data_addr(env->image, &env->bpp,
		&env->size, &env->endian);
	fdf_draw_map(env);
	mlx_put_image_to_window(env->mlx, env->window, env->image, 0, 0);
	mlx_destroy_image(env->mlx, env->image);
	return (0);
}

static void	fdf_resetview(t_env *env, int button)
{
	if (button == 6)
	{
		env->rx = 0;
		env->ry = 0;
		env->rz = 0;
	}
	else
	{
		env->rx = 0.785398;
		env->ry = 0;
		env->rz = 0.615472907;
	}
}

int			fdf_key_hook(int button, t_env *env)
{
	if (button == 53)
	{
		while (*(env->map))
			free(*env->map++);
		mlx_destroy_window(env->mlx, env->window);
		exit(EXIT_FAILURE);
	}
	else if (button == 13 || button == 1)
		env->yoffset += (button == 13) ? -10 : 10;
	else if (!button || button == 2)
		env->xoffset += (!button) ? -10 : 10;
	else if (button == 125 || button == 126)
		env->rx += (button == 126) ? .1 : -.1;
	else if (button == 123 || button == 124)
		env->ry += (button == 123) ? .1 : -.1;
	else if (button == 6 || button == 7)
		fdf_resetview(env, button);
	if (!button || button == 1 || button == 2 || button == 13
		|| button == 123 || button == 124 || button == 125
		|| button == 126 || button == 6 || button == 7)
		fdf_expose_hook(env);
	return (0);
}

int			fdf_mouse_hook(int button, int x, int y, t_env *env)
{
	(void)x;
	(void)y;
	if (button == 4 || button == 5)
	{
		env->xscale += (env->width / (env->xlen * 4))
					* ((button == 4) ? 1 : -1);
		env->yscale += (env->height / (env->ylen * 4))
					* ((button == 4) ? 1 : -1);
		env->zscale += (env->zinc)
					* ((button == 4) ? 1 : -1);
		fdf_expose_hook(env);
	}
	else if (button == 6 || button == 7)
	{
		env->rz += (button == 6) ? 0.1 : -0.1;
		fdf_expose_hook(env);
	}
	return (0);
}

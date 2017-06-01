/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 18:50:36 by bmontoya          #+#    #+#             */
/*   Updated: 2017/06/01 13:29:52 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <fdf.h>
#include <ftstdlib.h>
#include <ftstdio.h>
#include <stdlib.h>
#include <math.h>

void		fdf_calc_point(t_env *env, t_point *point, int x, int y)
{
	x = (x - (env->xlen / 2)) * env->xscale;
	y = (y - (env->ylen / 2)) * env->yscale;
	point->tx = x * (cos(env->ry) * cos(env->rz))
				- y * (cos(env->ry) * sin(env->rz))
				+ (point->z * env->zscale) * sin(env->ry)
				+ env->xoffset;
	point->ty = x * (sin(env->rx) * sin(env->ry) * cos(env->rz)
				+ cos(env->rx) * sin(env->rz))
				+ y * (sin(env->rz) * sin(env->rx) * sin(env->ry)
				+ cos(env->rx) * cos(env->rz))
				- (point->z * env->zscale) * (cos(env->ry) * sin(env->rx))
				+ env->yoffset;
}

void		fdf_print(void)
{
	ft_printf("--Controls--\n");
	ft_printf("Keys:\n");
	ft_printf("W/S: y translation\n");
	ft_printf("A/D: x translation\n");
	ft_printf("Z/X: Reset view\n");
	ft_printf("--Arrow Keys:\n");
	ft_printf("Up/Down: x rotation\n");
	ft_printf("Right/Left: y rotation\n");
	ft_printf("--Mouse Wheel:\n");
	ft_printf("Up/Down: Scaling\n");
	ft_printf("Right/Left: z rotation\n");
	ft_printf("------------\n");
}

int			main(int argc, char **argv)
{
	t_env	env;

	env.rx = 0.785398;
	env.ry = 0;
	env.rz = 0.615472907;
	env.width = 800;
	env.height = 800;
	env.xoffset = 0;
	env.yoffset = 0;
	env.maxz = 0;
	env.area = (env.width * env.height);
	if (argc == 2 && fdf_init_map(&env, argv[1]))
	{
		fdf_print();
		env.mlx = mlx_init();
		env.window = mlx_new_window(env.mlx, env.width, env.height, "mlx 42");
		mlx_expose_hook(env.window, &fdf_expose_hook, &env);
		mlx_hook(env.window, 2, 0, &fdf_key_hook, &env);
		mlx_mouse_hook(env.window, &fdf_mouse_hook, &env);
		mlx_loop(env.mlx);
	}
	else
		ft_printf("fdf: error\n");
	return (0);
}

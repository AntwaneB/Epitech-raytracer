/*
** main.c for rtv1 in /home/buchse_a/Documents/MUL_2013_rtv1
**
** Made by Antoine Buchser
** Login   <buchse_a@epitech.net>
**
** Started on  Thu Feb 20 15:47:24 2014 Antoine Buchser
** Last update Wed Jun  4 17:13:14 2014 froehly
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "mlx.h"
#include "rt.h"

void	init_color(t_color *color)
{
  color->r = 0;
  color->g = 0;
  color->b = 0;
}

void	cam_init(t_rt *rt)
{
  rt->camera->pos.x = -1300;
  rt->camera->pos.y = -933;
  rt->camera->pos.z = 300;
  rt->camera->rot.x = 0;
  rt->camera->rot.y = 0;
  rt->camera->rot.z = 35;
  rt->camera->mov.x = 500;
  rt->camera->mov.y = 0;
  rt->camera->mov.z = 0;
}

void	generate_functions_tab(t_rt *rt)
{
  rt->functions[0] = &manage_sphere;
  rt->functions[1] = &manage_plane;
  rt->functions[2] = &manage_cone;
  rt->functions[3] = &manage_cylindre;
}

void	rt_init(t_rt *rt, t_ima *img, t_cam *camera)
{
  rt->legend = 0;
  rt->img = img;
  rt->camera = camera;
  rt->objects = get_all_objects(rt->mapfile);
  cam_init(rt);
  if ((rt->mlx_ptr = mlx_init()) == NULL)
    my_error("mlx_init() failed. Stop unseting env plz.");
  if ((rt->win_ptr = mlx_new_window(rt->mlx_ptr, WIN_WIDTH,
				    WIN_HEIGHT, "Raytracer")) == NULL)
    my_error("mlx_new_window() failed. Stop unseting env plz.");
  rt->img->img_ptr = mlx_new_image(rt->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
  rt->img->firstbyte = mlx_get_data_addr(rt->img->img_ptr,
					 &(rt->img->bpp),
					 &(rt->img->sizeline),
					 &(rt->img->endian));
  rt->focale = (ANTIALIASING) ? 3200 : 800;
  rt->ambiant_min = 0.0;
  generate_functions_tab(rt);
}

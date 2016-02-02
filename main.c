/*
** main.c for rtv1 in /home/buchse_a/Documents/MUL_2013_rtv1
**
** Made by Antoine Buchser
** Login   <buchse_a@epitech.net>
**
** Started on  Thu Feb 20 15:47:24 2014 Antoine Buchser
** Last update Thu Jun  5 15:08:16 2014 Alexandre Page
*/

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include "mlx.h"
#include "rt.h"

t_obj		*find_closer(t_rt *rt, t_obj *obj)
{
  t_obj		*closer;

  (void)rt;
  closer = NULL;
  while (obj != NULL)
    {
      if ((closer == NULL || obj->k < closer->k)
	  && obj->inter == 1 && obj->k >= 0
	  && obj->type != SPOTLIGHT)
	closer = obj;
      obj = obj->next;
    }
  return (closer);
}

int		find_object(t_rt *rt, int x, int y)
{
  t_obj		*obj;
  t_obj		*closer;

  rt->camera->v.x = rt->focale;
  rt->camera->v.y = WIN_WIDTH / 2 - x;
  rt->camera->v.z = WIN_HEIGHT / 2 - y;
  rotation(&(rt->camera->v), rt->camera->rot.x,
	   rt->camera->rot.y, rt->camera->rot.z);
  obj = rt->objects;
  while (obj != NULL)
    {
      if (obj->type != SPOTLIGHT)
	rt->functions[obj->type](rt, obj, &(rt->camera->v));
      obj = obj->next;
    }
  rev_rotation(&(rt->camera->v), rt->camera->rot.x,
	       rt->camera->rot.y, rt->camera->rot.z);
  closer = find_closer(rt, rt->objects);
  if (closer != NULL)
    return (get_lum_object_mult(rt, closer));
  else
    return (0x000000);
}

void		rt_fill_aa(t_th_container *rt)
{
  int		x;
  int		y;
  unsigned int	color[8];

  x = rt->start->x - 1;
  while (++x < rt->end->x)
    {
      y = rt->start->y - 1;
      while (++y < rt->end->y)
	{
	  color[0] = find_object(rt->rt, x + 1, y);
	  color[1] = find_object(rt->rt, x + 1, y + 1);
	  color[2] = find_object(rt->rt, x, y);
	  color[3] = find_object(rt->rt, x, y + 1);
	  color[4] = find_object(rt->rt, x - 1, y);
	  color[5] = find_object(rt->rt, x - 1, y - 1);
	  color[6] = find_object(rt->rt, x - 1, y + 1);
	  color[7] = find_object(rt->rt, x + 1, y - 1);
	  mlx_put_pixel_in_image(rt->rt,
				 (x + 3 * WIN_WIDTH / 2) / 4,
				 (y + 3 * WIN_HEIGHT / 2) / 4, get_medium_color(color));
	}
      print_progress();
    }
  pthread_exit(0);
}

void		rt_fill_noaa(t_th_container *rt)
{
  int		x;
  int		y;

  x = rt->start->x - 1;
  while (++x < rt->end->x)
    {
      y = rt->start->y - 1;
      while (++y < rt->end->y)
	{
	  mlx_put_pixel_in_image(rt->rt, x, y,
				 find_object(rt->rt, x, y));
	}
      print_progress();
    }
  pthread_exit(0);
}

int	main(int ac, char **av)
{
  t_rt	rt;
  t_ima	img;
  t_cam	camera;
  int	(*functions[4])(t_rt *rt, t_obj *obj, t_pos *pos);

  if (ac != 2)
    my_error("usage: ./rtv1 [mapfile]\n");
  rt.functions = functions;
  rt.mapfile = strdup(av[1]);
  rt_init(&rt, &img, &camera);
  create_threads(&rt);
  mlx_put_image_to_window(rt.mlx_ptr, rt.win_ptr,
			  rt.img->img_ptr, 0, 0);
  my_legend(&rt);
  mlx_expose_hook(rt.win_ptr, manage_expose, &rt);
  mlx_key_hook(rt.win_ptr, manage_key, &rt);
  mlx_loop(rt.mlx_ptr);
  return (EXIT_SUCCESS);
}

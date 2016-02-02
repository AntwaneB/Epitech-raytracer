/*
** main.c for rtv1 in /home/buchse_a/Documents/MUL_2013_rtv1
**
** Made by Antoine Buchser
** Login   <buchse_a@epitech.net>
**
** Started on  Thu Feb 20 15:47:24 2014 Antoine Buchser
** Last update Fri Jun  6 11:01:50 2014 Alexandre Page
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "mlx.h"
#include "rt.h"

static void	move_arrows(int keycode, t_rt *rt)
{
  rt->camera->dir.x = rt->camera->mov.x * cos(dtor(rt->camera->rot.z));
  rt->camera->dir.y = rt->camera->mov.x * sin(dtor(rt->camera->rot.z));
  if (keycode == Z)
    {
      rt->camera->pos.x += rt->camera->dir.x;
      rt->camera->pos.y += rt->camera->dir.y;
    }
  else if (keycode == S)
    {
      rt->camera->pos.x -= rt->camera->dir.x;
      rt->camera->pos.y -= rt->camera->dir.y;
    }
  else if (keycode == Q)
    rt->camera->rot.z += 15;
  else if (keycode == D)
    rt->camera->rot.z -= 15;
  else if (keycode == NUM_SIX)
    rt->camera->rot.x += 15;
  else if (keycode == NUM_FOUR)
    rt->camera->rot.x -= 15;
}

static void	move_letters(int keycode, t_rt *rt)
{
  rt->camera->dir.x = rt->camera->mov.x * cos(dtor(rt->camera->rot.z + 90));
  rt->camera->dir.y = rt->camera->mov.x * sin(dtor(rt->camera->rot.z + 90));
  if (keycode == NUM_EIGHT)
    rt->camera->rot.y -= 15;
  else if (keycode == NUM_THREE)
    rt->camera->rot.y += 15;
  else if (keycode == SPACE)
    rt->camera->pos.z += 200;
  else if (keycode == CTRL)
    rt->camera->pos.z -= 200;
  else if (keycode == A)
    {
      rt->camera->pos.x += rt->camera->dir.x;
      rt->camera->pos.y += rt->camera->dir.y;
    }
  else if (keycode == E)
    {
      rt->camera->pos.x -= rt->camera->dir.x;
      rt->camera->pos.y -= rt->camera->dir.y;
    }
  else if (keycode == N)
    move_letters_next(rt);
}

int	manage_key(int key, t_rt *rt)
{
  if (key == ESC)
    exit(EXIT_SUCCESS);
  else if (key == Z || key == S || key == NUM_SIX ||
	   key == D || key == Q || key == NUM_FOUR)
    move_arrows(key, rt);
  else if (key == A || key == NUM_THREE || key == NUM_EIGHT ||
	   key == CTRL || key == E || key == SPACE || key == N)
    move_letters(key, rt);
  else if (key == NUM_PLUS || key == NUM_MINUS)
    light_numpad(key, rt);
  else if (my_key_legend(key, rt) == EXIT_SUCCESS)
    return (0);
  else
    return (0);
  if (key != N)
    create_threads(rt);
  mlx_put_image_to_window(rt->mlx_ptr, rt->win_ptr,
			  rt->img->img_ptr, 0, 0);
  my_legend(rt);
  return (0);
}

int	manage_expose(t_rt *rt)
{
  mlx_put_image_to_window(rt->mlx_ptr, rt->win_ptr, rt->img->img_ptr, 0, 0);
  my_legend(rt);
  return (0);
}

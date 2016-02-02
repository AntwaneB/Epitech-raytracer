/*
** main.c for rtv1 in /home/buchse_a/Documents/MUL_2013_rtv1
** 
** Made by Antoine Buchser
** Login   <buchse_a@epitech.net>
** 
** Started on  Thu Feb 20 15:47:24 2014 Antoine Buchser
** Last update Fri Jun  6 10:56:53 2014 Alexandre Page
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "mlx.h"
#include "rt.h"

static void	set_all_color(t_color *color, int rgb)
{
  color->r = rgb;
  color->g = rgb;
  color->b = rgb;
}

static void	init_pair(int *pairx, int *pairy, int *pairz, t_pos pos)
{
  *pairx = ((abs(pos.x) % 2) == 0);
  *pairy = ((abs(pos.y) % 2) == 0);
  *pairz = ((abs(pos.z) % 2) == 0);
}

void	manage_checkerboard(t_obj *obj, t_color *final_color)
{
  t_pos	pos;
  int	pairx;
  int	pairy;
  int	pairz;

  if (obj->checkerboard > 0)
    {
      pos.x = (int)((obj->p.x + MOVE) / obj->checkerboard);
      pos.y = (int)((obj->p.y + MOVE) / obj->checkerboard);
      pos.z = (int)((obj->p.z + MOVE) / obj->checkerboard);
      init_pair(&pairx, &pairy, &pairz, pos);
      if (pos.x + MOVE < 0)
	pairx = (pairx == 1) ? 0 : 1;
      if (pos.y + MOVE < 0)
	pairy = (pairy == 1) ? 0 : 1;
      if (pos.z + MOVE < 0)
	pairz = (pairz == 1) ? 0 : 1;
      if (pairz)
	set_all_color(final_color, ((pairx && pairy) || (!pairx && !pairy)) ?
		      159 : 63);
      else if ((pairx && pairy) || (!pairx && !pairy))
	set_all_color(final_color, 63);
      else
	set_all_color(final_color, 159);
    }
}

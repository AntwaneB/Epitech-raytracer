/*
** legend.c for legend in /home/froehl_f/rendu/mul_2013_rtracer
** 
** Made by froehly
** Login   <froehl_f@epitech.net>
** 
** Started on  Wed Jun  4 17:08:22 2014 froehly
** Last update Sat Jun  7 14:04:51 2014 Alexandre Page
*/

#include <stdlib.h>
#include "mlx.h"
#include "rt.h"

static void my_legend_key_next(t_rt *rt)
{
  mlx_string_put(rt->mlx_ptr, rt->win_ptr, 50, 270, 0xFAB0FB,
                 "ROTATION DROITE       : D");
  mlx_string_put(rt->mlx_ptr, rt->win_ptr, 50, 290, 0xFAB0FB,
		 "CAMERA POS            : N");
}

void	my_legend_key(t_rt *rt)
{
  mlx_string_put(rt->mlx_ptr, rt->win_ptr, 50, 50, 0xFAB0FB,
                 "TRANSLATION AVANT     : Z");
  mlx_string_put(rt->mlx_ptr, rt->win_ptr, 50, 70, 0xFAB0FB,
                 "TRANSLATION ARRIERE   : S");
  mlx_string_put(rt->mlx_ptr, rt->win_ptr, 50, 90, 0xFAB0FB,
                 "TRANSLATION GAUCHE    : A");
  mlx_string_put(rt->mlx_ptr, rt->win_ptr, 50, 110, 0xFAB0FB,
                 "TRANSLATION DROITE    : E");
  mlx_string_put(rt->mlx_ptr, rt->win_ptr, 50, 130, 0xFAB0FB,
                 "MONTER CAMERA         : SPACE");
  mlx_string_put(rt->mlx_ptr, rt->win_ptr, 50, 150, 0xFAB0FB,
                 "DESCENDRE CAMERA      : CTRL");
  mlx_string_put(rt->mlx_ptr, rt->win_ptr, 50, 170, 0xFAB0FB,
                 "ROTATION GAUCHE_X     : NUM 4");
  mlx_string_put(rt->mlx_ptr, rt->win_ptr, 50, 190, 0xFAB0FB,
                 "ROTATION DROITE_X     : NUM 6");
  mlx_string_put(rt->mlx_ptr, rt->win_ptr, 50, 210, 0xFAB0FB,
                 "ROTATION HAUT         : NUM 8");
  mlx_string_put(rt->mlx_ptr, rt->win_ptr, 50, 230, 0xFAB0FB,
                 "ROTATION BAS          : NUM 2");
  mlx_string_put(rt->mlx_ptr, rt->win_ptr, 50, 250, 0xFAB0FB,
                 "ROTATION GAUCHE       : Q");
  my_legend_key_next(rt);
}

void	my_legend(t_rt *rt)
{
  if (rt->legend == 1)
    my_legend_key(rt);
  else
    mlx_string_put(rt->mlx_ptr, rt->win_ptr, 50, 50, 0xFAB0FB,
                   "HELP                  : H");
}

int	my_key_legend(int key, t_rt *rt)
{
  if (key == HELP && rt->legend == 0)
    rt->legend = 1;
  else if (key == HELP && rt->legend == 1)
    rt->legend = 0;
  else
    return (EXIT_FAILURE);
  mlx_put_image_to_window(rt->mlx_ptr, rt->win_ptr,
                          rt->img->img_ptr, 0, 0);
  my_legend(rt);
  return (EXIT_SUCCESS);
}

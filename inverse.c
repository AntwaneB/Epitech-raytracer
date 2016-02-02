/*
** inverse.c for inverse in /home/froehl_f/rendu/mul_2013_rtracer
** 
** Made by froehly
** Login   <froehl_f@epitech.net>
** 
** Started on  Wed Jun  4 15:21:32 2014 froehly
** Last update Wed Jun  4 15:38:15 2014 froehly
*/

#include <stdlib.h>
#include "rt.h"

void	my_inverse(char *wordtab, t_obj *obj)
{
  int	inv;

  inv = atoi(wordtab);
  if (inv == 1)
    {
      obj->color.r = 255 - obj->color.r;
      obj->color.g = 255 - obj->color.g;
      obj->color.b = 255 - obj->color.b;
    }
}

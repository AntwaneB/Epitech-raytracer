/*
** main.c for rtv1 in /home/buchse_a/Documents/MUL_2013_rtv1
**
** Made by Antoine Buchser
** Login   <buchse_a@epitech.net>
**
** Started on  Thu Feb 20 15:47:24 2014 Antoine Buchser
** Last update Tue May 27 15:08:25 2014 Antoine Buchser
*/

#include "rt.h"

int	poscmp(t_pos pos1, t_pos pos2)
{
  if (pos1.x == pos2.x
      && pos1.y == pos2.y
      && pos1.z == pos2.z)
    return (1);
  else
    return (0);
}

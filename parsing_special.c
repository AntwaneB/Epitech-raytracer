/*
** main.c for rtv1 in /home/buchse_a/Documents/MUL_2013_rtv1
**
** Made by Antoine Buchser
** Login   <buchse_a@epitech.net>
**
** Started on  Thu Feb 20 15:47:24 2014 Antoine Buchser
** Last update Thu Jun  5 16:40:40 2014 Antoine Buchser
*/

#include <stdlib.h>
#include <string.h>
#include "rt.h"

int	get_object_type(char *type)
{
  if (strcmp(type, "sphere") == 0 || strcmp(type, "none") == 0)
    return (SPHERE);
  else if (strcmp(type, "plane") == 0 || strcmp(type, "marble") == 0)
    return (PLANE);
  else if (strcmp(type, "spotlight") == 0)
    return (SPOTLIGHT);
  else if (strcmp(type, "cone") == 0 || strcmp(type, "grain") == 0)
    return (CONE);
  else if (strcmp(type, "cylindre") == 0 || strcmp(type, "wood") == 0)
    return (CYLINDRE);
  else
    my_error("Fichier de map invalide.\n");
  return (-1);
}

int	is_valid_object(t_obj *tmp, int i)
{
  if ((tmp->type == SPHERE && i < 4)
      || (tmp->type == PLANE && i < 3)
      || (tmp->type == SPOTLIGHT && i < 3))
    return (0);
  else
    return (1);
}

void	tmp_set_posrot(t_obj *tmp, char **wordtab, int i)
{
  if (i == 1)
    tmp->pos.x = atoi(wordtab[i]);
  else if (i == 2)
    tmp->pos.y = atoi(wordtab[i]);
  else if (i == 3)
    tmp->pos.z = atoi(wordtab[i]);
  else if (i == 7)
    tmp->rot.x = atoi(wordtab[i]);
  else if (i == 8)
    tmp->rot.y = atoi(wordtab[i]);
  else if (i == 9)
    tmp->rot.z = atoi(wordtab[i]);
}

void	tmp_set_color(t_obj *tmp, char **wordtab, int i)
{
  if (i == 4)
    tmp->color.r = atoi(wordtab[i]);
  else if (i == 5)
    tmp->color.g = atoi(wordtab[i]);
  else if (i == 6)
    tmp->color.b = atoi(wordtab[i]);
}

void	limits_parsing(t_obj *tmp, char *limits_s, char *limits_e)
{
  char	**limits;

  limits = my_explode(limits_s);
  tmp->limits_s.x = atof(limits[0]);
  tmp->limits_s.y = atof(limits[1]);
  tmp->limits_s.z = atof(limits[2]);
  free_wordtab(limits);
  limits = my_explode(limits_e);
  tmp->limits_e.x = atof(limits[0]);
  tmp->limits_e.y = atof(limits[1]);
  tmp->limits_e.z = atof(limits[2]);
  free_wordtab(limits);
  if (tmp->limits_e.x != 0 || tmp->limits_e.y != 0 || tmp->limits_e.z != 0
      || tmp->limits_s.x != 0 || tmp->limits_s.y != 0 || tmp->limits_s.z != 0)
    tmp->limits = 1;
}

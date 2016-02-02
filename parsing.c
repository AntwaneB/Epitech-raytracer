/*
** main.c for rtv1 in /home/buchse_a/Documents/MUL_2013_rtv1
** 
** Made by Antoine Buchser
** Login   <buchse_a@epitech.net>
** 
** Started on  Thu Feb 20 15:47:24 2014 Antoine Buchser
** Last update Thu Jun  5 15:12:12 2014 Alexandre Page
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "rt.h"

static void	print_info(t_obj *tmp, char **wordtab, int i)
{
  if (i == 0)
    tmp->type = get_object_type(wordtab[i]);
  else if (i == 1 || i == 2 || i == 3)
    tmp_set_posrot(tmp, wordtab, i);
  else if (i == 4 || i == 5 || i == 6)
    tmp_set_color(tmp, wordtab, i);
  else if (i == 7 || i == 8 || i == 9)
    tmp_set_posrot(tmp, wordtab, i);
  else if (i == 10)
    tmp->size = atoi(wordtab[i]);
  else if (i == 11)
    tmp->shininess = atoi(wordtab[i]) / 100.0;
  else if (i == 12)
    tmp->checkerboard = atoi(wordtab[i]);
  else if (i == 13)
    tmp->reflex = atoi(wordtab[i]) / 100.0;
  else if (i == 14)
    tmp->transp = atoi(wordtab[i]) / 100.0;
  else if (i == 16)
    limits_parsing(tmp, wordtab[i - 1], wordtab[i]);
  else if (i == 17)
    tmp->material = get_object_type(wordtab[i]);
  else if (i == 18)
    my_inverse(wordtab[i], tmp);
}

static void	get_all_infos(t_obj *tmp, char **wordtab, int i)
{
  while (wordtab && wordtab[++i] != NULL)
    print_info(tmp, wordtab, i);
  if (!is_valid_object(tmp, i))
    my_error("Fichier de map invalide.\n");
}

void	add_object_to_list(t_obj **list, t_obj *new)
{
  t_obj	*tmp;
  t_obj	*elem;

  if ((elem = malloc(sizeof(*elem))) == NULL)
    my_perror(NULL);
  add_everything(elem, new);
  if (*list == NULL)
    *list = elem;
  else
    {
      tmp = *list;
      while (tmp->next != NULL)
	tmp = tmp->next;
      tmp->next = elem;
    }
}

void	init_tmp_to_null(t_obj *tmp)
{
  tmp->type = -1;
  tmp->pos.x = 0;
  tmp->pos.y = 0;
  tmp->pos.z = 0;
  tmp->rot.x = 0;
  tmp->rot.y = 0;
  tmp->rot.z = 0;
  tmp->color.r = 0;
  tmp->color.g = 0;
  tmp->color.b = 0;
  tmp->limits = 0;
  tmp->limits_s.x = 0;
  tmp->limits_s.y = 0;
  tmp->limits_s.z = 0;
  tmp->limits_e.x = 0;
  tmp->limits_e.y = 0;
  tmp->limits_e.z = 0;
  tmp->size = -1;
  tmp->shininess = 0;
  tmp->checkerboard = 0;
  tmp->reflex = 0;
  tmp->transp = 0;
  tmp->material = 0;
  tmp->next = NULL;
}

t_obj	*get_all_objects(char *filename)
{
  int	fd;
  char	*line;
  char	**wordtab;
  t_obj	*objects;
  t_obj	tmp;

  objects = NULL;
  if ((fd = open(filename, O_RDONLY)) == -1)
    my_perror(filename);
  get_next_line(fd);
  while ((line = get_next_line(fd)) != NULL)
    {
      if (line[0] != '\0')
	{
	  wordtab = my_str_to_wordtab(line);
	  init_tmp_to_null(&tmp);
	  get_all_infos(&tmp, wordtab, -1);
	  add_object_to_list(&objects, &tmp);
	  free(line);
	  free_wordtab(wordtab);
	}
    }
  return (objects);
}

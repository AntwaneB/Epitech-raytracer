/*
** threads.c for threads in /home/giubil_v
**
** Made by victor giubilei
** Login   <giubil_v@epitech.net>
**
** Started on  Thu May 29 18:25:45 2014 victor giubilei
** Last update Thu Jun  5 15:18:15 2014 Alexandre Page
*/

#include <stdlib.h>
#include <pthread.h>
#include "rt.h"

static void		cpy_pos(t_pos *old, t_pos *new)
{
  new->x = old->x;
  new->y = old->y;
  new->z = old->z;
}

static void		cpy_cam(t_cam *old, t_cam *new)
{
  cpy_pos(&(old->pos), &(new->pos));
  cpy_pos(&(old->v), &(new->v));
  cpy_pos(&(old->rot), &(new->rot));
  cpy_pos(&(old->mov), &(new->mov));
}

static void		cpy_rt(t_rt *old, t_rt *new)
{
  new->img = old->img;
  new->focale = old->focale;
  new->ambiant_min = old->ambiant_min;
  new->functions = old->functions;
}

static void		cpy_all(t_rt *new, t_rt *rt,
				t_th_container *all, int i)
{
  new->objects = get_all_objects(rt->mapfile);
  cpy_rt(rt, new);
  all->rt = new;
  fill_pos(all->start, all->end, i);
}

void			create_threads(t_rt *rt)
{
  pthread_t		threads[8];
  t_th_container	*all;
  int			i;
  t_rt			*new;

  i = -1;
  while (++i < 8)
    {
      if (!(new = malloc(sizeof(t_rt)))
	  ||!(new->camera = malloc(sizeof(t_cam)))
	  || !(all = malloc(sizeof(t_th_container)))
	  || !(all->start = malloc(sizeof(t_pos)))
	  || !(all->end = malloc(sizeof(t_pos))))
	exit(EXIT_FAILURE);
      cpy_all(new, rt, all, i);
      cpy_cam(rt->camera, new->camera);
      pthread_create(&(threads[i]), NULL,
		     (ANTIALIASING) ? (void *)rt_fill_aa
		     : (void *)rt_fill_noaa, all);
      if (!MULTI_THREAD)
	pthread_join(threads[i], NULL);
    }
  i = -1;
  while (++i < 8)
    pthread_join(threads[i], NULL);
}

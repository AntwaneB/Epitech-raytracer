/*
** main.c for rtv1 in /home/buchse_a/Documents/MUL_2013_rtv1
**
** Made by Antoine Buchser
** Login   <buchse_a@epitech.net>
**
** Started on  Thu Feb 20 15:47:24 2014 Antoine Buchser
** Last update Tue May 27 17:27:00 2014 victor giubilei
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include "mlx.h"
#include "get_next_line.h"
#include "rt.h"

static void	my_putstr(char *str)
{
  write(1, str, strlen(str));
}

static int	get_current_percent(int reset)
{
  static int	count = -1;
  static int	inc = 0;
  int		x;
  int		to;

  to = (ANTIALIASING) ? WIN_WIDTH * 4 : WIN_WIDTH;
  if (reset)
    {
      count = -1;
      inc = -1;
      return (-1);
    }
  count = (inc == 0) ? count + 1 : count;
  if (count == to - 1)
    count++;
  inc = (inc == 0) ? 1 : 0;
  x = count;
  if (x % (to / 100) == 0)
    return (x / (to / 100));
  else
    return (-1);
}

static void	print_percent(int percent)
{
  if (percent < 100)
    {
      printf(" %d%%", percent);
      fflush(stdout);
    }
  else
    {
      my_putstr(" Image ready\n");
      get_current_percent(1);
    }

}

void		print_progress(void)
{
  int		i;
  int		percent;
  static int	writing = 0;

  if ((percent = get_current_percent(0)) != -1 && !writing)
    {
      writing = 1;
      my_putstr("\rProgress : [");
      i = -1;
      while (++i < percent / 10)
	my_putstr("===");
      i = -1;
      while (++i < 10 - percent / 10)
	my_putstr("   ");
      my_putstr("]");
      print_percent(percent);
      writing = 0;
    }
}

/*
** main.c for rtv1 in /home/buchse_a/Documents/MUL_2013_rtv1
** 
** Made by Antoine Buchser
** Login   <buchse_a@epitech.net>
** 
** Started on  Thu Feb 20 15:47:24 2014 Antoine Buchser
** Last update Wed Mar 12 13:03:26 2014 Antoine Buchser
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

static void	write_error(char *str)
{
  write(2, str, strlen(str));
}

void	my_error(char *str)
{
  if (str != NULL)
    write_error(str);
  exit(EXIT_FAILURE);
}

void	my_perror(char *str)
{
  perror(str);
  exit(EXIT_FAILURE);
}

void	free_wordtab(char **wordtab)
{
  int	i;

  i = 0;
  while (wordtab[i] != NULL)
    {
      free(wordtab[i]);
      i++;
    }
  free(wordtab);
}

/*
** get_next_line.c for get_next_line in /home/buchse_a/Documents/CPE_2013_getnextline
** 
** Made by Antoine Buchser
** Login   <buchse_a@epitech.net>
** 
** Started on  Fri Nov 22 22:20:10 2013 Antoine Buchser
** Last update Thu Feb 20 16:51:22 2014 Antoine Buchser
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "get_next_line.h"

static void	cut_buffer(char buffer[], int j)
{
  int		i;

  i = 0;
  while (i < MAX_SIZE && i + j < MAX_SIZE)
    {
      buffer[i] = buffer[i + j];
      i++;
    }
  buffer[i] = '\0';
}

static char	*my_realloc(char *ptr, int size)
{
  char		*dest;
  int		ptr_len;
  int		i;

  ptr_len = 0;
  while (ptr[ptr_len])
    ptr_len++;
  if ((dest = malloc((ptr_len + size + 1) * sizeof(char))) == NULL)
    return (NULL);
  i = 0;
  while (ptr[i])
    {
      dest[i] = ptr[i];
      i++;
    }
  dest[i] = '\0';
  free(ptr);
  return (dest);
}

static void	my_strcat_gnl(char *dest, char *src)
{
  int		i;
  int		j;

  j = 0;
  while (dest[0])
    {
      dest++;
      j++;
    }
  i = 0;
  while (src[i] && src[i] != '\n')
    {
      dest[i] = src[i];
      i++;
    }
  dest[i] = '\0';
  if (src[i] == '\n')
    dest[i] = '\n';
  cut_buffer(src, i);
  dest = dest - j;
}

static int	check_eol(char *next_line, char *buffer)
{
  int		i;
  int		eol;

  i = 0;
  eol = 0;
  while (next_line[i] && eol == 0)
    {
      if (next_line[i] == '\n' || next_line[i] == '\0')
	{
	  next_line[i] = '\0';
	  i = 0;
	  while (buffer[i] != '\n' && buffer[i])
	    i++;
	  cut_buffer(buffer, i + 1);
	  eol = 1;
	}
      i++;
    }
  return (eol);
}

char		*get_next_line(const int fp)
{
  static char	buffer[MAX_SIZE + 1] = {0};
  char		*next_line;
  int		ret;

  if ((next_line = malloc((MAX_SIZE + 1) * sizeof(char))) == NULL)
    return (NULL);
  next_line[0] = '\0';
  my_strcat_gnl(next_line, buffer);
  while (check_eol(next_line, buffer) == 0)
    {
      if ((ret = read(fp, buffer, MAX_SIZE)) == -1)
	return (NULL);
      if (ret == 0)
	return (NULL);
      buffer[ret] = '\0';
      next_line = my_realloc(next_line, ret);
      my_strcat_gnl(next_line, buffer);
    }
  return (next_line);
}

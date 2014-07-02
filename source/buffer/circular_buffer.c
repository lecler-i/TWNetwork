/*
** circular_buffer.c for circular_buffer in /home/lecler_i/Work/Epitech/Tek2/SysUnix/PSU_2013_zappy/server/source
**
** Made by Thomas LECLERCQ
** Login   <lecler_i@epitech.net>
**
** Started on  Fri Jun 20 12:22:24 2014 Thomas LECLERCQ
** Last update Wed Jul  2 16:20:28 2014 Thomas LECLERCQ
*/

#include "circular_buffer.h"

int		circular_buffer_push(t_circular_buffer *this, const char *data, size_t size)
{
  char		*new_buffer;

  printf("LOOOL %p\n", this->buffer);
  new_buffer = (char*)realloc(this->buffer, this->pos + size + 1);
  if (new_buffer == NULL)
    return (-1);
  this->buffer = new_buffer;
  strncpy(this->buffer + this->pos, data, size);
  this->pos += size;
  this->buffer[this->pos] = 0;
  return (0);
}

int		circular_buffer_push_front(t_circular_buffer *this, const char *data, size_t size)
{
  char		*new_buffer;

  new_buffer = (char*)malloc(this->pos + size + 1);
  if (new_buffer == NULL)
    return (-1);
  strncpy(new_buffer, data, size);
  strncpy(new_buffer + size, this->buffer, this->pos);
  free(this->buffer);
  this->buffer = new_buffer;
  this->pos += size;
  this->buffer[this->pos] = 0;
  return (0);
}

char		*circular_buffer_pop(t_circular_buffer *this)
{
  char		*tmp;
  int		len;
  char		*data;

  data = NULL;
  if ((tmp = strstr(this->buffer, "\n")))
    {
      *tmp = 0;
      len = strlen(this->buffer);
      data = strdup(this->buffer);
      this->pos -= (len + 1);
      strncpy(this->buffer, tmp + 1, this->pos + 1);
    }
  return (data);
}


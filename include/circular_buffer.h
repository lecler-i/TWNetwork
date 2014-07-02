/*
** circular_buffer.h for circular_bufer in /home/lecler_i/Work/Epitech/Tek2/SysUnix/PSU_2013_zappy/server/source
**
** Made by Thomas LECLERCQ
** Login   <lecler_i@epitech.net>
**
** Started on  Thu Jun 26 19:53:48 2014 Thomas LECLERCQ
** Last update Mon Jun 30 11:04:53 2014 Thomas LECLERCQ
*/

#ifndef	__CIRCULAR_BUFFER_H__
#define	__CIRCULAR_BUFFER_H__

#ifndef _BSD_SOURCE
 #define _BSD_SOURCE
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct		s_circular_buffer
{
  char			*buffer;
  int			pos;
}			t_circular_buffer;

int			circular_buffer_push(t_circular_buffer *this, const char *data, size_t size);
char			*circular_buffer_pop(t_circular_buffer *this);
int			circular_buffer_push_front(t_circular_buffer *this, const char *data, size_t size);

#endif

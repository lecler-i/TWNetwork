/*
** send.c for send in /home/lecler_i/Work/Epitech/Tek2/SysUnix/PSU_2013_zappy/server/source/network
**
** Made by Thomas LECLERCQ
** Login   <lecler_i@epitech.net>
**
** Started on  Thu Jun 26 21:24:39 2014 Thomas LECLERCQ
** Last update Wed Jul  2 23:01:28 2014 Thomas LECLERCQ
*/

#include "network.h"
#include "circular_buffer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

static t_network		*network;

void		_network_set_internal_glob(t_network *_network)
{
  network = _network;
}

int		network_client_send_data(t_client *this, const char *data)
{
  char		*to_send;
  int		len;
  int		ret;

  /* printf("%p\n", network); */
  to_send = NULL;
  if ((len = asprintf(&to_send, "%s\n", data)) == -1)
    return (-1);
  printf("to send : [%s]\n", to_send);
  ret = write(this->sock, to_send, len);
  if (ret != len)
    {
      circular_buffer_push_front(&this->send, &to_send[ret], len - ret);
    }
  printf("%d of %d sent\n", ret, len);

  /* ret = circular_buffer_push(&this->recv, to_send, ret); */
  free(to_send);
  return (ret);
}

int		network_client_send(t_client *this, const char *fmt, ...)
{
  va_list	ap;
  char		*data;
  int		ret;

  data = NULL;
  va_start(ap, fmt);
  vasprintf(&data, fmt, ap);
  ret = network_client_send_data(this, data);
  va_end(ap);
  return (ret);
}

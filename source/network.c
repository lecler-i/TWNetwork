/*
** network.c for nnetwtroek in /home/lecler_i/Work/Epitech/Tek2/SysUnix/PSU_2013_zappy/server/source
**
** Made by Thomas LECLERCQ
** Login   <lecler_i@epitech.net>
**
** Started on  Thu Jun 26 19:47:02 2014 Thomas LECLERCQ
** Last update Fri Jun 27 10:58:47 2014 Thomas LECLERCQ
*/

#include "network.h"

void		network_handle_read_event(t_network *this, int sock)
{
  t_client	*client;
  char		*buf;

  if (sock == this->sock)
    network_handle_new_connection(this);
  else if ((client = network_client_search_by_sock(this, sock)))
    {
      if (network_client_get_data(client) == -1)
	{
	  if (this->on_lost_connection)
	    this->on_lost_connection(this->arg, client);
	  network_client_delete(this, client);
	}
      else
	{
	  while ((buf = circular_buffer_pop(&client->recv)))
	    {
	      if (this->on_request_recv)
		this->on_request_recv(this->arg, client, buf);
	      /* printf("[%s]\n", buf); */
	      free(buf);
	    }
	    /* 	push_to_request_queue(&this->kernel, client, buf); */
	}
    }
  else
    {
      printf("Cannot find client for socket %d\n", sock);
    }
}

int		network_init(t_network *this, short port)
{
  memset(this, 0, sizeof(*this));
  return (network_socket_init(this, port));
}

void		network_run(t_network *this)
{
  int		i;
  fd_set	read_fd_set;

  if (network_socket_listen(this) == -1)
    return ;
  FD_ZERO(&this->active_fd_set);
  FD_SET(this->sock, &this->active_fd_set);
  while (1)
    {
      read_fd_set = this->active_fd_set;
      if (select(FD_SETSIZE, &read_fd_set, 0, 0, 0) == -1)
	{
	  perror("select");
	  return ;
	}
      i = -1;
      while (++i < FD_SETSIZE)
	{
	  if (FD_ISSET(i, &read_fd_set))
	    {
	      network_handle_read_event(this, i);
	    }
	}
      /* handle_requests(server); */
    }
}

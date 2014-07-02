/*
** clients.c for clients in /home/lecler_i/Work/Epitech/Tek2/SysUnix/PSU_2013_myirc/server/source
**
** Made by Thomas LECLERCQ
** Login   <lecler_i@epitech.net>
**
** Started on  Fri Apr 25 10:10:41 2014 Thomas LECLERCQ
** Last update Wed Jul  2 09:56:12 2014 Thomas LECLERCQ
*/

#include "network.h"

int		network_client_get_data(t_client *this)
{
  int		ret;
  char		buf[NETWORK_READ_SIZE + 1];

  ret = read(this->sock, buf, NETWORK_READ_SIZE);
  if (ret == 0)
    {
      printf("Connection lost\n");
      return (-1);
    }
  if (ret == -1)
    {
      perror("read");
      return (-1);
    }
  circular_buffer_push(&this->recv, buf, ret);
  return (0);
}

t_client	*network_client_search_by_sock(t_network *this, int fd)
{
  t_client	*cur_client;

  cur_client = this->clients;
  while (cur_client)
    {
      if (cur_client->sock == fd)
	return (cur_client);
      cur_client = cur_client->next;
    }
  return (NULL);
}

int		network_client_delete(t_network *this, t_client *client)
{
  t_client	*cur_client;
  t_client	*tmp;

  cur_client = this->clients;
  tmp = NULL;
  while (cur_client)
    {
      if (cur_client == client)
	{
	  if (tmp)
	    tmp->next = cur_client->next;
	  else
	    this->clients = cur_client->next;
	  FD_CLR(cur_client->sock, &this->active_fd_set);
	  close(cur_client->sock);
	  fprintf(stderr, "Server: disconnect from host %s, port %d.\n",
		  inet_ntoa(client->sin.sin_addr), ntohs(client->sin.sin_port));
	  /* delete_request_from_client(&server->kernel, client); */
	  free(cur_client);
	  return (1);
	}
      tmp = cur_client;
      cur_client = cur_client->next;
    }
  return (0);
}

int		network_client_add(t_network *this, t_client *client)
{
  if (client == NULL)
    return (0);
  if (this->clients == NULL)
    {
      this->clients = client;
    }
  else
    {
      client->next = this->clients;
      this->clients = client;
    }
  if (this->on_accept_connection)
    this->on_accept_connection(this->arg, client);
  return (1);
}

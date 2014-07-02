/*
** init.c for init in /home/lecler_i/Work/Epitech/Tek2/SysUnix/PSU_2013_myirc/server
**
** Made by Thomas LECLERCQ
** Login   <lecler_i@epitech.net>
**
** Started on  Sun Apr 27 13:32:43 2014 Thomas LECLERCQ
** Last update Thu Jun 26 20:52:03 2014 Thomas LECLERCQ
*/

#include "network.h"

int		network_handle_new_connection(t_network *this)
{
  t_client	*client;
  socklen_t	size;

  if ((client = (t_client*)malloc(sizeof(*client))) == NULL)
    {
      fprintf(stderr, "malloc: cannot allocate new memory for client\n");
      return (-1);
    }
  memset(client, 0, sizeof(*client));
  size = sizeof(client->sin);
  client->sock = accept(this->sock, (struct sockaddr *)&client->sin, &size);
  if (client->sock < 0)
    {
      perror ("accept");
      return (-1);
    }
  fprintf(stderr, "Server: connect from host %s, port %d.\n",
	  inet_ntoa(client->sin.sin_addr), ntohs(client->sin.sin_port));
  FD_SET(client->sock, &this->active_fd_set);
  network_client_add(this, client);
  return (1);
}

int		network_socket_init(t_network *this, short port)
{
  this->sock = socket(PF_INET, SOCK_STREAM, 0);
  if (this->sock < 0)
    {
      perror("socket");
      return (-1);
    }
  this->sin.sin_family = AF_INET;
  this->sin.sin_port = htons(port);
  this->sin.sin_addr.s_addr = htonl(INADDR_ANY);
  if (bind(this->sock, (struct sockaddr *)&this->sin,
	   sizeof(this->sin)) == -1)
    {
      perror("bind");
      close(this->sock);
      return (-1);
    }
  return (0);
}

int		network_socket_listen(t_network *this)
{
  if (listen(this->sock, 1) == -1)
    {
      perror("listen");
      close(this->sock);
      return (-1);
    }
  return (0);
}

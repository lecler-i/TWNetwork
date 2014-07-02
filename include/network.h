/*
** network.h for network in /home/lecler_i/Work/Epitech/Tek2/SysUnix/PSU_2013_zappy/server/source
**
** Made by Thomas LECLERCQ
** Login   <lecler_i@epitech.net>
**
** Started on  Thu Jun 26 19:31:36 2014 Thomas LECLERCQ
** Last update Wed Jul  2 23:01:18 2014 Thomas LECLERCQ
*/

#ifndef		__NETWORK_H__
#define		__NETWORK_H__

#define _GNU_SOURCE

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>

#include "circular_buffer.h"

#define			NETWORK_READ_SIZE 512

typedef struct		s_client
{
  int			sock;
  struct sockaddr_in	sin;
  t_circular_buffer	recv;
  t_circular_buffer	send;

  void			*data;

  struct s_client	*next;

}			t_client;

typedef struct		s_network
{
  int			sock;
  struct sockaddr_in	sin;
  fd_set		active_fd_set;

  void			*arg;

  void			(*on_accept_connection)(void *, t_client *);
  void			(*on_lost_connection)(void *, t_client *);
  void			(*on_request_recv)(void *, t_client *, char *);

  t_client		*clients;
}			t_network;

/* NETWORK */
int		network_init(t_network *this, short port);
void		network_run(t_network *this);

/* CLIENT */
int		network_client_get_data(t_client *this);
t_client	*network_client_search_by_sock(t_network *this, int fd);
int		network_client_delete(t_network *this, t_client *client);
int		network_client_add(t_network *this, t_client *client);

/* SOCKET */
int		network_handle_new_connection(t_network *this);
int		network_socket_init(t_network *this, short port);
int		network_socket_listen(t_network *this);

/* SEND */
int		network_client_send_data(t_client *this, const char *data);
int		network_client_send(t_client *this, const char *fmt, ...);

#endif

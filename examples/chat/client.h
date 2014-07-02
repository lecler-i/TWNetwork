/*
** client.h for client in /tmp/TWNetwork/examples/chat
**
** Made by Thomas LECLERCQ
** Login   <lecler_i@epitech.net>
**
** Started on  Wed Jul  2 23:06:33 2014 Thomas LECLERCQ
** Last update Wed Jul  2 23:09:26 2014 Thomas LECLERCQ
*/

#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "network.h"

typedef stuct	s_user
{
  char		*nick;
  t_client	*c;
}		t_user;

typedef struct	s_chat
{
  t_user	*users;
  t_nework	server;
}		t_chat;

#endif

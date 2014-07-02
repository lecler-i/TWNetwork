/*
** client.c for client example in /tmp/TWNetwork/examples/chat
**
** Made by Thomas LECLERCQ
** Login   <lecler_i@epitech.net>
**
** Started on  Wed Jul  2 23:06:00 2014 Thomas LECLERCQ
** Last update Wed Jul  2 23:10:59 2014 Thomas LECLERCQ
*/


void		on_user_msg(t_chat *chat, t_client *c, char *msg)
{
  
}

int		main(int ac, const char **av)
{
  t_chat	chat;

  memset(&chat, 0, sizeof(chat));
  newtork_init(&chat.server, 4242);

  
  
}

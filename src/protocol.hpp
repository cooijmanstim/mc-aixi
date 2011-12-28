#ifndef __PROTOCOL_HPP__
#define __PROTOCOL_HPP__

#include "main.hpp"

#define PROTOCOL_VERSION 1
#define ACTION_MESSAGE_SIZE (1 + sizeof(action_t))
#define PERCEPT_MESSAGE_SIZE (1 + 2 * sizeof(percept_t))

int  protocol_connect(const char *host, const char *port);
void protocol_send_action(int sockfd, action_t action);
void protocol_recv_percept(int sockfd, percept_t *observation, percept_t *reward);

#endif // __PROTOCOL_HPP__

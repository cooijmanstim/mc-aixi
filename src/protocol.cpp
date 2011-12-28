#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <assert.h>
#include "protocol.hpp"

int protocol_connect(const char *host, const char *service) {
        int ret, sockfd;
        struct addrinfo hints, *addr;

        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;

        ret = getaddrinfo(host, service, &hints, &addr);
        assert(ret == 0);

        ret = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
        assert(ret != -1);

        sockfd = ret;

        ret = connect(sockfd, addr->ai_addr, addr->ai_addrlen);
        assert(ret == 0);

        freeaddrinfo(addr);
        addr = NULL;

        return sockfd;
}

void protocol_send_action(const int sockfd, const action_t action) {
        char action_message[ACTION_MESSAGE_SIZE];
        memset(action_message, 0, ACTION_MESSAGE_SIZE);
        action_message[0] = PROTOCOL_VERSION;
        int naction = htonl(action);
        memcpy(action_message + 1, &naction, sizeof(action));

        int n_bytes_sent = send(sockfd, &action_message, ACTION_MESSAGE_SIZE, 0);
        assert(n_bytes_sent != -1);
        assert(n_bytes_sent == ACTION_MESSAGE_SIZE);
}

void protocol_recv_percept(const int sockfd, percept_t *observation, percept_t *reward) {
        assert(observation != NULL);
        assert(reward != NULL);

        char percept_message[PERCEPT_MESSAGE_SIZE];
        memset(percept_message, 0, PERCEPT_MESSAGE_SIZE);
        char *p = percept_message;

        int n_bytes_recvd = recv(sockfd, percept_message, PERCEPT_MESSAGE_SIZE, 0);
        assert(n_bytes_recvd != -1);
        assert(n_bytes_recvd != 0);

        assert(p[0] == PROTOCOL_VERSION);
        p++;

        percept_t nobservation = 0, nreward = 0;
        memcpy(&nobservation, p, sizeof(nobservation)); p += sizeof(nobservation);
        memcpy(&nreward,      p, sizeof(nreward));      p += sizeof(nreward);

        *observation = ntohl(nobservation);
        *reward = ntohl(nreward);
}

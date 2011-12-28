#include <cassert>
#include <sys/types.h>
#include <sys/socket.h>
#include "protocol.hpp"
#include "external-environment.hpp"
#include "util.hpp"

ExternalEnvironment::ExternalEnvironment(options_t &options) {
        getRequiredOption(options, "external-environment-host", m_host);
        getRequiredOption(options, "external-environment-port", m_port);
        getRequiredOption(options, "external-environment-max-action",      m_max_action);
        getRequiredOption(options, "external-environment-max-observation", m_max_observation);
        getRequiredOption(options, "external-environment-max-reward",      m_max_reward);

        m_sockfd = protocol_connect(m_host.c_str(), m_port.c_str());
}

ExternalEnvironment::~ExternalEnvironment() {
        close(m_sockfd);
}

void ExternalEnvironment::performAction(const action_t action) {
	assert(isValidAction(action));

        protocol_send_action(m_sockfd, action);
        protocol_recv_percept(m_sockfd, &m_observation, &m_reward);

        assert(isValidObservation(m_observation));
        assert(isValidReward(m_reward));
}

action_t  ExternalEnvironment::maxAction()      const { return m_max_action; }
percept_t ExternalEnvironment::maxObservation() const { return m_max_observation; }
percept_t ExternalEnvironment::maxReward()      const { return m_max_reward; }

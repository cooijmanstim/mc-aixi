#ifndef __EXTERNAL_ENVIRONMENT_HPP__
#define __EXTERNAL_ENVIRONMENT_HPP__
#include "environment.hpp"

class ExternalEnvironment : public Environment {
public:
    ExternalEnvironment(options_t &options);
    ~ExternalEnvironment();

    void performAction(const action_t action);

    action_t maxAction() const;
    percept_t maxObservation() const;
    percept_t maxReward() const;

private:
    int m_max_action, m_max_observation, m_max_reward;
    int m_sockfd;
    std::string m_host, m_port;
};

#endif // __EXTERNAL_ENVIRONMENT_HPP__

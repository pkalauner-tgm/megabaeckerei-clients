//
// Created by Paul on 17.11.2015.
//

#ifndef SIMULATION_SOCKETHANDLER_H
#define SIMULATION_SOCKETHANDLER_H


#include "Oven.h"
#include <string>
#include <winsock2.h>
#include <thread>
#include <atomic>

class Oven;
class SocketHandler {
private:
    std::string hostname;
    int port;
    volatile bool active;
    long rc;
    SOCKET s;
    Oven *oven;

    int startWinsock(void);
    void initSocket(void);
    void handleRequestsLoop();
    void handleRequest(char* buf);

public:
    std::thread t;

    SocketHandler(Oven * wt, std::string hostname, int port);
    ~SocketHandler();

    void sendMessage(std::string message);
};


#endif //SIMULATION_SOCKETHANDLER_H
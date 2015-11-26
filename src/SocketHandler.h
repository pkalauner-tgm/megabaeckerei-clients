//
// Created by Paul on 17.11.2015.
//

#ifndef SIMULATION_SOCKETHANDLER_H
#define SIMULATION_SOCKETHANDLER_H


#include "WaterTank.h"
#include <string>
#include <winsock2.h>
#include <thread>
#include <atomic>

class WaterTank;
class SocketHandler {
private:
    std::string hostname;
    int port;
    volatile bool active;
    long rc;
    SOCKET s;
    WaterTank* waterTank;

    int startWinsock(void);
    void initSocket(void);
    void handleRequestsLoop();
    void handleRequest(char* buf);

public:
    std::thread t;

    SocketHandler(WaterTank* wt, std::string hostname, int port);
    ~SocketHandler();

    void sendMessage(std::string message);
};


#endif //SIMULATION_SOCKETHANDLER_H
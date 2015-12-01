//
// Created by Paul on 17.11.2015.
//

#include "SocketHandler.h"
#include <iostream>

SocketHandler::SocketHandler(WaterTank* wt, std::string hostname, int port) {
    this->active = true;
    this->hostname = hostname;
    this->port = port;
    this->waterTank = wt;
    this->initSocket();
}

SocketHandler::~SocketHandler() {
    active = false;
    this->sendMessage("disconnect");
    closesocket(s);
    WSACleanup();
}

void SocketHandler::initSocket(void) {
    SOCKADDR_IN addr;
    //long rc;

    // Winsock starten
    startWinsock();

    // Socket erstellen
    this->s = socket(AF_INET, SOCK_STREAM, 0);

    // Verbinden
    memset(&addr, 0, sizeof(SOCKADDR_IN));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(hostname.c_str());
    rc = connect(s, (SOCKADDR *) &addr, sizeof(SOCKADDR));
    t = std::thread(&SocketHandler::handleRequestsLoop, this);
}


void SocketHandler::handleRequestsLoop() {
    char buf[256];
    while (active && rc != SOCKET_ERROR) {
        rc = recv(s, buf, 256, 0);
        buf[rc] = '\0';
        this->handleRequest(buf);
    }
}

void SocketHandler::handleRequest(char *buf) {
    std::string msg = std::string(buf);
    std::cout << msg << std::endl;
    if (msg == "get_level_water") {
        sendMessage("level_water " + std::to_string(waterTank->getFuellstand()));
    } else if (msg == "toggle_water_to_mischer_ventil") {
        waterTank->toggle_mischer_ventil();
    } else if (msg == "toggle_lager_to_water_ventil") {
        waterTank->toggle_lager_ventil();
    } else {
        sendMessage("Invalid command");
    }
}

void SocketHandler::sendMessage(std::string message) {
    send(s, message.c_str(), (int) strlen(message.c_str()), 0);
}

int SocketHandler::startWinsock(void) {
    WSADATA wsa;
    return WSAStartup(MAKEWORD(2, 0), &wsa);
}
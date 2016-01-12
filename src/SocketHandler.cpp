//
// Created by Paul on 17.11.2015.
//

#include "SocketHandler.h"
#include <iostream>
#include <boost/algorithm/string.hpp>

SocketHandler::SocketHandler(MixTank * wt, std::string hostname, int port) {
    this->active = true;
    this->hostname = hostname;
    this->port = port;
    this->mixer = wt;
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
    this->sendMessage("identify MIXER");
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
    boost::replace_all(msg, "\r\n", "\n");
    //std::cout << msg << std::endl;
    if (msg == "get_level\n") {
        sendMessage("level_mixer " + std::to_string(mixer->getFuellstand()));
    } else if (msg == "toggle_mixer_to_oven_ventil\n") {
        mixer->toggle_oven_ventil();
    } else if (msg == "add_water10\n" || msg == "add_mix10\n") {
        int amount = 0;
        if (mixer->getFuellstand() <= (4000 - 10))
            amount = 10;
        else
            amount = 4000 - mixer->getFuellstand();

        mixer->setFuellstand(mixer->getFuellstand()+amount);
        sendMessage("level_mixer " + std::to_string(mixer->getFuellstand()));
    } else {
        sendMessage("Invalid command");
    }
}

void SocketHandler::sendMessage(std::string message) {
    std::string newmsg = message + "\n";
    send(s, newmsg.c_str(), (int) strlen(newmsg.c_str()), 0);
}

int SocketHandler::startWinsock(void) {
    WSADATA wsa;
    return WSAStartup(MAKEWORD(2, 0), &wsa);
}
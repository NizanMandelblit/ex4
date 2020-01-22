//
// Created by nizan on 13/01/2020.
//
#include <thread>
#include <unistd.h>
#include "MySerialServer.h"
#include "Server.h"


using namespace std;

int runServer(int port, ClientHandler *client) {

    int client_socket;
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);


    if (socketfd == -1) {
        //error
        cerr << "could not create a socket" << endl;
        return -1;
    }
    //bind socket to IP address
    //we first create the sockaddr obj.
    sockaddr_in address;//in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");//give me any IP allocated for my machine.
    address.sin_port = htons(port);
    //we need to convert our number
    //to a number that the network understands

    //the actual bind command
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        cerr << "could not bind socket to an IP" << endl;
        return -1;
    }

    if (listen(socketfd, 1) == -1) {
        cerr << "Error during listening command" << endl;
    }

    int result = 0;
    while (!server_side::isRun) {
        fd_set rfds;
        struct timeval tv;
        tv.tv_sec = 120;//timout in seconds
        setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (const char *) &tv, sizeof tv);

        //select-add it
        result = 1;// select(socketfd + 1, &rfds, (fd_set *) 0, (fd_set *) 0, &tv);
        if (result > 0) {
            // accepting a client
            int addrlen = sizeof(address);
            client_socket = accept(socketfd, (struct sockaddr *) &address, (socklen_t *) &addrlen);

        } else {
            server_side::isRun = true;
            continue;
        }
        client->handleClient(client_socket);
        close(socketfd);
    }

    if (client_socket == -1) {
        cerr << "Error accepting" << endl;
        return -1;
    }
    close(client_socket);

}


int MySerialServer::open(int port, ClientHandler *client) {
    thread tc(runServer, port, client);
    tc.join();

}


void MySerialServer::stop() {
    return;
}


MySerialServer::MySerialServer() {}

MySerialServer::~MySerialServer() {

}

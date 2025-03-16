// client.h
#ifndef CLIENT_H
#define CLIENT_H
#include <string>

bool connectToServer();
void sendData(const std::string& data);
void shutdownNetwork();

#endif // CLIENT_H
// messaging.h
#ifndef MESSAGING_H
#define MESSAGING_H
#include <string>

bool initializeMessaging();
void sendMessage(const std::string& message);
void shutdownMessaging();

#endif // MESSAGING_H
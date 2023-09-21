#ifndef SERVER_H
#define SERVER_H
#include "Connection.h"
#include "BulkProcessor.h"

class Server
{
public:
    Server(ushort port);
    void accept(tcp::acceptor &acceptor);
    void run();
private:
    ushort _port;
};

#endif // SERVER_H

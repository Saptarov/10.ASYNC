#ifndef CONNECTION_H
#define CONNECTION_H
#include "common.h"
#include "Config.h"
#include "BulkProcessor.h"

namespace asio = boost::asio;
using tcp = asio::ip::tcp;

class Connection : public std::enable_shared_from_this<Connection> {
public:
    explicit Connection(tcp::socket socket)
        : _socket(std::move(socket))
        , _processor(std::make_shared<BulkProcessor>(10))
    {}

    Connection(const Connection &) = delete;
    Connection(Connection &&) = delete;

    virtual ~Connection() = default;

    Connection &operator=(const Connection &) = delete;
    Connection &operator=(Connection &&) = delete;

    void startReading();
private:
    void handleRead(const boost::system::error_code error, const std::size_t length);
    void handleData(const std::size_t length);


    tcp::socket _socket;
    boost::asio::streambuf _buffer;
    SharedBulkProcessor _processor;

};

#endif // CLIENT_H

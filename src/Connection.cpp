#include "Connection.h"


void Connection::startReading() {
    auto self = shared_from_this();
    std::cout << std::this_thread::get_id() << " incoming connect" << std::endl;
    asio::async_read_until(_socket, _buffer, "\n",
                           [this, self](const boost::system::error_code error,
                           const std::size_t length)
    {
        handleRead(error, length);
    });
}

void Connection::handleRead(const boost::system::error_code error, const std::size_t length) {
    if (error) {
        std::cout << std::this_thread::get_id() << " Has error: \"" << error << "\"." << std::endl;
        return;
    }
    if (length != 0) {
        handleData(length);
        _buffer.consume(length);
    }
    startReading();
}

void replaceString(std::string& str, const std::string& from, const std::string& to) {
    if (from.empty()) {
        return;
    }
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

void Connection::handleData(const std::size_t length) {
    const std::string_view logRecord {asio::buffer_cast<const char *>(_buffer.data()), length};
    std::cout << std::this_thread::get_id() << " send " << logRecord << std::endl;
    _processor->processCommands(logRecord.data());
}

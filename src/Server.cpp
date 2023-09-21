#include "Server.h"

Server::Server(ushort port)
    : _port(port)
{}

void Server::accept(tcp::acceptor &acceptor) {
  acceptor.async_accept(
      [&](const boost::system::error_code error, tcp::socket socket) {
        if (!error) {
            pool->submit([&](){
                const std::shared_ptr<Connection> connection (new Connection (std::move(socket)));
                connection->startReading();
            });
        }

        accept(acceptor);
      });
}

void Server::run() {

  asio::io_context ioContext;

  std::cout << std::this_thread::get_id() << "Server listing port " << _port << std::endl;

  tcp::acceptor acceptor{ioContext, tcp::endpoint(tcp::v4(), _port)};
  accept(acceptor);

  asio::signal_set signals{ioContext, SIGINT, SIGTERM};
  signals.async_wait([&](auto, auto) { ioContext.stop(); });

  std::vector<std::thread> threads;
  const auto nThreads = std::thread::hardware_concurrency();
  threads.reserve(nThreads);
  for (unsigned int i = 0; i < nThreads; ++i) {
    threads.emplace_back([&ioContext]() { ioContext.run(); });
  }
  for (auto &th : threads) {
    th.join();
  }

  std::cout << std::this_thread::get_id() << " Server stopped." << std::endl;
}

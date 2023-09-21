#include "common.h"
#include "Server.h"

namespace po = boost::program_options;

int main(int argc, char* argv[]) {

    po::options_description options("bulk_server options");
    options.add_options()
            ("port,p", po::value<ushort>(), "Port number")
            ("bulk_size,b", po::value<size_t>(), "Bulk size")
            ("help,h", po::value<size_t>(), "Help info")
            ;

    po::variables_map vm;
    po::parsed_options parsed = po::command_line_parser(argc, argv).options(options).allow_unregistered().run();
    po::store(parsed, vm);
    po::notify(vm);

    if (vm.find("help") != vm.end()) {
        std::cout << options << std::endl;
        return 0;
    }

    if (vm.find("port") != vm.end()) {
        Config::port = vm["port"].as<ushort>();
    } else {
        std::cout << "WARNING: option port should be specified, will be started default port - " << Config::port << std::endl;
    }

    if (vm.find("bulk_size") != vm.end()) {
        Config::builk_size = vm["bulk_size"].as<ushort>();
    } else {
        std::cout << "WARNING: option bulk_size should be specified, will be started default value - " << Config::builk_size << std::endl;
    }

    pool = std::make_shared<Worker>(10);

    Server srv(Config::port);
    srv.run();

    while (!pool->isDone()) {
        std::this_thread::yield();
    }
    return 0;
}

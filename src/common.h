#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <iomanip>
#include <optional>
#include <limits>
#include <vector>
#include <list>
#include <stack>
#include <sstream>
#include <fstream>
#include <chrono>
#include <thread>
#include <algorithm>
#include <tuple>
#include <exception>
#include <cassert>
#include <map>
#include <type_traits>
#include <limits>
#include <memory>
#include <atomic>
#include <shared_mutex>
#include <mutex>
#include <thread>
//BOOST
#include <boost/algorithm/string/trim_all.hpp>
#include <boost/asio/co_spawn.hpp>
#include <boost/asio/detached.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/directory.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/functional/hash.hpp>
#include <boost/uuid/detail/sha1.hpp>
#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/bind/bind.hpp>
#include <boost/asio.hpp>
//
#include "Config.h"
#include "BulkWriter.h"
#include "Worker.h"

#endif // COMMON_H

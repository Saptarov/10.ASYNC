#ifndef __BULK_WRITER_H
#define __BULK_WRITER_H
#include <fstream>
#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <mutex>
#include <shared_mutex>

class BulkWriter
{
public:
    void output(std::vector<std::string>& blocks, uint numQueue);
private:
    std::shared_mutex _rwBlockMutex;
};

#endif // __BULK_WRITER_H

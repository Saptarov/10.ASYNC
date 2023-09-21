#ifndef BUILKPROCESSOR_H
#define BUILKPROCESSOR_H
#include "common.h"

class BulkProcessor {
public:
    BulkProcessor(int blockSize);
    ~BulkProcessor();
    void processCommands(const std::string& command);
    void processCommands(std::vector<std::string> commands);

private:
    void processCommand(const std::string& command);
    void startDynamicBlock();
    void endDynamicBlock();
    void runWriter();

private:
    struct DynamicBlock {
        DynamicBlock(bool lastClosedBracket);
        bool canWriteCommand();
    private:
        bool _lastClosedBracket;
    };

    const size_t _blockSize;
    std::list<DynamicBlock> _dynamicBlocks;
    std::vector<std::string> _blocks;
    uint _blockLen;
    std::mutex _writeQueue;
};

using SharedBulkProcessor = std::shared_ptr<BulkProcessor>;

#endif // BUILKPROCESSOR_H

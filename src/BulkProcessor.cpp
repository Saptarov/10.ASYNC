#include "BulkProcessor.h"

BulkProcessor::BulkProcessor(int blockSize)
    : _blockSize(blockSize)
{}

BulkProcessor::~BulkProcessor() {

}

void BulkProcessor::processCommands(const std::string& command) {
    if (command == "{") {
        startDynamicBlock();
    } else if (command == "}") {
        endDynamicBlock();
    } else {
        processCommand(command);
    }
}

void BulkProcessor::processCommands(std::vector<std::string> commands) {
    for (auto& command : commands) {
        std::cout << command << std::endl;
        if (command == "{") {
            startDynamicBlock();
        } else if (command == "}") {
            endDynamicBlock();
        } else {
            processCommand(command);
        }
    }
}

void BulkProcessor::processCommand(const std::string& command) {
    _blocks.push_back(command);
    if (_dynamicBlocks.empty() && _blocks.size() == _blockSize) {
        runWriter();
    }
}

void BulkProcessor::startDynamicBlock() {
    if (_dynamicBlocks.empty()) {
        runWriter();
        _dynamicBlocks.push_back(DynamicBlock(true));
    } else {
        _dynamicBlocks.push_back(DynamicBlock(false));
    }
}

void BulkProcessor::endDynamicBlock() {
    auto block = _dynamicBlocks.back();
    if (block.canWriteCommand()) {
        runWriter();
    }
    _dynamicBlocks.pop_back();
}

void BulkProcessor::runWriter() {
    std::lock_guard<std::mutex> l(_writeQueue);
    pool->submit([&](){//тут само собой бьет по производительности, коль будет замечанием, подправлю
        _blockLen++;
        BulkWriter writer;
        writer.output(_blocks, _blockLen);
    });
}

BulkProcessor::DynamicBlock::DynamicBlock(bool lastClosedBracket)
    : _lastClosedBracket(lastClosedBracket)
{}

bool BulkProcessor::DynamicBlock::canWriteCommand() {
    return _lastClosedBracket;
}


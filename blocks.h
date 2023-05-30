#ifndef BLOCKS_H
#define BLOCKS_H

#include "dbworker.h"

#include <QCryptographicHash>
#include <QList>

#include <string>

struct Block{
    std::string hash;
    size_t size;
};

class Blocks
{
public:
    Blocks();
    size_t get_block_number(const std::string&);
    size_t get_block_size(const std::string&);
    int get_block_data(size_t, char*, size_t);
    bool add_block(const std::string, std::string);
private:
    QList<Block> blocks;
    DbWorker *workDb;
};

#endif // BLOCKS_H

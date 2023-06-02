#ifndef BLOCKS_H
#define BLOCKS_H

#include "dbworker.h"

#include <QMap>
#include <QMutex>

#include <string>

struct Block{
    size_t num;
    size_t size;
};

class Blocks
{
public:
    Blocks();
    size_t get_block_number(const std::string&);
    size_t get_block_size(const std::string&);
    int get_block_data(size_t, char*, size_t);
private:
    bool get_all_block();
    QMap<std::string, Block> blocks;
    DbWorker *workDb;
    QSqlQuery t_query;
    QMutex mutex;
};

#endif // BLOCKS_H

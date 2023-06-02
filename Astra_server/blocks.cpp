#include "blocks.h"

Blocks::Blocks()
{
    workDb = new DbWorker;
    get_all_block();
}

bool Blocks::get_all_block()
{
    QString req = "SELECT * FROM info_block;";
    bool res = workDb->proc_req(req, t_query);
    while (t_query.next())
    {
        Block t_block;
        t_block.num = t_query.value(0).toInt();
        std::string hash = t_query.value(1).toString().toStdString();
        t_block.size = t_query.value(2).toInt();
        blocks.insert(hash, t_block);
        // qDebug() << "Block num: " << t_block.num << ", size: " << t_block.size << ", hash: " << QString::fromStdString(hash);
    }
    t_query.clear();
    return res;
}

// Узнать номер блока в блочном устройстве по хэшу
size_t Blocks::get_block_number(const std::string& hash)
{
    mutex.lock();
    qDebug() << "Find number block...";
    size_t num = 0;
    QMap<std::string, Block>::Iterator it = blocks.find(hash);
    if(it != blocks.end()){
        num = blocks.find(hash)->num;
    }
    mutex.unlock();
    return num;
}

// Размер блока в байтах
size_t Blocks::get_block_size(const std::string& hash)
{
    mutex.lock();
    qDebug() << "Find size block...";

    size_t t_size = 0;
    QMap<std::string, Block>::Iterator it = blocks.find(hash);
    if(it != blocks.end()){
        t_size = blocks.find(hash)->size;
    }
    mutex.unlock();
    return t_size;
}

// Прочитать данные из блочного устройства
int Blocks::get_block_data(size_t block_num, char* buffer, size_t /* buffer_size */)
{
    mutex.lock();
    qDebug() << "Reading data block by number from DB, where num: " << QString::number(block_num);
    QString req = "SELECT data FROM blocks WHERE num=" + QString::number(block_num) + ";";
    bool res = workDb->proc_req(req, t_query);
    qDebug() << "Test";
    std::string t_buffer="";
    while (t_query.next())
    {
        t_buffer = t_query.value(0).toString().toStdString();
    }
    strcpy(buffer, t_buffer.c_str());
    t_query.clear();
    mutex.unlock();
    return res;
}

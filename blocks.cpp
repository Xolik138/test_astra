#include "blocks.h"

#include <QDebug>

Blocks::Blocks()
{
    qDebug() << "Blocks";
}

// Узнать номер блока в блочном устройстве по хэшу
size_t Blocks::get_block_number(const std::string& hash)
{
    return 0;
}

// Размер блока в байтах
size_t Blocks::get_block_size(const std::string& hash)
{
    return 0;
}


// Прочитать данные из блочного устройства
int Blocks::get_block_data(size_t block_num, char* buffer, size_t buffer_size)
{
    return 0;
}

// Добавить данные в блочное устройство
bool add_block(const std::string hash, std::string data)
{
    return true;
}

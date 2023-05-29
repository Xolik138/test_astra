#ifndef CRYPTO_H
#define CRYPTO_H

#include <QObject>
#include <QCryptographicHash>

class Crypto
{
    Q_OBJECT
public:
    Crypto();
    ~Crypto();
private:
    QByteArray *hashArray[];
};

#endif // CRYPTO_H

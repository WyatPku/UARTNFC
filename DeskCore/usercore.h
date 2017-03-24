#ifndef USERCORE_H
#define USERCORE_H

#include <QObject>

class UserCore : public QObject
{
    Q_OBJECT
public:
    explicit UserCore(QObject *parent = 0);

signals:

public slots:
};

#endif // USERCORE_H
#ifndef DESKCORE_H
#define DESKCORE_H

#include <QString>
#include <QObject>

class DeskCore : public QObject
{
    Q_OBJECT
private:

public:
    explicit DeskCore(QObject *parent = 0);
private slots:

signals:

};

#endif // DESKCORE_H

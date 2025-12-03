#ifndef CORESERVICE_H
#define CORESERVICE_H

#include <QObject>

class CoreService : public QObject
{
    Q_OBJECT
public:
    explicit CoreService(QObject *parent = nullptr);

    Q_INVOKABLE void ping();

signals:
    void pong(const QString &message);
};

#endif // CORESERVICE_H

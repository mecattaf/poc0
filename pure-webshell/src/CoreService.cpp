#include "CoreService.h"
#include <QDebug>

CoreService::CoreService(QObject *parent)
    : QObject(parent)
{
}

void CoreService::ping()
{
    qDebug() << "CoreService: Ping received!";
    emit pong("pong from C++");
}

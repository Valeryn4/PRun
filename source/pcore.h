#ifndef PCORE_H
#define PCORE_H

#include <QObject>

class PCore : public QObject
{
    Q_OBJECT
public:
    explicit PCore(QObject *parent = 0);

signals:

public slots:
};

#endif // PCORE_H

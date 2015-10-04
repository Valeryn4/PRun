#ifndef PCORE_H
#define PCORE_H

#include <QObject>
#include <QMap>
#include <QString>

class PCore : public QObject
{
    Q_OBJECT
private:

public:
    explicit PCore(QObject *parent = 0);

signals:

public slots:
};

#endif // PCORE_H

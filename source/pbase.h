#ifndef PBASE_H
#define PBASE_H

#include <QObject>

class PBase : public QObject
{
    Q_OBJECT
public:
    explicit PBase(QObject *parent = 0);

signals:

public slots:
};

#endif // PBASE_H

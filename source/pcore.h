#ifndef PCORE_H
#define PCORE_H

#include <QObject>
#include <QMap>
#include <QString>
#include <QProcess>
#include <QDebug>

enum PROCESS_STATUS {
    DENIDED,
    RUN,
    STOP
};

class PCore : public QObject
{
    Q_OBJECT
private:
    int count_process;
    QMap<int, QProcess*> process_pull;
    int count_process_pull;
    QMap<int, PROCESS_STATUS> process_status;
    int count_process_status;
    QMap<int, QString> process_path;
    int count_process_path;
    int max_path;



public:
    explicit PCore(int max_path_ = 10, QObject *parent = 0);
    ~PCore();
    bool addProcessPath(QString path);
    bool addProcessPath(int ID, QString path);
    bool runProcess(int ID);
    bool kill(int ID);
    bool killAll();

    bool setStatus(int ID, PROCESS_STATUS status);
    bool setDenied(int ID);
    bool setAccess(int ID);

    bool getAccess(int ID);

signals:
    void signal_killAll();
    void signal_allProcessDead();

public slots:
    void slot_runProcess(int ID);
    void slot_killAll();
    void delete_proc_pull();
};

#endif // PCORE_H

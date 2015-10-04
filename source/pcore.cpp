#include "pcore.h"

PCore::PCore(int max_path_, QObject *parent) : QObject(parent)
{
    count_process = 0;
    count_process_path = 1;
    count_process_pull = 0;
    count_process_status = 0;
    max_path = max_path_;

    for (int i = 0; i < max_path; i++) {
        process_status[i] = STOP;
        process_pull[i] = new QProcess;
        process_path[i] = "NONE";
        connect(process_pull[i], SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(delete_proc_pull()));
        connect(process_pull[i], SIGNAL(error(QProcess::ProcessError)), this, SLOT(delete_proc_pull()));
    }
}

PCore::~PCore() {
    killAll();
    for (int i = 0; i < max_path; i++) {
        delete process_pull[i];
        qDebug() << "delete process " << i;
    }
}

bool PCore::runProcess(int ID) {
    if (process_status[ID] == DENIDED)
        return false;
    if (process_pull[ID]->state() == QProcess::NotRunning && process_status[ID] == STOP) {
        process_pull[ID]->start(process_path[ID]);
        qDebug() << "PROCESS ID: " << ID
                 << "\nPROCESS PATH: " << process_path[ID];
        process_pull[ID]->waitForStarted();
        if(process_pull[ID]->state() == QProcess::NotRunning) {
            qDebug() << "Process run FAIL ID: " << ID << " Path:" << process_path[ID];
            return false;
        }
        process_status[ID] = RUN;
        count_process++;
        return true;
    }
    return false;
}

bool PCore::killAll() {
    for (int i = 0; i < max_path; i++) {
        if (!process_pull[i]->state() == QProcess::NotRunning)
            process_pull[i]->kill();
        process_status[i] = STOP;
    }
    count_process = 0;
    emit signal_killAll();
    return true;
}

bool PCore::addProcessPath(QString path) {
    if (count_process_path <= max_path) {
        process_path[count_process_path] = path;
        count_process_path++;
        return true;
    }
    return false;
}

bool PCore::addProcessPath(int ID, QString path) {
    if (ID > max_path)
        return false;
    if (process_path[ID] == "NONE")
        count_process_path++;
    process_path[ID] = path;
    return true;
}

bool PCore::setStatus(int ID, PROCESS_STATUS status) {
    if (process_status[ID] == RUN) {
        qDebug() << "fail change status. process running!";
        return false;
    }
    if (status == RUN) {
        qDebug() << " fail change status. status RUN no correct!";
        return false;
    }
    process_status[ID] = status;
    return true;
}

bool PCore::setDenied(int ID) {
    if (process_status[ID] != RUN) {
        process_status[ID] = DENIDED;
        return true;
    }
    return false;
}

bool PCore::setAccess(int ID) {
    if (process_status[ID] != RUN) {
        process_status[ID] = STOP;
        return true;
    }
    return false;
}

bool PCore::kill(int ID) {
    if (process_pull[ID]->state() == QProcess::NotRunning){
        if (process_status[ID] == RUN) {
            process_status[ID] = STOP;
            count_process--;
            return false;
        }
        return false;
    }
    if (process_status[ID] != RUN && !process_pull[ID]->state() == QProcess::NotRunning) {
        count_process--;
        process_pull[ID]->kill();
        process_status[ID] = STOP;
        return true;
    }
    if (!process_pull[ID]->state() == QProcess::NotRunning && process_status[ID] == STOP) {
        process_pull[ID]->kill();
        return false;
    }
    return false;
}


// ================

void PCore::slot_killAll() {
    void killAll();
}

void PCore::slot_runProcess(int ID) {
    if (!this->runProcess(ID))
        qDebug() << "slot runProcess() FAIL!";
}

void PCore::delete_proc_pull() {
    int chek_count = 0;
    for (int i = 0; i < max_path; i++) {
        if (process_pull[i]->state() == QProcess::NotRunning) {
            qDebug() << "Process no run ID: " << i << ". Proc path: " << process_path[i];
            if (process_status[i] == RUN) {
                process_status[i] = STOP;
                count_process--;
                qDebug() << " change status ID: " << i;
            }
        }
        if (process_status[i] == RUN )
            chek_count++;
    }
    if (chek_count != count_process)
        qDebug() << "chek_count != count_process\n chek_count = " << chek_count << ". count_process = " << count_process;
    if (count_process == 0)
        qDebug() << "all process dead!";
}

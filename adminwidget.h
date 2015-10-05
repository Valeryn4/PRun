#ifndef ADMINWIDGET_H
#define ADMINWIDGET_H

#include <QMainWindow>

namespace Ui {
class AdminWidget;
}

class AdminWidget : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminWidget(QWidget *parent = 0);
    ~AdminWidget();

private:
    Ui::AdminWidget *ui;
};

#endif // ADMINWIDGET_H

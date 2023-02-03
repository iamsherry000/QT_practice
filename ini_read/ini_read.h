#ifndef INI_READ_H
#define INI_READ_H

#include <QMainWindow>

namespace Ui {
class ini_read;
}

class ini_read : public QMainWindow
{
    Q_OBJECT

public:
    explicit ini_read(QWidget *parent = nullptr);
    ~ini_read();

private slots:
    void on_pushButton_clicked();
    void openfile();

private:
    Ui::ini_read *ui;
};

#endif // INI_READ_H

#ifndef JSON_TEST_H
#define JSON_TEST_H

#include <QMainWindow>
#include <QJsonObject>
#include <QJsonArray>
#include <QTableWidgetItem>

namespace Ui {
class json_test;
}

struct employees{
    QString depart;
    QString name;
    QString gender;
    QString ext;
};

class json_test : public QMainWindow
{
    Q_OBJECT

public:
    explicit json_test(QWidget *parent = nullptr);
    ~json_test();

private slots:
    void on_pushButton_clicked();
    int openjson();
    void set_table(int,int, QString);
    void on_pushButton_2_clicked();

    //void mousePressEvent(QMouseEvent *event);
    void delete_row();
    void inset_row();
    //void mouseToolBar();

private:
    Ui::json_test *ui;
    int openfile = 0;
    QString comp_name,locate,estab,email;

};

#endif // JSON_TEST_H

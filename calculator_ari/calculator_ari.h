#ifndef CALCULATOR_ARI_H
#define CALCULATOR_ARI_H

#include <QMainWindow>
#include <QDebug>
#include <string>
#include <QStringList>
#include <QStack>
#include <QList>
#include <QString>

namespace Ui {
class calculator_ari;
}

class calculator_ari : public QMainWindow
{
    Q_OBJECT

public:
    explicit calculator_ari(QWidget *parent = nullptr);
    ~calculator_ari();

private slots:
    void ClearPressed();
    void NumPressed();
    void MathPressed();
    void on_btn_equal_clicked();

private:
    Ui::calculator_ari *ui;
    QString m_buttxt,m_l1txt;
    QStringList m_list;
    QByteArray byteArray;
    int m_count;

    QStringList get_negnum(QStringList list);
    int get_operators(char compare_c);
    int get_count(QStringList list);
    QStringList calculate_func(QStringList);
    QStringList multiple_check(QStringList list);
    QStringList divide_check(QStringList list);
};

#endif // CALCULATOR_ARI_H

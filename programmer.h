#ifndef PROGRAMMER_H
#define PROGRAMMER_H

#include <QWidget>
#include <QWidget>
#include<QStack>
#include <QKeyEvent>
#include<QMap>
#include<QPushButton>
#include<QDebug>
#include<QLabel>
#include<QLineEdit>
#include <math.h>


namespace Ui {
class Programmer;
}

class Programmer : public QWidget
{
    Q_OBJECT

public:
    explicit Programmer(QWidget *parent = nullptr);
    ~Programmer();
    bool  eventFilter(QObject *obj, QEvent *event);

    int curRow ;
    int curJZ;
    int lastJZ;
    QLabel *displayJZ;

    QString operand;
    QString op;
    QString lastKey;
    QVector<QString> operands;
    QVector<QPushButton *> digitBTNs;         //数组遍历（键盘）??????,digitBTNs=btnNums
    QVector<QLabel *>  labels;

    QString calculation( );  //判断是否需要这样计算，当有两个操作数和一个操作弧就需要(比如已经有1+2，就计算）

private slots:


    void  updateDisplayJZ(int row);

    void btnNumClicked();

    void transJZ();

    void btnBinaryOperatorClicked();

    void btnUnaryOperatorClicked();


    void on_btnPeriod_clicked();

    void on_btnDel_clicked();

    void on_btnEqual_clicked();

    void on_btnClearAll_clicked();

    void on_btnZhengFu_clicked();


    virtual void keyPressEvent(QKeyEvent *event);   //键盘事件


private:
    Ui::Programmer *ui;
};

#endif // PROGRAMMER_H

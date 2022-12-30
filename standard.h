#ifndef STANDARD_H
#define STANDARD_H

#include <QWidget>
#include<QStack>
#include <QKeyEvent>
#include<QMap>
#include<QPushButton>
#include<QDebug>
#include <math.h>


namespace Ui {
class Standard;
}

class Standard : public QWidget
{
    Q_OBJECT

public:
    explicit Standard(QWidget *parent = nullptr);
    ~Standard();

    QString operand;
    QString op;
    QString lastKey;
    QStack<QString> operands;
    QMap<int,QPushButton *> digitBTNs;         //数组遍历（键盘）??????,digitBTNs=btnNums

    QString calculation( );  //判断是否需要这样计算，当有两个操作数和一个操作弧就需要(比如已经有1+2，就计算）

private slots:
    void btnNumClicked();

    void btnBinaryOperatorClicked();

    void btnUnaryOperatorClicked();


    void on_btnPeriod_clicked();

    void on_btnDel_clicked();

    void on_btnClear_clicked();

    void on_btnEqual_clicked();

    void on_btnClearAll_clicked();

    void on_btnZhengFu_clicked();

    virtual void keyPressEvent(QKeyEvent *event);   //键盘事件
private:
    Ui::Standard *ui;
};

#endif // STANDARD_H

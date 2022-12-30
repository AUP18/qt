#ifndef SCIENCE_H
#define SCIENCE_H

#include <QWidget>
#include <QWidget>
#include<QStack>
#include <QKeyEvent>
#include<QMap>
#include<QPushButton>
#include<QDebug>
#include <math.h>

namespace Ui {
class Science;
}

class Science : public QWidget
{
    Q_OBJECT

public:
    explicit Science(QWidget *parent = nullptr);
    ~Science();
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
    Ui::Science *ui;
};

#endif // SCIENCE_H

#ifndef VOLUME_H
#define VOLUME_H

#include <QWidget>
#include <QLabel>
#include<QMap>
#include<QPushButton>
#include<QDebug>
#include <math.h>

namespace Ui {
class Volume;
}

enum  VolumeType
{
    L=1,
    ML=2
};

class Volume : public QWidget
{
    Q_OBJECT

public:
    explicit Volume(QWidget *parent = nullptr);
    ~Volume();
    bool eventFilter(QObject *obj, QEvent *event);
    void UpdateCur(QLabel*  lbl);
    QMap<int,QPushButton *> digitBTNs;         //数组遍历（键盘）??????,digitBTNs=btnNums
   void tranVolume();
private slots:
   void btnNumClicked();
   void on_btnPeriod_clicked();
   void on_btnDel_clicked();



   void on_btnClearAll_clicked();
private:
    Ui::Volume *ui;

    VolumeType  curType;
    QLabel * display;
    QString operand;
};

#endif // VOLUME_H

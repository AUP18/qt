#include "volume.h"
#include "ui_volume.h"

Volume::Volume(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Volume)
{
    ui->setupUi(this);

    ui->labelML->installEventFilter(this);

    ui->labelL->installEventFilter(this);


    digitBTNs = {{Qt::Key_0,ui->btnNum0},
               {Qt::Key_1,ui->btnNum1},
               {Qt::Key_2,ui->btnNum2},
               {Qt::Key_3,ui->btnNum3},
               {Qt::Key_4,ui->btnNum4},
               {Qt::Key_5,ui->btnNum5},
               {Qt::Key_6,ui->btnNum6},
               {Qt::Key_7,ui->btnNum7},
               {Qt::Key_8,ui->btnNum8},
               {Qt::Key_9,ui->btnNum9},
              };         //初始化; Qt::key_i是Qt内名称为0的按钮????

    foreach(auto btn, digitBTNs)           //循环，替代下面????????/
         connect(btn,SIGNAL(clicked()),this,SLOT(btnNumClicked()));

     UpdateCur(ui->labelML);

}


void Volume::btnNumClicked()
{

    QString digit = qobject_cast<QPushButton*>(sender())->text();

    if(operand == "0" )//避免出现023
    {
        operand =digit;
    }
   else
    {
         operand +=digit;
    }


   display->setText(operand);

   tranVolume( );
}

//小数点添加
void Volume::on_btnPeriod_clicked()
{

    if(!operand.contains("."))
        operand +=qobject_cast<QPushButton*>(sender())->text();//再加新按的数字
    display->setText(operand);//把按键的数字显示出来
}

static double K = 1000;

void Volume::tranVolume( )
{

    if( curType == L)
    {
        double l = operand.toDouble();
        double ml = l *K;
        ui->labelML->setText(QString("%1").arg(ml));
    }
    else if( curType == ML)
    {

        double ml = operand.toDouble();
        double l = ml / K;
        ui->labelL->setText(QString("%1").arg(l));
    }


}

void Volume::UpdateCur(QLabel*  lbl)
{

    display = lbl;

    if(  display ==  ui->labelL )
     curType = L;

    else if(  display ==  ui->labelML )
    curType = ML;

    QFont font1 ("Microsoft YaHei", 14,      QFont::Normal); //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是75）
    ui->labelML->setFont(font1);
    ui->labelL->setFont(font1);

    QFont font2 ("Microsoft YaHei", 18,      QFont::Bold); //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是75）
    display->setFont(font2);

    operand = display->text();
}


void Volume::on_btnDel_clicked()
{

    if( operand.length()>0 )
    {
         operand =operand.left(operand.length()-1);//取operand左边(原来长度-1)的部分

    }

    if(operand.length()==0)
    {
        operand= "0";
    }

   display->setText(operand);//把按键的数字显示出来

      tranVolume( );
}

bool Volume::eventFilter(QObject *obj, QEvent *event)
{
    if( event->type() == QEvent::MouseButtonPress)
    {
        display =(  QLabel *) obj;
        UpdateCur(display);

        return true;
    }

    return false;
}

Volume::~Volume()
{
    delete ui;
}

void Volume::on_btnClearAll_clicked()
{
    ui->labelL->setText("0");
    ui->labelML->setText("0");
    operand ="0";
}

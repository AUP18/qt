#include "currency.h"
#include "ui_currency.h"

Currency::Currency(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Currency)
{
    ui->setupUi(this);

    ui->labelCHN->installEventFilter(this);

    ui->labelUSA->installEventFilter(this);


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

     UpdateCur(ui->labelCHN);

}


void Currency::btnNumClicked()
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

   tranCurrency( );
}

//小数点添加
void Currency::on_btnPeriod_clicked()
{

    if(!operand.contains("."))
        operand +=qobject_cast<QPushButton*>(sender())->text();//再加新按的数字
    display->setText(operand);//把按键的数字显示出来
}

static double K = 6.96;

void Currency::tranCurrency( )
{

    if( curType == CHN)
    {
        double chn = operand.toDouble();
        double usa = chn / K;
        ui->labelUSA->setText(QString("%1").arg(usa));
    }
    else if( curType == USA)
    {

        double usa = operand.toDouble();
        double chn = usa * K;
        ui->labelCHN->setText(QString("%1").arg(chn));
    }


}

void Currency::UpdateCur(QLabel*  lbl)
{

    display = lbl;

    if(  display ==  ui->labelCHN )
     curType = CHN;

    else if(  display ==  ui->labelUSA )
    curType = USA;

    QFont font1 ("Microsoft YaHei", 14,      QFont::Normal); //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是75）
    ui->labelCHN->setFont(font1);
    ui->labelUSA->setFont(font1);

    QFont font2 ("Microsoft YaHei", 18,      QFont::Bold); //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是75）
    display->setFont(font2);

    operand = display->text();
}


void Currency::on_btnDel_clicked()
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

      tranCurrency( );
}

bool Currency::eventFilter(QObject *obj, QEvent *event)
{
    if( event->type() == QEvent::MouseButtonPress)
    {
        display =(  QLabel *) obj;
        UpdateCur(display);

        return true;
    }

    return false;
}

Currency::~Currency()
{
    delete ui;
}

void Currency::on_btnClearAll_clicked()
{
    ui->labelCHN->setText("0");
    ui->labelUSA->setText("0");
    operand ="0";
}

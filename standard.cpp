#include "standard.h"
#include "ui_standard.h"

Standard::Standard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Standard)
{
    ui->setupUi(this);


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

    ///////////////////////////////////////////////////
    foreach(auto btn, digitBTNs)           //循环，替代下面????????/
         connect(btn,SIGNAL(clicked()),this,SLOT(btnNumClicked()));

    //connect(ui->btnNum0,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    //connect(ui->btnNum1,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    //connect(ui->btnNum2,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    //connect(ui->btnNum3,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    //connect(ui->btnNum4,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    //connect(ui->btnNum5,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    //connect(ui->btnNum6,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    //connect(ui->btnNum7,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    //connect(ui->btnNum8,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    //connect(ui->btnNum9,SIGNAL(clicked()),this,SLOT(btnNumClicked()));

    connect(ui->btnPlus,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));      //+
    connect(ui->btnMinus,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));     //-
    connect(ui->btnMultiple,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));  //*
    connect(ui->btnDivide,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));    // /

    connect(ui->btnPercentage,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked())); //%
    connect(ui->btnInverse,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));    // 1/x
    connect(ui->btnSquare,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));     //x^2
    connect(ui->btnSqrt,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));       //根号
}

QString  Standard::calculation( )
{
        double result =0;

        //取操作数
        double operand1 = operands.pop().toDouble();//string型变double型
        double operand2 = operands.pop().toDouble();

        if(op == "+"){
            result = operand1 + operand2;
        }
        else if(op == "-"){
            result = operand1 - operand2;
        }
        else if(op == "×"){
            result = operand1 * operand2;
        }
        else if(op == "÷"){
            result = operand1 / operand2;
        }

      return QString::number(result); //使算数能够连起来

}


void Standard::btnNumClicked()
{

    if(       lastKey == "="     || lastKey =="1/x"
           || lastKey =="%"     || lastKey =="2√x"  || lastKey =="x²"  )
    {
        on_btnClearAll_clicked();
    }


    QString digit = qobject_cast<QPushButton*>(sender())->text();
    lastKey = digit;

    if(operand == "0" )//避免出现023
    {
        operand =digit;
    }
   else
    {
         operand +=digit;
    }


    ui->display->setText(operand);
}



//小数点添加
void Standard::on_btnPeriod_clicked()
{
    //QString str =ui->display->text();//先取原来按的数字
    //if(!str.contains("."))
        //str +=qobject_cast<QPushButton*>(sender())->text();//再加新按的数字
    //ui->display->setText(str);//把按键的数字显示出来
    if(!operand.contains("."))
        operand +=qobject_cast<QPushButton*>(sender())->text();//再加新按的数字
    ui->display->setText(operand);//把按键的数字显示出来
}


void Standard::on_btnDel_clicked()
{
    //QString str =ui->display->text();//先取原来按的数字
    //str =str.left(str.length()-1);//取str左边(原来长度-1)的部分
    //ui->display->setText(str);//把按键的数字显示出来

    if( operand.length()>0 )
    {
         operand =operand.left(operand.length()-1);//取operand左边(原来长度-1)的部分
         ui->display->setText(operand);//把按键的数字显示出来
    }

}


void Standard::on_btnClear_clicked()   //CE键
{
    operand.clear();
    ui->display->setText(operand);

}

void Standard::on_btnClearAll_clicked() //C键
{
    operand.clear();
    operands.clear();  //出栈，抛掉最前面
    op="";
    lastKey="";
    ui->display->setText(operand);
}


void Standard::btnBinaryOperatorClicked()
{
    if( operand.length()>0)
    {
       operands.push_front(operand);
    }

    if(op!=""  &&  operands.size()==2 )
    {
          QString   ret = calculation();
          ui->display->setText(   ret  );

          operands.push_front(ret);
    }

    operand ="";
    op = qobject_cast<QPushButton *>(sender())->text();
    lastKey = op;
}


void Standard::btnUnaryOperatorClicked()  //单操作符%,1/x,x^2,根号
{
    if(operand != "")
    {
        double result = operand.toDouble();

         QString   uo = qobject_cast<QPushButton*>(sender())->text();
         lastKey = uo;

        if(uo == "%")
            result /=100.0;
        else if(uo =="1/x")
            result =1/result;
        else if(uo =="x²")
            result *=result;
        else if(uo =="2√x")
            result = sqrt(result);

        ui->display->setText(QString::number(result));//把result以字符串显示在文本框中

        operand  = QString::number( result );
    }
}


void Standard::on_btnEqual_clicked()
{
    QString   eq = qobject_cast<QPushButton*>(sender())->text();
    lastKey = eq;

    if( operand.length()>0)
    {
       operands.push_front(operand);
    }

    if(op!=""  &&  operands.size()==2 )
    {
          QString   ret = calculation();
          operand = ret;

          ui->display->setText(   operand  );
          operands.push_front(operand);
    }

}


void Standard::on_btnZhengFu_clicked()
{
    QString   zf = qobject_cast<QPushButton*>(sender())->text();
    lastKey = zf;

    if( operand .length()>0)
    {
        if(operand.left(1)=="-")
        {
            operand=operand.right(operand.length()-1);
        }
        else
        {
            operand="-"+operand;
        }
        ui->display->setText(operand);
    }


}


void Standard::keyPressEvent(QKeyEvent *event)  //键盘事件/////////
{
    qDebug() << event->key();

    //可以这样写
    //if(event->key()== Qt::Key_0)    //如果按了0就让它输出
        //qDebug() << event->key();
        ////ui->btnNum0->animateClick(100);    //将键盘与按钮连起来;模拟鼠标按键按下去100ms再释放
    //else if (event->key()== Qt::Key_1)
   //     ui->btnNum1->animateClick(100);

    //也可以把ui->XXXX指针放在数组里面遍历
    foreach(auto btnkey , digitBTNs.keys())
    {
        if(event->key() == btnkey)
            digitBTNs[btnkey]->animateClick();
    }

    if(event->text() == "+" )
            ui->btnPlus->animateClick();
        else if(event->text() == "-" )
            ui->btnMinus->animateClick();
        else if(event->text() == "×" )
            ui->btnMultiple->animateClick();
        else if(event->text() == "÷" )
            ui->btnDivide->animateClick();
        else if(event->text() == "." )
            ui->btnPeriod->animateClick();   //小数点
        else if(event->text() == "%" )
            ui->btnPercentage->animateClick();
        else if(event->text() == "=" )
            ui->btnEqual->animateClick();   //=
        else if(event->key() == Qt::Key_Backspace )
            ui->btnDel->animateClick();

}



Standard::~Standard()
{
    delete ui;
}

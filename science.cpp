#include "science.h"
#include "ui_science.h"

Science::Science(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Science)
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
              };


    foreach(auto btn, digitBTNs)           //循环，替代下面????????/
         connect(btn,SIGNAL(clicked()),this,SLOT(btnNumClicked()));


    connect(ui->btnPlus,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));      //+
    connect(ui->btnMinus,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));     //-
    connect(ui->btnMultiple,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));  //*
    connect(ui->btnDivide,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));    // /
    connect(ui->btnXy,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));


     connect(ui->btnLn,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
     connect(ui->btnLog,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
     connect(ui->btn10x,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
     connect(ui->btnN1,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
     connect(ui->btnE,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));    // e
     connect(ui->btnPI,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));    // π
     connect(ui->btnAbs,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));    // |x|
    connect(ui->btnInverse,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));    // 1/x
    connect(ui->btnSquare,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));     //x^2
    connect(ui->btnSqrt,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));       //根号
}



QString  Science::calculation( )
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
        else if(op == "x^y"){
            result = pow( operand1  ,operand2);
        }
      return QString::number(result); //使算数能够连起来

}


void Science::btnNumClicked()
{
    if(       lastKey == "="     || lastKey =="1/x"  || lastKey =="log" || lastKey =="|x|"
           || lastKey =="%"     || lastKey =="2√x"  || lastKey =="x²"   || lastKey =="ln"
           || lastKey =="10^x"|| lastKey =="n!")
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
void Science::on_btnPeriod_clicked()
{

    if(!operand.contains("."))
        operand +=qobject_cast<QPushButton*>(sender())->text();//再加新按的数字
    ui->display->setText(operand);//把按键的数字显示出来
}


void Science::on_btnDel_clicked()
{
    if( operand.length()>0 )
    {
         operand =operand.left(operand.length()-1);//取operand左边(原来长度-1)的部分
         ui->display->setText(operand);//把按键的数字显示出来
    }
}


void Science::on_btnClear_clicked()   //CE键
{
    operand.clear();
    ui->display->setText(operand);

}

void Science::on_btnClearAll_clicked() //C键
{
    operand.clear();
    operands.clear();  //出栈，抛掉最前面
    op="";
    lastKey="";
    ui->display->setText(operand);
}


void Science::btnBinaryOperatorClicked()
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

int  fact(int ip) {
    if (ip == 1) {
        return 1;
    }
    else {
        return ip * fact(ip - 1);
    }
}

void Science::btnUnaryOperatorClicked()  //单操作符%,1/x,x^2,根号
{
    QString   uo = qobject_cast<QPushButton*>(sender())->text();
    lastKey = uo;

   if(uo =="π")
   {
       operand  = "3.1415926535897932384626433832795";
       ui->display->setText( operand );//把result以字符串显示在文本框中
       ui->display->setCursorPosition(0);
   }
   else if(uo =="e")
   {
       operand  = "2.7182818284590452353602874713527";
       ui->display->setText( operand );//把result以字符串显示在文本框中
       ui->display->setCursorPosition(0);
   }
   else
   {
       if(operand != "")
       {
            double result = operand.toDouble();

           if(uo == "%")
               result /=100.0;
           else if(uo =="1/x")
               result =1/result;
           else if(uo =="x²")
               result *=result;
           else if(uo =="2√x")
               result = sqrt(result);
           else if(uo =="|x|")
               result = abs(result);
           else if(uo =="n!")
               result = fact(result);
           else if(uo =="10^x")
               result = pow(10, result);
           else if(uo =="log")
               result = log10(  result);
           else if(uo =="ln")
               result = log( result);

             operand  = QString::number( result );
             ui->display->setText( operand );//把result以字符串显示在文本框中
       }
   }


}


void Science::on_btnEqual_clicked()
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


void Science::on_btnZhengFu_clicked()
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


void Science::keyPressEvent(QKeyEvent *event)  //键盘事件/////////
{
    qDebug() << event->key();


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
        else if(event->text() == "=" )
            ui->btnEqual->animateClick();   //=
        else if(event->key() == Qt::Key_Backspace )
            ui->btnDel->animateClick();

}



Science::~Science()
{
    delete ui;
}


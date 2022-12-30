#include "programmer.h"
#include "ui_programmer.h"

Programmer::Programmer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Programmer)
{
    ui->setupUi(this);

    labels={ ui->labelHEX,   ui->labelDEC ,  ui->labelOCT ,ui->labelBIN,  ui->label_3,  ui->label_4,  ui->label_5,  ui->label_6};

    foreach(auto lab, labels)
        lab->installEventFilter(this);

    digitBTNs =
                 { ui->btnNum0,ui->btnNum1,ui->btnNum2,ui->btnNum3,ui->btnNum4,ui->btnNum5,
                   ui->btnNum6,ui->btnNum7,ui->btnNum8,ui->btnNum9,ui->btnA,ui->btnB,ui->btnC,ui->btnD,ui->btnE,ui->btnF };         //初始化; Qt::key_i是Qt内名称为0的按钮????

    ///////////////////////////////////////////////////
    foreach(auto btn, digitBTNs)
        connect(btn,SIGNAL(clicked()),this,SLOT(btnNumClicked()));

    connect(ui->btnPlus,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));      //+
    connect(ui->btnMinus,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));     //-
    connect(ui->btnMultiple,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));  //*
    connect(ui->btnDivide,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));    // /


    updateDisplayJZ(1);
}

Programmer::~Programmer()
{
    delete ui;
}

void  Programmer::updateDisplayJZ(int row)
{
    lastJZ  = curJZ;

    curRow= row;
    if( curRow == 0 ) curJZ =  16;
    else   if( curRow == 1 ) curJZ =  10;
    else   if( curRow == 2) curJZ =  8;
    else   if( curRow == 3 ) curJZ =  2;

    displayJZ = labels[curRow];
    ui->gridLayout_3->addWidget(ui->labelCur , curRow , 0);

    for (int i=0; i<16 ; ++i)
    {
        digitBTNs[i]->setEnabled(  i< curJZ );
    }

    ui->btnPeriod->setEnabled(false);


    QString strV= displayJZ->text();
    ui->display->setText( strV );
    if( operand.length()>0  )
    {
        operand = strV;
    }


    for ( int i=0; i< operands.size();++i)
    {
        QString strV = operands.at(i);

        //取操作数
        bool ok;
        int  dec=strV.toInt(  &ok, lastJZ );
        operands[i] =QString::number(dec , curJZ);

    }


}

QString  FormatBin(int  dec)
{
    QString hex = QString::number(dec , 16);
    QString bin =  QString("%1").arg(dec,  hex.length() *4 , 2,  QLatin1Char('0'));
    QString ret= "";
    for(int i=0;i<bin.length();++i)
    {
        if( i %4 == 0 && i>0 )
        {
            ret.append(' ');
        }

        ret.append( bin[i] );
    }
    return ret;
}

void Programmer::transJZ( )
{
    QString strCur= labels[curRow]->text();
    switch (curJZ)
    {
    case 16:
    {
        bool ok ;
        int  dec =  strCur.toInt( &ok,16);

        labels[1]->setText(QString::number(dec , 10));
        labels[2]->setText(QString::number(dec , 8));
      //  labels[3]->setText(QString::number(dec , 2));

         labels[3]->setText(FormatBin(dec));

    }
        break;
    case 10:
    {
        int  dec =  strCur.toInt();
        labels[0]->setText(QString::number(dec , 16).toUpper());
        labels[2]->setText(QString::number(dec , 8));
       // labels[3]->setText(QString::number(dec , 2));

         labels[3]->setText(FormatBin(dec));

    }
        break;
    case 8:
    {
        bool ok ;
        int  dec =  strCur.toInt( &ok,8);
        labels[0]->setText(QString::number(dec , 16).toUpper());
        labels[1]->setText(QString::number(dec , 10));
       // labels[3]->setText(QString::number(dec , 2));

        labels[3]->setText(FormatBin(dec));
    }
        break;
    case 2:
    {
        bool ok ;
        int  dec =  strCur.toInt( &ok,2);
        labels[0]->setText(QString::number(dec , 16).toUpper());
        labels[1]->setText(QString::number(dec , 10));
        labels[2]->setText(QString::number(dec , 8));

        labels[3]->setText(FormatBin(dec));
    }
        break;
    }


}


void Programmer::btnNumClicked()
{
    QString digit = qobject_cast<QPushButton*>(sender())->text();
    lastKey = digit;

    QString strCur= labels[curRow]->text();

    if(operand == "0" )//避免出现023
    {
        operand =digit;
    }
   else
    {
         operand +=digit;
    }

    ui->display->setText(operand);
    displayJZ->setText(operand);

    transJZ( );

}

bool Programmer::eventFilter(QObject *obj, QEvent *event)
{
    if( event->type() == QEvent::MouseButtonPress)
    {

        QWidget * w=(  QWidget *) obj;
        int index = ui->gridLayout_3->indexOf(w);
        int row = 0,col,rs,cs;
        ui->gridLayout_3->getItemPosition(index ,&row, &col,&rs,&cs);

        updateDisplayJZ(row);

        return true;
    }

    return false;
}



QString  Programmer::calculation( )
{

    if(  operands.size() == 2  && op.length()>0 )
    {

        int  result =0;

        QString   strOperand1  =operands.at(0);
        QString   strOperand2  =operands.at(1);
        operands.clear();

        //取操作数
        bool ok;
        int  operand1 =strOperand1.toInt(  &ok, curJZ );
        int  operand2 =strOperand2.toInt(  &ok, curJZ );

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

        QString  strResult =QString::number(result , curJZ ).toUpper();

       return   strResult; //使算数能够连起来
    }

    return "";

}



//小数点添加
void Programmer::on_btnPeriod_clicked()
{

}


void Programmer::on_btnDel_clicked()
{
    if( operand.length()>0 )
    {
         operand =operand.left(operand.length()-1);//取operand左边(原来长度-1)的部分

         ui->display->setText(operand);//把按键的数字显示出来
         displayJZ->setText(operand);

          transJZ( );
    }

}



void Programmer::on_btnClearAll_clicked() //CE键
{
    operand.clear();
    operands.clear();  //出栈，抛掉最前面
    op="";
    lastKey="";
    ui->display->setText(operand);
    displayJZ->setText(operand);
    transJZ();
}


void Programmer::btnBinaryOperatorClicked()
{
    if( operand.length()>0)
    {
       operands.push_back(operand);
    }

    if(op!=""  &&  operands.size()==2 )
    {
          QString   ret = calculation();
          ui->display->setText(   ret  );
          displayJZ->setText(ret);
          transJZ();

          operands.push_back(ret);
    }

    operand ="";
    op = qobject_cast<QPushButton *>(sender())->text();
    lastKey = op;

}


void Programmer::btnUnaryOperatorClicked()  //单操作符%,1/x,x^2,根号
{

}


void Programmer::on_btnEqual_clicked()
{
    if(operand != "")
    {
        operands.push_back(operand);
        operand = "";
    }
    QString result = calculation();
    if(result.length()>0)
    {
        ui->display->setText(result);
        displayJZ->setText(result);
    }

}


void Programmer::on_btnZhengFu_clicked()
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
        displayJZ->setText(operand);
        transJZ();
    }


}


void Programmer::keyPressEvent(QKeyEvent *event)  //键盘事件/////////
{



}

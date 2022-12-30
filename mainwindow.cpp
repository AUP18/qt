#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "standard.h"
#include "science.h"
#include "programmer.h"
#include "datecalc.h"
#include "currency.h"
#include "volume.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->removeWidget(ui->page);

    Standard  * s1 = new Standard();
    Science  * s2 = new Science();
    Programmer  * s3 = new Programmer();
    DateCalc  * s4= new DateCalc();
    Currency *s5 = new Currency();
    Volume *s6 = new Volume();

    ui->stackedWidget->addWidget(s1);
    ui->stackedWidget->addWidget(s2);
    ui->stackedWidget->addWidget(s3);
    ui->stackedWidget->addWidget(s4);
    ui->stackedWidget->addWidget(s5);
    ui->stackedWidget->addWidget(s6);

       menu = new QMenu(this);

       QAction *pAct1 = new QAction("标准", this);
       pAct1->setData( 1);
       QAction *pAct2 = new QAction("科学", this);
          pAct2->setData( 2);
       QAction *pAct3 = new QAction("程序员", this);
         pAct3->setData( 3);
       QAction *pAct4 = new QAction("日期计算", this);
       pAct4->setData( 4);
       menu->addAction(pAct1);
       menu->addAction(pAct2);
       menu->addAction(pAct3);
       menu->addAction(pAct4);

        QAction *sep1 = new QAction( this);
        sep1->setSeparator(true);
        menu->addAction(sep1);

        QAction *pAct5 = new QAction("货币", this);
        pAct5->setData( 5);
        QAction *pAct6 = new QAction("容量", this);
           pAct6->setData( 6);
        menu->addAction(pAct5);
        menu->addAction(pAct6);


       foreach( auto a, menu->actions())
       {
           connect( a,  &QAction::triggered,  [ this ,a ]{

                   int index = a->data().toInt();
                  this->ui->labelType->setText( a->text());
                  this->ui->stackedWidget->setCurrentIndex(index);
           });
       }


       pAct1->trigger();


       ui->pushButtonMenu->setMenu( menu );


}

MainWindow::~MainWindow()
{
    delete ui;
}


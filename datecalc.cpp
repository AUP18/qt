#include "datecalc.h"
#include "ui_datecalc.h"

DateCalc::DateCalc(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DateCalc)
{
    ui->setupUi(this);

    connect(ui->dateEditStart , &QDateEdit::dateChanged , [ this ]( const QDate &date)
    {
        this->on_dateChanged(date );
    });
    connect(ui->dateEditEnd , &QDateEdit::dateChanged , [ this ]( const QDate &date)
    {
        this->on_dateChanged(date );
    });
}

DateCalc::~DateCalc()
{
    delete ui;
}

void DateCalc::on_dateChanged(const QDate &date)
{
     QDateTime start = ui->dateEditStart->dateTime();
     QDateTime end = ui->dateEditEnd->dateTime();

   int day =   end.daysTo(start);

   ui->labelResult->setText(QString("%1天").arg(day));
}


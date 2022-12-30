#ifndef DATECALC_H
#define DATECALC_H

#include <QWidget>

namespace Ui {
class DateCalc;
}

class DateCalc : public QWidget
{
    Q_OBJECT

public:
    explicit DateCalc(QWidget *parent = nullptr);
    ~DateCalc();

public slots:
    void on_dateChanged(const QDate &date);
private:
    Ui::DateCalc *ui;
};

#endif // DATECALC_H

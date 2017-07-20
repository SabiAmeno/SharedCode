#ifndef TIPTEST_H
#define TIPTEST_H

#include <QDialog>

namespace Ui {
class TipTest;
}

class TipTest : public QDialog
{
    Q_OBJECT

public:
    explicit TipTest(QWidget *parent = 0);
    ~TipTest();

private slots:
    void OnEjectDlg();
private:
    Ui::TipTest *ui;
};

#endif // TIPTEST_H

#include "tiptest.h"
#include "ui_tiptest.h"
#include "tooltip.h"

TipTest::TipTest(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TipTest)
{
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, this, &TipTest::OnEjectDlg);
}

TipTest::~TipTest()
{
    delete ui;
}

void TipTest::OnEjectDlg()
{
    QString slist;
	slist += "1\n";
	slist += "1\n";
	slist += "1\n";
	slist += "1\n";
	slist += "1\n";
	slist += "1\n";
	slist += "1\n";
	slist += "1\n";
	slist += "1\n";
	slist += "1\n";
	slist += "1\n";
	slist += "1\n";
	slist += "1\n";
	slist += "1\n";
	slist += "1\n";
	slist += "1\n";
	slist += "1\n";
	slist += "1\n";
	slist += "1\n";
	slist += "1\n";
	slist += "1\n";
	slist += "1\n";
	slist += "1\n";
	slist += "1\n";
	slist += "1\n";
	slist += "1\n";
	slist += "1\n";
	ToolTip::ShowTip(ui->pushButton->pos(), slist);
}

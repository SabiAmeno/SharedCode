#include <QMouseEvent>
#include <QTextBrowser>
#include <QDesktopWidget>
#include <QDebug>

#include "tooltip.h"
#include "ui_tooltip.h"

#define TIMEOUT_ISVALID(x) \
    (x > 0)

//ToolTip* ToolTip::tip_instance = nullptr;

ToolTip::ToolTip(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToolTip)
{
    ui->setupUi(this);
	setFocusPolicy(Qt::StrongFocus);
	ui->textBrowser->setTabStopWidth(2);
    setWindowFlags(Qt::FramelessWindowHint);
	setWindowFlags(Qt::Popup);
	ui->textBrowser->setAutoFillBackground(true);
	QPalette pt = ui->textBrowser->palette();
	pt.setBrush(QPalette::Base, QColor(253, 246, 227));
	ui->textBrowser->setPalette(pt);

	timer.start(1000);
	connect(&timer, &QTimer::timeout, this, &ToolTip::KeepAlive);
}

ToolTip::~ToolTip()
{
    delete animation;
    delete ui;
}

ToolTip * ToolTip::Instance()
{
	static ToolTip tool;
	return &tool;
}

void ToolTip::setToolMesg(const QString &tip)
{
    msgs = tip;
    ui->textBrowser->setPlainText(msgs);
}

void ToolTip::setTimeout(uint64_t timeout)
{
    time_out = timeout;
    if(TIMEOUT_ISVALID(time_out)) {
        timer.stop();
        disconnect(&timer, &QTimer::timeout, this, &ToolTip::KeepAlive);
        connect(&timer, &QTimer::timeout, this, [&]{close();});
        timer.start();
    }
}

void ToolTip::KeepAlive()
{
    if(is_show && isActiveWindow())
        return;
    timer.stop();
    delete animation;
    animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(100);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->start();
    connect(animation, SIGNAL(finished()), this, SLOT(close()));
}

void ToolTip::enterEvent(QEvent *event)
{
    is_show = true;
    if(animation) {
        timer.start(1000);
        animation->stop();
        setWindowOpacity(1);
    }
	qDebug() << "enter";
}

void ToolTip::leaveEvent(QEvent *event)
{
    QRect scope(pos(), QSize(width(), height()));
	is_show = scope.contains(QCursor::pos());
	qDebug() << "Pos:(" << QCursor::pos().x() << "," << QCursor::pos().y() << ")";
	qDebug() << "Leave";
}

void ToolTip::mouseMoveEvent(QMouseEvent *event)
{
    QRect scope(pos(), QSize(width(), height()));
    if(scope.contains(event->pos()))
        is_show = true;
}

void ToolTip::ShowTip(const QPoint& pos, const QString &tip, uint64_t timeout, QWidget *parent)
{
	ToolTip* const tip_instance = Instance();
	QPoint real_pos = pos;
	auto screenRect = QApplication::desktop()->screenGeometry();
	float x_w = screenRect.right() - pos.x();
	float y_h = screenRect.bottom() - pos.y();
	if (x_w < tip_instance->width())
		real_pos.setX(screenRect.right() - tip_instance->width());
	if (y_h < tip_instance->height())
		real_pos.setY(screenRect.bottom() - tip_instance->height() - 40);

	tip_instance->move(real_pos);
	tip_instance->setFocusPolicy(Qt::StrongFocus);
	tip_instance->setWindowOpacity(1);
	tip_instance->setToolMesg(tip);
	tip_instance->setTimeout(timeout);
	tip_instance->show();
}

void ToolTip::Hide()
{
	Instance()->close();
}

#ifndef TOOLTIP_H
#define TOOLTIP_H

#include <QTimer>
#include <QWidget>
#include <QPropertyAnimation>

namespace Ui {
class ToolTip;
}

class ToolTip : public QWidget
{
    Q_OBJECT

public:
    ~ToolTip();
	static void ShowTip(const QPoint& pos, const QString& tip, uint64_t timeout = 0, QWidget* parent = 0);
	static void Hide();
private slots:
    void KeepAlive();
protected:
	explicit ToolTip(QWidget *parent = 0);

    virtual void enterEvent(QEvent *event);
    virtual void leaveEvent(QEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);

private:
	static ToolTip* Instance();
	void setToolMesg(const QString& tip);
	void setTimeout(uint64_t timeout = 0);

    Ui::ToolTip *ui;
    QTimer      timer;
    bool        is_show = true;
    uint64_t    time_out = 0;

    QPropertyAnimation *animation = nullptr;
//	static ToolTip*    tip_instance;
};

#endif // TOOLTIP_H

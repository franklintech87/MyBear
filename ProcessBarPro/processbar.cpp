#include "processbar.h"

#include <QPainter>
#include <QPaintEvent>
#include <QDebug>

ProcessBar::ProcessBar(QWidget *parent) :
    QWidget(parent),
    mStartAngle(90)
{
    /* default setting */
    mPercent = 0;

    mColorMap.insert(100, QColor(52, 168, 83)); // green
    mColorMap.insert(30, QColor(251, 188, 5));  // yellow
    mColorMap.insert(10, QColor(234, 67, 53));  // red

    mShadowColor = QColor(0xd2e3fc);
    mBackgroundColor = QColor(180, 197, 210);

    mTextFont.setFamily("Microsoft YaHei");
    mTextFont.setPixelSize(22);

    mPercentFont.setFamily("Microsoft YaHei");
    mPercentFont.setPixelSize(35);
}

void ProcessBar::setContentColor(int value, const QColor &color)
{
    mColorMap.insert(value, color);
}

void ProcessBar::updateValue_slot(int value)
{
    if (qAbs(value) <= 100) {
        mPercent = value;
        update();
    }
}

void ProcessBar::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    int width = event->rect().width() - 20;
    int height = event->rect().height() - 20;
    int size = qMin(width, height);

    const QRectF drawingRectF(10.0, 10.0, size, size);

    QPen pen;
    pen.setWidth(12);
    pen.setCapStyle(Qt::RoundCap);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    //! [1] draw Background
    painter.save();
    pen.setBrush(mBackgroundColor);
    painter.setPen(pen);
    painter.drawArc(drawingRectF, 0, 360 * 16);
    painter.restore();
    //! [1] draw Background

    if (mPercent != 0) {
        int span = 3.6 * mPercent;

        //! [2.1] draw Shadow
        painter.save();
        pen.setBrush(mShadowColor);
        painter.setPen(pen);
        painter.drawArc(drawingRectF, (mStartAngle - 0) * 16, (span + 0) * 16);
        painter.restore();
        //! [2.1] draw Shadow

        //! [2.2] draw Content
        painter.save();
        pen.setWidth(10);
        pen.setBrush(_getCurrentColor(mPercent));
        painter.setPen(pen);
        painter.drawArc(drawingRectF, mStartAngle * 16, span * 16);
        painter.restore();
        //! [2.2] draw Content
    }

    //! [3] draw Text
    painter.save();
    if (!mTitle.isEmpty()) {
        painter.setFont(mTextFont);
        painter.drawText(drawingRectF.adjusted(0, -50, 0, 0), Qt::AlignCenter, mTitle);

        painter.setFont(mPercentFont);
        painter.drawText(drawingRectF.adjusted(0, 30, 0, 0), Qt::AlignCenter, QString("%1%").arg(mPercent));
    } else {
        painter.setFont(mPercentFont);
        painter.drawText(drawingRectF.adjusted(0, 0, 0, 0), Qt::AlignCenter, QString("%1%").arg(mPercent));
    }

    painter.restore();
    //! [3] draw Text
}

QColor ProcessBar::_getCurrentColor(int value)
{
    QColor c;

    auto list = mColorMap.keys();
    for (int i = list.count() - 1; i >= 0; --i) {
        if (value <= list.at(i)) {
            c = mColorMap.value(list.at(i));
        }
    }
    return c;
}

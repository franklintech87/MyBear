#ifndef PROCESSBAR_H
#define PROCESSBAR_H

/* author: liuyufei */

#include <QWidget>
#include <QMap>

class ProcessBar : public QWidget
{
    Q_OBJECT

public:
    explicit ProcessBar(QWidget *parent = nullptr);

    void setStartAngle(int start) { mStartAngle = start; }
    void setContentColor(int value, const QColor &color);

    void setShadowColor(const QColor &color) { mShadowColor = color; }
    void setBackgroundColor(const QColor &color) { mBackgroundColor = color; }

    void setTitleText(QString title) { mTitle = title; }

    void setTextFont(const QFont &font) { mTextFont = font; }
    void setPercentFont(const QFont &font) { mPercentFont = font; }

public slots:
    void updateValue_slot(int value);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int mPercent;
    int mStartAngle;

    QMap<int, QColor> mColorMap;

    QString mTitle;

    QColor mShadowColor;
    QColor mBackgroundColor;

    QFont mTextFont;
    QFont mPercentFont;

    QColor _getCurrentColor(int value);
};

#endif // PROCESSBAR_H

/*********************************************************
**描述：该模块实现了一个电池电量显示控件
**
**
*********************************************************/
#include "batterylabel.h"
#include <QTimer>
#include <QPainter>
//#include <QDebug>

#define BORDER_WIDTH   3

BatteryLabel::BatteryLabel(QWidget *parent)
    : QWidget(parent)
{
    m_minValue = 0;
    m_maxValue = 100;
    m_currentValue = 40;
    m_alarmValue = 20;
    m_suffValue = 80;
    m_borderColor = QColor(100, 100, 100);
    m_alarmColor = QColor(250, 118, 113);
    m_normalColor = QColor(255, 215, 0);
    m_suffColor = QColor(50, 205, 51);

    m_charging = false;
}

BatteryLabel::~BatteryLabel()
{

}

void BatteryLabel::setRange(double minValue, double maxValue)
{
    if (minValue >= maxValue) {
        return;
    }
    if (m_currentValue < minValue || m_currentValue > maxValue) {
        return;
    }
    m_minValue = minValue;
    m_maxValue = maxValue;
    update();
}

void BatteryLabel::setMinValue(double minValue)
{
    setRange(minValue, m_maxValue);
}

void BatteryLabel::setMaxValue(double maxValue)
{
    setRange(m_minValue, maxValue);
}

void BatteryLabel::setValue(double value)
{
    if (value < m_minValue || value > m_maxValue) {
        return;
    }

    if (value > m_currentValue) {
        m_charging = true;                //电量增加，判断为正则充电
    } else if(value < m_currentValue) {
        m_charging = false;
    }
    m_currentValue = value;
    update();
}

void BatteryLabel::setAlarmValue(double alarmValue)
{
    if (m_alarmValue != alarmValue) {
        m_alarmValue = alarmValue;
        update();
    }
}

bool BatteryLabel::isCharging()
{
    return m_charging;
}

void BatteryLabel::setChargingstat(bool chg)
{
    m_charging = chg;
}

void BatteryLabel::setBorderColor(const QColor &borderColor)
{
    if (m_borderColor != borderColor) {
        m_borderColor = borderColor;
        update();
    }
}

void BatteryLabel::setAlarmColor(const QColor &alarmColor)
{
    if (m_alarmColor != alarmColor) {
        m_alarmColor = alarmColor;
        update();
    }
}

void BatteryLabel::setNormalColor(const QColor &normalColor)
{
    if (m_normalColor != normalColor) {
        m_normalColor = normalColor;
        update();
    }
}

void BatteryLabel::setSuffColor(const QColor &suffColor)
{
    if (m_suffColor != suffColor) {
        m_suffColor = suffColor;
        update();
    }
}

QSize BatteryLabel::sizeHint() const
{
    return QSize(150, 80);
}


void BatteryLabel::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    drawBorder(&painter);
    drawBackground(&painter);
    if (m_charging) {
        drawCharging(&painter);
    }
}

/*绘制电池边框*/
void BatteryLabel::drawBorder(QPainter *painter)
{
    painter->save();
    double headWidth = width() / 10;
    double batteryWidth = width() - headWidth;

    QPointF topLeft(BORDER_WIDTH, BORDER_WIDTH);
    QPointF bottomRight(batteryWidth, height() - BORDER_WIDTH);
    m_batteryRect = QRectF(topLeft, bottomRight);

    painter->setPen(QPen(m_borderColor, BORDER_WIDTH));
    //painter->setBrush(Qt::NoBrush);

    painter->drawRoundRect(m_batteryRect, 10, 20);

    QPointF headRectTopLeft(m_batteryRect.topRight().x(), height() / 3);
    QPointF headRectBottomRight(width(), height() - height() / 3);
    QRectF headRect(headRectTopLeft, headRectBottomRight);

    //painter->setBrush(headRectGradient);

    painter->drawRoundRect(headRect, 25, 50);
    painter->restore();
}

/* 绘制背景，即电量显示条 */
void BatteryLabel::drawBackground(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    if (m_currentValue <= m_alarmValue) {
        painter->setBrush(QColor(m_alarmColor));
    } else if (m_currentValue <= m_suffValue) {
        painter->setBrush(QColor(m_normalColor));
    } else {
        painter->setBrush(QColor(m_suffColor));
    }

    int margin = qMin(width(), height()) / 15;
    double ratio = (m_currentValue - m_minValue) / (m_maxValue - m_minValue);
    double width = (m_batteryRect.width() - (margin * 2)) * ratio;
    QPointF topLeft(m_batteryRect.topLeft().x() + margin, m_batteryRect.topLeft().y() + margin);
    QPointF bottomRight(width + margin + BORDER_WIDTH, m_batteryRect.bottomRight().y() - margin);
    QRectF rect(topLeft, bottomRight);

    painter->drawRoundRect(rect, 10, 10);
    painter->restore();
}

/* 绘制充电标志 */
void BatteryLabel::drawCharging(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor(255, 255, 255));
    int h = height();
    const QPointF points[6] = {
        QPointF(m_batteryRect.width() / 2 + 10, 0),
        QPointF(m_batteryRect.width() / 2, h / 2 - 5),
        QPointF(m_batteryRect.width() / 2 + 20, h / 2 - 5),
        QPointF(m_batteryRect.width() / 2 - 10, h),
        QPointF(m_batteryRect.width() / 2, h / 2 + 5),
        QPointF(m_batteryRect.width() / 2 - 20, h / 2 + 5)
    };
    painter->drawConvexPolygon(points, 6);
    painter->restore();
}

/*****************************************************
**该模块实现了一个水波形容器的进度条显示控件
**
**
*****************************************************/

#include "waterwaveprogress.h"

#include <QTimer>
#include <qmath.h>
#include <QPainter>
#include <QPainterPath>
#include <QtMath>
#include <QDebug>

#define RADIUS 100

WaterWaveProgress::WaterWaveProgress(QWidget *parent)
    : QWidget(parent)
{
    m_value = 60;
    m_minValue = 0;
    m_maxValue = 100;
    m_waterDensity = 2;
    m_waterHeight = 0.03;
    m_offset = 0;
    m_borderWidth = 2;
    m_bgColor = QColor(0, 100, 255);

    m_timer = new QTimer(this);
    connect(m_timer,  SIGNAL(timeout()), SLOT(timeout()));
    m_timer->start(100);
}

WaterWaveProgress::~WaterWaveProgress()
{
    if (m_timer->isActive()) {
        m_timer->stop();
    }
}

void WaterWaveProgress::setRange(int minValue, int maxValue)
{
    if (minValue >= maxValue) {
        return;
    }

    m_minValue = minValue;
    m_maxValue = maxValue;

    if (m_value < m_minValue) {
        setValue(m_minValue);
    }

    if (m_value > m_maxValue) {
        setValue(m_maxValue);
    }

    update();
}

void WaterWaveProgress::setMinValue(int minValue)
{
    setRange(minValue, m_maxValue);
}

void WaterWaveProgress::setMaxValue(int maxValue)
{
    setRange(m_minValue, maxValue);
}

void WaterWaveProgress::setValue(int value)
{
    if (value <= m_maxValue && value >= m_minValue && value != m_value) {
        m_value = value;
        update();
    }
}

void WaterWaveProgress::setWaterDensity(int waterDensity)
{
    if (m_waterDensity != waterDensity) {
        m_waterDensity = waterDensity;
        update();
    }
}

void WaterWaveProgress::setWaterHeight(double waterHeight)
{
    if (m_waterHeight != waterHeight) {
        m_waterHeight = waterHeight;
        update();
    }
}

void WaterWaveProgress::setOffset(int offset)
{
    if (m_offset != offset) {
        m_offset = offset;
        update();
    }
}

void WaterWaveProgress::setBorderWidth(double borderWidth)
{
    if (m_borderWidth != borderWidth) {
        m_borderWidth = borderWidth;
        update();
    }
}

void WaterWaveProgress::setBgColor(const QColor &bgColor)
{
    if (m_bgColor != bgColor) {
        m_bgColor = bgColor;
        update();
    }
}

QSize WaterWaveProgress::sizeHint() const
{
    return QSize(RADIUS * 2, RADIUS * 2);
}

void WaterWaveProgress::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    int side = qMin(width(), height());
    painter.scale(side / 200.0, side / 200.0);		/* 比例缩放 */
    painter.setRenderHint(QPainter::Antialiasing);

    drawValue(&painter);
    drawText(&painter);
}

void WaterWaveProgress::drawValue(QPainter *painter)
{
    int side = qMin(height(), width());
    int startX = m_borderWidth;
    int startY = m_borderWidth;
    int endX = side - m_borderWidth;
    int endY = side - m_borderWidth;

    const double percent = 1 - (double)(m_value - m_minValue) / (m_maxValue - m_minValue);
    double W = m_waterDensity * M_PI / endX;
    double amplitude = endY * m_waterHeight; //水波振幅
    double k = endY * percent;

    k = (side * percent) + startY;

    QPainterPath waterPath1;
    QPainterPath waterPath2;

    //qDebug() << QString("startx:%1, endx:%2, starty:%3, endy:%4").
                //arg(startX).arg(endX).arg(startY).arg(endY) << endl;
    waterPath1.moveTo(startX, endY);
    waterPath2.moveTo(startX, endY);

    m_offset += 0.6;
    if (m_offset > (endX / 2)) {
        m_offset = 0;
    }

    for (int x = startX; x <= endX; x++) {
        double waterY1 = (double)(amplitude * sin(W * x + m_offset)) + k;
        double waterY2 = (double)(amplitude * sin(W * x + m_offset + (endX / 2 * W))) + k;

        if (m_value == m_minValue) {
            waterY1 = endY;
            waterY2 = endY;
        }

        if (m_value == m_maxValue) {
            waterY1 = startY;
            waterY2 = startY;
        }

        waterPath1.lineTo(x, waterY1);
        waterPath2.lineTo(x, waterY2);
    }

    waterPath1.lineTo(endX, endY);
    waterPath2.lineTo(endX, endY);

    QPainterPath bigPath;

    bigPath.addEllipse(startX, startY, side - m_borderWidth * 2, side - m_borderWidth * 2);

    /* 画圆形容器 */
    QPen pen;
    pen.setWidth(m_borderWidth);
    pen.setColor(QColor(255, 255, 255));
    painter->setPen(pen);
    painter->drawPath(bigPath);

    /* 画水波路径 */
    QPainterPath path;
    QColor waterColor1 = m_bgColor;
    waterColor1.setAlpha(100);
    QColor waterColor2 = m_bgColor;
    waterColor2.setAlpha(200);

    painter->save();
    painter->setPen(Qt::NoPen);

    path = bigPath.intersected(waterPath1);
    painter->setBrush(waterColor1);
    painter->drawPath(path);

    path = bigPath.intersected(waterPath2);
    painter->setBrush(waterColor2);
    painter->drawPath(path);

    painter->restore();
}

void WaterWaveProgress::drawText(QPainter *painter)
{
    int side = qMin(height(), width());
    side = side - m_borderWidth * 2;
    int r = side / 2;
    int width = side * qCos(M_PI / 4);      //文本框矩形长度
    int height = r * qSin(M_PI / 4);        //文本框矩形宽度

    painter->setPen(QColor(255, 255, 255)); //字体颜色
    QFont font;
    font.setFamily("Microsoft YaHei");
    font.setPointSize(height / 2);
    font.setBold(true);
    painter->setFont(font);

    /*设置文本矩形框放置位置并绘制文本*/
    if (m_value <= 50) {
        QRectF rec(r - r * qCos(M_PI / 4), r,
                    width, height);
        //painter->drawRect(rec);
        painter->drawText(rec, Qt::AlignCenter, QString::number(m_value) + "%");
    } else {
        QRectF rec(r - r * qCos(M_PI / 4), r - r * qSin(M_PI / 4),
                    width, 2 * height);
        //painter->drawRect(rec);
        painter->drawText(rec, Qt::AlignCenter, QString::number(m_value) + "%");
    }
}

void WaterWaveProgress::timeout()
{
    m_offset += 0.4;
    update();
}

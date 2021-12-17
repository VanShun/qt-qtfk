#include "circleclicklabel.h"

#include <QTimer>
#include <QPainter>
#include <QMouseEvent>
#include <QStyleOptionFrame>
#include <QDebug>

#define MIN_CIRCLE   4
#define MAX_CIRCLE   40

CircleClickLabel::CircleClickLabel(QWidget *parent)
    : QWidget(parent)
{
    m_circleOn = false;
    m_crValue = MIN_CIRCLE;

    m_circleTimer = new QTimer(this);
    m_circleTimer->setInterval(20);
    connect(m_circleTimer, SIGNAL(timeout()), SLOT(updateRender()));
}

CircleClickLabel::~CircleClickLabel()
{
    //delete m_circleTimer;  no need
}

QSize CircleClickLabel::sizeHint() const
{
    return QSize(180, 180);
}

void CircleClickLabel::updateRender()
{
    m_crValue += 2;
    if (m_crValue > MAX_CIRCLE) {
        m_crValue = MIN_CIRCLE;
        m_circleOn = false;
        m_circleTimer->stop();
    }

    update();
}

void CircleClickLabel::mousePressEvent(QMouseEvent *event)
{
    m_circleOn = true;
    m_pos = event->pos();
    qDebug() << m_pos << endl;
    m_crValue = MIN_CIRCLE;
    m_circleTimer->start();
}

void CircleClickLabel::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    if (m_circleOn) {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(QPen(QColor(20, 203, 232, 50), 3));
        painter.drawEllipse(m_pos, m_crValue, m_crValue);
        painter.drawRect(0, 0, width(), height());
    }
}

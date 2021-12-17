#include "marqueelabel.h"

#include <QTimer>
#include <QPainter>
#include <QDebug>

MarqueeLabel::MarqueeLabel(QWidget *parent)
    : QWidget(parent)
{
    setAutoFillBackground(true);
    QSizePolicy tbsizepolicy = this->sizePolicy();
    tbsizepolicy.setHorizontalPolicy(QSizePolicy::MinimumExpanding);
    tbsizepolicy.setVerticalPolicy(QSizePolicy::MinimumExpanding);
    this->setSizePolicy(tbsizepolicy);
    //resize(300, 40);
    initWidget();
}

MarqueeLabel::~MarqueeLabel()
{
    if (m_timer->isActive()) {
        m_timer->stop();
    }
}

void MarqueeLabel::initWidget()
{
    m_step = 2;
    m_interval = 20;

    m_enmouseHoverStop = false;
    m_moveStyle = MoveStyleRightToLeft;

    m_mouseHover = false;
    m_moveRight = true;
    m_initX = 0;
    m_initY = 0;

    m_labText = new QLabel(this);
    m_labText->setAlignment(Qt::AlignVCenter);
    m_labText->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_text = "";
    setText("hello qt");
    setForeground(QColor(100, 184, 255));
    setBackground(QColor(222, 222, 222));

    m_timer = new QTimer(this);
    m_timer->setInterval(m_interval);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(timeout()));
    m_timer->start();
}

void MarqueeLabel::setText(const QString &text)
{
    qDebug() << "settext:" << text << endl;
    if (m_text != text && text != "") {
        m_text = text;
        m_labText->setText(text);
        QFont font = this->font();
        font.setPointSize(40);
        m_labText->setFont(font);
        QFontMetricsF fm(font);
        QRectF rec = fm.boundingRect(text);
        m_textwidth = rec.width();
        m_textheight = rec.height();
        //qDebug() << text << textWidth << textHeight << m_textwidth << m_textheight << endl;

        //这边进行this->resize不会起效果，暂时没搞懂为什么
        this->resize(QSize(m_textwidth + 150, m_textheight + 20));
        m_labText->resize(QSize(m_textwidth + 15, m_textheight + 5));

        if (m_moveStyle == MoveStyleLeftAndRight) {
            m_initX = 0;
        } else if (m_moveStyle == MoveStyleLeftToRight) {
            m_initX = -m_labText->width();
        } else if (m_moveStyle == MoveStyleRightToLeft) {
            m_initX = width();
        }
    }
}

void MarqueeLabel::clearText()
{
    m_labText->clear();
}

void MarqueeLabel::setStep(int step)
{
    if (m_step != step) {
        m_step = step;
    }
}

void MarqueeLabel::setInterval(int interval)
{
    if (m_interval != interval) {
        m_interval = interval;
        m_timer->setInterval(interval);
    }
}

void MarqueeLabel::enMouseHoverStop(bool en)
{
    if (m_enmouseHoverStop != en) {
        m_enmouseHoverStop = en;
    }
}

void MarqueeLabel::setForeground(const QColor &foreground)
{
    if(m_foreground != foreground) {
        m_foreground = foreground;
        QPalette pt = m_labText->palette();
        pt.setColor(QPalette::WindowText, foreground);
        m_labText->setPalette(pt);
    }
}

void MarqueeLabel::setBackground(const QColor &background)
{
    if (m_background != background) {
        m_background = background;
        QPalette pt = palette();
        pt.setColor(QPalette::Window, background);
        setPalette(pt);
    }
}

void MarqueeLabel::setMoveStyle(MarqueeLabel::MoveStyle moveStyle)
{
    if (m_moveStyle != moveStyle) {
       m_moveStyle = moveStyle;
    }
}

QSize MarqueeLabel::sizeHint() const
{
    qDebug() << "sizehint" << endl;
    return QSize(200, 30);
}

void MarqueeLabel::timeout()
{
    if (m_enmouseHoverStop && m_mouseHover) {
        return;
    }

    if (m_moveStyle == MoveStyleLeftAndRight) {
        if(m_textwidth <= width()) {
            if(m_initX + m_textwidth > width()) {
                m_moveRight = false;
            } else if(m_initX <= 0) {
                m_moveRight = true;
            }
        } else {
            if (m_initX == 10) {
                m_moveRight = false;
            } else if (m_initX <= width() - m_textwidth - 10) {
                m_moveRight = true;
            }
        }

        if (m_moveRight) {
            m_initX += m_step;
        } else {
            m_initX -= m_step;
        }
        m_labText->move(m_initX, m_initY);
    } else if (m_moveStyle == MoveStyleLeftToRight) {
        if(m_initX > width()) {
            m_initX = -m_textwidth;
        }

        m_initX += m_step;
        m_labText->move(m_initX, m_initY);
    } else if (m_moveStyle == MoveStyleRightToLeft) {
        if (m_initX < -m_textwidth) {
            m_initX = width();
        }

        m_initX -= m_step;
        m_labText->move(m_initX, m_initY);
    }
}

void MarqueeLabel::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    //qDebug() << "resizeevent" << width() << height() << endl;
    //qDebug() << "labelresize" << m_labText->width() << m_labText->height() << endl;
    m_initY = (height() - m_textheight) / 2;
}

void MarqueeLabel::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    m_mouseHover = true;
    if (m_enmouseHoverStop) {
        QFont font = m_labText->font();
        font.setUnderline(true);
        m_labText->setFont(font);
        setCursor(Qt::PointingHandCursor);
    }
}

void MarqueeLabel::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    m_mouseHover = false;
    if (m_enmouseHoverStop) {
        QFont font = m_labText->font();
        font.setUnderline(false);
        m_labText->setFont(font);
        setCursor(Qt::ArrowCursor);
    }
}

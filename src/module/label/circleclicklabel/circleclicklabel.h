#ifndef CIRCLECLICKLABEL_H
#define CIRCLECLICKLABEL_H

/* =================================================
 * 该模块实现了单击后出现圆环水波的控件,可以被其它控件继承来继续
 * 实现相关功能
 ================================================= */

#include <QWidget>


class  CircleClickLabel : public QWidget
{
    Q_OBJECT
public:
    explicit CircleClickLabel(QWidget *parent = nullptr);
    ~CircleClickLabel();

    virtual QSize sizeHint() const override;

protected Q_SLOTS:
    virtual void updateRender();

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;

    bool m_circleOn;
    QTimer *m_circleTimer;
    int m_crValue;
    QPoint m_pos;

};

#endif // CIRCLECLICKLABEL_H

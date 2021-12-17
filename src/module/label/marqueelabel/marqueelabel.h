#ifndef MARQUEELABEL_H
#define MARQUEELABEL_H


#include <QLabel>


class  MarqueeLabel : public QWidget
{
    Q_OBJECT
public:
    enum MoveStyle {
        MoveStyleLeftAndRight = 0,
        MoveStyleLeftToRight = 1,
        MoveStyleRightToLeft = 2
    };

    explicit MarqueeLabel(QWidget *parent = nullptr);
    ~MarqueeLabel();

    void initWidget();

    void setText(const QString &text);

    void clearText();

    void setStep(int step);

    void setInterval(int interval);

    void enMouseHoverStop(bool en);

    void setForeground(const QColor &foreground);

    void setBackground(const QColor &background);

    void setMoveStyle(MoveStyle moveStyle);

    virtual QSize sizeHint() const override;

private Q_SLOTS:
    void timeout();

protected:
    virtual void resizeEvent(QResizeEvent *event) override;

    virtual void enterEvent(QEvent *event) override;

    virtual void leaveEvent(QEvent *event) override;

private:
    QString m_text;
    int m_step, m_interval;
    bool m_enmouseHoverStop, m_mouseHover, m_moveRight;
    int m_initX, m_initY;
    int m_textwidth, m_textheight;
    QLabel *m_labText;
    QTimer *m_timer;

    QColor m_foreground, m_background;

    MoveStyle m_moveStyle;

};

#endif // TTKMARQUEELABEL_H

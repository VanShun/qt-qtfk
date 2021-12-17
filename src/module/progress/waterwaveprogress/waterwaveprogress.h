#ifndef WATERWAVEPROGRESS_H
#define WATERWAVEPROGRESS_H

/*****************************************************
**该模块实现了一个水波形容器的进度条显示控件
**
**
*****************************************************/
#include <QWidget>


class  WaterWaveProgress : public QWidget
{
    Q_OBJECT
public:
    explicit WaterWaveProgress(QWidget *parent = nullptr);

    virtual ~WaterWaveProgress();

    void setRange(int minValue, int maxValue);

    void setMinValue(int minValue);

    void setMaxValue(int maxValue);

    void setValue(int value);

    void setWaterDensity(int waterDensity);

    void setWaterHeight(double waterHeight);

    void setOffset(int offset);

    void setBorderWidth(double borderWidth);

    void setBgColor(const QColor &bgColor);

    virtual QSize sizeHint() const override;

protected:
    virtual void paintEvent(QPaintEvent *event) override;

private:
    void drawValue(QPainter *painter);

    void drawText(QPainter *painter);

private Q_SLOTS:
    void timeout();

private:
    uint8_t m_value, m_minValue, m_maxValue, m_waterDensity, m_borderWidth;
    double m_waterHeight, m_offset;
    QColor m_bgColor;
    QTimer *m_timer;

};

#endif // TTKWAVEPROGRESSWIDGET_H

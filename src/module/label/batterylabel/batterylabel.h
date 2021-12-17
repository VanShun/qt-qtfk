#ifndef BATTERYLABEL_H
#define BATTERYLABEL_H

#include <QWidget>


class  BatteryLabel : public QWidget
{
    Q_OBJECT    
public:
    explicit BatteryLabel(QWidget *parent = nullptr);

    virtual ~BatteryLabel();

    void setRange(double minValue, double maxValue);

    void setMinValue(double minValue);

    void setMaxValue(double maxValue);

    void setValue(double value);

    void setAlarmValue(double alarmValue);

    bool isCharging();

    void setChargingstat(bool chg);

    void setBorderColor(const QColor &borderColor);

    void setAlarmColor(const QColor &alarmColor);

    void setNormalColor(const QColor &normalColor);

    void setSuffColor(const QColor &suffColor);

    virtual QSize sizeHint() const override;

protected:
    virtual void paintEvent(QPaintEvent *event) override;

    void drawBorder(QPainter *painter);

    void drawBackground(QPainter *painter);

    void drawCharging(QPainter *painter);

private:    
    double m_minValue, m_maxValue, m_alarmValue, m_suffValue, m_currentValue;

    /* 边框、低电量、正常电量、充足电量颜色 */
    QColor m_borderColor, m_alarmColor, m_normalColor, m_suffColor;

    bool m_charging; //是否在充电
    QRectF m_batteryRect;

};

#endif // BATTERYLABEL_H

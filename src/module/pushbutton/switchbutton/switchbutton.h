#ifndef SWITCHBUTTON_H
#define SWITCHBUTTON_H

#include <QPushButton>

class Switchbutton : public QPushButton
{
    Q_OBJECT
public:
    explicit Switchbutton(QWidget *parent = 0);

    //获取当前选中状态
    bool GetCheck() const {return isCheck;}

    //设置当前选中状态
    void SetCheck(bool isCheck);

private:
    bool isCheck;
    QString styleOn;
    QString styleOff;

private slots:
    void ChangeOnOff();
};

#endif // SWITCHBUTTON_H

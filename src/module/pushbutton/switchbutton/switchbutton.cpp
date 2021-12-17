#include "switchbutton.h"

Switchbutton::Switchbutton(QWidget *parent): QPushButton(parent)
{
    setCursor(QCursor(Qt::PointingHandCursor));
    isCheck = false;

    styleOn = "border-image: url(:/images/btncheckon.png); border: 0px;";
    styleOff = "border-image: url(:/images/btncheckoff.png); border: 0px;";

    //setFixedSize(80,30);            //不允许变化大小
    setStyleSheet(styleOff);        //设置当前样式
    connect(this, SIGNAL(clicked()), this, SLOT(ChangeOnOff()));
    this->setFlat(true);
}

void Switchbutton::ChangeOnOff()
{
    if (isCheck) {
        setStyleSheet(styleOff);
        isCheck = false;
    } else {
        setStyleSheet(styleOn);
        isCheck = true;
    }
}

//设置当前选中状态
void Switchbutton::SetCheck(bool isCheck)
{
    if (this->isCheck != isCheck) {
        this->isCheck = !isCheck;
        ChangeOnOff();
    }
}


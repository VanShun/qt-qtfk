/********************************************************************************
** Form generated from reading UI file 'mainwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWIDGET_H
#define UI_MAINWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <batterylabel.h>
#include <circleclicklabel.h>
#include <ipedit.h>
#include <loadingprogress.h>
#include <marqueelabel.h>
#include <rgradientlabel.h>
#include <switchbutton.h>
#include <waterwaveprogress.h>

QT_BEGIN_NAMESPACE

class Ui_MainWidget
{
public:
    Switchbutton *pushButton;
    WaterWaveProgress *widget;
    MarqueeLabel *widget_2;
    CircleClickLabel *widget_3;
    BatteryLabel *widget_4;
    RGradientLabel *widget_5;
    IpEdit *widget_6;
    LoadingProgress *widget_7;

    void setupUi(QWidget *MainWidget)
    {
        if (MainWidget->objectName().isEmpty())
            MainWidget->setObjectName(QString::fromUtf8("MainWidget"));
        MainWidget->resize(958, 466);
        pushButton = new Switchbutton(MainWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(30, 10, 91, 41));
        widget = new WaterWaveProgress(MainWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(30, 60, 171, 201));
        widget_2 = new MarqueeLabel(MainWidget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setGeometry(QRect(250, 10, 361, 61));
        widget_3 = new CircleClickLabel(MainWidget);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget_3->setGeometry(QRect(810, 320, 141, 101));
        widget_3->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 255, 255);"));
        widget_4 = new BatteryLabel(MainWidget);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        widget_4->setGeometry(QRect(250, 80, 161, 71));
        widget_5 = new RGradientLabel(MainWidget);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        widget_5->setGeometry(QRect(39, 269, 151, 121));
        widget_6 = new IpEdit(MainWidget);
        widget_6->setObjectName(QString::fromUtf8("widget_6"));
        widget_6->setGeometry(QRect(250, 180, 171, 31));
        widget_7 = new LoadingProgress(MainWidget);
        widget_7->setObjectName(QString::fromUtf8("widget_7"));
        widget_7->setGeometry(QRect(229, 229, 91, 71));

        retranslateUi(MainWidget);

        QMetaObject::connectSlotsByName(MainWidget);
    } // setupUi

    void retranslateUi(QWidget *MainWidget)
    {
        MainWidget->setWindowTitle(QApplication::translate("MainWidget", "Form", nullptr));
        pushButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWidget: public Ui_MainWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIDGET_H

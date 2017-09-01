/********************************************************************************
** Form generated from reading UI file 'KSJSCZDemoMainWindow.ui'
**
** Created: Fri Sep 1 16:40:35 2017
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KSJSCZDEMOMAINWINDOW_H
#define UI_KSJSCZDEMOMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_KSJSCZDemoMainWindow
{
public:
    QPushButton *StartCapturePushButton;
    QPushButton *StopCapturePushButton;
    QLabel *InfoLabel;
    QCheckBox *ThresholdCheckBox;
    QLabel *StaticText_4;
    QSpinBox *ExpLinesSpinBox;
    QPushButton *ScobelPushButton;

    void setupUi(QDialog *KSJSCZDemoMainWindow)
    {
        if (KSJSCZDemoMainWindow->objectName().isEmpty())
            KSJSCZDemoMainWindow->setObjectName(QString::fromUtf8("KSJSCZDemoMainWindow"));
        KSJSCZDemoMainWindow->resize(1266, 795);
        StartCapturePushButton = new QPushButton(KSJSCZDemoMainWindow);
        StartCapturePushButton->setObjectName(QString::fromUtf8("StartCapturePushButton"));
        StartCapturePushButton->setGeometry(QRect(1060, 20, 79, 31));
        StopCapturePushButton = new QPushButton(KSJSCZDemoMainWindow);
        StopCapturePushButton->setObjectName(QString::fromUtf8("StopCapturePushButton"));
        StopCapturePushButton->setGeometry(QRect(1170, 20, 79, 31));
        InfoLabel = new QLabel(KSJSCZDemoMainWindow);
        InfoLabel->setObjectName(QString::fromUtf8("InfoLabel"));
        InfoLabel->setGeometry(QRect(1070, 330, 131, 20));
        ThresholdCheckBox = new QCheckBox(KSJSCZDemoMainWindow);
        ThresholdCheckBox->setObjectName(QString::fromUtf8("ThresholdCheckBox"));
        ThresholdCheckBox->setGeometry(QRect(1060, 120, 91, 20));
        StaticText_4 = new QLabel(KSJSCZDemoMainWindow);
        StaticText_4->setObjectName(QString::fromUtf8("StaticText_4"));
        StaticText_4->setGeometry(QRect(1060, 80, 101, 16));
        ExpLinesSpinBox = new QSpinBox(KSJSCZDemoMainWindow);
        ExpLinesSpinBox->setObjectName(QString::fromUtf8("ExpLinesSpinBox"));
        ExpLinesSpinBox->setEnabled(true);
        ExpLinesSpinBox->setGeometry(QRect(1178, 78, 63, 25));
        ExpLinesSpinBox->setReadOnly(false);
        ExpLinesSpinBox->setMinimum(2);
        ExpLinesSpinBox->setMaximum(99999);
        ScobelPushButton = new QPushButton(KSJSCZDemoMainWindow);
        ScobelPushButton->setObjectName(QString::fromUtf8("ScobelPushButton"));
        ScobelPushButton->setGeometry(QRect(1060, 180, 79, 31));

        retranslateUi(KSJSCZDemoMainWindow);

        QMetaObject::connectSlotsByName(KSJSCZDemoMainWindow);
    } // setupUi

    void retranslateUi(QDialog *KSJSCZDemoMainWindow)
    {
        KSJSCZDemoMainWindow->setWindowTitle(QApplication::translate("KSJSCZDemoMainWindow", "Dialog", 0, QApplication::UnicodeUTF8));
        StartCapturePushButton->setText(QApplication::translate("KSJSCZDemoMainWindow", "Start", 0, QApplication::UnicodeUTF8));
        StopCapturePushButton->setText(QApplication::translate("KSJSCZDemoMainWindow", "Stop", 0, QApplication::UnicodeUTF8));
        InfoLabel->setText(QApplication::translate("KSJSCZDemoMainWindow", "....", 0, QApplication::UnicodeUTF8));
        ThresholdCheckBox->setText(QApplication::translate("KSJSCZDemoMainWindow", "Threshold", 0, QApplication::UnicodeUTF8));
        StaticText_4->setText(QApplication::translate("KSJSCZDemoMainWindow", "Exposure Lines:", 0, QApplication::UnicodeUTF8));
        ScobelPushButton->setText(QApplication::translate("KSJSCZDemoMainWindow", "Scobel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class KSJSCZDemoMainWindow: public Ui_KSJSCZDemoMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KSJSCZDEMOMAINWINDOW_H

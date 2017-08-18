/********************************************************************************
** Form generated from reading UI file 'KSJSCZDemoMainWindow.ui'
**
** Created: Fri Aug 18 12:17:50 2017
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
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QScrollBar>

QT_BEGIN_NAMESPACE

class Ui_KSJSCZDemoMainWindow
{
public:
    QPushButton *StartCapturePushButton;
    QPushButton *StopCapturePushButton;
    QLabel *InfoLabel;
    QScrollBar *HorizontalScrollBar;
    QScrollBar *VerticalScrollBar;

    void setupUi(QDialog *KSJSCZDemoMainWindow)
    {
        if (KSJSCZDemoMainWindow->objectName().isEmpty())
            KSJSCZDemoMainWindow->setObjectName(QString::fromUtf8("KSJSCZDemoMainWindow"));
        KSJSCZDemoMainWindow->resize(1266, 795);
        StartCapturePushButton = new QPushButton(KSJSCZDemoMainWindow);
        StartCapturePushButton->setObjectName(QString::fromUtf8("StartCapturePushButton"));
        StartCapturePushButton->setGeometry(QRect(1170, 10, 79, 31));
        StopCapturePushButton = new QPushButton(KSJSCZDemoMainWindow);
        StopCapturePushButton->setObjectName(QString::fromUtf8("StopCapturePushButton"));
        StopCapturePushButton->setGeometry(QRect(1170, 60, 79, 31));
        InfoLabel = new QLabel(KSJSCZDemoMainWindow);
        InfoLabel->setObjectName(QString::fromUtf8("InfoLabel"));
        InfoLabel->setGeometry(QRect(1120, 150, 131, 20));
        HorizontalScrollBar = new QScrollBar(KSJSCZDemoMainWindow);
        HorizontalScrollBar->setObjectName(QString::fromUtf8("HorizontalScrollBar"));
        HorizontalScrollBar->setGeometry(QRect(1080, 760, 160, 16));
        HorizontalScrollBar->setOrientation(Qt::Horizontal);
        VerticalScrollBar = new QScrollBar(KSJSCZDemoMainWindow);
        VerticalScrollBar->setObjectName(QString::fromUtf8("VerticalScrollBar"));
        VerticalScrollBar->setGeometry(QRect(1140, 460, 16, 160));
        VerticalScrollBar->setOrientation(Qt::Vertical);

        retranslateUi(KSJSCZDemoMainWindow);

        QMetaObject::connectSlotsByName(KSJSCZDemoMainWindow);
    } // setupUi

    void retranslateUi(QDialog *KSJSCZDemoMainWindow)
    {
        KSJSCZDemoMainWindow->setWindowTitle(QApplication::translate("KSJSCZDemoMainWindow", "Dialog", 0, QApplication::UnicodeUTF8));
        StartCapturePushButton->setText(QApplication::translate("KSJSCZDemoMainWindow", "Start", 0, QApplication::UnicodeUTF8));
        StopCapturePushButton->setText(QApplication::translate("KSJSCZDemoMainWindow", "Stop", 0, QApplication::UnicodeUTF8));
        InfoLabel->setText(QApplication::translate("KSJSCZDemoMainWindow", "....", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class KSJSCZDemoMainWindow: public Ui_KSJSCZDemoMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KSJSCZDEMOMAINWINDOW_H

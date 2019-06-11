/********************************************************************************
** Form generated from reading UI file 'KSJSCZDemoMainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KSJSCZDEMOMAINWINDOW_H
#define UI_KSJSCZDEMOMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollBar>

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
            KSJSCZDemoMainWindow->setObjectName(QStringLiteral("KSJSCZDemoMainWindow"));
        KSJSCZDemoMainWindow->resize(1266, 795);
        StartCapturePushButton = new QPushButton(KSJSCZDemoMainWindow);
        StartCapturePushButton->setObjectName(QStringLiteral("StartCapturePushButton"));
        StartCapturePushButton->setGeometry(QRect(1170, 10, 79, 31));
        StopCapturePushButton = new QPushButton(KSJSCZDemoMainWindow);
        StopCapturePushButton->setObjectName(QStringLiteral("StopCapturePushButton"));
        StopCapturePushButton->setGeometry(QRect(1170, 60, 79, 31));
        InfoLabel = new QLabel(KSJSCZDemoMainWindow);
        InfoLabel->setObjectName(QStringLiteral("InfoLabel"));
        InfoLabel->setGeometry(QRect(1120, 150, 131, 20));
        HorizontalScrollBar = new QScrollBar(KSJSCZDemoMainWindow);
        HorizontalScrollBar->setObjectName(QStringLiteral("HorizontalScrollBar"));
        HorizontalScrollBar->setGeometry(QRect(1080, 760, 160, 16));
        HorizontalScrollBar->setOrientation(Qt::Horizontal);
        VerticalScrollBar = new QScrollBar(KSJSCZDemoMainWindow);
        VerticalScrollBar->setObjectName(QStringLiteral("VerticalScrollBar"));
        VerticalScrollBar->setGeometry(QRect(1140, 460, 16, 160));
        VerticalScrollBar->setOrientation(Qt::Vertical);

        retranslateUi(KSJSCZDemoMainWindow);

        QMetaObject::connectSlotsByName(KSJSCZDemoMainWindow);
    } // setupUi

    void retranslateUi(QDialog *KSJSCZDemoMainWindow)
    {
        KSJSCZDemoMainWindow->setWindowTitle(QApplication::translate("KSJSCZDemoMainWindow", "Dialog", Q_NULLPTR));
        StartCapturePushButton->setText(QApplication::translate("KSJSCZDemoMainWindow", "Start", Q_NULLPTR));
        StopCapturePushButton->setText(QApplication::translate("KSJSCZDemoMainWindow", "Stop", Q_NULLPTR));
        InfoLabel->setText(QApplication::translate("KSJSCZDemoMainWindow", "....", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class KSJSCZDemoMainWindow: public Ui_KSJSCZDemoMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KSJSCZDEMOMAINWINDOW_H

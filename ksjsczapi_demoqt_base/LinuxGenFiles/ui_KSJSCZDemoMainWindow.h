/********************************************************************************
** Form generated from reading UI file 'KSJSCZDemoMainWindow.ui'
**
** Created: Tue May 23 13:19:26 2017
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
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_KSJSCZDemoMainWindow
{
public:
    QGroupBox *UserInputGroupBox;
    QLabel *StaticText_1;
    QLabel *StaticText_2;
    QLabel *StaticText_ExpostureTimeRange;
    QLabel *StaticText_ExpostureLinesRange;
    QLabel *StaticText_3;
    QLabel *StaticText_4;
    QSpinBox *ExpLinesSpinBox;
    QLabel *StaticText_5;
    QLabel *StaticText_6;
    QLabel *StaticText_GainRange;
    QSpinBox *GainSpinBox;
    QGroupBox *FieldOfViewGroupBox;
    QLabel *StaticText_7;
    QLabel *StaticText_8;
    QLabel *StaticText_9;
    QLabel *StaticText_10;
    QSpinBox *ColStartSpinBox;
    QSpinBox *ColSizeSpinBox;
    QSpinBox *RowStartSpinBox;
    QSpinBox *RowSizeSpinBox;
    QDoubleSpinBox *ExpTimeSpinBox;
    QComboBox *TriggerModeComBox;
    QLabel *StaticText_11;
    QGroupBox *RegisterGroupBox;
    QSpinBox *RegValueSpinBox;
    QLabel *StaticText_16;
    QLabel *StaticText_17;
    QSpinBox *RegAddressSpinBox;
    QPushButton *ReadRegPushButton;
    QPushButton *WriteRegPushButton;
    QLabel *StaticText_RegAddress;
    QLabel *StaticText_RegValue;
    QLabel *StaticText_Version;
    QPushButton *StartCapturePushButton;

    void setupUi(QDialog *KSJSCZDemoMainWindow)
    {
        if (KSJSCZDemoMainWindow->objectName().isEmpty())
            KSJSCZDemoMainWindow->setObjectName(QString::fromUtf8("KSJSCZDemoMainWindow"));
        KSJSCZDemoMainWindow->resize(1266, 700);
        UserInputGroupBox = new QGroupBox(KSJSCZDemoMainWindow);
        UserInputGroupBox->setObjectName(QString::fromUtf8("UserInputGroupBox"));
        UserInputGroupBox->setGeometry(QRect(814, 16, 447, 465));
        StaticText_1 = new QLabel(UserInputGroupBox);
        StaticText_1->setObjectName(QString::fromUtf8("StaticText_1"));
        StaticText_1->setGeometry(QRect(12, 72, 115, 16));
        StaticText_2 = new QLabel(UserInputGroupBox);
        StaticText_2->setObjectName(QString::fromUtf8("StaticText_2"));
        StaticText_2->setGeometry(QRect(222, 74, 69, 16));
        StaticText_2->setFrameShape(QFrame::NoFrame);
        StaticText_ExpostureTimeRange = new QLabel(UserInputGroupBox);
        StaticText_ExpostureTimeRange->setObjectName(QString::fromUtf8("StaticText_ExpostureTimeRange"));
        StaticText_ExpostureTimeRange->setGeometry(QRect(300, 76, 133, 16));
        StaticText_ExpostureTimeRange->setFrameShape(QFrame::StyledPanel);
        StaticText_ExpostureLinesRange = new QLabel(UserInputGroupBox);
        StaticText_ExpostureLinesRange->setObjectName(QString::fromUtf8("StaticText_ExpostureLinesRange"));
        StaticText_ExpostureLinesRange->setGeometry(QRect(300, 110, 133, 16));
        StaticText_ExpostureLinesRange->setFrameShape(QFrame::StyledPanel);
        StaticText_3 = new QLabel(UserInputGroupBox);
        StaticText_3->setObjectName(QString::fromUtf8("StaticText_3"));
        StaticText_3->setGeometry(QRect(222, 108, 69, 16));
        StaticText_3->setFrameShape(QFrame::NoFrame);
        StaticText_4 = new QLabel(UserInputGroupBox);
        StaticText_4->setObjectName(QString::fromUtf8("StaticText_4"));
        StaticText_4->setGeometry(QRect(12, 106, 115, 16));
        ExpLinesSpinBox = new QSpinBox(UserInputGroupBox);
        ExpLinesSpinBox->setObjectName(QString::fromUtf8("ExpLinesSpinBox"));
        ExpLinesSpinBox->setGeometry(QRect(130, 104, 77, 25));
        ExpLinesSpinBox->setMaximum(99999);
        StaticText_5 = new QLabel(UserInputGroupBox);
        StaticText_5->setObjectName(QString::fromUtf8("StaticText_5"));
        StaticText_5->setGeometry(QRect(12, 142, 115, 16));
        StaticText_6 = new QLabel(UserInputGroupBox);
        StaticText_6->setObjectName(QString::fromUtf8("StaticText_6"));
        StaticText_6->setGeometry(QRect(222, 144, 69, 16));
        StaticText_6->setFrameShape(QFrame::NoFrame);
        StaticText_GainRange = new QLabel(UserInputGroupBox);
        StaticText_GainRange->setObjectName(QString::fromUtf8("StaticText_GainRange"));
        StaticText_GainRange->setGeometry(QRect(300, 146, 133, 16));
        StaticText_GainRange->setFrameShape(QFrame::StyledPanel);
        GainSpinBox = new QSpinBox(UserInputGroupBox);
        GainSpinBox->setObjectName(QString::fromUtf8("GainSpinBox"));
        GainSpinBox->setGeometry(QRect(130, 140, 77, 25));
        GainSpinBox->setMaximum(99999);
        FieldOfViewGroupBox = new QGroupBox(UserInputGroupBox);
        FieldOfViewGroupBox->setObjectName(QString::fromUtf8("FieldOfViewGroupBox"));
        FieldOfViewGroupBox->setGeometry(QRect(10, 170, 423, 83));
        StaticText_7 = new QLabel(FieldOfViewGroupBox);
        StaticText_7->setObjectName(QString::fromUtf8("StaticText_7"));
        StaticText_7->setGeometry(QRect(24, 24, 65, 16));
        StaticText_7->setFrameShape(QFrame::NoFrame);
        StaticText_8 = new QLabel(FieldOfViewGroupBox);
        StaticText_8->setObjectName(QString::fromUtf8("StaticText_8"));
        StaticText_8->setGeometry(QRect(24, 54, 65, 16));
        StaticText_8->setFrameShape(QFrame::NoFrame);
        StaticText_9 = new QLabel(FieldOfViewGroupBox);
        StaticText_9->setObjectName(QString::fromUtf8("StaticText_9"));
        StaticText_9->setGeometry(QRect(236, 54, 65, 16));
        StaticText_9->setFrameShape(QFrame::NoFrame);
        StaticText_10 = new QLabel(FieldOfViewGroupBox);
        StaticText_10->setObjectName(QString::fromUtf8("StaticText_10"));
        StaticText_10->setGeometry(QRect(236, 24, 65, 16));
        StaticText_10->setFrameShape(QFrame::NoFrame);
        ColStartSpinBox = new QSpinBox(FieldOfViewGroupBox);
        ColStartSpinBox->setObjectName(QString::fromUtf8("ColStartSpinBox"));
        ColStartSpinBox->setGeometry(QRect(96, 20, 77, 25));
        ColStartSpinBox->setMaximum(99999);
        ColSizeSpinBox = new QSpinBox(FieldOfViewGroupBox);
        ColSizeSpinBox->setObjectName(QString::fromUtf8("ColSizeSpinBox"));
        ColSizeSpinBox->setGeometry(QRect(96, 50, 77, 25));
        ColSizeSpinBox->setMaximum(99999);
        RowStartSpinBox = new QSpinBox(FieldOfViewGroupBox);
        RowStartSpinBox->setObjectName(QString::fromUtf8("RowStartSpinBox"));
        RowStartSpinBox->setGeometry(QRect(310, 20, 77, 25));
        RowStartSpinBox->setMaximum(99999);
        RowSizeSpinBox = new QSpinBox(FieldOfViewGroupBox);
        RowSizeSpinBox->setObjectName(QString::fromUtf8("RowSizeSpinBox"));
        RowSizeSpinBox->setGeometry(QRect(310, 50, 77, 25));
        RowSizeSpinBox->setMaximum(99999);
        ExpTimeSpinBox = new QDoubleSpinBox(UserInputGroupBox);
        ExpTimeSpinBox->setObjectName(QString::fromUtf8("ExpTimeSpinBox"));
        ExpTimeSpinBox->setGeometry(QRect(130, 68, 77, 25));
        ExpTimeSpinBox->setSingleStep(0.1);
        TriggerModeComBox = new QComboBox(UserInputGroupBox);
        TriggerModeComBox->setObjectName(QString::fromUtf8("TriggerModeComBox"));
        TriggerModeComBox->setGeometry(QRect(130, 32, 303, 22));
        StaticText_11 = new QLabel(UserInputGroupBox);
        StaticText_11->setObjectName(QString::fromUtf8("StaticText_11"));
        StaticText_11->setGeometry(QRect(16, 34, 87, 16));
        RegisterGroupBox = new QGroupBox(UserInputGroupBox);
        RegisterGroupBox->setObjectName(QString::fromUtf8("RegisterGroupBox"));
        RegisterGroupBox->setGeometry(QRect(10, 272, 425, 97));
        RegValueSpinBox = new QSpinBox(RegisterGroupBox);
        RegValueSpinBox->setObjectName(QString::fromUtf8("RegValueSpinBox"));
        RegValueSpinBox->setGeometry(QRect(74, 60, 77, 25));
        RegValueSpinBox->setMaximum(999999);
        RegValueSpinBox->setSingleStep(1);
        StaticText_16 = new QLabel(RegisterGroupBox);
        StaticText_16->setObjectName(QString::fromUtf8("StaticText_16"));
        StaticText_16->setGeometry(QRect(16, 28, 57, 16));
        StaticText_16->setFrameShape(QFrame::NoFrame);
        StaticText_17 = new QLabel(RegisterGroupBox);
        StaticText_17->setObjectName(QString::fromUtf8("StaticText_17"));
        StaticText_17->setGeometry(QRect(16, 64, 43, 16));
        StaticText_17->setFrameShape(QFrame::NoFrame);
        RegAddressSpinBox = new QSpinBox(RegisterGroupBox);
        RegAddressSpinBox->setObjectName(QString::fromUtf8("RegAddressSpinBox"));
        RegAddressSpinBox->setGeometry(QRect(74, 24, 77, 25));
        RegAddressSpinBox->setMaximum(99999);
        RegAddressSpinBox->setSingleStep(4);
        ReadRegPushButton = new QPushButton(RegisterGroupBox);
        ReadRegPushButton->setObjectName(QString::fromUtf8("ReadRegPushButton"));
        ReadRegPushButton->setGeometry(QRect(268, 34, 63, 33));
        WriteRegPushButton = new QPushButton(RegisterGroupBox);
        WriteRegPushButton->setObjectName(QString::fromUtf8("WriteRegPushButton"));
        WriteRegPushButton->setGeometry(QRect(352, 34, 63, 33));
        StaticText_RegAddress = new QLabel(RegisterGroupBox);
        StaticText_RegAddress->setObjectName(QString::fromUtf8("StaticText_RegAddress"));
        StaticText_RegAddress->setGeometry(QRect(156, 30, 61, 16));
        StaticText_RegAddress->setFrameShape(QFrame::StyledPanel);
        StaticText_RegValue = new QLabel(RegisterGroupBox);
        StaticText_RegValue->setObjectName(QString::fromUtf8("StaticText_RegValue"));
        StaticText_RegValue->setGeometry(QRect(156, 66, 99, 16));
        StaticText_RegValue->setFrameShape(QFrame::StyledPanel);
        StaticText_Version = new QLabel(UserInputGroupBox);
        StaticText_Version->setObjectName(QString::fromUtf8("StaticText_Version"));
        StaticText_Version->setGeometry(QRect(12, 440, 209, 16));
        StaticText_Version->setFrameShape(QFrame::StyledPanel);
        StartCapturePushButton = new QPushButton(UserInputGroupBox);
        StartCapturePushButton->setObjectName(QString::fromUtf8("StartCapturePushButton"));
        StartCapturePushButton->setGeometry(QRect(12, 388, 113, 33));

        retranslateUi(KSJSCZDemoMainWindow);

        QMetaObject::connectSlotsByName(KSJSCZDemoMainWindow);
    } // setupUi

    void retranslateUi(QDialog *KSJSCZDemoMainWindow)
    {
        KSJSCZDemoMainWindow->setWindowTitle(QApplication::translate("KSJSCZDemoMainWindow", "Dialog", 0, QApplication::UnicodeUTF8));
        UserInputGroupBox->setTitle(QApplication::translate("KSJSCZDemoMainWindow", "Camera Setting", 0, QApplication::UnicodeUTF8));
        StaticText_1->setText(QApplication::translate("KSJSCZDemoMainWindow", "Exposure Time(ms):", 0, QApplication::UnicodeUTF8));
        StaticText_2->setText(QApplication::translate("KSJSCZDemoMainWindow", "Range(ms):", 0, QApplication::UnicodeUTF8));
        StaticText_ExpostureTimeRange->setText(QApplication::translate("KSJSCZDemoMainWindow", "ExpostureTimeRange", 0, QApplication::UnicodeUTF8));
        StaticText_ExpostureLinesRange->setText(QApplication::translate("KSJSCZDemoMainWindow", "ExposureLinesRange", 0, QApplication::UnicodeUTF8));
        StaticText_3->setText(QApplication::translate("KSJSCZDemoMainWindow", "Range:", 0, QApplication::UnicodeUTF8));
        StaticText_4->setText(QApplication::translate("KSJSCZDemoMainWindow", "Exposure Lines:", 0, QApplication::UnicodeUTF8));
        StaticText_5->setText(QApplication::translate("KSJSCZDemoMainWindow", "Gain:", 0, QApplication::UnicodeUTF8));
        StaticText_6->setText(QApplication::translate("KSJSCZDemoMainWindow", "Range:", 0, QApplication::UnicodeUTF8));
        StaticText_GainRange->setText(QApplication::translate("KSJSCZDemoMainWindow", "ExposureLinesRange", 0, QApplication::UnicodeUTF8));
        FieldOfViewGroupBox->setTitle(QApplication::translate("KSJSCZDemoMainWindow", "Field of View", 0, QApplication::UnicodeUTF8));
        StaticText_7->setText(QApplication::translate("KSJSCZDemoMainWindow", "Col Start:", 0, QApplication::UnicodeUTF8));
        StaticText_8->setText(QApplication::translate("KSJSCZDemoMainWindow", "Col Size:", 0, QApplication::UnicodeUTF8));
        StaticText_9->setText(QApplication::translate("KSJSCZDemoMainWindow", "Row Size:", 0, QApplication::UnicodeUTF8));
        StaticText_10->setText(QApplication::translate("KSJSCZDemoMainWindow", "Row Start:", 0, QApplication::UnicodeUTF8));
        StaticText_11->setText(QApplication::translate("KSJSCZDemoMainWindow", "Trigger Mode", 0, QApplication::UnicodeUTF8));
        RegisterGroupBox->setTitle(QApplication::translate("KSJSCZDemoMainWindow", "Register", 0, QApplication::UnicodeUTF8));
        StaticText_16->setText(QApplication::translate("KSJSCZDemoMainWindow", "Address:", 0, QApplication::UnicodeUTF8));
        StaticText_17->setText(QApplication::translate("KSJSCZDemoMainWindow", "Value:", 0, QApplication::UnicodeUTF8));
        ReadRegPushButton->setText(QApplication::translate("KSJSCZDemoMainWindow", "Read", 0, QApplication::UnicodeUTF8));
        WriteRegPushButton->setText(QApplication::translate("KSJSCZDemoMainWindow", "Write", 0, QApplication::UnicodeUTF8));
        StaticText_RegAddress->setText(QApplication::translate("KSJSCZDemoMainWindow", "0x0000", 0, QApplication::UnicodeUTF8));
        StaticText_RegValue->setText(QApplication::translate("KSJSCZDemoMainWindow", "0x00000000", 0, QApplication::UnicodeUTF8));
        StaticText_Version->setText(QApplication::translate("KSJSCZDemoMainWindow", "Ver: 0.0.0.0", 0, QApplication::UnicodeUTF8));
        StartCapturePushButton->setText(QApplication::translate("KSJSCZDemoMainWindow", "Start", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class KSJSCZDemoMainWindow: public Ui_KSJSCZDemoMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KSJSCZDEMOMAINWINDOW_H

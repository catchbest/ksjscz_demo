/********************************************************************************
** Form generated from reading UI file 'KSJSCZDemoMainWindow.ui'
**
** Created: Fri Aug 18 12:21:55 2017
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
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
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
    QPushButton *SetFovPushButton;
    QDoubleSpinBox *ExpTimeSpinBox;
    QComboBox *TriggerModeComBox;
    QLabel *StaticText_11;
    QLabel *StaticText_Version;
    QPushButton *StartCapturePushButton;
    QLabel *StaticText_12;
    QSpinBox *TriggerDelaySpinBox;
    QLabel *StaticText_13;
    QLabel *StaticText_TriggerDelay;
    QLabel *StaticText_Count;
    QGroupBox *groupBox;
    QCheckBox *ParseQRCODECheckBox;
    QCheckBox *ParseUPCECheckBox;
    QCheckBox *ParsePDF417CheckBox;
    QCheckBox *ParseEAN8CheckBox;
    QCheckBox *ParseISBN13CheckBox;
    QCheckBox *ParseUPCACheckBox;
    QCheckBox *ParseCODE39CheckBox;
    QCheckBox *ParseISBN10CheckBox;
    QCheckBox *ParseCODE128CheckBox;
    QCheckBox *ParseEAN13CheckBox;
    QCheckBox *ParseI25CheckBox;
    QSpinBox *DensitySpinBox;
    QLabel *StaticText_14;
    QLabel *StaticText_Zbar;
    QCheckBox *ProcessDataCheckBox;
    QCheckBox *MirrorCheckBox;
    QLabel *StaticText_FPS;
    QGroupBox *RegisterGroupBox;
    QLabel *StaticText_16;
    QLabel *StaticText_17;
    QPushButton *ReadRegPushButton;
    QPushButton *WriteRegPushButton;
    QLineEdit *LineEdit_RegValue;
    QLineEdit *LineEdit_RegAddress;
    QGroupBox *GPIO;
    QCheckBox *ALedCheckBox;
    QCheckBox *BLedCheckBox;
    QCheckBox *IOOUT1CheckBox;
    QCheckBox *IOOUT2CheckBox;
    QCheckBox *IOOUT3CheckBox;
    QPushButton *ReadGpioPushButton;
    QCheckBox *IOIN1CheckBox;
    QCheckBox *IOIN2CheckBox;
    QCheckBox *IOIN3CheckBox;
    QCheckBox *FlipCheckBox;
    QLabel *StaticText_Main;

    void setupUi(QDialog *KSJSCZDemoMainWindow)
    {
        if (KSJSCZDemoMainWindow->objectName().isEmpty())
            KSJSCZDemoMainWindow->setObjectName(QString::fromUtf8("KSJSCZDemoMainWindow"));
        KSJSCZDemoMainWindow->resize(1266, 795);
        UserInputGroupBox = new QGroupBox(KSJSCZDemoMainWindow);
        UserInputGroupBox->setObjectName(QString::fromUtf8("UserInputGroupBox"));
        UserInputGroupBox->setGeometry(QRect(836, 2, 425, 711));
        StaticText_1 = new QLabel(UserInputGroupBox);
        StaticText_1->setObjectName(QString::fromUtf8("StaticText_1"));
        StaticText_1->setGeometry(QRect(8, 112, 115, 16));
        StaticText_2 = new QLabel(UserInputGroupBox);
        StaticText_2->setObjectName(QString::fromUtf8("StaticText_2"));
        StaticText_2->setGeometry(QRect(200, 114, 69, 16));
        StaticText_2->setFrameShape(QFrame::NoFrame);
        StaticText_ExpostureTimeRange = new QLabel(UserInputGroupBox);
        StaticText_ExpostureTimeRange->setObjectName(QString::fromUtf8("StaticText_ExpostureTimeRange"));
        StaticText_ExpostureTimeRange->setGeometry(QRect(278, 116, 133, 16));
        StaticText_ExpostureTimeRange->setFrameShape(QFrame::StyledPanel);
        StaticText_ExpostureLinesRange = new QLabel(UserInputGroupBox);
        StaticText_ExpostureLinesRange->setObjectName(QString::fromUtf8("StaticText_ExpostureLinesRange"));
        StaticText_ExpostureLinesRange->setGeometry(QRect(278, 84, 133, 16));
        StaticText_ExpostureLinesRange->setFrameShape(QFrame::StyledPanel);
        StaticText_3 = new QLabel(UserInputGroupBox);
        StaticText_3->setObjectName(QString::fromUtf8("StaticText_3"));
        StaticText_3->setGeometry(QRect(200, 82, 69, 16));
        StaticText_3->setFrameShape(QFrame::NoFrame);
        StaticText_4 = new QLabel(UserInputGroupBox);
        StaticText_4->setObjectName(QString::fromUtf8("StaticText_4"));
        StaticText_4->setGeometry(QRect(8, 80, 101, 16));
        ExpLinesSpinBox = new QSpinBox(UserInputGroupBox);
        ExpLinesSpinBox->setObjectName(QString::fromUtf8("ExpLinesSpinBox"));
        ExpLinesSpinBox->setEnabled(true);
        ExpLinesSpinBox->setGeometry(QRect(126, 78, 63, 25));
        ExpLinesSpinBox->setReadOnly(false);
        ExpLinesSpinBox->setMinimum(2);
        ExpLinesSpinBox->setMaximum(99999);
        StaticText_5 = new QLabel(UserInputGroupBox);
        StaticText_5->setObjectName(QString::fromUtf8("StaticText_5"));
        StaticText_5->setGeometry(QRect(8, 140, 115, 16));
        StaticText_6 = new QLabel(UserInputGroupBox);
        StaticText_6->setObjectName(QString::fromUtf8("StaticText_6"));
        StaticText_6->setGeometry(QRect(200, 142, 69, 16));
        StaticText_6->setFrameShape(QFrame::NoFrame);
        StaticText_GainRange = new QLabel(UserInputGroupBox);
        StaticText_GainRange->setObjectName(QString::fromUtf8("StaticText_GainRange"));
        StaticText_GainRange->setGeometry(QRect(278, 144, 133, 16));
        StaticText_GainRange->setFrameShape(QFrame::StyledPanel);
        GainSpinBox = new QSpinBox(UserInputGroupBox);
        GainSpinBox->setObjectName(QString::fromUtf8("GainSpinBox"));
        GainSpinBox->setGeometry(QRect(126, 138, 63, 25));
        GainSpinBox->setMaximum(99999);
        FieldOfViewGroupBox = new QGroupBox(UserInputGroupBox);
        FieldOfViewGroupBox->setObjectName(QString::fromUtf8("FieldOfViewGroupBox"));
        FieldOfViewGroupBox->setGeometry(QRect(8, 198, 407, 83));
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
        StaticText_9->setGeometry(QRect(186, 54, 65, 16));
        StaticText_9->setFrameShape(QFrame::NoFrame);
        StaticText_10 = new QLabel(FieldOfViewGroupBox);
        StaticText_10->setObjectName(QString::fromUtf8("StaticText_10"));
        StaticText_10->setGeometry(QRect(186, 24, 65, 16));
        StaticText_10->setFrameShape(QFrame::NoFrame);
        ColStartSpinBox = new QSpinBox(FieldOfViewGroupBox);
        ColStartSpinBox->setObjectName(QString::fromUtf8("ColStartSpinBox"));
        ColStartSpinBox->setGeometry(QRect(96, 20, 77, 25));
        ColStartSpinBox->setMaximum(1280);
        ColSizeSpinBox = new QSpinBox(FieldOfViewGroupBox);
        ColSizeSpinBox->setObjectName(QString::fromUtf8("ColSizeSpinBox"));
        ColSizeSpinBox->setGeometry(QRect(96, 50, 77, 25));
        ColSizeSpinBox->setMaximum(1280);
        RowStartSpinBox = new QSpinBox(FieldOfViewGroupBox);
        RowStartSpinBox->setObjectName(QString::fromUtf8("RowStartSpinBox"));
        RowStartSpinBox->setGeometry(QRect(260, 20, 77, 25));
        RowStartSpinBox->setMaximum(1024);
        RowSizeSpinBox = new QSpinBox(FieldOfViewGroupBox);
        RowSizeSpinBox->setObjectName(QString::fromUtf8("RowSizeSpinBox"));
        RowSizeSpinBox->setGeometry(QRect(260, 50, 77, 25));
        RowSizeSpinBox->setMaximum(1024);
        SetFovPushButton = new QPushButton(FieldOfViewGroupBox);
        SetFovPushButton->setObjectName(QString::fromUtf8("SetFovPushButton"));
        SetFovPushButton->setGeometry(QRect(346, 30, 53, 37));
        ExpTimeSpinBox = new QDoubleSpinBox(UserInputGroupBox);
        ExpTimeSpinBox->setObjectName(QString::fromUtf8("ExpTimeSpinBox"));
        ExpTimeSpinBox->setGeometry(QRect(126, 108, 63, 25));
        ExpTimeSpinBox->setSingleStep(0.01);
        TriggerModeComBox = new QComboBox(UserInputGroupBox);
        TriggerModeComBox->setObjectName(QString::fromUtf8("TriggerModeComBox"));
        TriggerModeComBox->setGeometry(QRect(124, 44, 287, 22));
        StaticText_11 = new QLabel(UserInputGroupBox);
        StaticText_11->setObjectName(QString::fromUtf8("StaticText_11"));
        StaticText_11->setGeometry(QRect(8, 46, 87, 16));
        StaticText_Version = new QLabel(UserInputGroupBox);
        StaticText_Version->setObjectName(QString::fromUtf8("StaticText_Version"));
        StaticText_Version->setGeometry(QRect(10, 690, 209, 16));
        StaticText_Version->setFrameShape(QFrame::StyledPanel);
        StartCapturePushButton = new QPushButton(UserInputGroupBox);
        StartCapturePushButton->setObjectName(QString::fromUtf8("StartCapturePushButton"));
        StartCapturePushButton->setGeometry(QRect(174, 288, 79, 31));
        StaticText_12 = new QLabel(UserInputGroupBox);
        StaticText_12->setObjectName(QString::fromUtf8("StaticText_12"));
        StaticText_12->setGeometry(QRect(8, 170, 115, 16));
        TriggerDelaySpinBox = new QSpinBox(UserInputGroupBox);
        TriggerDelaySpinBox->setObjectName(QString::fromUtf8("TriggerDelaySpinBox"));
        TriggerDelaySpinBox->setGeometry(QRect(126, 168, 63, 25));
        TriggerDelaySpinBox->setMaximum(99999);
        StaticText_13 = new QLabel(UserInputGroupBox);
        StaticText_13->setObjectName(QString::fromUtf8("StaticText_13"));
        StaticText_13->setGeometry(QRect(200, 170, 69, 16));
        StaticText_13->setFrameShape(QFrame::NoFrame);
        StaticText_TriggerDelay = new QLabel(UserInputGroupBox);
        StaticText_TriggerDelay->setObjectName(QString::fromUtf8("StaticText_TriggerDelay"));
        StaticText_TriggerDelay->setGeometry(QRect(278, 172, 133, 16));
        StaticText_TriggerDelay->setFrameShape(QFrame::StyledPanel);
        StaticText_Count = new QLabel(UserInputGroupBox);
        StaticText_Count->setObjectName(QString::fromUtf8("StaticText_Count"));
        StaticText_Count->setGeometry(QRect(348, 296, 65, 16));
        StaticText_Count->setFrameShape(QFrame::StyledPanel);
        groupBox = new QGroupBox(UserInputGroupBox);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(12, 328, 403, 145));
        ParseQRCODECheckBox = new QCheckBox(groupBox);
        ParseQRCODECheckBox->setObjectName(QString::fromUtf8("ParseQRCODECheckBox"));
        ParseQRCODECheckBox->setGeometry(QRect(208, 92, 75, 16));
        ParseUPCECheckBox = new QCheckBox(groupBox);
        ParseUPCECheckBox->setObjectName(QString::fromUtf8("ParseUPCECheckBox"));
        ParseUPCECheckBox->setGeometry(QRect(296, 48, 77, 16));
        ParsePDF417CheckBox = new QCheckBox(groupBox);
        ParsePDF417CheckBox->setObjectName(QString::fromUtf8("ParsePDF417CheckBox"));
        ParsePDF417CheckBox->setGeometry(QRect(118, 92, 79, 16));
        ParseEAN8CheckBox = new QCheckBox(groupBox);
        ParseEAN8CheckBox->setObjectName(QString::fromUtf8("ParseEAN8CheckBox"));
        ParseEAN8CheckBox->setGeometry(QRect(30, 48, 67, 16));
        ParseISBN13CheckBox = new QCheckBox(groupBox);
        ParseISBN13CheckBox->setObjectName(QString::fromUtf8("ParseISBN13CheckBox"));
        ParseISBN13CheckBox->setGeometry(QRect(118, 70, 73, 16));
        ParseUPCACheckBox = new QCheckBox(groupBox);
        ParseUPCACheckBox->setObjectName(QString::fromUtf8("ParseUPCACheckBox"));
        ParseUPCACheckBox->setGeometry(QRect(208, 48, 59, 16));
        ParseCODE39CheckBox = new QCheckBox(groupBox);
        ParseCODE39CheckBox->setObjectName(QString::fromUtf8("ParseCODE39CheckBox"));
        ParseCODE39CheckBox->setGeometry(QRect(208, 70, 81, 16));
        ParseISBN10CheckBox = new QCheckBox(groupBox);
        ParseISBN10CheckBox->setObjectName(QString::fromUtf8("ParseISBN10CheckBox"));
        ParseISBN10CheckBox->setGeometry(QRect(30, 70, 69, 16));
        ParseCODE128CheckBox = new QCheckBox(groupBox);
        ParseCODE128CheckBox->setObjectName(QString::fromUtf8("ParseCODE128CheckBox"));
        ParseCODE128CheckBox->setGeometry(QRect(296, 70, 85, 16));
        ParseEAN13CheckBox = new QCheckBox(groupBox);
        ParseEAN13CheckBox->setObjectName(QString::fromUtf8("ParseEAN13CheckBox"));
        ParseEAN13CheckBox->setGeometry(QRect(118, 48, 73, 16));
        ParseI25CheckBox = new QCheckBox(groupBox);
        ParseI25CheckBox->setObjectName(QString::fromUtf8("ParseI25CheckBox"));
        ParseI25CheckBox->setGeometry(QRect(30, 92, 69, 16));
        DensitySpinBox = new QSpinBox(groupBox);
        DensitySpinBox->setObjectName(QString::fromUtf8("DensitySpinBox"));
        DensitySpinBox->setGeometry(QRect(296, 16, 43, 21));
        DensitySpinBox->setMinimum(1);
        DensitySpinBox->setMaximum(32);
        StaticText_14 = new QLabel(groupBox);
        StaticText_14->setObjectName(QString::fromUtf8("StaticText_14"));
        StaticText_14->setGeometry(QRect(188, 18, 99, 16));
        StaticText_14->setFrameShape(QFrame::NoFrame);
        StaticText_Zbar = new QLabel(groupBox);
        StaticText_Zbar->setObjectName(QString::fromUtf8("StaticText_Zbar"));
        StaticText_Zbar->setGeometry(QRect(8, 118, 385, 16));
        StaticText_Zbar->setFrameShape(QFrame::StyledPanel);
        ProcessDataCheckBox = new QCheckBox(groupBox);
        ProcessDataCheckBox->setObjectName(QString::fromUtf8("ProcessDataCheckBox"));
        ProcessDataCheckBox->setGeometry(QRect(30, 20, 113, 16));
        MirrorCheckBox = new QCheckBox(UserInputGroupBox);
        MirrorCheckBox->setObjectName(QString::fromUtf8("MirrorCheckBox"));
        MirrorCheckBox->setGeometry(QRect(14, 296, 81, 16));
        StaticText_FPS = new QLabel(UserInputGroupBox);
        StaticText_FPS->setObjectName(QString::fromUtf8("StaticText_FPS"));
        StaticText_FPS->setGeometry(QRect(276, 296, 61, 16));
        StaticText_FPS->setFrameShape(QFrame::StyledPanel);
        RegisterGroupBox = new QGroupBox(UserInputGroupBox);
        RegisterGroupBox->setObjectName(QString::fromUtf8("RegisterGroupBox"));
        RegisterGroupBox->setGeometry(QRect(8, 562, 407, 65));
        StaticText_16 = new QLabel(RegisterGroupBox);
        StaticText_16->setObjectName(QString::fromUtf8("StaticText_16"));
        StaticText_16->setGeometry(QRect(10, 26, 57, 16));
        StaticText_16->setFrameShape(QFrame::NoFrame);
        StaticText_17 = new QLabel(RegisterGroupBox);
        StaticText_17->setObjectName(QString::fromUtf8("StaticText_17"));
        StaticText_17->setGeometry(QRect(148, 26, 43, 16));
        StaticText_17->setFrameShape(QFrame::NoFrame);
        ReadRegPushButton = new QPushButton(RegisterGroupBox);
        ReadRegPushButton->setObjectName(QString::fromUtf8("ReadRegPushButton"));
        ReadRegPushButton->setGeometry(QRect(316, 18, 41, 33));
        WriteRegPushButton = new QPushButton(RegisterGroupBox);
        WriteRegPushButton->setObjectName(QString::fromUtf8("WriteRegPushButton"));
        WriteRegPushButton->setGeometry(QRect(362, 18, 41, 33));
        LineEdit_RegValue = new QLineEdit(RegisterGroupBox);
        LineEdit_RegValue->setObjectName(QString::fromUtf8("LineEdit_RegValue"));
        LineEdit_RegValue->setGeometry(QRect(198, 24, 111, 20));
        LineEdit_RegAddress = new QLineEdit(RegisterGroupBox);
        LineEdit_RegAddress->setObjectName(QString::fromUtf8("LineEdit_RegAddress"));
        LineEdit_RegAddress->setGeometry(QRect(74, 24, 65, 20));
        GPIO = new QGroupBox(UserInputGroupBox);
        GPIO->setObjectName(QString::fromUtf8("GPIO"));
        GPIO->setGeometry(QRect(10, 478, 407, 69));
        ALedCheckBox = new QCheckBox(GPIO);
        ALedCheckBox->setObjectName(QString::fromUtf8("ALedCheckBox"));
        ALedCheckBox->setGeometry(QRect(214, 20, 95, 16));
        BLedCheckBox = new QCheckBox(GPIO);
        BLedCheckBox->setObjectName(QString::fromUtf8("BLedCheckBox"));
        BLedCheckBox->setGeometry(QRect(312, 20, 91, 16));
        IOOUT1CheckBox = new QCheckBox(GPIO);
        IOOUT1CheckBox->setObjectName(QString::fromUtf8("IOOUT1CheckBox"));
        IOOUT1CheckBox->setGeometry(QRect(12, 20, 61, 16));
        IOOUT2CheckBox = new QCheckBox(GPIO);
        IOOUT2CheckBox->setObjectName(QString::fromUtf8("IOOUT2CheckBox"));
        IOOUT2CheckBox->setGeometry(QRect(78, 20, 61, 16));
        IOOUT3CheckBox = new QCheckBox(GPIO);
        IOOUT3CheckBox->setObjectName(QString::fromUtf8("IOOUT3CheckBox"));
        IOOUT3CheckBox->setGeometry(QRect(146, 20, 59, 16));
        ReadGpioPushButton = new QPushButton(GPIO);
        ReadGpioPushButton->setObjectName(QString::fromUtf8("ReadGpioPushButton"));
        ReadGpioPushButton->setGeometry(QRect(10, 40, 107, 23));
        IOIN1CheckBox = new QCheckBox(GPIO);
        IOIN1CheckBox->setObjectName(QString::fromUtf8("IOIN1CheckBox"));
        IOIN1CheckBox->setGeometry(QRect(142, 44, 57, 16));
        IOIN2CheckBox = new QCheckBox(GPIO);
        IOIN2CheckBox->setObjectName(QString::fromUtf8("IOIN2CheckBox"));
        IOIN2CheckBox->setGeometry(QRect(202, 44, 59, 16));
        IOIN3CheckBox = new QCheckBox(GPIO);
        IOIN3CheckBox->setObjectName(QString::fromUtf8("IOIN3CheckBox"));
        IOIN3CheckBox->setGeometry(QRect(264, 44, 57, 16));
        FlipCheckBox = new QCheckBox(UserInputGroupBox);
        FlipCheckBox->setObjectName(QString::fromUtf8("FlipCheckBox"));
        FlipCheckBox->setGeometry(QRect(98, 296, 65, 16));
        StaticText_Main = new QLabel(UserInputGroupBox);
        StaticText_Main->setObjectName(QString::fromUtf8("StaticText_Main"));
        StaticText_Main->setGeometry(QRect(230, 690, 187, 16));
        StaticText_Main->setFrameShape(QFrame::StyledPanel);

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
        SetFovPushButton->setText(QApplication::translate("KSJSCZDemoMainWindow", "Set", 0, QApplication::UnicodeUTF8));
        StaticText_11->setText(QApplication::translate("KSJSCZDemoMainWindow", "Trigger Mode", 0, QApplication::UnicodeUTF8));
        StaticText_Version->setText(QApplication::translate("KSJSCZDemoMainWindow", "Ver: 0.0.0.0", 0, QApplication::UnicodeUTF8));
        StartCapturePushButton->setText(QApplication::translate("KSJSCZDemoMainWindow", "Start", 0, QApplication::UnicodeUTF8));
        StaticText_12->setText(QApplication::translate("KSJSCZDemoMainWindow", "Trigger Delay:", 0, QApplication::UnicodeUTF8));
        StaticText_13->setText(QApplication::translate("KSJSCZDemoMainWindow", "Range:", 0, QApplication::UnicodeUTF8));
        StaticText_TriggerDelay->setText(QApplication::translate("KSJSCZDemoMainWindow", "TriggerDelayRange", 0, QApplication::UnicodeUTF8));
        StaticText_Count->setText(QApplication::translate("KSJSCZDemoMainWindow", "0", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("KSJSCZDemoMainWindow", "1D Bar or 2D Bar", 0, QApplication::UnicodeUTF8));
        ParseQRCODECheckBox->setText(QApplication::translate("KSJSCZDemoMainWindow", "QRCODE", 0, QApplication::UnicodeUTF8));
        ParseUPCECheckBox->setText(QApplication::translate("KSJSCZDemoMainWindow", "UPCE", 0, QApplication::UnicodeUTF8));
        ParsePDF417CheckBox->setText(QApplication::translate("KSJSCZDemoMainWindow", "PDF417", 0, QApplication::UnicodeUTF8));
        ParseEAN8CheckBox->setText(QApplication::translate("KSJSCZDemoMainWindow", "EAN8", 0, QApplication::UnicodeUTF8));
        ParseISBN13CheckBox->setText(QApplication::translate("KSJSCZDemoMainWindow", "ISBN13", 0, QApplication::UnicodeUTF8));
        ParseUPCACheckBox->setText(QApplication::translate("KSJSCZDemoMainWindow", "UPCA", 0, QApplication::UnicodeUTF8));
        ParseCODE39CheckBox->setText(QApplication::translate("KSJSCZDemoMainWindow", "CODE39", 0, QApplication::UnicodeUTF8));
        ParseISBN10CheckBox->setText(QApplication::translate("KSJSCZDemoMainWindow", "ISBN10", 0, QApplication::UnicodeUTF8));
        ParseCODE128CheckBox->setText(QApplication::translate("KSJSCZDemoMainWindow", "CODE128", 0, QApplication::UnicodeUTF8));
        ParseEAN13CheckBox->setText(QApplication::translate("KSJSCZDemoMainWindow", "EAN13", 0, QApplication::UnicodeUTF8));
        ParseI25CheckBox->setText(QApplication::translate("KSJSCZDemoMainWindow", "I25", 0, QApplication::UnicodeUTF8));
        StaticText_14->setText(QApplication::translate("KSJSCZDemoMainWindow", "Sample Density:", 0, QApplication::UnicodeUTF8));
        StaticText_Zbar->setText(QString());
        ProcessDataCheckBox->setText(QApplication::translate("KSJSCZDemoMainWindow", "Process Image", 0, QApplication::UnicodeUTF8));
        MirrorCheckBox->setText(QApplication::translate("KSJSCZDemoMainWindow", "Mirror ", 0, QApplication::UnicodeUTF8));
        StaticText_FPS->setText(QApplication::translate("KSJSCZDemoMainWindow", "0fps", 0, QApplication::UnicodeUTF8));
        RegisterGroupBox->setTitle(QApplication::translate("KSJSCZDemoMainWindow", "Register", 0, QApplication::UnicodeUTF8));
        StaticText_16->setText(QApplication::translate("KSJSCZDemoMainWindow", "Address:", 0, QApplication::UnicodeUTF8));
        StaticText_17->setText(QApplication::translate("KSJSCZDemoMainWindow", "Value:", 0, QApplication::UnicodeUTF8));
        ReadRegPushButton->setText(QApplication::translate("KSJSCZDemoMainWindow", "Read", 0, QApplication::UnicodeUTF8));
        WriteRegPushButton->setText(QApplication::translate("KSJSCZDemoMainWindow", "Write", 0, QApplication::UnicodeUTF8));
        GPIO->setTitle(QApplication::translate("KSJSCZDemoMainWindow", "GPIO", 0, QApplication::UnicodeUTF8));
        ALedCheckBox->setText(QApplication::translate("KSJSCZDemoMainWindow", "A Led Shine", 0, QApplication::UnicodeUTF8));
        BLedCheckBox->setText(QApplication::translate("KSJSCZDemoMainWindow", "B Led Shine", 0, QApplication::UnicodeUTF8));
        IOOUT1CheckBox->setText(QApplication::translate("KSJSCZDemoMainWindow", "H_OUT0", 0, QApplication::UnicodeUTF8));
        IOOUT2CheckBox->setText(QApplication::translate("KSJSCZDemoMainWindow", "H_OUT1", 0, QApplication::UnicodeUTF8));
        IOOUT3CheckBox->setText(QApplication::translate("KSJSCZDemoMainWindow", "G_OUT0", 0, QApplication::UnicodeUTF8));
        ReadGpioPushButton->setText(QApplication::translate("KSJSCZDemoMainWindow", "Read Inpput", 0, QApplication::UnicodeUTF8));
        IOIN1CheckBox->setText(QApplication::translate("KSJSCZDemoMainWindow", "H_IN0", 0, QApplication::UnicodeUTF8));
        IOIN2CheckBox->setText(QApplication::translate("KSJSCZDemoMainWindow", "H_IN1", 0, QApplication::UnicodeUTF8));
        IOIN3CheckBox->setText(QApplication::translate("KSJSCZDemoMainWindow", "G_IN0", 0, QApplication::UnicodeUTF8));
        FlipCheckBox->setText(QApplication::translate("KSJSCZDemoMainWindow", "Flip", 0, QApplication::UnicodeUTF8));
        StaticText_Main->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class KSJSCZDemoMainWindow: public Ui_KSJSCZDemoMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KSJSCZDEMOMAINWINDOW_H

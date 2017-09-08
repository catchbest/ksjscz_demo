/********************************************************************************
** Form generated from reading UI file 'KSJSCZDemoMainWindow.ui'
**
** Created: Wed Sep 6 14:32:04 2017
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
    QLabel *StaticText_4;
    QSpinBox *ExpLinesSpinBox;
    QLabel *StaticText_5;
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
    QComboBox *TriggerModeComBox;
    QLabel *StaticText_11;
    QLabel *StaticText_Version;
    QPushButton *StartCapturePushButton;
    QLabel *StaticText_12;
    QSpinBox *TriggerDelaySpinBox;
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
    QCheckBox *ProcessDataCheckBox;
    QLabel *StaticText_Zbar;
    QCheckBox *MirrorCheckBox;
    QLabel *StaticText_FPS;
    QCheckBox *FlipCheckBox;

    void setupUi(QDialog *KSJSCZDemoMainWindow)
    {
        if (KSJSCZDemoMainWindow->objectName().isEmpty())
            KSJSCZDemoMainWindow->setObjectName(QString::fromUtf8("KSJSCZDemoMainWindow"));
        KSJSCZDemoMainWindow->resize(1266, 795);
        KSJSCZDemoMainWindow->setContextMenuPolicy(Qt::NoContextMenu);
        UserInputGroupBox = new QGroupBox(KSJSCZDemoMainWindow);
        UserInputGroupBox->setObjectName(QString::fromUtf8("UserInputGroupBox"));
        UserInputGroupBox->setGeometry(QRect(964, 6, 303, 697));
        StaticText_4 = new QLabel(UserInputGroupBox);
        StaticText_4->setObjectName(QString::fromUtf8("StaticText_4"));
        StaticText_4->setGeometry(QRect(20, 362, 65, 16));
        ExpLinesSpinBox = new QSpinBox(UserInputGroupBox);
        ExpLinesSpinBox->setObjectName(QString::fromUtf8("ExpLinesSpinBox"));
        ExpLinesSpinBox->setEnabled(true);
        ExpLinesSpinBox->setGeometry(QRect(90, 358, 63, 25));
        ExpLinesSpinBox->setReadOnly(false);
        ExpLinesSpinBox->setMinimum(2);
        ExpLinesSpinBox->setMaximum(99999);
        StaticText_5 = new QLabel(UserInputGroupBox);
        StaticText_5->setObjectName(QString::fromUtf8("StaticText_5"));
        StaticText_5->setGeometry(QRect(182, 362, 39, 16));
        GainSpinBox = new QSpinBox(UserInputGroupBox);
        GainSpinBox->setObjectName(QString::fromUtf8("GainSpinBox"));
        GainSpinBox->setGeometry(QRect(226, 358, 63, 25));
        GainSpinBox->setMaximum(99999);
        FieldOfViewGroupBox = new QGroupBox(UserInputGroupBox);
        FieldOfViewGroupBox->setObjectName(QString::fromUtf8("FieldOfViewGroupBox"));
        FieldOfViewGroupBox->setGeometry(QRect(6, 432, 283, 127));
        StaticText_7 = new QLabel(FieldOfViewGroupBox);
        StaticText_7->setObjectName(QString::fromUtf8("StaticText_7"));
        StaticText_7->setGeometry(QRect(8, 26, 65, 16));
        StaticText_7->setFrameShape(QFrame::NoFrame);
        StaticText_8 = new QLabel(FieldOfViewGroupBox);
        StaticText_8->setObjectName(QString::fromUtf8("StaticText_8"));
        StaticText_8->setGeometry(QRect(162, 26, 39, 16));
        StaticText_8->setFrameShape(QFrame::NoFrame);
        StaticText_9 = new QLabel(FieldOfViewGroupBox);
        StaticText_9->setObjectName(QString::fromUtf8("StaticText_9"));
        StaticText_9->setGeometry(QRect(162, 64, 39, 16));
        StaticText_9->setFrameShape(QFrame::NoFrame);
        StaticText_10 = new QLabel(FieldOfViewGroupBox);
        StaticText_10->setObjectName(QString::fromUtf8("StaticText_10"));
        StaticText_10->setGeometry(QRect(8, 64, 65, 16));
        StaticText_10->setFrameShape(QFrame::NoFrame);
        ColStartSpinBox = new QSpinBox(FieldOfViewGroupBox);
        ColStartSpinBox->setObjectName(QString::fromUtf8("ColStartSpinBox"));
        ColStartSpinBox->setGeometry(QRect(82, 22, 69, 25));
        ColStartSpinBox->setMaximum(1280);
        ColSizeSpinBox = new QSpinBox(FieldOfViewGroupBox);
        ColSizeSpinBox->setObjectName(QString::fromUtf8("ColSizeSpinBox"));
        ColSizeSpinBox->setGeometry(QRect(206, 22, 69, 25));
        ColSizeSpinBox->setMaximum(1280);
        RowStartSpinBox = new QSpinBox(FieldOfViewGroupBox);
        RowStartSpinBox->setObjectName(QString::fromUtf8("RowStartSpinBox"));
        RowStartSpinBox->setGeometry(QRect(82, 60, 69, 25));
        RowStartSpinBox->setMaximum(1024);
        RowSizeSpinBox = new QSpinBox(FieldOfViewGroupBox);
        RowSizeSpinBox->setObjectName(QString::fromUtf8("RowSizeSpinBox"));
        RowSizeSpinBox->setGeometry(QRect(206, 60, 69, 25));
        RowSizeSpinBox->setMaximum(1024);
        SetFovPushButton = new QPushButton(FieldOfViewGroupBox);
        SetFovPushButton->setObjectName(QString::fromUtf8("SetFovPushButton"));
        SetFovPushButton->setGeometry(QRect(160, 92, 115, 31));
        TriggerModeComBox = new QComboBox(UserInputGroupBox);
        TriggerModeComBox->setObjectName(QString::fromUtf8("TriggerModeComBox"));
        TriggerModeComBox->setGeometry(QRect(92, 22, 203, 22));
        StaticText_11 = new QLabel(UserInputGroupBox);
        StaticText_11->setObjectName(QString::fromUtf8("StaticText_11"));
        StaticText_11->setGeometry(QRect(8, 24, 81, 16));
        StaticText_Version = new QLabel(UserInputGroupBox);
        StaticText_Version->setObjectName(QString::fromUtf8("StaticText_Version"));
        StaticText_Version->setGeometry(QRect(10, 674, 257, 16));
        StaticText_Version->setFrameShape(QFrame::NoFrame);
        StaticText_Version->setFrameShadow(QFrame::Plain);
        StaticText_Version->setWordWrap(false);
        StartCapturePushButton = new QPushButton(UserInputGroupBox);
        StartCapturePushButton->setObjectName(QString::fromUtf8("StartCapturePushButton"));
        StartCapturePushButton->setGeometry(QRect(16, 56, 79, 31));
        StaticText_12 = new QLabel(UserInputGroupBox);
        StaticText_12->setObjectName(QString::fromUtf8("StaticText_12"));
        StaticText_12->setGeometry(QRect(128, 404, 89, 16));
        TriggerDelaySpinBox = new QSpinBox(UserInputGroupBox);
        TriggerDelaySpinBox->setObjectName(QString::fromUtf8("TriggerDelaySpinBox"));
        TriggerDelaySpinBox->setGeometry(QRect(226, 398, 63, 25));
        TriggerDelaySpinBox->setMaximum(99999);
        groupBox = new QGroupBox(UserInputGroupBox);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(12, 100, 281, 203));
        ParseQRCODECheckBox = new QCheckBox(groupBox);
        ParseQRCODECheckBox->setObjectName(QString::fromUtf8("ParseQRCODECheckBox"));
        ParseQRCODECheckBox->setGeometry(QRect(188, 88, 75, 16));
        ParseUPCECheckBox = new QCheckBox(groupBox);
        ParseUPCECheckBox->setObjectName(QString::fromUtf8("ParseUPCECheckBox"));
        ParseUPCECheckBox->setGeometry(QRect(102, 88, 77, 16));
        ParsePDF417CheckBox = new QCheckBox(groupBox);
        ParsePDF417CheckBox->setObjectName(QString::fromUtf8("ParsePDF417CheckBox"));
        ParsePDF417CheckBox->setGeometry(QRect(188, 66, 79, 16));
        ParseEAN8CheckBox = new QCheckBox(groupBox);
        ParseEAN8CheckBox->setObjectName(QString::fromUtf8("ParseEAN8CheckBox"));
        ParseEAN8CheckBox->setGeometry(QRect(16, 44, 67, 16));
        ParseISBN13CheckBox = new QCheckBox(groupBox);
        ParseISBN13CheckBox->setObjectName(QString::fromUtf8("ParseISBN13CheckBox"));
        ParseISBN13CheckBox->setGeometry(QRect(102, 66, 73, 16));
        ParseUPCACheckBox = new QCheckBox(groupBox);
        ParseUPCACheckBox->setObjectName(QString::fromUtf8("ParseUPCACheckBox"));
        ParseUPCACheckBox->setGeometry(QRect(16, 88, 59, 16));
        ParseCODE39CheckBox = new QCheckBox(groupBox);
        ParseCODE39CheckBox->setObjectName(QString::fromUtf8("ParseCODE39CheckBox"));
        ParseCODE39CheckBox->setGeometry(QRect(16, 110, 81, 16));
        ParseISBN10CheckBox = new QCheckBox(groupBox);
        ParseISBN10CheckBox->setObjectName(QString::fromUtf8("ParseISBN10CheckBox"));
        ParseISBN10CheckBox->setGeometry(QRect(16, 66, 69, 16));
        ParseCODE128CheckBox = new QCheckBox(groupBox);
        ParseCODE128CheckBox->setObjectName(QString::fromUtf8("ParseCODE128CheckBox"));
        ParseCODE128CheckBox->setGeometry(QRect(102, 110, 85, 16));
        ParseEAN13CheckBox = new QCheckBox(groupBox);
        ParseEAN13CheckBox->setObjectName(QString::fromUtf8("ParseEAN13CheckBox"));
        ParseEAN13CheckBox->setGeometry(QRect(102, 44, 73, 16));
        ParseI25CheckBox = new QCheckBox(groupBox);
        ParseI25CheckBox->setObjectName(QString::fromUtf8("ParseI25CheckBox"));
        ParseI25CheckBox->setGeometry(QRect(188, 44, 69, 16));
        DensitySpinBox = new QSpinBox(groupBox);
        DensitySpinBox->setObjectName(QString::fromUtf8("DensitySpinBox"));
        DensitySpinBox->setGeometry(QRect(126, 138, 43, 21));
        DensitySpinBox->setMinimum(1);
        DensitySpinBox->setMaximum(32);
        StaticText_14 = new QLabel(groupBox);
        StaticText_14->setObjectName(QString::fromUtf8("StaticText_14"));
        StaticText_14->setGeometry(QRect(18, 140, 99, 16));
        StaticText_14->setFrameShape(QFrame::NoFrame);
        ProcessDataCheckBox = new QCheckBox(groupBox);
        ProcessDataCheckBox->setObjectName(QString::fromUtf8("ProcessDataCheckBox"));
        ProcessDataCheckBox->setGeometry(QRect(14, 20, 113, 16));
        StaticText_Zbar = new QLabel(groupBox);
        StaticText_Zbar->setObjectName(QString::fromUtf8("StaticText_Zbar"));
        StaticText_Zbar->setGeometry(QRect(14, 172, 253, 23));
        StaticText_Zbar->setFrameShape(QFrame::StyledPanel);
        MirrorCheckBox = new QCheckBox(UserInputGroupBox);
        MirrorCheckBox->setObjectName(QString::fromUtf8("MirrorCheckBox"));
        MirrorCheckBox->setGeometry(QRect(20, 328, 73, 16));
        StaticText_FPS = new QLabel(UserInputGroupBox);
        StaticText_FPS->setObjectName(QString::fromUtf8("StaticText_FPS"));
        StaticText_FPS->setGeometry(QRect(112, 64, 61, 16));
        StaticText_FPS->setFrameShape(QFrame::StyledPanel);
        FlipCheckBox = new QCheckBox(UserInputGroupBox);
        FlipCheckBox->setObjectName(QString::fromUtf8("FlipCheckBox"));
        FlipCheckBox->setGeometry(QRect(108, 328, 65, 16));

        retranslateUi(KSJSCZDemoMainWindow);

        QMetaObject::connectSlotsByName(KSJSCZDemoMainWindow);
    } // setupUi

    void retranslateUi(QDialog *KSJSCZDemoMainWindow)
    {
        KSJSCZDemoMainWindow->setWindowTitle(QApplication::translate("KSJSCZDemoMainWindow", "Dialog", 0, QApplication::UnicodeUTF8));
        UserInputGroupBox->setTitle(QApplication::translate("KSJSCZDemoMainWindow", "Camera Setting", 0, QApplication::UnicodeUTF8));
        StaticText_4->setText(QApplication::translate("KSJSCZDemoMainWindow", "Exposure:", 0, QApplication::UnicodeUTF8));
        StaticText_5->setText(QApplication::translate("KSJSCZDemoMainWindow", "Gain:", 0, QApplication::UnicodeUTF8));
        FieldOfViewGroupBox->setTitle(QApplication::translate("KSJSCZDemoMainWindow", "Field of View", 0, QApplication::UnicodeUTF8));
        StaticText_7->setText(QApplication::translate("KSJSCZDemoMainWindow", "Col Start:", 0, QApplication::UnicodeUTF8));
        StaticText_8->setText(QApplication::translate("KSJSCZDemoMainWindow", "Size:", 0, QApplication::UnicodeUTF8));
        StaticText_9->setText(QApplication::translate("KSJSCZDemoMainWindow", "Size:", 0, QApplication::UnicodeUTF8));
        StaticText_10->setText(QApplication::translate("KSJSCZDemoMainWindow", "Row Start:", 0, QApplication::UnicodeUTF8));
        SetFovPushButton->setText(QApplication::translate("KSJSCZDemoMainWindow", "Set", 0, QApplication::UnicodeUTF8));
        StaticText_11->setText(QApplication::translate("KSJSCZDemoMainWindow", "Trigger Mode", 0, QApplication::UnicodeUTF8));
        StaticText_Version->setText(QApplication::translate("KSJSCZDemoMainWindow", "0.0.0.0", 0, QApplication::UnicodeUTF8));
        StartCapturePushButton->setText(QApplication::translate("KSJSCZDemoMainWindow", "Start", 0, QApplication::UnicodeUTF8));
        StaticText_12->setText(QApplication::translate("KSJSCZDemoMainWindow", "Trigger Delay:", 0, QApplication::UnicodeUTF8));
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
        ProcessDataCheckBox->setText(QApplication::translate("KSJSCZDemoMainWindow", "Process Image", 0, QApplication::UnicodeUTF8));
        StaticText_Zbar->setText(QString());
        MirrorCheckBox->setText(QApplication::translate("KSJSCZDemoMainWindow", "Mirror ", 0, QApplication::UnicodeUTF8));
        StaticText_FPS->setText(QApplication::translate("KSJSCZDemoMainWindow", "0fps", 0, QApplication::UnicodeUTF8));
        FlipCheckBox->setText(QApplication::translate("KSJSCZDemoMainWindow", "Flip", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class KSJSCZDemoMainWindow: public Ui_KSJSCZDemoMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KSJSCZDEMOMAINWINDOW_H

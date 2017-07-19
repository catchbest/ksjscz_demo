#ifndef __KSJSCZDEMO_MAINWINDOW_H_
#define __KSJSCZDEMO_MAINWINDOW_H_

#include "QtCore/QTimer"
#include "QtGui/QDialog"
#include "QtGui/QMatrix"
#include "QtNetwork/QtNetwork"


namespace Ui { class KSJSCZDemoMainWindow; }

class CKSJSCZDemoMainWindow : public QDialog
{
	Q_OBJECT

public:
	explicit CKSJSCZDemoMainWindow(QWidget *parent = 0);
	~CKSJSCZDemoMainWindow();

private:
	Ui::KSJSCZDemoMainWindow *ui;

protected slots:
	void NewConnect();
	void DisConnect();
	void SendMessage();
	void ReadMessage();

protected:
	virtual void paintEvent(QPaintEvent *);

protected:

	QTcpServer *m_pTcpServer;
	QTcpSocket *m_pClientConnection;
};

#endif // __KSJSCZDEMO_MAINWINDOWS_H_

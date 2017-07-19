

#include <QtGui/QPainter>
#include <QtGui/QResizeEvent>
#include <QtCore/QSettings>

#include "KSJSCZDemoMainWindow.h"
#include <unistd.h>
#include <sys/time.h>
#include "ui_KSJSCZDemoMainWindow.h"



CKSJSCZDemoMainWindow::CKSJSCZDemoMainWindow(QWidget *parent) :
QDialog(parent)
, ui(new Ui::KSJSCZDemoMainWindow)
{
	ui->setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);

	m_pClientConnection = NULL;

	m_pTcpServer = new QTcpServer(this);

	// Change the ip to you camera ip ( 192.168.111.111 ?)
	if (!m_pTcpServer->listen(QHostAddress("192.168.1.202"), 6666))
	{
		ui->label_1->setText("Tcp Error: " + m_pTcpServer->errorString());
	}
	else
	{
		connect(m_pTcpServer, SIGNAL(newConnection()), this, SLOT(NewConnect()));
	}

	connect(ui->StartCapturePushButton, SIGNAL(clicked()), this, SLOT(SendMessage()));
}

CKSJSCZDemoMainWindow::~CKSJSCZDemoMainWindow()
{
	delete ui;
}

void CKSJSCZDemoMainWindow::paintEvent(QPaintEvent *)
{
}

void CKSJSCZDemoMainWindow::NewConnect()
{
	if (m_pClientConnection == NULL)
	{
		m_pClientConnection = m_pTcpServer->nextPendingConnection();

		connect(m_pClientConnection, SIGNAL(readyRead()), this, SLOT(ReadMessage()));
		connect(m_pClientConnection, SIGNAL(disconnected()), this, SLOT(DisConnect()));

		ui->label_1->setText("Tcp Connected!");
	}
	else
	{
		ui->label_1->setText("Error: Tcp Has Connected!");
	}
}


void CKSJSCZDemoMainWindow::DisConnect()
{
	m_pClientConnection->deleteLater();
	m_pClientConnection = NULL;

	ui->label_1->setText("Tcp Disconnected!");
}


void CKSJSCZDemoMainWindow::SendMessage()
{
	if (m_pClientConnection != NULL)
	{
		QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
		QString   str = time.toString("yyyy-MM-dd hh:mm:ss\r\n"); //设置显示格式

		QByteArray block = str.toLatin1();

		m_pClientConnection->write(block);

		ui->label_2->setText(time.toString("yyyy-MM-dd hh:mm:ss"));
	}
}


void CKSJSCZDemoMainWindow::ReadMessage()
{
	if (m_pClientConnection != NULL)
	{
		char pBuffer[128] = { 0 };
		m_pClientConnection->read(pBuffer, 128);

		QString msg(pBuffer);

		ui->label_2->setText(msg);
	}
}
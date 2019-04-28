#ifndef COMMUNICATIONCLASS_H
#define COMMUNICATIONCLASS_H

#ifdef WIN32
#pragma execution_character_set("utf-8")

#endif

#include<QWidget>
#include<QFile>
#include<QTextStream>
#include<QByteArray>
#include<QFile>
#include<QTextCodec>
#include<QJsonObject>
#include<QDebug>
#include<QjsonDocument>
#include<QTcpSocket>
#include<QVariant>
#include<QException>
#include<QMessageBox>

class CommunicationClass :public QWidget
{
	Q_OBJECT

public:
	CommunicationClass();
	~CommunicationClass();
	bool sendRequest(QString fileName, QString language, QString system = "");	//上层调用，向服务器传送编译请求（文件路径，程序种类，系统种类）
	void sendArgs(QString args);						                        //上层向服务器传递程序输入参数
	void send(QString news, int length = -1);
	void send(QByteArray news);
	void send(int news,int length=-1);
	void sendUInt32(unsigned int num);


public slots:void newsComeFromSever();			                                //从服务器传回数据

public: 
signals:void newsComming(QString);				                                //当服务器传回数据时触发
signals:void endConnect();

public:
	QTcpSocket *socket;
	QString ip;
	int port;
};

#endif

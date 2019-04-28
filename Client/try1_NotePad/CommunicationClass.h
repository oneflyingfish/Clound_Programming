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
	bool sendRequest(QString fileName, QString language, QString system = "");	//�ϲ���ã�����������ͱ��������ļ�·�����������࣬ϵͳ���ࣩ
	void sendArgs(QString args);						                        //�ϲ�����������ݳ����������
	void send(QString news, int length = -1);
	void send(QByteArray news);
	void send(int news,int length=-1);
	void sendUInt32(unsigned int num);


public slots:void newsComeFromSever();			                                //�ӷ�������������

public: 
signals:void newsComming(QString);				                                //����������������ʱ����
signals:void endConnect();

public:
	QTcpSocket *socket;
	QString ip;
	int port;
};

#endif

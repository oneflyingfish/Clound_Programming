#include "CommunicationClass.h"

CommunicationClass::CommunicationClass()
{
	//�������ļ�����ȡ������ip��port
	if (!QFile::exists("./config"))
	{
		QMessageBox::information(this, tr("error"), tr("fail to read the config about server"));
		return;
	}

	QFile file("./config");
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	QTextStream configReader(&file);
	try
	{
		configReader >> ip >> port;
	}
	catch (QException ex)
	{
		QMessageBox::information(this, tr("error"), tr("fail to read the config about server"));
	}

	file.close();

	qDebug() << "ip=" << ip << "  port=" << port << endl;

	//��ʼ���׽���
	socket = new QTcpSocket(this);	//ʵ�����׽���
	socket->abort();				//���������׽���
	connect(socket, SIGNAL(readyRead()), this, SLOT(newsComeFromSever()));				//�������ݵ���ʱ����������
    connect(socket, SIGNAL(disconnected()), this, SIGNAL(endConnect()));                //��������
	//sendRequest(tr("C:\\Users\\ASUS\\Desktop\\11\\file.txt"), tr("C"), tr("Linux"));	//ģ�ⷢ������
}

CommunicationClass::~CommunicationClass()
{
	socket->close();
	delete socket;
}

bool CommunicationClass::sendRequest(QString fileName, QString language, QString system)
{
	socket->connectToHost(ip, port);										//�ͻ������ӷ�����

	if(!socket->waitForConnected(20000))									//�ж��Ƿ�ɹ����ӷ�����
	{
		QMessageBox::information(this, tr("error"), tr("failed to connect to the server"));
		return false;
	}

	if (!QFile::exists(fileName))
	{
		QMessageBox::information(this, tr("error"), tr("the file is not save on the disk"));
	}

	QFile file(fileName);
	file.open(QIODevice::ReadOnly | QIODevice::Text);

	int fileSizeByDisk = file.size();					//ͨ������ϵͳ����
	qDebug() << "disk size" << fileSizeByDisk << endl;

	try
	{
		QTextStream stream(&file);
		stream.setCodec("UTF-8");						//���ö�ȡʱ����ΪUTF-8

		QByteArray data = stream.readAll().toUtf8();	//��ȡ�ı�����������
		int fileSize = data.count();
		qDebug() << "string size" << fileSize << endl;

		QJsonObject json = QJsonObject();
		json.insert("order", "upload");
        QStringList fileNameList = fileName.split('/');
		json.insert("filename",fileNameList[fileNameList.size()-1]);
		json.insert("filesize", fileSize);
		json.insert("language", language);

		QJsonDocument doc(json);
		QByteArray news = doc.toJson(QJsonDocument::Compact);

		int newsLength = news.length();

		qDebug() << json.count() << "  " << newsLength;

		this->sendUInt32(newsLength);
		this->send(news);
		this->send(data);
	}
	catch (QException ex)
	{
		QMessageBox::information(this, tr("error"), tr("failed to send request"));
	}

	file.close();
	return true;
}

void CommunicationClass::sendArgs(QString args)
{
	this->send(args);
}

void CommunicationClass::newsComeFromSever()
{
	QByteArray bytes = socket->readAll();

	qDebug() << "news��" << bytes << endl;			//�����������Ϣ

	QString news = QVariant(bytes).toString();		//QVariant��һ������ת������������������

	emit newsComming(news);							//�����ź�
}

void CommunicationClass::send(QString news,int length)
{
	if (length < 0)
	{
		this->socket->write(news.toUtf8());					//��������
	}
	else
	{
		this->socket->write(news.toUtf8().toStdString().c_str(), length);					//��������
	}
	this->socket->flush();
}

void CommunicationClass::send(QByteArray news)
{
	this->socket->write(news);									//��������
	this->socket->flush();
}

void CommunicationClass::send(int news, int length)
{
	QString string = "";
	QString str = QString::number(news, 10);
	int len = str.length();

	int times =length-len;
	if (times > 0);
	{
		for (int i = 0; i < times; i++)
		{
			string += "i";
		}
	}
	string += str;

	this->socket->write(string.toUtf8().toStdString().c_str());						//��������

	socket->flush();
}

void CommunicationClass::sendUInt32(unsigned int num)
{
	QByteArray bytes;
	bytes.resize(4);

	bytes[0] =(uchar)(0x000000ff & num);
	bytes[1] = (uchar)((0x0000ff00 & num)>>8);
	bytes[2] = (uchar)((0x00ff0000 & num)>>16);
	bytes[3] = (uchar)((0xff000000 & num)>>24);

	this->send(bytes);
}
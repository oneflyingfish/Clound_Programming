#pragma once
#pragma execution_character_set("utf-8")
#include <QtWidgets/QWidget>
#include<QBoxLayout>
#include<QString>
#include<QLabel>
#include<QPixmap>

/// <summary>
/// "�鿴����"/"��������"/"�鿴��Ȩ"ʱ�õ��ĵ�����ʾ��
/// </summary>
class MyDialog : public QWidget
{
	Q_OBJECT
public:
	//��ʾ�Ի��򣬲���1�����⣬����2��ͼƬ
	MyDialog(QString,QString, QWidget *parent = Q_NULLPTR);
};


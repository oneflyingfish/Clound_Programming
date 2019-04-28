#pragma once
#pragma execution_character_set("utf-8")
#include <QtWidgets/QWidget>
#include<QBoxLayout>
#include<QString>
#include<QLabel>
#include<QPixmap>

/// <summary>
/// "查看帮助"/"关于我们"/"查看版权"时用到的弹出显示框
/// </summary>
class MyDialog : public QWidget
{
	Q_OBJECT
public:
	//显示对话框，参数1：标题，参数2：图片
	MyDialog(QString,QString, QWidget *parent = Q_NULLPTR);
};


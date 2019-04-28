#ifndef MYTABWIDGET_H
#define MYTABWIDGET_H

#ifdef WIN32
#pragma execution_character_set("utf-8")

#endif

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QStatusbar>
#include <QLabel>
#include <QString>
#include <QTextEdit>
#include <QGroupBox>
#include <QBoxLayout>
#include <QProgressBar>
#include <QSplitter>
#include <QPushButton>
#include <QDateTime>
#include <QCheckBox>
#include <QLineEdit>
#include <stdio.h>
#include "Qsci/QSciScintilla.h"
#include "MyTextEdit.h"

class MyTabWidget :public QWidget
{
	Q_OBJECT
public:
	MyTabWidget();
	~MyTabWidget();
	void AddTxt(QString txt, QColor color = Qt::black);
	void AddStartSeparate();
	void AddEndSeparate();
	void SetTheFileKind(QString);
	void SetTheFileName(QString);
	void SendProgramArgs(bool);

public:
signals:void sendArgEmit(QObject*);

public slots:
	void sendArgclicked();

public:
	MyTextEdit *textEdit= new MyTextEdit();
	QTextEdit *outputTextEdit = new QTextEdit();
	QGroupBox *outputGroupBox = new QGroupBox(tr("输出"));
	QStatusBar *statusBar = new QStatusBar();
	QSplitter *splitter = new QSplitter(Qt::Vertical, 0);
	QPushButton *sendArg = new QPushButton(tr("传参"));
	QLineEdit* argLine = new QLineEdit();
	//状态栏
	QLabel *programTipLabel = new QLabel(tr("文件类型："));
	QLabel *fileNameLabel=new QLabel();
	QLabel *programLabel = new QLabel();
	/*QLabel *progressLabel = new QLabel();
	QProgressBar *progressBar = new QProgressBar();*/
	QCheckBox *downloadFile = new QCheckBox(tr("下载二进制文件"));

	QString startString ;
	QString showFileKindString;
	QString memoryFileNameString;
};

#endif
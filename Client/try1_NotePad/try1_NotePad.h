#ifndef TRY_NOTEPAD_H
#define TRY_NOTEPAD_H

#ifdef WIN32
#pragma execution_character_set("utf-8")

#endif

#include<QtWidgets/QWidget>
#include<QtWidgets/QApplication>
#include<QIcon>
#include<QMenu>
#include<QSizePolicy>
#include<QMenuBar>
#include<QGridLayout>
#include<QAction>
#include<QString>
#include<QTextEdit>
#include<QTextDocument>
#include<QBitmap>
#include<QTextFrame>
#include<QTextFrameFormat>
#include<QByteArray>
#include<QFile>
#include<QActionGroup>
#include<QTranslator>
#include<QComboBox>
#include<QPushButton>
#include<QToolBar>
#include<QAbstractItemView>
#include<QStringList>
#include<QStatusBar>
#include<QProgressBar>
#include<QLabel>
#include<QToolButton>
#include<QSpacerItem> 
#include<QDesktopServices>
#include<QFileDialog>
#include<QTabWidget>
#include<QCloseEvent>
#include<QStandardPaths>
#include<qdebug.h>
#include<QDesktopServices>
#include"MyTabWidget.h"
#include"MyDialog.h"
#include"MyTextEdit.h"
#include"CommunicationClass.h"

class try1_NotePad : public QWidget
{
	Q_OBJECT

public:
	try1_NotePad(QWidget *parent = Q_NULLPTR);
	~try1_NotePad();
	void StartRun();
	void EndRun();

protected:
	virtual void closeEvent(QCloseEvent*);

//文件
public slots:void fileNewFile();
public slots:void fileOpen();
public slots:void fileSave();
public slots:void fileSaveAll();
public slots:void fileSaveAs();
public slots:void fileOpenCmd();
public slots:void fileOpenPath();
public slots:void fileClose();
public slots:void fileExit();
//编辑
public slots:void editUndo();
public slots:void editRedo();
public slots:void editCut();
public slots:void editCopy();
public slots:void editPaste();
//public slots:void editGoto();
//public slots:void editFindAll();
public slots:void editSelectAll();
public slots:void editUpperOrLower();
public slots:void editShowSpace();
//查看
public slots:void viewAutoLine();
public slots:void setLanguageChinese(bool);
public slots:void setLanguageEnglish(bool);
//语言
public slots:void ProgramText();
public slots:void ProgramC();
public slots:void ProgramCpp();
public slots:void ProgramJava();
public slots:void ProgramPython2();
public slots:void ProgramPython3();
//工具
public slots:void ToolLanguage();
//运行
public slots:void runExec();
//帮助
public slots:void helpViewHelp();
public slots:void helpAboutUs();
//语言选择
//public slots:void chooseLanguage();
//TabWidget
public slots:void addNewTabEmit();
public slots:void deleteTabEmit(int);
//发送参数
public slots:void sendArgEmit(QObject*);
//程序种类改变
public slots:void changeProgram(QString);
//tab改变
public slots:void changeTabWidget(int);
//lineEdit
//public slots:void lineEditEnter();
//中英文互译

//运行结束
public slots:void endRunning();
public slots:void newsCommingForShow(QString);
//帮助对话关闭
public slots:void helpClose();
//关于我们对话关闭
public slots:void aboutUsClose();

private:
	void getForm();
	void connectSignalAndSlot();
	void loadText();
	MyTabWidget* getCurrentTabWidget();

private:
	//菜单栏
	QMenuBar *menuBar;
	//工具栏
	QToolBar *toolBar;

	//文件菜单
	QMenu *fileMenu;
	QAction *newAction;
	QAction *openAction;
	QAction *saveAction;
	QAction *saveAllAction;
	QAction *resaveAction;
	QAction *openCmdAction;
	QAction *openPathAction;
	QAction *closeAction;
	QAction *exitAction;

	//编辑菜单
	QMenu *editMenu;
	QAction *repealAction;
	QAction *redoAction;
	QAction *cutAction;
	QAction *copyAction;
	QAction *pasteAction;
	QAction *lowOrUpperAction;
	//QAction *gotoAction;
	//QAction *findAllAction;
	QAction *selectAllAction;
	QAction *showSpaceAction;

	//查看菜单
	QMenu *formatMenu;
	QAction *autoLineAction;
	//QAction *fontAction;
	QMenu *languageMenu;
	QAction *ChineseSelectedAction;
	QAction *EnglishSelectedAction;

	//语言菜单
	QMenu *languageMenuP;
	QAction *textAction;
	//QAction *bashAction;
	QAction *cAction;
	QAction *cppAction;
	//QAction *cSharpMenu;
	QAction *javaAction;
	QAction *python2Action;
	QAction *python3Action;

	//工具菜单
	QMenu *toolMenu;
	QAction *dictionaryAction;

	//运行菜单
	QMenu *runMenu;
	QAction *runAction;

	//帮助菜单
	QMenu *helpMenu;
	QAction *helpAction;
	QAction *aboutAction;

	//编辑
	QTabWidget *tabWidget;
	QToolButton *addTabButton;
	QLabel *spaceLabel;

	QComboBox *osKind;                  //未启用，留下接口
	QComboBox *languageKind;
	QTranslator *EnglishTranslator;
	QList<MyTabWidget*> tabList;
	//QLineEdit *lineEdit;

	QString fileDialogTip;
	QString saveAsDialogTip;
	QString runningFilename;
	MyTabWidget* runningTab;
	CommunicationClass *communicate;

	//信息框
	MyDialog *helpDialog = NULL;
	MyDialog *aboutUsDialog = NULL;

	int status = 0;		//0：正常 1:跳转 2:查找
};

#endif
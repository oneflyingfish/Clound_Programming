#include "try1_NotePad.h"

//定义构造函数
try1_NotePad::try1_NotePad(QWidget *parent):QWidget(parent)
{
	this->setWindowIcon(QIcon(":/try1_NotePad/Icon/NotepadLogo.ico"));

	//加载翻译家
	EnglishTranslator = new QTranslator(this);
	EnglishTranslator->load("./try1_notepad_en.qm");
	//初始化界面
	getForm();
	//绑定信号
	connectSignalAndSlot();
	//加载文字
	loadText();
}

//绑定信号
void try1_NotePad::connectSignalAndSlot()
{
	//connect(newAction, SIGNAL(destroyed(QObject*)), this, SLOT(fileExit()));
	//文件菜单
	connect(newAction, SIGNAL(triggered(bool)), this, SLOT(fileNewFile()));
	connect(openAction, SIGNAL(triggered(bool)), this, SLOT(fileOpen()));
	connect(saveAction, SIGNAL(triggered(bool)), this, SLOT(fileSave()));
	connect(saveAllAction, SIGNAL(triggered(bool)), this, SLOT(fileSaveAll()));
	connect(resaveAction, SIGNAL(triggered(bool)), this, SLOT(fileSaveAs()));
	connect(openCmdAction, SIGNAL(triggered(bool)), this, SLOT(fileOpenCmd()));
	connect(openPathAction, SIGNAL(triggered(bool)), this, SLOT(fileOpenPath()));
	connect(closeAction, SIGNAL(triggered(bool)), this, SLOT(fileClose()));
	connect(exitAction, SIGNAL(triggered(bool)), this, SLOT(fileExit()));
	//编辑菜单
	connect(repealAction, SIGNAL(triggered(bool)), this, SLOT(editUndo()));
	connect(cutAction, SIGNAL(triggered(bool)), this, SLOT(editCut()));
	connect(copyAction, SIGNAL(triggered(bool)), this, SLOT(editCopy()));
	connect(pasteAction, SIGNAL(triggered(bool)), this, SLOT(editPaste()));
	connect(redoAction, SIGNAL(triggered(bool)), this, SLOT(editRedo()));
	connect(lowOrUpperAction, SIGNAL(triggered(bool)), this, SLOT(editUpperOrLower()));
	//connect(gotoAction, SIGNAL(triggered(bool)), this, SLOT(editSelectAll()));
	//connect(findAllAction, SIGNAL(triggered(bool)), this, SLOT(editFindAll()));
	connect(selectAllAction, SIGNAL(triggered(bool)), this, SLOT(editSelectAll()));
	connect(showSpaceAction, SIGNAL(triggered(bool)), this, SLOT(editShowSpace()));
	//查看菜单
	connect(autoLineAction, SIGNAL(triggered(bool)), this, SLOT(viewAutoLine()));
	connect(ChineseSelectedAction, SIGNAL(triggered(bool)), this, SLOT(setLanguageChinese(bool)));
	connect(EnglishSelectedAction, SIGNAL(triggered(bool)), this, SLOT(setLanguageEnglish(bool)));
	//语言菜单
	connect(textAction, SIGNAL(triggered(bool)), this, SLOT(ProgramText()));
	connect(cAction, SIGNAL(triggered(bool)), this, SLOT(ProgramC()));
	connect(cppAction, SIGNAL(triggered(bool)), this, SLOT(ProgramCpp()));
	connect(javaAction, SIGNAL(triggered(bool)), this, SLOT(ProgramJava()));
	connect(python2Action, SIGNAL(triggered(bool)), this, SLOT(ProgramPython2()));
	connect(python3Action, SIGNAL(triggered(bool)), this, SLOT(ProgramPython3()));
	//工具菜单
	connect(dictionaryAction, SIGNAL(triggered(bool)), this, SLOT(ToolLanguage()));
	//运行菜单
	connect(runAction, SIGNAL(triggered(bool)), this, SLOT(runExec()));
	//帮助菜单
	connect(helpAction,SIGNAL(triggered(bool)), this, SLOT(helpViewHelp()));
	connect(aboutAction, SIGNAL(triggered(bool)), this, SLOT(helpAboutUs()));
	//TabWidget
	connect(addTabButton, SIGNAL(clicked(bool)), this, SLOT(addNewTabEmit()));
	connect(tabWidget->tabBar(), SIGNAL(tabCloseRequested(int)), this, SLOT(deleteTabEmit(int)));
	////发送参数
	//connect(tabWidget, SIGNAL(sendArgEmit(QObject*)), this, SLOT(sendArgEmit()));
	//程序种类改变
	connect(languageKind, SIGNAL(currentIndexChanged(QString)),this,SLOT(changeProgram(QString)));
	//tab改变
	connect(tabWidget, SIGNAL(currentChanged(int)), this, SLOT(changeTabWidget(int)));
	//lineEdit
	//connect(lineEdit, SIGNAL(editingFinished()), this, SLOT(lineEditEnter()));

	connect(helpDialog, SIGNAL(destroyed(QObject*)), this, SLOT(helpClose()));
	connect(aboutUsDialog, SIGNAL(destroyed(QObject*)), this, SLOT(aboutUsClose()));
}

void try1_NotePad::helpClose()
{
	delete this->helpDialog;
	this->helpDialog = NULL;
}

void try1_NotePad::aboutUsClose()
{
	delete this->aboutUsDialog;
	this->aboutUsDialog = NULL;
}

//加载文字
void try1_NotePad::loadText()
{
	this->setWindowTitle(tr("Cloud Programming"));
	//文件菜单
	fileDialogTip = tr("打开一个/多个文件");
	saveAsDialogTip = tr("保存为");

	fileMenu->setTitle(tr("文件(&F)"));
	newAction->setText(tr("新建(&N)"));
	openAction->setText(tr("打开(&O)"));
	saveAction->setText(tr("保存(&S)"));
	saveAllAction->setText(tr("保存所有"));
	resaveAction->setText(tr("另存为"));
	openCmdAction->setText(tr("打开命令行"));
	openPathAction->setText(tr("打开文件所在路径"));
	closeAction->setText(tr("关闭"));
	exitAction->setText(tr("退出"));

	//编辑菜单
	editMenu->setTitle(tr("编辑(&E)"));
	repealAction->setText(tr("撤销(&Z)"));
	redoAction->setText(tr("反撤销(&Y)"));
	cutAction->setText(tr("剪切(&X)"));
	copyAction->setText(tr("复制(&C)"));
	pasteAction->setText(tr("粘贴(&V)"));
	//gotoAction->setText(tr("转到(&G)"));
	//findAllAction->setText(tr("查找所有"));
	selectAllAction->setText(tr("全选(A)"));
	lowOrUpperAction->setText(tr("大/小写转化"));
	showSpaceAction->setText(tr("显示空格"));

	//查看菜单
	formatMenu->setTitle(tr("查看(&M)"));
	autoLineAction->setText(tr("自动换行(&W)"));
	//fontAction->setText(tr("字体(&F)"));
	languageMenu->setTitle(tr("语言(&Language)"));
	ChineseSelectedAction->setText(tr("中文"));
	EnglishSelectedAction->setText(tr("English"));

	//语言菜单
	languageMenuP->setTitle(tr("语言(&P)"));
	textAction->setText(tr("Text"));
	//bashAction->setText(tr("Bash"));
	cAction->setText(tr("C"));
	cppAction->setText(tr("C++"));
	//cSharpMenu->setText(tr("C#"));
	javaAction->setText(tr("Java"));
	python2Action->setText(tr("python"));
	python3Action->setText(tr("python3"));

	//工具菜单
	toolMenu->setTitle(tr("工具(&T)"));
	dictionaryAction->setText(tr("字典(&D)"));

	//运行菜单
	runMenu->setTitle(tr("运行(&F)"));
	runAction->setText(tr("执行程序"));
	runAction->setShortcut(tr("F5"));

	//帮助菜单
	helpMenu->setTitle(tr("帮助(&H)"));
	helpAction->setText(tr("查看帮助(&H)"));
	aboutAction->setText(tr("关于我们(&A)"));

	this->addTabButton->setToolTip(tr("点击新建文本"));

	//刷新Tab
	for (int i = 0; i < tabList.count(); i++)
	{
		tabList[i]->outputGroupBox->setTitle(tr("输出"));
		tabList[i]->sendArg->setText(tr("传参"));
		tabList[i]->sendArg->setToolTip(tr("点击传送参数"));
		tabList[i]->downloadFile->setText(tr("下载二进制文件"));
		tabList[i]->startString = tr("开始执行");
		tabList[i]->argLine->setPlaceholderText(tr("此处写入程序参数，可分多次写入"));
		tabList[i]->programTipLabel->setText(tr("文件类型"));
		tabList[i]->memoryFileNameString =tr("临时文件");
	}
}

try1_NotePad::~try1_NotePad()
{
	if (tabList.count() > 0)
	{
		for (int i = 0; i < tabList.count(); i++)
		{
			delete tabList[i];
		}
	}

	menuBar->deleteLater();
	//工具栏
	toolBar->deleteLater();

	//文件菜单
	fileMenu->deleteLater();
	newAction->deleteLater();
	openAction->deleteLater();
	saveAction->deleteLater();
	saveAllAction->deleteLater();
	resaveAction->deleteLater();
	openCmdAction->deleteLater();
	openPathAction->deleteLater();
	closeAction->deleteLater();
	exitAction->deleteLater();

	//编辑菜单
	editMenu->deleteLater();
	repealAction->deleteLater();
	redoAction->deleteLater();
	cutAction->deleteLater();
	copyAction->deleteLater();
	pasteAction->deleteLater();
	lowOrUpperAction->deleteLater();
	//gotoAction->deleteLater();
	//findAllAction->deleteLater();
	selectAllAction->deleteLater();
	showSpaceAction->deleteLater();

	//查看菜单
	formatMenu->deleteLater();
	autoLineAction->deleteLater();
	//fontAction->deleteLater();
	languageMenu->deleteLater();
	ChineseSelectedAction->deleteLater();
	EnglishSelectedAction->deleteLater();

	//语言菜单
	languageMenuP->deleteLater();
	textAction->deleteLater();
	//bashAction->deleteLater();
	cAction->deleteLater();
	cppAction->deleteLater();
	//cSharpMenu->deleteLater();
	javaAction->deleteLater();
	python2Action->deleteLater();
	python3Action->deleteLater();

	//工具菜单
	toolMenu->deleteLater();
	dictionaryAction->deleteLater();

	//运行菜单
	runMenu->deleteLater();
	runAction->deleteLater();

	//帮助菜单
	helpMenu->deleteLater();
	helpAction->deleteLater();
	aboutAction->deleteLater();

	//编辑
	tabWidget->deleteLater();
	addTabButton->deleteLater();
	spaceLabel->deleteLater();

	osKind->deleteLater();
	languageKind->deleteLater();
	EnglishTranslator->deleteLater();
}

void try1_NotePad::getForm()
{
	this->resize(1000, 700);
	this->setStyleSheet("QWidget{background-color: rgb(255, 255, 255);font: 10pt \"微软雅黑\";}");

	//定义菜单栏
	menuBar = new QMenuBar();
	//文件菜单
	fileMenu =new QMenu();
	newAction=new QAction();
	newAction->setIcon(QIcon("./Icon/new.ico"));
	newAction->setShortcut(tr("Ctrl+N"));
	openAction=new QAction();
	openAction->setIcon(QIcon("./Icon/openFile.ico"));
	openAction->setShortcut(tr("Ctrl+O"));
	saveAction = new QAction();
	saveAction->setIcon(QIcon("./Icon/save.ico"));
	saveAction->setShortcut(tr("Ctrl+S"));
	saveAllAction = new QAction();
	saveAllAction->setIcon(QIcon("./Icon/saveAll.ico"));
	saveAction->setShortcut(tr("Alt+T"));
	openCmdAction = new QAction();
	openCmdAction->setIcon(QIcon("./Icon/openCmd.ico"));
	
	openPathAction = new QAction();
	openPathAction->setIcon(QIcon("./Icon/openPath.ico"));
	resaveAction = new QAction();
	resaveAction->setIcon(QIcon("./Icon/resave.ico"));
	closeAction = new QAction();
	closeAction->setIcon(QIcon("./Icon/close.ico"));
	exitAction=new QAction();
	exitAction->setIcon(QIcon("./Icon/closeAll.ico"));

	//组合文件菜单
	fileMenu->addAction(newAction);
	fileMenu->addAction(openAction);
	fileMenu->addAction(saveAction);
	fileMenu->addAction(saveAllAction);
	fileMenu->addAction(resaveAction);
	fileMenu->addSeparator();
	fileMenu->addAction(openCmdAction);
	fileMenu->addAction(openPathAction);
	fileMenu->addSeparator();
	fileMenu->addAction(closeAction);
	fileMenu->addAction(exitAction);

	//编辑菜单
	editMenu =new QMenu();
	repealAction=new QAction();
	repealAction->setIcon(QIcon("./Icon/repeal.ico"));
	repealAction->setShortcut(tr("Ctrl+Z"));
	redoAction = new QAction();
	redoAction->setIcon(QIcon("./Icon/redo.ico"));
	redoAction->setShortcut(tr("Ctrl+Y"));
	cutAction=new QAction();
	cutAction->setIcon(QIcon("./Icon/cut.ico"));
	cutAction->setShortcut(tr("Ctrl+X"));
	copyAction=new QAction();
	copyAction->setIcon(QIcon("./Icon/copy.ico"));
	copyAction->setShortcut(tr("Ctrl+C"));
	pasteAction=new QAction();
	pasteAction->setIcon(QIcon("./Icon/paste.ico"));
	pasteAction->setShortcut(tr("Ctrl+V"));
	/*gotoAction=new QAction();
	gotoAction->setIcon(QIcon("./Icon/goto.ico"));
	gotoAction->setShortcut(tr("Ctrl+G"));
	findAllAction = new QAction();
	findAllAction->setIcon(QIcon("./Icon/find.ico"));
	findAllAction->setShortcut(tr("Ctrl+F"));*/
	selectAllAction=new QAction();
	selectAllAction->setIcon(QIcon("./Icon/selectAll.ico"));
	selectAllAction->setShortcut(tr("Ctrl+A"));
	lowOrUpperAction = new QAction();
	lowOrUpperAction->setIcon(QIcon("./Icon/changeKind.ico"));
	lowOrUpperAction->setShortcut(tr("Ctrl+U"));
	showSpaceAction =new QAction();
	showSpaceAction->setCheckable(true);
	showSpaceAction->setIcon(QIcon("./Icon/showSpace.ico"));
	//组合编辑菜单
	editMenu->addAction(repealAction);
	editMenu->addAction(redoAction);
	editMenu->addSeparator();
	editMenu->addAction(cutAction);
	editMenu->addAction(copyAction);
	editMenu->addAction(pasteAction);
	editMenu->addSeparator();
	//editMenu->addAction(gotoAction);
	editMenu->addSeparator();
	editMenu->addAction(selectAllAction);
	editMenu->addAction(lowOrUpperAction);
	editMenu->addAction(showSpaceAction);

	//查看菜单
	formatMenu =new QMenu();
	autoLineAction=new QAction();
	autoLineAction->setCheckable(true);
	//fontAction=new QAction();
	languageMenu = new QMenu();
	ChineseSelectedAction = new QAction();
	ChineseSelectedAction->setCheckable(true);
	EnglishSelectedAction = new QAction();
	EnglishSelectedAction->setCheckable(true);
	//设置互斥
	QActionGroup *actionGroup = new QActionGroup(languageMenu);
	actionGroup->addAction(ChineseSelectedAction);
	actionGroup->addAction(EnglishSelectedAction);
	ChineseSelectedAction->setChecked(true);
	//组合查看菜单
	formatMenu->addAction(autoLineAction);
	//formatMenu->addAction(fontAction);
	formatMenu->addMenu(languageMenu);
	languageMenu->addAction(ChineseSelectedAction);
	languageMenu->addAction(EnglishSelectedAction);
	
	//语言菜单
	languageMenuP = new QMenu();
	textAction = new QAction();
	textAction->setCheckable(true);
	//bashAction = new QAction();
	//bashAction->setCheckable(true);
	cAction = new QAction();
	cAction->setCheckable(true);
	cppAction = new QAction();
	cppAction->setCheckable(true);
	//cSharpMenu = new QAction();
	//cSharpMenu->setCheckable(true);
	javaAction = new QAction();
	javaAction->setCheckable(true);
	python2Action = new QAction();
	python2Action->setCheckable(true);
	python3Action = new QAction();
	python3Action->setCheckable(true);
	//设置互斥
	QActionGroup *actionGroupL = new QActionGroup(languageMenuP);
	actionGroupL->addAction(textAction);
	//actionGroupL->addAction(bashAction);
	actionGroupL->addAction(cAction);
	actionGroupL->addAction(cppAction);
	//actionGroupL->addAction(cSharpMenu);
	actionGroupL->addAction(javaAction);
	actionGroupL->addAction(python2Action);
	actionGroupL->addAction(python3Action);
	textAction->setChecked(true);
	//组合语言菜单
	languageMenuP->addAction(textAction);
	//languageMenuP->addAction(bashAction);
	languageMenuP->addAction(cAction);
	languageMenuP->addAction(cppAction);
	//languageMenuP->addAction(cSharpMenu);
	languageMenuP->addAction(javaAction);
	languageMenuP->addAction(python2Action);
	languageMenuP->addAction(python3Action);

	//工具菜单
	toolMenu = new QMenu();
	dictionaryAction = new QAction();
	dictionaryAction->setIcon(QIcon("./Icon/dictionary.ico"));
	//组合工具菜单
	toolMenu->addAction(dictionaryAction);

	//运行菜单
	runMenu = new QMenu();
	runAction = new QAction();
	runAction->setIcon(QIcon("./Icon/run.ico"));
	//组合运行菜单
	runMenu->addAction(runAction);

	//帮助菜单
	helpMenu =new QMenu();
	helpAction=new QAction();
	helpAction->setIcon(QIcon("./Icon/help.ico"));
	aboutAction=new QAction();
	aboutAction->setIcon(QIcon("./Icon/about.ico"));
	//组合帮助菜单
	helpMenu->addAction(helpAction);
	helpMenu->addSeparator();
	helpMenu->addAction(aboutAction);

	//组合总菜单栏
	menuBar->addMenu(fileMenu);
	menuBar->addMenu(editMenu);
	menuBar->addMenu(formatMenu);
	menuBar->addMenu(languageMenuP);
	menuBar->addMenu(toolMenu);
	menuBar->addMenu(runMenu);
	menuBar->addMenu(helpMenu);

	//定义工具栏
	toolBar = new QToolBar();
	toolBar->setStyleSheet("background-color: rgb(255, 255, 255);");
	toolBar->setIconSize(QSize(18, 18));
	toolBar->addAction(newAction);
	toolBar->addAction(openAction);
	toolBar->addAction(saveAction);
	toolBar->addAction(resaveAction);
	toolBar->addAction(saveAllAction);
	toolBar->addAction(openPathAction);

	toolBar->addSeparator();
	toolBar->addAction(closeAction);
	toolBar->addAction(exitAction);

	toolBar->addSeparator();
	toolBar->addAction(repealAction);
	toolBar->addAction(redoAction);
	toolBar->addAction(cutAction);
	toolBar->addAction(copyAction);
	toolBar->addAction(pasteAction);
	toolBar->addAction(selectAllAction);

	toolBar->addSeparator();
	osKind = new QComboBox();
	languageKind = new QComboBox();
	osKind->setEditable(false);
	osKind->setIconSize(QSize(10, 10));
	osKind->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Expanding);
	osKind->setMaximumWidth(115);
	osKind->setStyleSheet("border: 1px solid rgb(230, 230, 230); background-color: rgb(255, 255, 255);color: rgb(0, 0, 0);font: 10pt \"微软雅黑\";");
	//osKind->addItems(QStringList() << "LocalHost" << "Windows" << "Linux" << "Mac os");
	osKind->addItems(QStringList() << "Windows" << "Linux" << "Mac os");
	for (int i = 0; i < osKind->count(); i++)
	{
		osKind->setItemIcon(i, QIcon("./Icon/system.ico"));
	}
	osKind->setCurrentText(tr("Linux"));

	languageKind->setEditable(false);
	languageKind->setIconSize(QSize(14, 14));
	languageKind->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
	languageKind->setMaximumWidth(115);
	languageKind->setStyleSheet("border: 1px solid rgb(230, 230, 230); background-color: rgb(255, 255, 255);color: rgb(0, 0, 0);font: 10pt \"微软雅黑\";");
	languageKind->addItems(QStringList() << "Text" << "C" << "C++" <<"Java" << "python" << "python3");
	for (int i = 0; i < languageKind->count(); i++)
	{
		languageKind->setItemIcon(i, QIcon("./Icon/program.ico"));
	}
	languageKind->setCurrentText(tr("Text"));

    osKind->setVisible(false);      //禁用系统选择
	//toolBar->addWidget(osKind);
	QWidget *spacing1 = new QWidget();
	spacing1->setMinimumWidth(5);
	toolBar->addWidget(spacing1);
	toolBar->addWidget(languageKind);
	QWidget *spacing2 = new QWidget();
	spacing1->setMinimumWidth(5);
	toolBar->addWidget(spacing2);
	toolBar->addAction(runAction);

	toolBar->addSeparator();
	//toolBar->addAction(gotoAction);
	toolBar->addAction(dictionaryAction);
	toolBar->addAction(openCmdAction);
	toolBar->addAction(helpAction);
	toolBar->addAction(aboutAction);

	//定义中间的窗体
	tabWidget = new QTabWidget();
	tabWidget->setStyleSheet("QTabWidget{background-color: rgba(255,255,255,0);} QTabBar::close-button{image:url(./Icon/closeTab.ico);subcontrol-position: Right;} QTabBar::close-button::hover{image:url(./Icon/closeTabHover.ico);}");
	((QTabBar*)tabWidget->tabBar())->setTabsClosable(true);
	tabWidget->setMovable(true);
	//添加tabBar右侧的添加按钮
	QWidget *tabTopRightWidget = new QWidget();				//定义空白窗体
	
	QHBoxLayout *tabTopRightHBox = new QHBoxLayout();
	addTabButton = new QToolButton();						//定义添加按钮
	addTabButton->setIcon(QIcon("./Icon/addTab.ico"));

	tabWidget->tabBar()->addAction(newAction);
	tabWidget->addAction(newAction);

	addTabButton = new QToolButton();
	addTabButton->setStyleSheet("border: 1px solid rgb(255, 255, 255,0);");
	addTabButton->setIcon(QIcon("./Icon/addTab.ico"));
	addTabButton->setToolTip(tr("点击新建文本"));
	/*lineEdit = new QLineEdit();
	lineEdit->setPlaceholderText("input the key words here");*/
	tabWidget->setCornerWidget(addTabButton, Qt::TopRightCorner);

	MyTabWidget* newTab = new MyTabWidget();
	tabList.append(newTab);
	tabWidget->addTab(newTab, QIcon("./Icon/tabIcon.ico"), tr("new") + QString::number(tabList.count(), 10));
	connect(newTab, SIGNAL(sendArgEmit(QObject*)), this, SLOT(sendArgEmit(QObject*)));

	//设置相关参数
	/*textEdit = new QTextEdit();
	textEdit->setStyleSheet("QTextEdit{font: 12pt \"微软雅黑\";}");
	textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	textEdit->setFrameShape(QFrame::Box);*/
	//设置换行
	//textEdit->setWordWrapMode(QTextOption::NoWrap);							//设置不自动换行
	//textEdit->setWordWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);		//标点处换行
	//textEdit->setWordWrapMode(QTextOption::WrapAnywhere);						//强行换行
	//textEdit->setWordWrapMode(QTextOption::boundaries);						//句末换行

	QVBoxLayout *mainVBoxLayout = new QVBoxLayout();
	mainVBoxLayout->setMenuBar(menuBar);
	mainVBoxLayout->addWidget(toolBar);
	mainVBoxLayout->addWidget(tabWidget);
	//mainVBoxLayout->addWidget(statusBar);
	mainVBoxLayout->setMargin(0);
	this->setLayout(mainVBoxLayout);
}

void try1_NotePad::closeEvent(QCloseEvent *)
{
	this->fileSaveAll();
}

MyTabWidget* try1_NotePad::getCurrentTabWidget()
{
	return (MyTabWidget*)(this->tabWidget->currentWidget());
}

//定义槽函数
//新建文件
void try1_NotePad:: fileNewFile()
{
	this->addTabButton->click();
}

//打开文件
void try1_NotePad:: fileOpen()
{
	QStringList filePathList = QFileDialog::getOpenFileNames(this, fileDialogTip, QStandardPaths::writableLocation(QStandardPaths::DesktopLocation));
	for (int i = 0; i < filePathList.count(); i++)
	{
	START:
		if (i >= filePathList.count())
		{
			return;
		}

		for (int j = 0; j < tabList.count(); j++)
		{
			if (this->tabList[j]->fileNameLabel->text() == filePathList[i])
			{
				int choice=QMessageBox::information(this, tr("warning"), QString("are you sure to reload \"%1\" without saving firstly" ).arg(filePathList[i]),QMessageBox::Yes | QMessageBox::Cancel);
				if (choice == QMessageBox::Yes)
				{
					this->tabWidget->setCurrentWidget(tabList[j]);
					break;
				}
				else
				{
					i++;
					goto START;
				}
			}
			else if (j >= tabList.count()-1)
			{
				this->addTabButton->click();	//建立新的编辑页面并跳转
			}
		}


		QFile file(filePathList[i]);
		file.open(QIODevice::ReadOnly | QIODevice::Text);

		QByteArray t = file.readAll();
		this->getCurrentTabWidget()->textEdit->setText(QString(t));
		this->getCurrentTabWidget()->SetTheFileName(filePathList[i]);
		this->tabWidget->tabBar()->setTabText(tabWidget->currentIndex(), filePathList[i].section(tr("/"), -1));

		file.close();


		if (filePathList[i].toLower().endsWith(tr(".c")))
		{
			
			this->cAction->trigger();
		}
		else if(filePathList[i].toLower().endsWith(tr(".cpp")) || filePathList[i].toLower().endsWith(tr(".cc")))
		{
			this->cppAction->trigger();
		}
		else if (filePathList[i].toLower().endsWith(tr(".java")))
		{
			this->javaAction->trigger();
		}
		else if (filePathList[i].toLower().endsWith(tr(".py")))
		{
			this->python2Action->trigger();
		}
		else
		{
			this->textAction->trigger();
		}
	}
}

void try1_NotePad::fileSave()
{
	MyTabWidget* tabWidget = getCurrentTabWidget();
	QString fileName = tr("");

	if (tabWidget->fileNameLabel->text()==tr("临时文件") || tabWidget->fileNameLabel->text() == tr("temporary files"))
	{
		fileName = QFileDialog::getSaveFileName(this,saveAsDialogTip, QStandardPaths::writableLocation(QStandardPaths::DesktopLocation)+ tr("/")+ this->tabWidget->tabBar()->tabText(this->tabWidget->currentIndex()));
	}
	else
	{
		fileName = tabWidget->fileNameLabel->text();
	}

	if (fileName == tr(""))
	{
		return;
	}

	QFile file(fileName);
	file.open(QIODevice::WriteOnly | QIODevice::Text);

	QTextStream writer(&file);
	writer.setCodec("UTF-8");
	writer << tabWidget->textEdit->text();
	writer.flush();

	this->tabWidget->tabBar()->setTabText(this->tabWidget->currentIndex(), fileName.section(tr("/"), -1));
	this->getCurrentTabWidget()->fileNameLabel->setText(fileName);
	file.close();
}

void try1_NotePad::fileSaveAll()
{
	MyTabWidget *widget = this->getCurrentTabWidget();
	for (int i = 0; i < tabWidget->count(); i++)
	{
		this->tabWidget->setCurrentIndex(i);
		if (this->getCurrentTabWidget()->textEdit->text() == tr(""))
		{
			this->getCurrentTabWidget()->AddTxt(tr("this function will not save the blank file, you can try to use \"save\" or \"save as\".\n"), Qt::blue);
			continue;
		}
		this->fileSave();
	}

	this->tabWidget->setCurrentWidget(widget);
}

void try1_NotePad:: fileSaveAs()
{
	QString fileName = QFileDialog::getSaveFileName(this, saveAsDialogTip, QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) + tr("/new"));

	QFile file(fileName);
	file.open(QIODevice::WriteOnly | QIODevice::Text);

	QTextStream writer(&file);
	writer.setCodec("UTF-8");
	writer << this->getCurrentTabWidget()->textEdit->text();
	writer.flush();

	file.close();
}

void try1_NotePad:: fileOpenCmd()
{
	system("cmd.exe");
}

void try1_NotePad:: fileOpenPath()
{
	if (!QDesktopServices::openUrl(QUrl(this->getCurrentTabWidget()->fileNameLabel->text().section("/", 0, -2), QUrl::TolerantMode)))
	{
		QMessageBox::information(this, "warning", "path is not exist");
	}
}

void try1_NotePad:: fileClose()
{
	this->deleteTabEmit(this->tabWidget->tabBar()->currentIndex());
}

void try1_NotePad:: fileExit()
{
	//this->fileSaveAll();
	this->close();
}

//编辑
void try1_NotePad:: editUndo()
{
	this->getCurrentTabWidget()->textEdit->undo();
}

void try1_NotePad:: editCut()
{
	this->getCurrentTabWidget()->textEdit->cut();
}

void try1_NotePad:: editCopy()
{
	this->getCurrentTabWidget()->textEdit->copy();
}

void try1_NotePad:: editPaste()
{
	this->getCurrentTabWidget()->textEdit->paste();
}

void try1_NotePad::editRedo()
{
	this->getCurrentTabWidget()->textEdit->redo();
}

//void try1_NotePad:: editGoto()
//{
//	if (this->status == 0)
//	{
//		tabWidget->setCornerWidget(lineEdit, Qt::TopRightCorner);
//		this->status = 1;
//	}
//	else if (this->status == 1)
//	{
//		tabWidget->setCornerWidget(addTabButton, Qt::TopRightCorner);
//		this->status = 0;
//	}
//	if (this->status == 2)
//	{
//		this->status = 1;
//	}
//}

//void try1_NotePad::editFindAll()
//{
//	if (this->status == 0)
//	{
//		tabWidget->setCornerWidget(lineEdit, Qt::TopRightCorner);
//		this->status = 2;
//	}
//	else if (this->status == 1)
//	{
//		this->status = 2;
//	}
//	if (this->status == 2)
//	{
//
//		tabWidget->setCornerWidget(addTabButton, Qt::TopRightCorner);
//		this->status = 0;
//	}
//}

//void try1_NotePad::lineEditEnter()
//{
//	if (this->status == 1)
//	{
//		this->getCurrentTabWidget()->textEdit->
//	}
//	else if (this->status == 2)
//	{
//		this->getCurrentTabWidget()->textEdit->find;
//	}
//}

void try1_NotePad:: editSelectAll()
{
	this->getCurrentTabWidget()->textEdit->selectAll();
}

void try1_NotePad:: editUpperOrLower()
{
	static int a = 0;	//0：变小写 1：变大写
	if (a == 0)
	{
		this->getCurrentTabWidget()->textEdit->replaceSelectedText(this->getCurrentTabWidget()->textEdit->selectedText().toLower());
		a = (a + 1) % 2;
	}
	else if (a == 1)
	{
		this->getCurrentTabWidget()->textEdit->replaceSelectedText(this->getCurrentTabWidget()->textEdit->selectedText().toUpper());
		a = (a + 1) % 2;
	}
	
}

void try1_NotePad::editShowSpace()
{
	if (showSpaceAction->isChecked())
	{
		this->getCurrentTabWidget()->textEdit->setWhitespaceVisibility(QsciScintilla::WsVisible);
	}
	else
	{
		this->getCurrentTabWidget()->textEdit->setWhitespaceVisibility(QsciScintilla::WsInvisible);
	}
}

//查看
void try1_NotePad:: viewAutoLine()
{
	if (autoLineAction->isChecked())
	{
		this->getCurrentTabWidget()->textEdit->setWrapMode(QsciScintilla::WrapCharacter);
	}
	else
	{
		this->getCurrentTabWidget()->textEdit->setWrapMode(QsciScintilla::WrapNone);
	}
	
}

void try1_NotePad::setLanguageChinese(bool value)
{
	if (value)
	{
		qApp->removeTranslator(EnglishTranslator);
		this->loadText();
	}
}

void try1_NotePad::setLanguageEnglish(bool value)
{
	if (value)
	{
		qApp->installTranslator(EnglishTranslator);
		this->loadText();
	}
}

//语言
void try1_NotePad:: ProgramText()
{
	this->languageKind->setCurrentIndex(0);
}

void try1_NotePad:: ProgramC()
{
	this->languageKind->setCurrentIndex(1);
}

void try1_NotePad:: ProgramCpp()
{
	this->languageKind->setCurrentIndex(2);
}

void try1_NotePad:: ProgramJava()
{
	this->languageKind->setCurrentIndex(3);
}

void try1_NotePad:: ProgramPython2()
{
	this->languageKind->setCurrentIndex(4);
}

void try1_NotePad:: ProgramPython3()
{
	this->languageKind->setCurrentIndex(5);
}

//工具
void try1_NotePad:: ToolLanguage()
{
    QDesktopServices::openUrl(QString("http://fanyi.youdao.com/"));
}

//帮助
void try1_NotePad::helpViewHelp()
{
	if (helpDialog == NULL)
	{
		this->helpDialog = new MyDialog("help", "./Pictures/helpView.png");
	}
	else
	{
		helpDialog->show();
	}
}

void try1_NotePad:: helpAboutUs()
{
	if (aboutUsDialog == NULL)
	{
		this->aboutUsDialog = new MyDialog("about us", "./Pictures/aboutUs.png");
	}
	else
	{
		aboutUsDialog->show();
	}
}

//TabWidget
void try1_NotePad::addNewTabEmit()
{
	if (tabList.count() > 0)
	{
		for (int i = 0; i < tabList.count(); i++)
		{
			if (tabList[i]->textEdit->text() == tr(""))
			{
				this->tabWidget->setCurrentWidget(tabList[i]);
				return;
			}
		}
	}

	MyTabWidget* newTab = new MyTabWidget();
	tabList.append(newTab);
	tabWidget->addTab(newTab, QIcon("./Icon/tabIcon.ico"), tr("new") + QString::number(tabList.count(), 10));
	this->tabWidget->setCurrentWidget(newTab);
	connect(newTab, SIGNAL(sendArgEmit(QObject*)), this,SLOT(sendArgEmit(QObject*)));
}

void try1_NotePad:: deleteTabEmit(int index)
{
	MyTabWidget *widget = this->getCurrentTabWidget();
	bool gotoOldWidget = true;


	this->tabWidget->setCurrentIndex(index);
	if (this->getCurrentTabWidget() == widget)
	{
		gotoOldWidget = false;
	}

	this->fileSave();

	this->tabList.removeOne(this->getCurrentTabWidget());
	disconnect(this->getCurrentTabWidget(), SIGNAL(sendArgEmit(QObject*)), this, SLOT(sendArgEmit(QObject*)));
	this->tabWidget->removeTab(index);

	if (gotoOldWidget)
	{
		this->tabWidget->setCurrentWidget(widget);
	}

	if (tabList.count() <= 0)
	{
		this->close();
	}
}

//程序种类改变
void try1_NotePad::changeProgram(QString name)
{
	this->getCurrentTabWidget()->SetTheFileKind(name);
}

void try1_NotePad::changeTabWidget(int newIndex)
{
	if (newIndex <0)
	{
		return;
	}
	//this->tabWidget->setCurrentIndex(newIndex);
	this->languageKind->setCurrentText(this->getCurrentTabWidget()->programLabel->text());
}

//发送参数
void try1_NotePad::sendArgEmit(QObject* obj)
{
	MyTabWidget *tab = (MyTabWidget*)obj;
	if (tab->fileNameLabel->text() == this->runningFilename)
	{
		//发送参数
		communicate->sendArgs(runningTab->argLine->text()+tr("\n"));

		tab->SendProgramArgs(true);
	}
	else
	{
		tab->SendProgramArgs(false);
	}
}

//运行
void try1_NotePad::runExec()
{
	this->fileSave();
	if (this->getCurrentTabWidget()->fileNameLabel->text() == tr("临时文件") || this->getCurrentTabWidget()->fileNameLabel->text() == tr("temporary files"))
	{
		this->getCurrentTabWidget()->AddTxt(tr("failed to save the code.\n"), Qt::red);
		return;
	}

	runningTab = this->getCurrentTabWidget();
	runningFilename = runningTab->fileNameLabel->text();

	this->StartRun();

	//发送代码
	if (!communicate->sendRequest(runningFilename, this->languageKind->currentText(), this->osKind->currentText()))
	{
		this->EndRun();
	}
}

void try1_NotePad::endRunning()
{
    disconnect(communicate, SIGNAL(newsComming(QString)), this, SLOT(newsCommingForShow(QString)));
    disconnect(communicate, SIGNAL(endConnect()), this, SLOT(endRunning()));
    communicate->close();
    this->EndRun();

    communicate->deleteLater();
    communicate = NULL;
}

void try1_NotePad::StartRun()
{
	this->runningFilename = this->getCurrentTabWidget()->fileNameLabel->text();
	this->getCurrentTabWidget()->AddStartSeparate();
	this->runAction->setEnabled(false);

	communicate = new CommunicationClass();
	connect(communicate, SIGNAL(newsComming(QString)), this, SLOT(newsCommingForShow(QString)));
    connect(communicate, SIGNAL(endConnect()), this, SLOT(endRunning()));
}

void try1_NotePad::EndRun()
{
	runningFilename = tr("");
	this->getCurrentTabWidget()->AddEndSeparate();
	this->runAction->setEnabled(true);
}

void try1_NotePad::newsCommingForShow(QString news)
{
	this->runningTab->AddTxt(news);
}
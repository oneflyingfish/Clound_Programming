#include "MyTabWidget.h"
#include<QDebug>

MyTabWidget::MyTabWidget()
{
	startString = QString("开始执行");
	memoryFileNameString = QString("临时文件");

	//添加默认编辑页
	this->SetTheFileName(tr(""));
	this->SetTheFileKind(tr("Text"));
	this->argLine->setPlaceholderText(tr("此处写入程序参数，可分多次写入"));
	//this->progressBar->setMaximumWidth(200);

	//定义状态栏
	statusBar->setStyleSheet("statusBar{background-color: rgba(255,255,255,0);}");
	fileNameLabel->setStyleSheet("font: 10pt \"微软雅黑\";color: rgb(255, 142, 49);");
	downloadFile->setStyleSheet("font: 10pt \"微软雅黑\";color: red;");
	programLabel->setStyleSheet("font: 10pt \"微软雅黑\";color: green;");
	programTipLabel->setStyleSheet("font: 10pt \"微软雅黑\";color: green;");

	//定义状态栏相关显示
	statusBar->addWidget(fileNameLabel);
    downloadFile->setVisible(false);                //保留接口，未启用
	//statusBar->addPermanentWidget(downloadFile);
	statusBar->addPermanentWidget(programTipLabel);
	statusBar->addPermanentWidget(programLabel);
	////添加编译进度条
	//statusBar->addPermanentWidget(progressLabel);
	//statusBar->addPermanentWidget(progressBar);

	//定义参数输入
	QHBoxLayout *hbox = new QHBoxLayout();
	sendArg->setToolTip(tr("点击发送输入参数"));
	hbox->addWidget(argLine);
	hbox->addWidget(sendArg);
	hbox->setMargin(0);
	hbox->setSpacing(1);

	//定义QGroupbox内部布局
	QVBoxLayout *vbox = new QVBoxLayout();
	vbox->addWidget(outputTextEdit);
	outputTextEdit->setStyleSheet("font: 12pt \"Consolas\";");
	vbox->addLayout(hbox);
	vbox->setSpacing(0);
	outputGroupBox->setLayout(vbox);
	outputGroupBox->setStyleSheet("background-color: rgba(255,255,255,0);font: 10pt \"微软雅黑\";");
	vbox->setMargin(0);

	//分割器设置
	splitter->addWidget(textEdit);
	splitter->addWidget(outputGroupBox);
	splitter->setStretchFactor(0, 2);
	splitter->setStretchFactor(1, 0);

	//定义整体布局
	QVBoxLayout *vMainVbox = new QVBoxLayout();
	vMainVbox->addWidget(splitter);
	vMainVbox->addWidget(statusBar);
	vMainVbox->setMargin(0);

	this->setLayout(vMainVbox);

	this->outputTextEdit->setReadOnly(true);
	this->outputTextEdit->setWordWrapMode(QTextOption::WrapAnywhere);						//强行换行
	this->downloadFile->setChecked(false);

	this->outputTextEdit->setContextMenuPolicy(Qt::NoContextMenu);
	this->argLine->setContextMenuPolicy(Qt::NoContextMenu);

	connect(this->sendArg, SIGNAL(clicked(bool)),this,SLOT(sendArgclicked()));
	//connect(this->argLine, SIGNAL(editingFinished()), this, SLOT(sendArgclicked()));

	//编译输出框测试代码
	//this->AddStartSeparate();
	//this->AddTxt("这是编译内容\n");
	//this->AddTxt("111111");
	//this->AddEndSeparate();
}

MyTabWidget::~MyTabWidget()
{
	textEdit ->deleteLater();
	outputTextEdit ->deleteLater();
	outputGroupBox ->deleteLater();
	statusBar ->deleteLater();
	splitter ->deleteLater();
	sendArg ->deleteLater();
	argLine ->deleteLater();
	//状态栏
	programTipLabel ->deleteLater();
	fileNameLabel ->deleteLater();
	programLabel ->deleteLater();
	/*progressLabel ->deleteLater();
	progressBar ->deleteLater();*/
	downloadFile ->deleteLater();
}

void MyTabWidget::SetTheFileKind(QString myFileKind)
{
	if (myFileKind == "")
	{
		this->programLabel->setText("Text");
		this->textEdit->ChooseLexerAndApis("Text");
	}
	else
	{
		this->programLabel->setText(myFileKind);
		this->textEdit->ChooseLexerAndApis(myFileKind);
	}
}

void MyTabWidget::SetTheFileName(QString fileName)
{
	if (fileName == tr(""))
	{
		this->fileNameLabel->setText(memoryFileNameString);
	}
	else
	{
		this->fileNameLabel->setText(fileName);
	}

}

void MyTabWidget::AddTxt(QString str,QColor color)
{
	this->outputTextEdit->setTextColor(color);
	this->outputTextEdit->insertPlainText(str);
}

void MyTabWidget::AddStartSeparate()
{
	this->outputTextEdit->setTextColor(Qt::red);
	this->outputTextEdit->append(tr("\n")+startString+tr("：")+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+"---------------\n");
}

void MyTabWidget::AddEndSeparate()
{
	this->outputTextEdit->setTextColor(Qt::green);
	this->outputTextEdit->append(tr("$end...")+"\n");
}

//点击传参按钮
void MyTabWidget::sendArgclicked()
{
	emit sendArgEmit(this);
}

void MyTabWidget::SendProgramArgs(bool b)
{
	if (b == true)
	{
		//this->AddTxt(QString("send args(\"%1\") successfully.\n").arg(this->argLine->text()), QColor(170, 85, 127));
        this->AddTxt(this->argLine->text()+tr("\n"), QColor(170, 85, 127));
		this->argLine->setText(tr(""));
	}
	else
	{
		this->AddTxt(QString("Sending parameters is not allowed.\n"), Qt::red);
		this->argLine->setText(tr(""));
	}
}
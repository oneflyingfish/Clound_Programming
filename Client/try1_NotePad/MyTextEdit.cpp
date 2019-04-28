#include"MyTextEdit.h"

//定义构造函数
MyTextEdit::MyTextEdit(QWidget *parent) :QsciScintilla(parent)
{
	languageString = QString("Text");
	messageTitleString = QString("提示");
	messageContanteString = QString("词法配置文件加载失败");

	//初始化词法分析器和高亮
	this->InitLexerAndApis();
	InitTextEdit();
}

void MyTextEdit::InitTextEdit()
{
	this->setMarginsBackgroundColor(QColor(225, 225, 225));
	this->setMarkerForegroundColor(Qt::black);

	//设置相关编辑参数
	this->setMarginType(0, QsciScintilla::NumberMargin);							//设置编号为0的页边显示行号 
	this->setMarginLineNumbers(0, true);											//对该页边启用行号
	this->setMarginWidth(0, 50);													//设置页边宽度
	this->SendScintilla(QsciScintilla::SCI_SETCODEPAGE, QsciScintilla::SC_CP_UTF8);	//设置编码为UTF-8

	this->verticalScrollBar()->setStyleSheet("background:arga(0,0,0,3);");
	this->horizontalScrollBar()->setStyleSheet("background:arga(0,0,0,3);");

	this->setAutoCompletionSource(QsciScintilla::AcsAll);							//设置自动完成所有项
	this->setAutoCompletionCaseSensitivity(true);									//设置大小写敏感
	this->setAutoCompletionThreshold(1);											//每输入1个字符就出现自动完成的提示
	this->setFolding(QsciScintilla::BoxedTreeFoldStyle, 1);
	this->setFoldMarginColors(QColor(255, 255, 255), QColor(255, 255, 255));


	this->setAutoIndent(true);														//开启自动缩进	
	this->setCaretLineVisible(true);												//显示选中的行号
	this->setBraceMatching(QsciScintilla::SloppyBraceMatch);						//设置括号匹配
	this->setSelectionBackgroundColor(QColor(100, 100, 100, 50));					//设置点选背景色
	this->setSelectionForegroundColor(Qt::darkBlue);
	this->setCaretLineBackgroundColor(QColor(233, 233, 233, 50));					//显示选中行的背景色	
	this->setMarginsBackgroundColor(QColor(255, 255, 255, 0));
	this->setMarginsForegroundColor(Qt::gray);										//设置行号字体颜色
	this->setMarginsFont(QFont("consolas", 14, 1));									//设置行号字体
	this->setFont(QFont("consolas", 14, 1));										//设置编辑字体

	this->setTabWidth(4);
	this->setIndentationWidth(4);													//设置缩进为4
	this->setAutoCompletionFillupsEnabled(true);
	//this->zoomIn(2);
}

MyTextEdit::~MyTextEdit()
{
	//C语法
	cLexer ->deleteLater();
	apisC ->deleteLater();

	//C++语法
	cppLexer ->deleteLater();
	apisCpp ->deleteLater();

	//Java语法
	javaLexer ->deleteLater();
	apisJava ->deleteLater();

	//python2语法
	python2Lexer ->deleteLater();
	apisPython2 ->deleteLater();

	//python3语法
	python3Lexer ->deleteLater();
	apisPython3 ->deleteLater();
}

void MyTextEdit::InitLexerAndApis()
{
	//准备C
	if (!apisC->load(QString("./Lexer/cApi.ini")))
	{
		QMessageBox::information(this,messageTitleString, QString("C") + messageContanteString);
	}
	else
	{
		apisC->prepare();
	}
	cLexer->setColor(Qt::red, QsciLexerCPP::Keyword);
	cLexer->setColor(Qt::blue, QsciLexerCPP::Number);
	cLexer->setColor(QColor(85, 255, 255), QsciLexerCPP::GlobalClass);
	cLexer->setColor(QColor(85, 255, 255), QsciLexerCPP::InactiveGlobalClass);

	//准备C++
	if (!apisCpp->load(QString("./Lexer/cppApi.ini")))
	{
		QMessageBox::information(this, messageTitleString, QString("C++") + messageContanteString);
	}
	else
	{
		apisCpp->prepare();
	}
	cppLexer->setColor(Qt::red, QsciLexerCPP::Keyword);
	cppLexer->setColor(Qt::blue, QsciLexerCPP::Number);
	cppLexer->setColor(QColor(85, 255, 255), QsciLexerCPP::GlobalClass);
	cppLexer->setColor(QColor(85, 255, 255), QsciLexerCPP::InactiveGlobalClass);

	//准备Java
	if (!apisJava->load(QString("./Lexer/javaApi.ini")))
	{
		QMessageBox::information(this, messageTitleString, QString("java") + messageContanteString);
	}
	else
	{
		apisJava->prepare();
	}
	javaLexer->setColor(Qt::red, QsciLexerJava::Keyword);
	javaLexer->setColor(Qt::blue, QsciLexerJava::Number);
	javaLexer->setColor(QColor(85, 255, 255), QsciLexerJava::GlobalClass);
	javaLexer->setColor(QColor(85, 255, 255), QsciLexerJava::InactiveGlobalClass);

	//准备python2
	if (!apisPython2->load(QString("./Lexer/python2Api.ini")))
	{
		QMessageBox::warning(this, messageTitleString, QString("python2") + messageContanteString);
	}
	else
	{
		apisPython2->prepare();
	}
	python2Lexer->setColor(Qt::red, QsciLexerPython::Keyword);
	python2Lexer->setColor(Qt::blue, QsciLexerPython::Number);
	python2Lexer->setColor(QColor(85, 255, 255), QsciLexerPython::ClassName);

	//准备python3
	if (!apisPython3->load(QString("./Lexer/python3Api.ini")))
	{
		QMessageBox::warning(this, messageTitleString, QString("python3")+messageContanteString);
	}
	else
	{
		apisPython3->prepare();
	}
	python3Lexer->setColor(Qt::red, QsciLexerPython::Keyword);
	python3Lexer->setColor(Qt::blue, QsciLexerPython::Number);
	python3Lexer->setColor(QColor(85, 255, 255), QsciLexerPython::ClassName);
}

void MyTextEdit::ChooseLexerAndApis(QString str)
{
	if (str.toLower() == "text")
	{
		this->setLexer(NULL);
	}
	else if (str.toLower() == "c")
	{
		this->setLexer(this->cLexer);
	}
	else if (str.toLower() == "c++")
	{
		this->setLexer(this->cppLexer);
	}
	else if (str.toLower() == "java")
	{
		this->setLexer(this->javaLexer);
	}
	else if (str.toLower() == "python2" || str.toLower() == "python")
	{
		this->setLexer(this->python2Lexer);
	}
	else if (str.toLower() == "python3")
	{
		this->setLexer(this->python3Lexer);
	}
	else
	{
		this->setLexer(NULL);
	}
	InitTextEdit();
}

//void MyTextEdit::contextMenuEvent(QContextMenuEvent *event)
//{
//	QMenu *menu = createStandardContextMenu();
//	menu->addAction(tr("My Menu Item"));
//	//...
//	menu->exec(event->globalPos());
//	delete menu;
//}
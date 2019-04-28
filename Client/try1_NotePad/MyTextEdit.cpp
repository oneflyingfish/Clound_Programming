#include"MyTextEdit.h"

//���幹�캯��
MyTextEdit::MyTextEdit(QWidget *parent) :QsciScintilla(parent)
{
	languageString = QString("Text");
	messageTitleString = QString("��ʾ");
	messageContanteString = QString("�ʷ������ļ�����ʧ��");

	//��ʼ���ʷ��������͸���
	this->InitLexerAndApis();
	InitTextEdit();
}

void MyTextEdit::InitTextEdit()
{
	this->setMarginsBackgroundColor(QColor(225, 225, 225));
	this->setMarkerForegroundColor(Qt::black);

	//������ر༭����
	this->setMarginType(0, QsciScintilla::NumberMargin);							//���ñ��Ϊ0��ҳ����ʾ�к� 
	this->setMarginLineNumbers(0, true);											//�Ը�ҳ�������к�
	this->setMarginWidth(0, 50);													//����ҳ�߿��
	this->SendScintilla(QsciScintilla::SCI_SETCODEPAGE, QsciScintilla::SC_CP_UTF8);	//���ñ���ΪUTF-8

	this->verticalScrollBar()->setStyleSheet("background:arga(0,0,0,3);");
	this->horizontalScrollBar()->setStyleSheet("background:arga(0,0,0,3);");

	this->setAutoCompletionSource(QsciScintilla::AcsAll);							//�����Զ����������
	this->setAutoCompletionCaseSensitivity(true);									//���ô�Сд����
	this->setAutoCompletionThreshold(1);											//ÿ����1���ַ��ͳ����Զ���ɵ���ʾ
	this->setFolding(QsciScintilla::BoxedTreeFoldStyle, 1);
	this->setFoldMarginColors(QColor(255, 255, 255), QColor(255, 255, 255));


	this->setAutoIndent(true);														//�����Զ�����	
	this->setCaretLineVisible(true);												//��ʾѡ�е��к�
	this->setBraceMatching(QsciScintilla::SloppyBraceMatch);						//��������ƥ��
	this->setSelectionBackgroundColor(QColor(100, 100, 100, 50));					//���õ�ѡ����ɫ
	this->setSelectionForegroundColor(Qt::darkBlue);
	this->setCaretLineBackgroundColor(QColor(233, 233, 233, 50));					//��ʾѡ���еı���ɫ	
	this->setMarginsBackgroundColor(QColor(255, 255, 255, 0));
	this->setMarginsForegroundColor(Qt::gray);										//�����к�������ɫ
	this->setMarginsFont(QFont("consolas", 14, 1));									//�����к�����
	this->setFont(QFont("consolas", 14, 1));										//���ñ༭����

	this->setTabWidth(4);
	this->setIndentationWidth(4);													//��������Ϊ4
	this->setAutoCompletionFillupsEnabled(true);
	//this->zoomIn(2);
}

MyTextEdit::~MyTextEdit()
{
	//C�﷨
	cLexer ->deleteLater();
	apisC ->deleteLater();

	//C++�﷨
	cppLexer ->deleteLater();
	apisCpp ->deleteLater();

	//Java�﷨
	javaLexer ->deleteLater();
	apisJava ->deleteLater();

	//python2�﷨
	python2Lexer ->deleteLater();
	apisPython2 ->deleteLater();

	//python3�﷨
	python3Lexer ->deleteLater();
	apisPython3 ->deleteLater();
}

void MyTextEdit::InitLexerAndApis()
{
	//׼��C
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

	//׼��C++
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

	//׼��Java
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

	//׼��python2
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

	//׼��python3
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
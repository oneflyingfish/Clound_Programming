#ifndef MYTEXTEDIT_H
#define MYTEXTEDIT_H

#ifdef WIN32
#pragma execution_character_set("utf-8")

#endif

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QColor>
#include <QMessageBox>
#include <QScrollBar>
#include <QContextMenuEvent>
#include <QMenu>
#include <QString>
#include "Qsci/QSciLexer.h"
#include "Qsci/QSciScintilla.h"
#include "Qsci/QsciLexerCPP.h"
#include "Qsci/QsciLexerJava.h"
#include "Qsci/QsciLexerPython.h"
#include "Qsci/QsciAPIs.h"

class MyTextEdit : public QsciScintilla
{
	//避免因为继承而二次定义
#ifndef Q_OBJECT
	#define Q_OBJECT
#endif

public:
	MyTextEdit(QWidget *parent = Q_NULLPTR);
	~MyTextEdit();
	void InitLexerAndApis();
	void ChooseLexerAndApis(QString);
	void InitTextEdit();

protected:
	//virtual void contextMenuEvent(QContextMenuEvent *event);	//重载右键菜单

public:
	QString languageString;
	QString messageTitleString;
	QString messageContanteString;

	//C语法
	QsciLexer *cLexer = new QsciLexerCPP();
	QsciAPIs *apisC = new QsciAPIs(cLexer);

	//C++语法
	QsciLexer *cppLexer = new QsciLexerCPP();
	QsciAPIs *apisCpp = new QsciAPIs(cppLexer);									

	//Java语法
	QsciLexer *javaLexer = new QsciLexerJava();
	QsciAPIs *apisJava = new QsciAPIs(javaLexer);									

	//python2语法
	QsciLexer *python2Lexer = new QsciLexerPython();
	QsciAPIs *apisPython2 = new QsciAPIs(python2Lexer);	

	//python3语法
	QsciLexer *python3Lexer = new QsciLexerPython();
	QsciAPIs *apisPython3 = new QsciAPIs(python3Lexer);
};

#endif
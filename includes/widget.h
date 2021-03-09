#ifndef __WIDGET_H__
#define __WIDGET_H__

#include <QWidget>
#include <QQuickWidget>
#include <QVBoxLayout>
#include <QSize>
#include <QList>
#include "engine.h"
#include "AndroidFileDialog.h"
#include <QTextToSpeech>

class widget : public QWidget
{
	Q_OBJECT
	Q_PROPERTY(QStringList myList READ getList NOTIFY onListChanged)
	Q_PROPERTY(QString question READ getQuestion NOTIFY onQuestionChanged)
	Q_PROPERTY(int currentPx READ getCurrentPx NOTIFY onCurrentPxChanged)

public:
	widget(QWidget *widget = NULL);
	~widget();
	Q_INVOKABLE QSize getSize();

	Q_INVOKABLE QStringList getList() { return mList; }
	Q_INVOKABLE QString getQuestion() { return mQuestion; }

	Q_INVOKABLE bool verifique(QString);
	Q_INVOKABLE void lookQuestion();
	
	Q_INVOKABLE void openFile();
	Q_INVOKABLE void nextQuestion();

	Q_INVOKABLE int getCurrentPx();

signals:
	void onListChanged();
	void onQuestionChanged();
	void onCurrentPxChanged();

private slots:
	void openFileNameReady(QString fileName);
	void onSpeechReady(QTextToSpeech::State state);

private:
	void build();
	void configure();
	void setLayouts();
	void setLenSplitPx();
	void callRandomType();
	void callWin();

	//application
	QVBoxLayout *mVLayout;
	QQuickWidget *mQuickWidget;
	QStringList mList;
	QString mQuestion;
	engine *mEngine;
	QSize mSize;

	//file dialog
	AndroidFileDialog *fileDialog;
	QTextToSpeech *mSpeech;
	QString mPeddingtoSay;
	
	enum {
		OPEN,
		CLOSED
	} mType;
};



#endif

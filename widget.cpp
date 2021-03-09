#include "widget.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QGenericArgument>
#include <QQmlContext>
#include <QMetaObject>
#include <QQuickItem>
#include <QMessageBox>
#include <QQmlError>
#include <QSize>
#include <QRect>
#include <QFile>
#include <string>

using std::string;

widget::widget(QWidget *w)
	: QWidget(w)
{
	build();
	configure();
	setLayouts();
}

widget::~widget() {
	delete mEngine;
}


QSize widget::getSize()
{
	return mSize;
}


void widget::build() 
{
	mQuickWidget = new QQuickWidget(this);
	mVLayout = new QVBoxLayout(this);
	mEngine = new engine();
	fileDialog = new AndroidFileDialog();
	mSpeech = new QTextToSpeech(QTextToSpeech::availableEngines()[0], static_cast<QObject*>(this));
}


void widget::configure() 
{
	connect(fileDialog, SIGNAL(existingFileNameReady(QString)), this, SLOT(openFileNameReady(QString)));
	connect(mSpeech, SIGNAL(stateChanged), this, SLOT(onSpeechReady));
	

	QRect rct = QApplication::desktop()->screenGeometry();
	mSize = QSize(rct.width(), rct.height());
	mVLayout->setMargin(0);

	mQuickWidget->setFixedSize(mSize);
	mQuickWidget->setSource(QUrl(QStringLiteral("qrc:/qml/main.qml")));
	mQuickWidget->rootContext()->setContextProperty("widget", this);

	QList<QQmlError> qmlerrors = mQuickWidget->errors();

	if (qmlerrors.count() > 0) {
		QStringList errors;
		for (QQmlError error : qmlerrors)
			errors << tr("error on file %1 line %2 column %3\n%4\n\n")
				.arg(error.url().toString())
				.arg(error.line())
				.arg(error.column())
				.arg(error.description());
		QMessageBox::critical(this, "errors log file /sdcard/qml_errors.log", errors.join("\n"));
		
		QFile file_log("/sdcard/qml_errors.log");
		file_log.open(QIODevice::WriteOnly | QIODevice::Text);
		file_log.write(errors.join("\n").toStdString().c_str());
		file_log.flush();
		file_log.close();
		QWidget::close();
		

	}

}

void widget::setLayouts() 
{
	mVLayout->addWidget(mQuickWidget);
	QWidget::setLayout(mVLayout);
}




bool widget::verifique(QString answer) {
	try {
		if (mType == CLOSED)
			lookQuestion();
		bool isCorrect = mEngine->isCorrect(mQuestion.toStdString(), answer.toStdString());
		emit onCurrentPxChanged();
		return isCorrect;
	} catch (string str) {
		QMessageBox::critical(this, "error", str.c_str());
		return true;
	}
}


void widget::lookQuestion() {
	switch (mType) {
		case OPEN:
			mQuestion = mEngine->answerOf(mQuestion.toStdString()).c_str();
			mType = CLOSED;
			break;
		case CLOSED:
			mQuestion = mEngine->questionOf(mQuestion.toStdString()).c_str();
			mType = OPEN;
			break;
	}
	emit onQuestionChanged();
}



void widget::openFile() {
	if (not fileDialog->isGranted())
		if (not fileDialog->requestPermission())
			return;
	fileDialog->provideExistingFileName();
									

}

void widget::openFileNameReady(QString fileName)
{
    if (not fileName.isNull()) {
	try {
		mEngine->loadFile(fileName.toStdString());	
		mEngine->setRange(10);
		nextQuestion();
		setLenSplitPx();
		callRandomType();
		emit onCurrentPxChanged();
	} catch (string str) {
			QMessageBox::warning(this, "Warning", str.c_str());
	}
    }
}

void widget::nextQuestion() {
	mQuestion.clear();
	mList.clear();
	mType = OPEN;

	try {

		auto question = mEngine->nextQuestion();
		mQuestion = question->begin()->first.c_str();
		for (string str : question->begin()->second)
			mList << str.c_str();
	
		mPeddingtoSay = mQuestion;
		mSpeech->say(mPeddingtoSay);
		emit onQuestionChanged();
		emit onListChanged();
	} catch (string str) {
		if (str == "eof")
			callWin();
		else if (str.find("nextRange:") != string::npos)
				QMessageBox::warning(this, "error", str.c_str());
		else
				QMessageBox::warning(this, "error", str.c_str());
	}
}


void widget::onSpeechReady(QTextToSpeech::State state) {
	if (state == QTextToSpeech::Ready) {
		if (not mPeddingtoSay.isEmpty()) {
			QString tmp;
			tmp = mPeddingtoSay;
			mPeddingtoSay.clear();
			mSpeech->say(tmp);
		}
	}
}

void widget::callWin() {
	QObject *obj  = mQuickWidget->rootObject();
	QMetaObject::invokeMethod(obj, "win");

}

void widget::callRandomType() {
	QObject *obj = mQuickWidget->rootObject()->findChild<QObject*>("answer");
	if (obj == NULL) {
		QMessageBox::critical(this, "QQuickWidget", "can't find child answer");
		return;
	}

	QMetaObject::invokeMethod(obj, "randomizeType");
	
}

int widget::getCurrentPx() {
	return mEngine->getCurrentPxProgress();
}

void widget::setLenSplitPx() {
	int l = mEngine->getLenSplit();
	QObject *obj  = mQuickWidget->rootObject();
	obj->setProperty("lenSplit", l);
}



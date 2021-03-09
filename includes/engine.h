#ifndef __ENGINE_H__
#define __ENGINE_H__


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include <unistd.h>
#include <map>

#include "tutil.h"

using std::string, std::vector, std::map, std::fstream, std::find, std::pair;

class engine 
{

public:
	engine(){};

	void loadFile(string);
	void print();

	bool isCorrect(string key, string value);
	void setRange(int);
	void jumpNexRange();
	map<string, vector<string>> *nextQuestion();

	string questionOf(string str);
	string answerOf(string str);

	float getCurrentPxProgress();
	int getLenSplit();	

private:
	void setDefaults();
	void load();
	void randQuestion(vector<string>& questions, string question);
	bool hasAvailable();
	bool gotTheEnd();
	void checkAvailable();
	void resetRange();
	bool isLearned(vector<int>) const;
	string removeJunk(string str);
	bool haveIn(string, char) const;
	int phrasePercent(string, string);
	map<string, bool> newRange(vector<string>);
	string fixAccents(string);
	string onlyValidWords(string);
	void loadCurrents();
	float psCurrents();

	map<string, map<string, vector<int>>> mWords;
	map<string, map<string, vector<int>>> mCurrents;
	map<string, vector<string>> mQuestion;
	string mFileName;
	

	int mBeginRange, mEndRange;
	int mLenRange;

	enum {
		CORRECTS,
		INCORRECTS,
		WAS
	};
	
	
};



#endif

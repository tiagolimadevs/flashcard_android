#include "engine.h"
#include <stdio.h>
#include <stdlib.h>

#include <QMessageBox>
#include <QWidget>
#include <QString>

#define MIN(X1,X2) (X1 < X2 ? X1 : X2)
#define IS_UPPER(ch) (ch > 'A' && ch < 'Z')
#define TO_LOWER(ch) (IS_UPPER(ch) ? (ch-'A')+'a' : ch)

void engine::loadFile(string filename) {
	mFileName = filename;
	setDefaults();
	load();
}

void engine::setDefaults() {
	mBeginRange = mEndRange = mLenRange = 0;
}


void engine::load() {
	fstream fs;
	fs.open(mFileName, fstream::in);
	if (! fs.is_open()) {
		throw (string("error can't open ")+mFileName);
		return;
	}

	mWords.clear();
	string line, key;
	int idx, currentLine = 0;
	while (std::getline(fs, line)) {
		currentLine++;
		idx = line.find('=');
		if (idx == string::npos) {
			fs.close();
			throw (string("sintaxy error \n")+std::to_string(currentLine)+":`"+line+"`\nfile should be <key=value>`");
		}
		
		key = line.substr(0, idx);
	
		map<string, vector<int>> value;
		value[line.substr(idx+1, line.length())] = vector<int>() << 0 << 0 << 0;
		mWords[key] = value;
	}

	
	fs.close();
	if (mWords.size() < 3)
		throw (string("file should have three lines or more..."));
	return;
}



void engine::setRange(int len) {
	mLenRange = MIN(mWords.size(), len);
	mBeginRange = 0;
	mEndRange = mLenRange;
	loadCurrents();
}



void engine::jumpNexRange() {
	int count = mWords.size();
	int endSize = mEndRange+mLenRange;

	mBeginRange = mEndRange;
	mBeginRange = mEndRange;

	if (endSize >= count)
		mEndRange = count;
	else
		mEndRange = endSize;

	loadCurrents();
}

void engine::loadCurrents() {
	string key;
	mCurrents.clear();
	for (int x = mBeginRange; x < mEndRange; x++) {
		key = keyAt(mWords, x);
		mCurrents[key] = mWords[key];
	}
}


bool engine::isLearned(vector<int> vec) const {
	if (vec[WAS] == 1)
		return true;

	const int incorrects = vec[INCORRECTS];
	const int corrects = vec[CORRECTS];
	if (corrects > incorrects+2)
		return true;
	return false;
}


bool engine::hasAvailable() {
	vector<int> value;	
	for (int x = 0; x < (mEndRange-mBeginRange); x++) {
		value = valueAt(mCurrents, x).begin()->second;
		if (not isLearned(value))
			return true;
	}
	return false;
}


void engine::resetRange() {
	for (int x = 0; x < (mEndRange-mBeginRange); x++)
		mCurrents[keyAt(mCurrents, x)].begin()->second[WAS] = 0;
}


bool engine::gotTheEnd() {
	return (mEndRange+1 >= mWords.size());
}

void engine::checkAvailable() {
	while (not hasAvailable()) {
		resetRange();
		if (not hasAvailable()) {
			if (gotTheEnd())
				throw string("eof");
			jumpNexRange();
			log("5");
			log ("nextRange: "+sto("%d", mBeginRange)+" - "+sto("%d", mEndRange)+" ");
			log("6");
		}
		
	}
}


map<string, vector<string>> *engine::nextQuestion() {
	checkAvailable();

	vector<int> vec;
	int n;
	do {
		n = rand() % (mEndRange-mBeginRange);
		vec = valueAt(mCurrents, n).begin()->second;
	}  while (isLearned(vec));

	map<string, vector<string>> *question = new map<string, vector<string>>;
	
	string key = keyAt(mCurrents, n);
	vector<string> questions;
	randQuestion(questions, mCurrents[key].begin()->first);
	question->insert(pair<string, vector<string>>(key, questions));

	return question;
}


void engine::randQuestion(vector<string>& questions, string question) {
	string value;
	int rn = rand() % 3;
	int r, p = 0;
	while (p < 3) {
		if (p == rn)
			questions.push_back(question);
		else {
			do {	
				r = rand() % mWords.size();
				value = valueAt(mWords, r).begin()->first;
			} while (find(questions.begin(), questions.end(), value) != questions.end() || value == question);
			questions.push_back(value);
		}
		p++;
	}

}


bool engine::isCorrect(string key, string value) {

	map<string, vector<int>>& v = mCurrents[key];


	string str1, str2;
	bool correct;
	
	str1 = v.begin()->first;
	str2 = value;

	
	//throw (str1+" : "+str2+" == "+string(sto("%d", phrasePercent(str2, str1))));

	correct = (phrasePercent(str2, str1) > 50
	&& phrasePercent(str1, str2) > 50);

	if (correct) {
		v.begin()->second[CORRECTS] += 1;
		v.begin()->second[WAS] = 1;
	} else
		v.begin()->second[INCORRECTS] += 1;

	return correct;
}

string engine::questionOf(string str) {
	return keyOf(mWords, str);
}

string engine::answerOf(string str) {
	return mWords[str].begin()->first;
}



string engine::fixAccents(string str) {
	map<char, string> hashes;
	hashes['a'] = "àáâäæãåā";
	hashes['e'] = "êéèëē";
	hashes['i'] = "ìīïíî";
	hashes['o'] = "õōøœòöôó";
	hashes['u'] = "ūüúûù";
	hashes['n'] = "ñ";
	hashes['c'] = "ç";
	
	for (int x = 0; x < str.length(); x++) {
		unsigned char ch = TO_LOWER(str[x]);
		for (auto it = hashes.begin(); it != hashes.end(); it++)
			if (haveIn(it->second, ch))
				if (ch != 195)
					str[x] = it->first;
	}

	return str;
}


string engine::onlyValidWords(string str) {
	string ret;
	char ch;
	for (int x = 0; str[x] != '\0'; x++) {
		ch = TO_LOWER(str[x]);
		if ((int(ch) >= int('a') && int(ch) <= int('z'))
		|| (int(ch) >= int('A') && int(ch) <= int('Z'))
		|| (int(ch) >= int('0') && int(ch) <= int('9')))
			ret.push_back(ch);
	}
	return ret;
}


string engine::removeJunk(string str) {
	str = fixAccents(str);
	str = onlyValidWords(str);
	return str;
}


bool engine::haveIn(string str, char ch) const {
	for (int x = 0; str[x] != '\0'; x++)
		if (str[x] == ch)
			return true;
	return false;

}


map<string, bool> engine::newRange(vector<string> vec) {
	map<string, bool> ret;
	for (string str : vec)
		ret[removeJunk(str)] = false;
	return ret;
}


int engine::phrasePercent(string s1, string s2) {
	int countWordsCorrects = 0;
	int size_vec_str_2;
	map<string, bool> useds;

	vector<string> vec_str_1 = explode(s1, ' ');
	vector<string> vec_str_2 = explode(s2, ' ');
	size_vec_str_2 = vec_str_2.size();

	useds = newRange(vec_str_2);

	
	string str1, str2;
	// get all words vec_str_1
	for (string ustr1 : vec_str_1) { 
		//remove junks like ,?!...
		str1 = removeJunk(ustr1); 
		//get all words vec_str_1
		for (string ustr2 : vec_str_2) {
			//remove junks too
			str2 = removeJunk(ustr2);
			//then if it's not empty 
			//and if has no been used
			if (not str2.empty() and not useds[str2]) {
				//then will check if they are equal
				if (str1 == str2) { 
					//to set this str2 like used
					useds[str2] = true;
					//and increase count of words currects
					countWordsCorrects += 1;
					//and then jump to next word
					break; 
				}
			}
		}
	}

	//clear memories
	useds.clear();
	vec_str_1.clear();
	vec_str_2.clear();

	//then will return how much percents words corrects
	return countWordsCorrects * 100 / size_vec_str_2;
}


float engine::getCurrentPxProgress() {
	float x = mBeginRange+psCurrents()+1;
	float y = mWords.size();
	return x/y*100;
}

float engine::psCurrents() {
	int lr = 0;
	int c = (mEndRange-mBeginRange);
	vector<int> va;
	for (int x = 0; x < c; x++) {
		va = valueAt(mCurrents, x).begin()->second;
		lr += va[CORRECTS]-(va[INCORRECTS]);
	}
	
	return lr/3;
}

int engine::getLenSplit() {
	return mWords.size()/mLenRange;
}

#include "word.h"

//#define SHOW

word::word() {
	store = NULL;
	attr = NULL;
	tag = NULL;
}

word::~word() {
	if (store)
		delete[]store;
	if (attr)
		delete[]attr;
	if (tag)
		delete[]tag;
}

//set the store, attr, tag with str which is not splited by '/'
void word::setWordTrain(string str) {
	if (store) {
		delete[]store;
		store = NULL;
	}
	if (attr) {
		delete[]attr;
		attr = NULL;
	}
	if (tag) {
		delete[]tag;
		tag = NULL;
	}

	int i, j, d = 0, d1, len = str.size();
	for (i = 0; i < len; i++)
		if (str[i] == '/')
			break;
	d1 = i;
	store = new char[d1 + 1];
	for (j = 0; d < d1; j++, d++)
		store[j] = str[d];
	store[j] = '\0';

#ifdef SHOW
	cout << d1 + 1 << " " << strlen(store) << endl;
#endif // SHOW

	for (++i; i < len; i++)
		if (str[i] == '/')
			break;
	d1 = i;
	attr = new char[d1 - d];

#ifdef SHOW
	cout << d1 - d << " ";
#endif

	for (j = 0, ++d; d < d1; j++, d++)
		attr[j] = str[d];
	attr[j] = '\0';

#ifdef SHOW
	cout << strlen(attr) << endl;
#endif
	if (len > d) {
		tag = new char[len - d];

#ifdef SHOW
		cout << len - d << " ";
#endif

		for (j = 0, ++d; d < len; j++, d++)
			tag[j] = str[d];
		tag[j] = '\0';

#ifdef SHOW
		cout << strlen(tag) << endl;
		cout << store << " " << attr << " " << tag << endl;
#endif
	}
}

void word::setWordTest(string& str) {
	if (store)
		delete[]store;
	if (attr)
		delete[]attr;

	int i, j, d = 0, d1, len = str.size();
	for (i = 0; i<len; i++)
		if (str[i] == '/') {
			d1 = i;
			break;
		}
	store = new char[d1 + 1];
	for (j = 0; d < d1; j++, d++)
		store[j] = str[d];
	store[j] = '\0';

#ifdef SHOW
	cout << d1 + 1 << " " << strlen(store) << endl;
#endif // SHOW

#ifdef SHOW
	cout << len - d << " ";
#endif // SHOW
	attr = new char[len - d];
	for (j = 0, ++d; d < len; j++, d++)
		attr[j] = str[d];
	attr[j] = '\0';

#ifdef SHOW
	cout << strlen(attr) << endl;
	cout << store << " " << attr << endl;
#endif // SHOW
}

char *word::getWord() {
	if (store)
		return store;
	//cout << "The word is empty!" << endl;
	return NULL;
}

char *word::getAttr() {
	if (attr)
		return attr;
	//cout << "The attr is empty!" << endl;
	return NULL;
}

char *word::getTag() {
	if (tag)
		return tag;
	//cout << "The tag is empty!" << endl;
	return NULL;
}

void word::demo() {
	string str = "企业/NN/O";
	setWordTrain(str);
	cout << getWord() << endl;
	cout << getAttr() << endl;
	cout << getTag() << endl;

	string str2 = "企业/NN";
	setWordTest(str2);
	cout << getWord() << endl;
	cout << getAttr() << endl;
}

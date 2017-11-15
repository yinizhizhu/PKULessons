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
void word::setWord(string& str) {
	int i, j, d = 0, d1, len = str.size();
	for (i=0; i<len; i++)
		if (str[i] == '/') {
			d1 = i;
			break;
		}
	store = new char[d1+1];
	for (j = 0; d < d1; j++, d++)
		store[j] = str[d];
	store[j] = '\0';

#ifdef SHOW
	cout << d1 + 1 << " " << strlen(store) << endl;
#endif // SHOW

	for (++i; i<len; i++)
		if (str[i] == '/') {
			d1 = i;
			break;
		}
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

char *word::getWord() {
	if (store)
		return store;
	cout << "The word is empty!" << endl;
	return NULL;
}

char *word::getAttr() {
	if (attr)
		return attr;
	cout << "The attr is empty!" << endl;
	return NULL;
}

char *word::getTag() {
	if (tag)
		return tag;
	cout << "The tag is empty!" << endl;
	return NULL;
}

void word::demo() {
	string str = "ÆóÒµ/NN/O";
	setWord(str);
	cout << getWord() << endl;
	cout << getAttr() << endl;
	cout << getTag() << endl;
}
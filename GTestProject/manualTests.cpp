#include "pch.h"
#include "wordSort.h"
#include "manualTests.h"

void TEST_COMP_1() {
	char word1[] = "a";
	char word2[] = "b";
	if (comp(word1, word2)) {
		std::cout << "<TEST_COMP_1> - PASS" << std::endl;
	}
	else{
		std::cout << "<TEST_COMP_1> - FAIL" << std::endl;
	}
}

void TEST_COMP_2() {
	char word1[] = "b";
	char word2[] = "a";
	if (!comp(word1, word2)) {
		std::cout << "<TEST_COMP_2> - PASS" << std::endl;
	}
	else {
		std::cout << "<TEST_COMP_2> - FAIL" << std::endl;
	}
}

void TEST_COMP_3() {
	char word1[] = "a";
	char word2[] = "a";
	if (comp(word1, word2)) {
		std::cout << "<TEST_COMP_3> - PASS" << std::endl;
	}
	else {
		std::cout << "<TEST_COMP_3> - FAIL" << std::endl;
	}
}

void TEST_ISEQUAL_1() {
	char word1[] = "a";
	char word2[] = "a";
	if (isEqual(word1, word2)) {
		std::cout << "<TEST_ISEQUAL_1> - PASS" << std::endl;
	}
	else {
		std::cout << "<TEST_ISEQUAL_1> - FAIL" << std::endl;
	}
}

void TEST_ISEQUAL_2() {
	char word1[] = "a";
	char word2[] = "b";
	if (!isEqual(word1, word2)) {
		std::cout << "<TEST_ISEQUAL_2> - PASS" << std::endl;
	}
	else {
		std::cout << "<TEST_ISEQUAL_2> - FAIL" << std::endl;
	}
}

void TEST_ISEQUAL_3() {
	char word1[] = "ab";
	char word2[] = "c";
	if (!isEqual(word1, word2)) {
		std::cout << "<TEST_ISEQUAL_3> - PASS" << std::endl;
	}
	else {
		std::cout << "<TEST_ISEQUAL_3> - FAIL" << std::endl;
	}

}

void TEST_COPY_1() {
	char word1[] = "a";
	char word2[sizeof(word1)];
	copy(word1, word2);
	if (isEqual(word1, word2)) {
		std::cout << "<TEST_COPY_1> - PASS" << std::endl;
	}
	else {
		std::cout << "<TEST_COPY_1> - FAIL" << std::endl;
	}
}

void TEST_SEARCH_1() {
	char word[] = "a";
	Pair x;
	copy(word, x.word);
	pairArr[0] = x;
	words = 1;

	if (search(word)) {
		std::cout << "<TEST_SEARCH_1> - PASS" << std::endl;
	}
	else {
		std::cout << "<TEST_SEARCH_1> - FAIL" << std::endl;
	}
}

void TEST_SEARCH_2() {
	char word1[] = "a";
	char word2[] = "b";
	Pair x;
	copy(word1, x.word);
	pairArr[0] = x;
	words = 1;

	if (!search(word2)) {
		std::cout << "<TEST_SEARCH_2> - PASS" << std::endl;
	}
	else {
		std::cout << "<TEST_SEARCH_2> - FAIL" << std::endl;
	}
}

void TEST_PROCESS_1() {
	char word[] = "addme";
	process(word);
	if (isEqual(pairArr[nextPos-1].word, word)) {
		std::cout << "<TEST_PROCESS_1> - PASS" << std::endl;
	}
	else {
		std::cout << "<TEST_PROCESS_1> - FAIL" << std::endl;
	}
}

void TEST_READWORDS_1(){
	int locations[SIZE];
	std::ofstream file("TEST_READWORDS_1.txt");
	file << "word notWord notWord word word";
	file.close();

	std::string word = "word";

	std::ifstream readFile("TEST_READWORDS_1.txt");
	
	readWords(readFile, locations, word);

	readFile.close();

	if (locations[0] == 0 && locations[1] == 3 && locations[2] == 4) {
		std::cout << "<TEST_READWORDS_1> - PASS" << std::endl;
	}
	else {
		std::cout << "<TEST_READWORDS_1> - FAIL" << std::endl;
	}
}

void TEST_READWORDS_2() {
	std::ofstream file("TEST_READWORDS_1.txt");
	file << "one two three four five";
	file.close();

	std::ifstream readFile("TEST_READWORDS_1.txt");

	readWords(readFile);

	readFile.close();

	if (words == 5){
		std::cout << "<TEST_READWORDS_1> - PASS" << std::endl;
	}
	else {
		std::cout << "<TEST_READWORDS_1> - FAIL" << std::endl;
	}
	rWBool = false;
}

void TEST_READWORDS_3() {
	std::ofstream file("TEST_READWORDS_1.txt");
	file << "??.word1 /<>2 `|3 #%4 ()5";
	file.close();

	std::ifstream readFile("TEST_READWORDS_1.txt");

	readWords(readFile);

	readFile.close();

	if (words == 1) {
		std::cout << "<TEST_READWORDS_2> - PASS" << std::endl;
	}
	else {
		std::cout << "<TEST_READWORDS_2> - FAIL" << std::endl;
	}
	rWBool = false;
}

void TEST_READWORDS_4() {
	std::ofstream file("TEST_READWORDS_1.txt");
	file << "one two three four five";
	file.close();

	std::ifstream readFile("TEST_READWORDS_1.txt");
	readWords(readFile);
	readFile.close();

	std::ofstream file2("TEST_READWORDS_1.txt");
	file2 << "one two three four five six";
	file2.close();

	std::ifstream readFile2("TEST_READWORDS_1.txt");
	readWords(readFile2);
	readFile2.close();

	if (words == 5) {
		std::cout << "<TEST_READWORDS_3> - PASS" << std::endl;
	}
	else {
		std::cout << "<TEST_READWORDS_3> - FAIL" << std::endl;
	}
	rWBool = false;
}

void TEST_INSERTFIRST_1() {
	char word[] = "word";
	Pair p;
	copy(word, p.word);
	p.occurance = 1;

	TreeNode* rootPtr = insertFirst(p);
	if (rootPtr != NULL && isEqual(rootPtr->pair.word, word) && rootPtr->pair.occurance == 1) {
		std::cout << "<TEST_INSERTFIRST_1> - PASS" << std::endl;
	}
	else {
		std::cout << "<TEST_INSERTFIRST_1> - FAIL" << std::endl;
	}
	delete rootPtr;
}

void TEST_INSERTFIRST_2() {
	Pair p;
	TreeNode* rootPtr = insertFirst(p);
	if (rootPtr != NULL && rootPtr->left == NULL && rootPtr->right == NULL) {
		std::cout << "<TEST_INSERTFIRST_2> - PASS" << std::endl;
	}
	else {
		std::cout << "<TEST_INSERTFIRST_2> - FAIL" << std::endl;
	}
	delete rootPtr;
}

void TEST_INSERTALPHA_1() {
	char word1[] = "a";
	Pair p1;
	copy(word1, p1.word);
	p1.occurance = 1;

	char word2[] = "z";
	Pair p2;
	copy(word2, p2.word);
	p2.occurance = 1;

	TreeNode* rootPtr = insertFirst(p1);
	insertAlpha(p2, rootPtr);

	if(rootPtr != NULL && rootPtr->left == NULL && rootPtr->right != NULL) {
		std::cout << "<TEST_INSERTALPHA_1> - PASS" << std::endl;
	}
	else {
		std::cout << "<TEST_INSERTALPHA_1> - FAIL" << std::endl;
	}
	delete rootPtr;
}

void TEST_INSERTALPHA_2() {
	char word1[] = "z";
	Pair p1;
	copy(word1, p1.word);
	p1.occurance = 1;

	char word2[] = "a";
	Pair p2;
	copy(word2, p2.word);
	p2.occurance = 1;

	TreeNode* rootPtr = insertFirst(p1);
	insertAlpha(p2, rootPtr);

	if (rootPtr != NULL && rootPtr->right == NULL && rootPtr->left != NULL) {
		std::cout << "<TEST_INSERTALPHA_2> - PASS" << std::endl;
	}
	else {
		std::cout << "<TEST_INSERTALPHA_2> - FAIL" << std::endl;
	}
	delete rootPtr;
}

void TEST_INSERTCOMPLETE_1() {
	char word1[] = "a";
	Pair p1;
	copy(word1, p1.word);
	p1.occurance = 2;

	char word2[] = "a";
	Pair p2;
	copy(word2, p2.word);
	p2.occurance = 1;

	TreeNode* rootPtr = insertFirst(p1);
	insertComplete(p2, rootPtr);

	if (rootPtr != NULL && rootPtr->left == NULL && rootPtr->right != NULL) {
		std::cout << "<TEST_INSERTCOMPLETE_1> - PASS" << std::endl;
	}
	else {
		std::cout << "<TEST_INSERTCOMPLETE_1> - FAIL" << std::endl;
	}
	delete rootPtr;
}

void TEST_INSERTCOMPLETE_2() {
	char word1[] = "a";
	Pair p1;
	copy(word1, p1.word);
	p1.occurance = 1;

	char word2[] = "a";
	Pair p2;
	copy(word2, p2.word);
	p2.occurance = 2;

	TreeNode* rootPtr = insertFirst(p1);
	insertComplete(p2, rootPtr);

	if (rootPtr != NULL && rootPtr->right == NULL && rootPtr->left != NULL) {
		std::cout << "<TEST_INSERTCOMPLETE_2> - PASS" << std::endl;
	}
	else {
		std::cout << "<TEST_INSERTCOMPLETE_2> - FAIL" << std::endl;
	}
	delete rootPtr;
}

void TEST_INSERTCOMPLETE_3() {
	char word1[] = "a";
	Pair p1;
	copy(word1, p1.word);
	p1.occurance = 1;

	char word2[] = "z";
	Pair p2;
	copy(word2, p2.word);
	p2.occurance = 1;

	TreeNode* rootPtr = insertFirst(p1);
	insertComplete(p2, rootPtr);

	if (rootPtr != NULL && rootPtr->left == NULL && rootPtr->right != NULL) {
		std::cout << "<TEST_INSERTCOMPLETE_3> - PASS" << std::endl;
	}
	else {
		std::cout << "<TEST_INSERTCOMPLETE_3> - FAIL" << std::endl;
	}
	delete rootPtr;
}

void TEST_INSERTCOMPLETE_4() {
	char word1[] = "z";
	Pair p1;
	copy(word1, p1.word);
	p1.occurance = 1;

	char word2[] = "a";
	Pair p2;
	copy(word2, p2.word);
	p2.occurance = 1;

	TreeNode* rootPtr = insertFirst(p1);
	insertComplete(p2, rootPtr);

	if (rootPtr != NULL && rootPtr->right == NULL && rootPtr->left != NULL) {
		std::cout << "<TEST_INSERTCOMPLETE_4> - PASS" << std::endl;
	}
	else {
		std::cout << "<TEST_INSERTCOMPLETE_4> - FAIL" << std::endl;
	}
	delete rootPtr;
}

void TEST_READALPHA_1() {
	char word1[] = "b";
	Pair p1;
	copy(word1, p1.word);
	p1.occurance = 1;

	char word2[] = "a";
	Pair p2;
	copy(word2, p2.word);
	p2.occurance = 1;

	char word3[] = "c";
	Pair p3;
	copy(word3, p3.word);
	p3.occurance = 1;

	TreeNode* rootPtr = insertFirst(p1);
	insertAlpha(p2, rootPtr);
	insertAlpha(p3, rootPtr);

	std::vector<Pair*> results;

	std::ofstream writeFile("TEST_READALPHA_1_OUT.txt");
	readAlpha(rootPtr, writeFile, results);
	writeFile.close();

	if (comp(results[0]->word, results[1]->word) && comp(results[1]->word, results[2]->word)) {
		std::cout << "<TEST_READALPHA_1> - PASS" << std::endl;
	}
	else {
		std::cout << "<TEST_READALPHA_1> - FAIL" << std::endl;
	}
	delete rootPtr;
}

void TEST_READCOMPLETE_1() {
	char word1[] = "b";
	Pair p1;
	copy(word1, p1.word);
	p1.occurance = 2;

	char word2[] = "a";
	Pair p2;
	copy(word2, p2.word);
	p2.occurance = 1;

	char word3[] = "c";
	Pair p3;
	copy(word3, p3.word);
	p3.occurance = 3;

	TreeNode* rootPtr = insertFirst(p1);
	insertComplete(p2, rootPtr);
	insertComplete(p3, rootPtr);

	std::vector<Pair*> results;

	std::ofstream writeFile("TEST_READCOMPLETE_1_OUT.txt");
	readComplete(rootPtr, writeFile, results);
	writeFile.close();

	if (results[0]->occurance > results[1]->occurance && results[1]->occurance > results[2]->occurance) {
		std::cout << "<TEST_READCOMPLETE_1> - PASS" << std::endl;
	}
	else {
		std::cout << "<TEST_READCOMPLETE_1> - FAIL" << std::endl;
	}
}

void TEST_DELETETREE_1() {
	char word1[] = "a";
	Pair p1;
	copy(word1, p1.word);

	char word2[] = "b";
	Pair p2;
	copy(word2, p2.word);

	char word3[] = "c";
	Pair p3;
	copy(word3, p3.word);

	TreeNode* rootPtr = insertFirst(p1);
	insertAlpha(p2, rootPtr);
	insertAlpha(p3, rootPtr);

	deleteTree(rootPtr);

	if (rootPtr->right == NULL && rootPtr->left == NULL) {
		std::cout << "<TEST_DELETETREE_1> - PASS" << std::endl;
	}
	else {
		std::cout << "<TEST_DELETETREE_1> - FAIL" << std::endl;
	}
	delete rootPtr;
}

void TEST_COUNT_1() {
	nextPos = 0;
	std::ofstream file("TEST_COUNT_1.txt");
	file << "one two two three four three three four five four five four five five five";
	file.close();

	count("TEST_COUNT_1.txt");
	std::string line;
	std::vector<std::string> readOrder;

	std::ifstream readFile("count.txt");
	while (std::getline(readFile, line)) {
		std::string lineW = line.substr(0, line.find(" - "));
		std::string lineC = line.substr(lineW.length()+3);
		readOrder.push_back(lineW);
		readOrder.push_back(lineC);
	}
	readFile.close();

	bool oneCheck = (readOrder[0] == "one" && stoi(readOrder[1]) == 1);
	bool twoCheck = (readOrder[2] == "two" && stoi(readOrder[3]) == 2);
	bool threeCheck = (readOrder[4] == "three" && stoi(readOrder[5]) == 3);
	bool fourCheck = (readOrder[6] == "four" && stoi(readOrder[7]) == 4);
	bool fiveCheck = (readOrder[8] == "five" && stoi(readOrder[9]) == 5);

	if (oneCheck && twoCheck && threeCheck && fourCheck && fiveCheck) {
		std::cout << "<TEST_COUNT_1> - PASS" << std::endl;
	}
	else {
		std::cout << "<TEST_COUNT_1> - FAIL" << std::endl;
	}
	rWBool = false;
}

void TEST_COUNT_2() {
	nextPos = 0;
	std::ofstream file("TEST_COUNT_2.txt");
	file << "";
	file.close();

	count("TEST_COUNT_2.txt");
	std::string line;
	std::vector<std::string> readOrder;

	std::ifstream readFile("count.txt");
	std::getline(readFile, line);
	readFile.close();

	if (line == "no words found in file") {
		std::cout << "<TEST_COUNT_2> - PASS" << std::endl;
	}
	else {
		std::cout << "<TEST_COUNT_2> - FAIL" << std::endl;
	}
	rWBool = false;
}

void TEST_LOCATION_1() {
	std::ofstream file("TEST_LOCATION_1.txt");
	file << "word notWord notWord word word";
	file.close();

	std::string word = "word";

	wordsLocation(word, "TEST_LOCATION_1.txt");

	std::vector<int> numbers;

	std::ifstream inFile("location.txt");

	std::string line;
	std::getline(inFile, line);
	while (getline(inFile, line)) {
		numbers.push_back(stoi(line));
	}
	bool oneCheck = (numbers[0] == 0);
	bool twoCheck = (numbers[1] == 3);
	bool threeCheck = (numbers[2] == 4);

	if (oneCheck && twoCheck && threeCheck) {
		std::cout << "<TEST_LOCATION_1> - PASS" << std::endl;
	}
	else {
		std::cout << "<TEST_LOCATION_1> - FAIL" << std::endl;
	}
}

void TEST_LOCATION_2() {
	std::ofstream file("TEST_LOCATION_2.txt");
	file << "notWord notWord";
	file.close();

	std::string word = "word";

	wordsLocation(word, "TEST_LOCATION_2.txt");

	std::ifstream inFile("location.txt");

	std::string allText;
	std::getline(inFile, allText);

	if (allText == "no locations found") {
		std::cout << "<TEST_LOCATION_2> - PASS" << std::endl;
	}
	else {
		std::cout << "<TEST_LOCATION_2> - FAIL" << std::endl;
	}
	rWBool = false;
	nextPos = 0;
}

void TEST_ALPHASORT_1() {
	std::ofstream file;
	file.open("TEST_ALPHASORT_1.txt");
	file << "c a b f d z";
	file.close();

	alphaSort("TEST_ALPHASORT_1.txt");

	std::ifstream inFile("alphaSort.txt");
	std::vector<std::string> allLines;
	int lines = 0;

	std::string line;
	while (getline(inFile, line)) {
		lines++;
		allLines.push_back(line);
	}
	inFile.close();

	bool pass = false;
	for (int i = 0; i < lines - 1; i++) {
		if (allLines[i] < allLines[i + 1]){
			pass = true;
		}
		else {
			pass = false;
			break;
		}
	}

	if (pass) {
		std::cout << "<TEST_ALPHASORT_1> - PASS" << std::endl;
	}
	else {
		std::cout << "<TEST_ALPHASORT_1> - FAIL" << std::endl;
	}
}

void TEST_ALPHASORT_2() {
	rWBool = false;
	nextPos = 0;

	std::ofstream file("TEST_ALPHASORT_2.txt");
	file << "c a b a f a d a z";
	file.close();

	alphaSort("TEST_ALPHASORT_2.txt");

	std::ifstream inFile("alphaSort.txt");
	std::vector<std::string> allLines;
	int lines = 0;

	std::string line;
	while (getline(inFile, line)) {
		lines++;
		allLines.push_back(line);
	}
	inFile.close();

	bool pass = false;
	for (int i = 0; i < lines - 1; i++) {
		if (allLines[i] < allLines[i + 1]) {
			pass = true;
		}
		else {
			pass = false;
			break;
		}
	}

	for (int i = 0; i < lines - 1; i++) {
		for (int j = i + 1; j < lines; j++) {
			if (allLines[i] == allLines[j]){
				pass = false;
			}
		}
	}

	if (pass) {
		std::cout << "<TEST_ALPHASORT_2> - PASS" << std::endl;
	}
	else {
		std::cout << "<TEST_ALPHASORT_2> - FAIL" << std::endl;
	}
}

void TEST_COMPLETESORT_1() {
	rWBool = false;
	nextPos = 0;

	std::ofstream file("TEST_COMPLETESORT_1.txt");
	file << "cow a b f d z";
	file.close();

	completeSort("TEST_COMPLETESORT_1.txt");

	std::ifstream inFile("completeSort.txt");
	std::vector<std::string> allLines;
	int lines = 0;

	std::string line;
	while (getline(inFile, line)) {
		lines++;
		line = line.substr(0, line.find(" - "));
		allLines.push_back(line);
	}

	bool pass = false;
	for (int i = 0; i < lines - 1; i++) {
		if (allLines[i] < allLines[i + 1]) {
			pass = true;
		}
		else {
			pass = false;
			break;
		}
	}

	if (pass) {
		std::cout << "<TEST_COMPLETESORT_1> - PASS" << std::endl;
	}
	else {
		std::cout << "<TEST_COMPLETESORT_1> - FAIL" << std::endl;
	}
}

void TEST_COMPLETESORT_2() {
	rWBool = false;
	nextPos = 0;

	std::ofstream file("TEST_COMPLETESORT_2.txt");
	file << "c a b f d z c a b f d z";
	file.close();

	completeSort("TEST_COMPLETESORT_2.txt");

	std::ifstream inFile("completeSort.txt");
	std::vector<std::string> allLines;
	int lines = 0;

	std::string line;
	while (getline(inFile, line)) {
		lines++;
		line = line.substr(0, line.find(" - "));
		allLines.push_back(line);
	}

	bool pass = false;
	for (int i = 0; i < lines - 1; i++) {
		if (allLines[i] < allLines[i + 1]) {
			pass = true;
		}
		else {
			pass = false;
			break;
		}
	}

	for (int i = 0; i < lines - 1; i++) {
		for (int j = i + 1; j < lines; j++) {
			if (allLines[i] == allLines[j]) {
				pass = false;
			}
		}
	}

	if (pass) {
		std::cout << "<TEST_COMPLETESORT_2> - PASS" << std::endl;
	}
	else {
		std::cout << "<TEST_COMPLETESORT_2> - FAIL" << std::endl;
	}
}

void TEST_COMPLETESORT_3() {
	rWBool = false;
	nextPos = 0;

	std::ofstream file("TEST_COMPLETESORT_3.txt");
	file << "c a b f d z z";
	file.close();

	completeSort("TEST_COMPLETESORT_3.txt");

	std::ifstream inFile("completeSort.txt");
	std::vector<std::string> allLines1Occ;
	std::vector<std::string> allLines2Occ;
	int lines1Occ = 0;
	int lines2Occ = 0;

	std::string line;
	std::string word;
	std::string occ;
	while (getline(inFile, line)) {
		word = line.substr(0, line.find(" - "));
		occ = line.substr(word.length() + 3);
		if (stoi(occ) == 1) {
			allLines1Occ.push_back(word);
			lines1Occ++;
		}
		else{
			allLines2Occ.push_back(word);
			lines2Occ++;
		}
	}

	bool pass = true;

	for (int i = 0; i < lines2Occ; i++) {
		for (int j = i + 1; j < lines2Occ; j++) {
			if (allLines2Occ[i] == allLines2Occ[j]) {
				pass = false;
			}
		}
		for (int j = 0; j < lines1Occ; j++) {
			if (allLines2Occ[i] == allLines1Occ[j]) {
				pass = false;
			}
		}
		if (lines2Occ > 1) {
			if (!(allLines2Occ[i] < allLines2Occ[i + 1])) {
				pass = false;
			}
		}
		
	}

	for (int i = 0; i < lines1Occ - 1; i++) {
		for (int j = i + 1; j < lines1Occ; j++) {
			if (allLines1Occ[i] == allLines1Occ[j]) {
				pass = false;
			}
		}
		if (lines1Occ > 1) {
			if (!(allLines1Occ[i] < allLines1Occ[i + 1])) {
				pass = false;
			}
		}
	}

	if (pass) {
		std::cout << "<TEST_COMPLETESORT_3> - PASS" << std::endl;
	}
	else {
		std::cout << "<TEST_COMPLETESORT_3> - FAIL" << std::endl;
	}
}

void runCOMP() {
	std::cout << " \n--- comp ---\n" << std::endl;
	TEST_COMP_1();
	TEST_COMP_2();
	TEST_COMP_3();
}

void runISEQUAL() {
	std::cout << " \n--- isEqual ---\n" << std::endl;
	TEST_ISEQUAL_1();
	TEST_ISEQUAL_2();
	TEST_ISEQUAL_3();
}

void runCOPY() {
	std::cout << " \n--- copy ---\n" << std::endl;
	TEST_COPY_1();
}

void runSEARCH() {
	std::cout << " \n--- search ---\n" << std::endl;
	TEST_SEARCH_1();
	TEST_SEARCH_2();
}

void runPROCESS() {
	std::cout << " \n--- process ---\n" << std::endl;
	TEST_PROCESS_1();
}

void runREADWORDS() {
	std::cout << " \n--- readWords ---\n" << std::endl;
	TEST_READWORDS_1();
	TEST_READWORDS_2();
	TEST_READWORDS_3();
	TEST_READWORDS_4();
}

void runINSERTFIRST() {
	std::cout << " \n--- insertFirst ---\n" << std::endl;
	TEST_INSERTFIRST_1();
	TEST_INSERTFIRST_2();
}

void runINSERTALPHA() {
	std::cout << " \n--- insertAlpha ---\n" << std::endl;
	TEST_INSERTALPHA_1();
	TEST_INSERTALPHA_2();
}

void runINSERTCOMPLETE() {
	std::cout << " \n--- insertComplete ---\n" << std::endl;
	TEST_INSERTCOMPLETE_1();
	TEST_INSERTCOMPLETE_2();
	TEST_INSERTCOMPLETE_3();
	TEST_INSERTCOMPLETE_4();
}

void runREADALPHA() {
	std::cout << " \n--- readAlpha ---\n" << std::endl;
	TEST_READALPHA_1();
}

void runREADCOMPLETE() {
	std::cout << " \n--- readComplete ---\n" << std::endl;
	TEST_READCOMPLETE_1();
}

void runDELETETREE() {
	std::cout << " \n--- deleteTree ---\n" << std::endl;
	TEST_DELETETREE_1();
}

void runCOUNT() {
	std::cout << " \n--- count ---\n" << std::endl;
	TEST_COUNT_1();
	TEST_COUNT_2();
}

void runLOCATION() {
	std::cout << " \n--- location ---\n" << std::endl;
	TEST_LOCATION_1();
	TEST_LOCATION_2();
}

void runALPHASORT() {
	std::cout << " \n--- alphaSort ---\n" << std::endl;
	TEST_ALPHASORT_1();
	TEST_ALPHASORT_2();
}

void runCOMPLETESORT() {
	std::cout << " \n--- compelteSort ---\n" << std::endl;
	TEST_COMPLETESORT_1();
	TEST_COMPLETESORT_2();
	TEST_COMPLETESORT_3();
}

void runAll() {
	runCOMP();
	runISEQUAL();
	runCOPY();
	runSEARCH();
	runPROCESS();
	runREADWORDS();
	runINSERTFIRST();
	runINSERTALPHA();
	runINSERTCOMPLETE();
	runREADALPHA();
	runREADCOMPLETE();
	runDELETETREE();

	runCOUNT();
	runLOCATION();
	runALPHASORT();
	runCOMPLETESORT();
	std::cout << "\n";
}
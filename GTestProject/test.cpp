#include "pch.h"
#include "wordSort.h"
#include "testCaseGenerator.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;
void checkNode(TreeNode* n);
void checkNodeComplete(TreeNode* n);

struct WordFixture : public testing::TestWithParam<int> {
	vector<char*> inputs;
	void SetUp() {
		inputs = getInputsAlpha(2);
	}
	void TearDown() {
		while (!inputs.empty()) {
			delete inputs.back();
			inputs.pop_back();
		}
	}
};

struct SearchFixture : public testing::TestWithParam<int> {
	vector<char*> inputs;
	char newWord[101];
	void SetUp() {
		words = rand() % 6;
		nextPos = words;
		inputs = getInputsAlpha(words + 1);
		// The first 5 inputs are used to populate pairArr
		for (int i = 0; i < words; i++) {
			strcpy(pairArr[i].word, inputs[i]);
		}
		// The last input is used to populate a new word not in the pairArr
		strcpy(newWord, inputs.back());
	}
	void TearDown() {
		for (int i = 0; i < words; i++) {
			pairArr[i].word[0] = '\0';
			pairArr[i].occurance = 0;
		}
		nextPos = 0;
		words = 0;
		while (!inputs.empty()) {
			delete inputs.back();
			inputs.pop_back();
		}
	}
};

struct ReadWordFixture : public testing::TestWithParam<int> {
	vector<Pair*> inputs;
	vector<string> text;
	ifstream ifs;
	void SetUp() { 
		srand(unsigned(time(0)));
		inputs = getInputsComplete(rand() % 6 + 1);

		// Generate text from distinct words
		for (Pair* p : inputs) {
			for (int i = 0; i < p->occurance; i++) {
				text.push_back(string(p->word));
			}
		}
		random_shuffle(text.begin(), text.end());

		// Output text to file
		ofstream ofs;
		ofs.open("test.txt", ofstream::out | ofstream::trunc);
		for (string w : text) {
			w.insert(rand() % w.length(), getPunct()); // Add punctuation
			ofs << w << getPunct() << " ";
		}
		ofs.close();
		ifs.open("test.txt", ofstream::in);
	}
	void TearDown() {
		ifs.close();
		for (int i = 0; i < words; i++) {
			pairArr[i].word[0] = '\0';
			pairArr[i].occurance = 0;
		}
		nextPos = 0;
		words = 0;
		while (!inputs.empty()) {
			delete inputs.back();
			inputs.pop_back();
		}
	}
};

struct InsertNodeAlphaFixture : public testing::TestWithParam<int> {
	TreeNode* root;
	vector<Pair*> inputs;

	void SetUp() {
		//create a list of pairs including words and their occurances which was sorted alphabetically
		inputs = getInputsAlphaPairArr(10);
	}

	void TearDown() {
		for (int i = 0; i < words; i++) {
			pairArr[i].word[0] = '\0';
			pairArr[i].occurance = 0;
		}
		nextPos = 0;
		words = 0;
		while (!inputs.empty()) {
			delete inputs.back();
			inputs.pop_back();
		}
		delete root;
	}
};

struct InsertNodeCompleteFixture : public testing::TestWithParam<int> {
	TreeNode* root;
	vector<Pair*> inputs;

	void SetUp() {
		//create a list of pairs including words and their occurances which was sorted alphabetically
		inputs = getInputsComplete(10);
	}

	void TearDown() {
		for (int i = 0; i < words; i++) {
			pairArr[i].word[0] = '\0';
			pairArr[i].occurance = 0;
		}
		nextPos = 0;
		words = 0;
		while (!inputs.empty()) {
			delete inputs.back();
			inputs.pop_back();
		}
		delete root;
	}
};


struct ReadAlphaFixture : public testing::TestWithParam<int> {
	TreeNode* root;
	ofstream writeFile;
	vector<Pair*> oracle;
	vector<Pair*> inputs;
	vector<Pair*> results;
	void SetUp() {
		//create a list of pairs including words and their occurances which was sorted alphabetically
		oracle = getInputsAlphaPairArr(15);
		for (int i = 0; i < oracle.size(); i++) {
			inputs.push_back(oracle[i]);
		}
		//shuffle the places of pairs 
		auto rng = default_random_engine{};
		shuffle(begin(inputs), end(inputs), rng);
		//create tree root
		root = insertFirst(*inputs[0]);
		//add pairs to the tree
		for (int i = 1; i < inputs.size(); i++) {
			insertAlpha(*inputs[i], root);
		}

		writeFile.open("ReadAlpha.txt", ofstream::out);
	}
	void TearDown() {
		writeFile.close();
		for (int i = 0; i < words; i++) {
			pairArr[i].word[0] = '\0';
			pairArr[i].occurance = 0;
		}
		nextPos = 0;
		words = 0;
		rWBool = 0;
		while (!oracle.empty()) {
			delete oracle.back();
			oracle.pop_back();
		}
		delete root;
	}
};

struct ReadCompleteFixture : public testing::TestWithParam<int> {
	TreeNode* root;
	ofstream writeFile;
	vector<Pair*> oracle;
	vector<Pair*> inputs;
	vector<Pair*> results;
	void SetUp() {
		//create a list of pairs including words and their occurances which was sorted alphabetically
		oracle = getInputsComplete(15);
		for (int i = 0; i < oracle.size(); i++) {
			inputs.push_back(oracle[i]);
		}
		//shuffle the places of pairs 
		auto rng = default_random_engine{};
		shuffle(begin(inputs), end(inputs), rng);
		//create tree root
		root = insertFirst(*inputs[0]);
		//add pairs to the tree
		for (int i = 1; i < inputs.size(); i++) {
			insertComplete(*inputs[i], root);
		}

		writeFile.open("ReadComplete.txt", ofstream::out);
	}
	void TearDown() {
		writeFile.close();
		for (int i = 0; i < words; i++) {
			pairArr[i].word[0] = '\0';
			pairArr[i].occurance = 0;
		}
		nextPos = 0;
		words = 0;
		rWBool = 0;
		while (!oracle.empty()) {
			delete oracle.back();
			oracle.pop_back();
		}
		delete root;
	}
};

struct DeleteTreeFixture : public testing::TestWithParam<int> {
	TreeNode* root;
	vector<Pair*> inputs;
	vector<TreeNode*> nodes;
	void SetUp() {
		//create a list of pairs including words and their occurances which was sorted alphabetically
		inputs = getInputsComplete(15);
		//create tree root
		root = insertFirst(*inputs[0]);
		nodes.push_back(root);
		//add pairs to the tree
		for (int i = 1; i < inputs.size(); i++) {
			nodes.push_back(insertComplete(*inputs[i], root));
		}
	}
	void TearDown() {
		for (int i = 0; i < words; i++) {
			pairArr[i].word[0] = '\0';
			pairArr[i].occurance = 0;
		}
		nextPos = 0;
		words = 0;
		rWBool = 0;
		while (!inputs.empty()) {
			delete inputs.back();
			inputs.pop_back();
		}
		delete root;
	}
};

struct AlphaSortFixture : public testing::TestWithParam<int> {
	vector<Pair*> oracle;
	vector<Pair*> inputs;
	int WORDS = 15;
	void SetUp() {
		//create inputs
		oracle = getInputsAlphaPairArr(WORDS);
		for (int i = 0; i < oracle.size(); i++) {
			inputs.push_back(oracle[i]);
		}
		//shuffle the places of pairs 
		auto rng = default_random_engine{};
		shuffle(begin(inputs), end(inputs), rng);
		//write test into test.txt
		ofstream ofs;
		ofs.open("test.txt");
		for (int i = 0; i < inputs.size(); i++) {
			ofs << inputs[i]->word << "\n";
		}
		ofs.close();
	}

	void TearDown() {
		for (int i = 0; i < words; i++) {
			pairArr[i].word[0] = '\0';
			pairArr[i].occurance = 0;
		}
		nextPos = 0;
		words = 0;
		rWBool = 0;
		while (!oracle.empty()) {
			delete oracle.back();
			oracle.pop_back();
		}
	}
};

struct CompleteSortFixture : public testing::TestWithParam<int> {
	vector<Pair*> oracle;
	vector<Pair*> inputs;
	vector<int> occurance;
	int WORDS = 15;
	vector<int> locations;
	void SetUp() {
		//create inputs
		oracle = getInputsComplete(WORDS);
		for (int i = 0; i < oracle.size(); i++) {
			inputs.push_back(oracle[i]);
			occurance.push_back(oracle[i]->occurance);
		}
		//randomly save words from vector inputs to test.txt
		ofstream ofs;
		ofs.open("test.txt");
		while (inputs.size() > 0) {
			int index = getRandom(0, inputs.size() - 1);
			ofs << inputs[index]->word << "\n";
			occurance[index] -= 1;
			if (occurance[index] == 0) {
				inputs.erase(inputs.begin() + index);
				occurance.erase(occurance.begin() + index);
			}
		}
		ofs.close();
	}

	void TearDown() {
		for (int i = 0; i < words; i++) {
			pairArr[i].word[0] = '\0';
			pairArr[i].occurance = 0;
		}
		nextPos = 0;
		words = 0;
		rWBool = 0;
		while (!oracle.empty()) {
			delete oracle.back();
			oracle.pop_back();
		}
	}
};

struct CountFixture : public testing::TestWithParam<int> {
	vector<Pair*> oracle;
	vector<Pair*> inputs;
	vector<int> occurance;
	int WORDS = 15;
	int searchWordIndex;
	vector<int> locations;
	int totalWords = 0;
	void SetUp() {
		//create inputs
		oracle = getInputsComplete(WORDS);
		for (int i = 0; i < oracle.size(); i++) {
			inputs.push_back(oracle[i]);
			occurance.push_back(oracle[i]->occurance);
		}
		//randomly pick a search word
		searchWordIndex = getRandom(0, oracle.size() - 1);
		//randomly save words from vector inputs to test.txt
		ofstream ofs;
		ofs.open("test.txt");
		while (inputs.size() > 0) {
			int index = getRandom(0, inputs.size() - 1);
			ofs << inputs[index]->word << "\n";
			if (isEqual(oracle[searchWordIndex]->word, inputs[index]->word)) {
				locations.push_back(totalWords);
			}
			occurance[index] -= 1;
			if (occurance[index] == 0) {
				inputs.erase(inputs.begin() + index);
				occurance.erase(occurance.begin() + index);
			}
			totalWords++;
		}
		ofs.close();
	}
	void TearDown() {
		for (int i = 0; i < words; i++) {
			pairArr[i].word[0] = '\0';
			pairArr[i].occurance = 0;
		}
		nextPos = 0;
		words = 0;
		rWBool = 0;
		while (!oracle.empty()) {
			delete oracle.back();
			oracle.pop_back();
		}
	}
};

// Run randomized test multiple times
INSTANTIATE_TEST_CASE_P(Instantiation, WordFixture, ::testing::Range(1, 11), );
INSTANTIATE_TEST_CASE_P(Instantiation, SearchFixture, ::testing::Range(1, 11), );
INSTANTIATE_TEST_CASE_P(Instantiation, ReadWordFixture, ::testing::Range(1, 11), );
INSTANTIATE_TEST_CASE_P(Instantiation, ReadAlphaFixture, ::testing::Range(1, 11), );
INSTANTIATE_TEST_CASE_P(Instantiation, ReadCompleteFixture, ::testing::Range(1, 11), );
INSTANTIATE_TEST_CASE_P(Instantiation, DeleteTreeFixture, ::testing::Range(1, 11), );
INSTANTIATE_TEST_CASE_P(Instantiation, InsertNodeAlphaFixture, ::testing::Range(1, 11), );

TEST_F(WordFixture, WordCompare) {
	// Input[0] > Input[1]
	EXPECT_TRUE(comp(inputs[0], inputs[1]));
	EXPECT_TRUE(comp(inputs[1], inputs[1]));
	EXPECT_FALSE(comp(inputs[1], inputs[0]));
}

TEST_F(WordFixture, WordEqual) {
	EXPECT_TRUE(isEqual(inputs[0], inputs[0]));
	EXPECT_FALSE(isEqual(inputs[0], inputs[1]));
}

TEST_F(WordFixture, WordCopy) {
	char newWord[101];
	copy(inputs[0], newWord);
	EXPECT_TRUE(strcmp(inputs[0], newWord) == 0);
}

TEST_F(SearchFixture, WordSearch) {
	// Randomly choose an existing word in pairArr and search for it
	int randIndx = rand() % words;
	int prevOccur = pairArr[randIndx].occurance;
	EXPECT_TRUE(search(pairArr[randIndx].word));
	EXPECT_TRUE(pairArr[randIndx].occurance - prevOccur == 1);
	// Search for new word
	EXPECT_FALSE(search(newWord));
}

TEST_F(SearchFixture, WordProcess) {
	int randIndx = rand() % words;
	int prevOccur = pairArr[randIndx].occurance;
	int prevWords = words;
	int prevNextPos = nextPos;
	// Randomly choose an existing word in pairArr and process it
	process(pairArr[randIndx].word);
	EXPECT_EQ(prevWords, words);
	EXPECT_EQ(prevNextPos, nextPos);
	// Process a new word
	process(newWord);
	EXPECT_EQ(prevWords, words - 1);
	EXPECT_EQ(prevNextPos, nextPos - 1);
}

TEST_F(ReadWordFixture, ReadWordsLoc) {
	// One of the words in the input
	int randIdx = rand() % inputs.size();
	string word = string(inputs[randIdx]->word);
	int checkNextLoc = 0;
	int checkloc[100]; // correct location array
	int location[100];
	
	for (int i = 0; i < text.size(); i++) {
		if (text[i] == word)
			checkloc[checkNextLoc++] = i;
	}

	int nextLoc = readWords(ifs, location, word);

	EXPECT_EQ(words, text.size()); // Every word has been read
	// Correctly captured all occurances of search word
	EXPECT_EQ(nextLoc, inputs[randIdx]->occurance); 
	for (int i = 0; i < nextLoc; i++) {
		EXPECT_EQ(checkloc[i], location[i]);
	}
}

TEST_F(ReadWordFixture, ReadWordsPair) {
	readWords(ifs);
	for (int i = 0; i < words; i++) {
		bool found = false;
		for (Pair* p : inputs) {
			if (string(p->word) == string(pairArr[i].word) && p->occurance == pairArr[i].occurance) {
				found = true;
				break;
			}
		}
		// Number of words in pairArr is equal to that of words in inputs
		EXPECT_TRUE(found);
	}
	// Check for number of distinct words
	EXPECT_TRUE(words == nextPos && words == inputs.size());
}

TEST_F(InsertNodeAlphaFixture, insertFirst) {
	root = insertFirst(*inputs[0]);
	EXPECT_EQ(root->pair.occurance, inputs[0]->occurance);
	EXPECT_EQ(comp(root->pair.word, inputs[0]->word), true);
	EXPECT_EQ(root->left, nullptr);
	EXPECT_EQ(root->right, nullptr);
}

TEST_F(InsertNodeAlphaFixture, insertAlpha) {
	//Shuffle the inputs array. 
	//By running this function multiple times, we can test a lot of different combination
	auto rng = default_random_engine{};
	shuffle(begin(inputs), end(inputs), rng);
	
	//Create the root using the last inputs
	//Reason for using back() and insert backwards: 
	//	In case we need to pass the inputs array down the recursion,
	//	using vector.pop_back() is less expensive
	root = insertFirst(*inputs.back());

	//Insert the rest of the nodes
	for (int i = inputs.size() - 2; i >= 0; i--) {
		insertAlpha(*inputs[i], root);
	}
	
	//Recursively check the nodes
	checkNode(root);
}

// Recursion for InsertAlpha
void checkNode(TreeNode* n) {
	if (n->left != nullptr) {
		EXPECT_TRUE(comp(n->left->pair.word, n->pair.word));
		checkNode(n->left);
	}
	else {
		EXPECT_TRUE(n->left == nullptr);
	}

	if (n->right != nullptr) {
		EXPECT_FALSE(comp(n->right->pair.word, n->pair.word));
		checkNode(n->right);
	} else {
		EXPECT_TRUE(n->right == nullptr);
	}
}

TEST_F(InsertNodeCompleteFixture, insertComplete) {
	//Shuffle the inputs array. 
	//By running this function multiple times, we can test a lot of different combination
	auto rng = default_random_engine{};
	shuffle(begin(inputs), end(inputs), rng);
	root = insertFirst(*inputs.back());

	//Insert the rest of the nodes
	for (int i = inputs.size() - 2; i >= 0; i--) {
		insertComplete(*inputs[i], root);
	}

	//Recursively check the nodes
	checkNodeComplete(root);
}

void checkNodeComplete(TreeNode* n) {
	if (n->left != nullptr) {
		EXPECT_TRUE(n->left->pair.occurance >= n->pair.occurance || 
					!comp(n->left->pair.word, n->pair.word));
		checkNodeComplete(n->left);
	}
	else {
		EXPECT_TRUE(n->left == nullptr);
	}

	if (n->right != nullptr) {
		EXPECT_TRUE(n->right->pair.occurance < n->pair.occurance || 
					comp(n->right->pair.word, n->pair.word));
		checkNodeComplete(n->right);
	}
	else {
		EXPECT_TRUE(n->right == nullptr);
	}
}

TEST_F(ReadAlphaFixture, ReadBSTTreeAlphabetically) {
	readAlpha(root, writeFile, results);
	for (int i = 0; i < oracle.size(); i++) {
		EXPECT_TRUE(isEqual(results[i]->word, oracle[i]->word));
	}
}

TEST_F(ReadCompleteFixture, ReadBSTTreeCompletely) {
	readComplete(root, writeFile, results);
	for (int i = 0; i < oracle.size(); i++) {
		EXPECT_TRUE(isEqual(results[i]->word, oracle[i]->word));
		EXPECT_TRUE(results[i]->occurance == oracle[i]->occurance);
	}
}

TEST_F(DeleteTreeFixture, DeleteTree) {
	deleteTree(root);
	char expectedWord[101];
	expectedWord[0] = '\0';
	int expectedOccurance = 0;
	for (int i = 0; i < nodes.size(); i++) {
		EXPECT_TRUE(isEqual(nodes[i]->pair.word, expectedWord));
		EXPECT_TRUE(nodes[i]->pair.occurance == expectedOccurance);
	}
}

TEST_F(CountFixture, Count) {
	count("test.txt");
	ifstream inFile("count.txt");
	int lines = 0;
	string line;
	while (getline(inFile, line)) {
		char word[101];
		strcpy(word, line.substr(0, line.find(" - ")).c_str());
		int index = -1;
		for (int i = 0; i < oracle.size(); i++) {
			if (isEqual(oracle[i]->word, word)) {
				index = i;
			}
		}
		//the word is existing in oracle
		EXPECT_TRUE(index != -1);
		int occurance = stoi(line.substr(line.find(" - ") + 3, line.length()));
		//check the occurance
		EXPECT_TRUE(oracle[index]->occurance == occurance);
	}
	inFile.close();
	//test if the number of distinct words is counted correctly
	EXPECT_TRUE(words == WORDS);
}

TEST_F(CountFixture, Location) {
	string word(oracle[searchWordIndex]->word);
	wordsLocation(word, "test.txt");
	ifstream inFile("location.txt");
	int lines = 0;
	string line;
	getline(inFile, line);
	while (getline(inFile, line)) {
		int location = stoi(line);
		EXPECT_TRUE(location == locations[lines]);
		lines++;
	}
	EXPECT_TRUE(lines > 0);
	inFile.close();
}

TEST_F(AlphaSortFixture, SortAlphabetically) {
	alphaSort("test.txt");
	ifstream inFile("alphaSort.txt");
	int lines = 0;
	string line;
	while (getline(inFile, line)) {
		char word[101];
		strcpy(word, line.c_str());
		//test if words are sorted alphabetically
		EXPECT_TRUE(isEqual(oracle[lines]->word, word));
		lines++;
	}
	inFile.close();
}

TEST_F(CompleteSortFixture, SortCompletely) {
	completeSort("test.txt");
	ifstream inFile("completeSort.txt");
	int lines = 0;
	string line;
	while (getline(inFile, line)) {
		char word[101];
		strcpy(word, line.substr(0, line.find(" - ")).c_str());
		//test if words are sorted completely (numerical-alphabetical)
		EXPECT_TRUE(isEqual(oracle[lines]->word, word));
		int occurance = stoi(line.substr(line.find(" - ") + 3, line.length()));
		EXPECT_TRUE(oracle[lines]->occurance == occurance);
		lines++;
	}
	inFile.close();
}
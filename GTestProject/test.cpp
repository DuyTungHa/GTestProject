#include "pch.h"
#include "wordSort.h"
#include "testCaseGenerator.h"
#include <vector>
#include <string>

using namespace std;

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
		nextPos = words = rand() % 6;
		inputs = getInputsAlpha(words + 1);
		for (int i = 0; i < words; i++) {
			strcpy(pairArr[i].word, inputs[i]);
		}
		strcpy(newWord, inputs.back());
	}
	void TearDown() {
		for (int i = 0; i < words; i++) {
			pairArr[i].word[0] = '\0';
			pairArr[i].occurance = 0;
		}
		nextPos = words = 0;
		while (!inputs.empty()) {
			delete inputs.back();
			inputs.pop_back();
		}
	}
};

// Run randomized test multiple times
INSTANTIATE_TEST_CASE_P(Instantiation, WordFixture, ::testing::Range(1, 11), );
INSTANTIATE_TEST_CASE_P(Instantiation, SearchFixture, ::testing::Range(1, 11), );

TEST_F(WordFixture, WordCompare) {
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
	int randIndx = rand() % words;
	int prevOccur = pairArr[randIndx].occurance;
	EXPECT_TRUE(search(pairArr[randIndx].word));
	EXPECT_TRUE(pairArr[randIndx].occurance - prevOccur == 1);
	EXPECT_FALSE(search(newWord));
}

TEST_F(SearchFixture, WordProcess) {
	int randIndx = rand() % words;
	int prevOccur = pairArr[randIndx].occurance;
	int prevWords = words;
	int prevNextPos = nextPos;
	process(pairArr[randIndx].word, 0);
	EXPECT_EQ(prevWords, words);
	EXPECT_EQ(prevNextPos, nextPos);
	process(newWord, 0);
	EXPECT_EQ(prevWords, words - 1);
	EXPECT_EQ(prevNextPos, nextPos - 1);
}
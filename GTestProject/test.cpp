#include "pch.h"
#include "wordSort.h"
#include "testCaseGenerator.h"
#include <vector>
#include <string>

using namespace std;

struct WordFixture : public testing::Test {
	vector<char*> inputs;
	void SetUp() {
	
	}
	void TearDown() {
		while (!inputs.empty()) {
			delete inputs.back();
			inputs.pop_back();
		}
	}
};


TEST_F(WordFixture, WordCompare) {
	inputs = getInputsAlpha(3);

	// EXPECT_FALSE(comp(inputs[1], inputs[0]));
	EXPECT_TRUE(comp(inputs[0], inputs[1]));
	// EXPECT_FALSE(isEqual(inputs[0], inputs[1]));
}
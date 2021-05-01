#include "pch.h"
#include "wordSort.h"
#include "testCaseGenerator.h"
#include <vector>
#include <string>

using namespace std;


TEST(TestCaseName, TestName) {
	vector<char*> inputs = getInputsAlpha(3);

	EXPECT_FALSE(comp(inputs[1], inputs[0]));
	EXPECT_TRUE(comp(inputs[0], inputs[1]));

	EXPECT_FALSE(isEqual(inputs[0], inputs[1]));

	while (!inputs.empty()) {
		delete inputs.back();
		inputs.pop_back();
	}
}
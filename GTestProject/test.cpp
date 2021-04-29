#include "pch.h"
#include "system.h"
#include <vector>

using namespace std;

TEST(TestCaseName, TestName) {
	vector<int> a = { 1 , 1 };
	EXPECT_EQ(sum(a), 2);
	EXPECT_TRUE(true);
}
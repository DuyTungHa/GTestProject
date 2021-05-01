#include "pch.h"
#include "testCaseGenerator.h"
#include "wordSort.h"

std::vector<std::string> wordPool = { "alpaca","bee","cat","dog","eagle","frog",
"giraffle", "hippopotamus","iguana","jaguar","koala","llama","monkey","newt",
"otter","parrot","quail","raccoon","saola","tortoise","utonagan","vaquita","wasp",
"xerus","yak","zebra" };

int getRandom(int min, int max) {
	static std::random_device randev;
	static std::mt19937 mt_eng(randev());
	std::uniform_int_distribution<int> uniform(min, max);
	return uniform(mt_eng);
}

std::vector<char*> getInputsAlpha(int numberOfInputs) {
	int range = wordPool.size() / numberOfInputs;

	std::vector<char*> inputs;
	for (int i = 0; i < numberOfInputs; i++) {
		int index = range * i + getRandom(1,range) - 1;
		std::string sWord = wordPool[index];
		char* word;
		word = new char[sWord.length() + 1];
		inputs.push_back(strcpy(word, sWord.c_str()));
	}

	return inputs;
}
/*
std::vector<Pair*> getInputsComplete(int numberOfInputs) {
	std::vector<char*> words = getInputsAlpha(numberOfInputs);

	int previousOccurance = 1;
	std::vector<int> occurances;
	std::vector<int> oo;
	for (int i = 0; i < numberOfInputs; i++) {
		int occurance = previousOccurance + getRandom(0,5);
		if (occurance == previousOccurance) {
			oo.push_back(oo[i - 1] + 1);
		}
		else {
			oo.push_back(1);
		}
		occurances.push_back(occurance);
		previousOccurance = occurance;
	}

	std::vector<Pair*> inputs;
	for (int i = occurances.size()-1; i >= 0; i--) {
		if (oo[i] == 1) {
			Pair* input = new Pair;
			int index = getRandom(0, words.size() - 1);
			strcpy(input->word, words[index]);
			delete words[index];
			words.erase(words.begin() + index);
			input->occurance = occurances[i];
			inputs.push_back(input);
		}
		else {
			int index = words.size()-1;
			for (int t = 0; t < oo[i]; i++) {
				Pair* input = new Pair;
				index -= getRandom(0, words.size()/oo[i] - 1);
				strcpy(input->word, words[index]);
				delete words[index];
				words.erase(words.begin() + index);
				input->occurance = occurances[i-t];
				inputs.push_back(input);
			}
			i -= oo[i];
		}
	}

	return inputs;
}
*/
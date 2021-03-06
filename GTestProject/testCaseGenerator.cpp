#include "pch.h"
#include "testCaseGenerator.h"
#include "wordSort.h"

std::vector<std::string> wordPool = { 
"aardvark","addax","agouti","alligator","alpaca","anteater","antelope","ant","ape",
"baboon","bat","bear","bee","beluga","bird","boar","bobcat","bongo","bonobo","butterfly",
"camel","cat","cattle","cheetah","chicken","cicada","clam","cockroach","codfish","coyote",
"deer","dinosaur","dog","dolphin","donkey","dove","duck","eagle","echidna","eel","elephant",
"elk","emu","falcon","ferret","finch","fish","fly","fox","frog","gerbil","giraffle","gnat",
"gnu","goat","goose","gorilla","hamster","hare","hawk","hedgehog","heron","hippopotamus",
"iguana","jaguar","jellyfish","kangaroo","koala","lark","lemur","leopard","llama","louse",
"magpie","manatee","monkey","moose","mosquito","mouse","mule","muskat","newt","nightingale",
"opossum","ostrich","otter","owl","ox","oyster","panda","parrot","peacock","penguin","pig",
"quail","rabbit","raccoon","rat","reindeer","rhinoceros","seal","serval","shark","sheep","snake",
"tiger","tortoise","turkey","turtle","utonagan","vaquita","wasp","whale","wolf","wombat","xerus"
,"yak","zebra" 
};

std::vector<std::string> punctuation = { ".", ",", ":", ";", "'", "\""};

int getRandom(int min, int max) {
	if (min == max) return min;
	static std::random_device randev;
	static std::mt19937 mt_eng(randev());
	std::uniform_int_distribution<int> uniform(min, max);
	return uniform(mt_eng);
}

std::string getPunct() {
	return punctuation[getRandom(0, punctuation.size() - 1)];
}

std::vector<char*> getInputsAlpha(int numberOfInputs) {
	int range = wordPool.size() / numberOfInputs;

	std::vector<char*> inputs;
	for (int i = 0; i < numberOfInputs; i++) {
		int index = range * i + getRandom(1, range) - 1;
		std::string sWord = wordPool[index];
		char* word;
		word = new char[sWord.length() + 1];
		inputs.push_back(strcpy(word, sWord.c_str()));
	}

	return inputs;
}

std::vector<Pair*> getInputsAlphaPairArr(int numberOfInputs) {
	int range = wordPool.size() / numberOfInputs;

	std::vector<Pair*> inputs;
	for (int i = 0; i < numberOfInputs; i++) {
		int index = range * i + getRandom(1, range) - 1;
		std::string sWord = wordPool[index];
		Pair* input = new Pair;
		strcpy(input->word, sWord.c_str());
		input->occurance = getRandom(1,50);
		inputs.push_back(input);
	}

	return inputs;
}

std::vector<Pair*> getInputsComplete(int numberOfInputs) {
	std::vector<char*> words = getInputsAlpha(numberOfInputs);

	int previousOccurance = getRandom(1, 5);
	//random #occurances
	std::vector<int> occurances;
	//count repeated occurances
	std::vector<int> oo;

	occurances.push_back(previousOccurance);
	oo.push_back(1);
	for (int i = 1; i < numberOfInputs; i++) {
		int occurance = previousOccurance + getRandom(0, 5);
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
	for (int i = occurances.size() - 1; i >= 0; i--) {
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
			int index = words.size();
			int range = words.size() / oo[i];
			std::vector<Pair*> reversedInputs;
			for (int t = 0; t < oo[i]; t++) {
				Pair* input = new Pair;
				index -= getRandom(1, range);
				strcpy(input->word, words[index]);
				delete words[index];
				words.erase(words.begin() + index);
				input->occurance = occurances[i - t];
				reversedInputs.push_back(input);
			}
			for (int t = reversedInputs.size() - 1; t >= 0; t--) {
				inputs.push_back(reversedInputs[t]);
			}
			i -= oo[i] - 1;
		}
	}

	return inputs;
}

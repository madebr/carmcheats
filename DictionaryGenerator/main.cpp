#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <ios>

enum class StringMode {
	None = 0,
	AppendS = 1
};

struct StringWithMode {
	std::string value;
	StringMode mode;
};

std::vector<StringWithMode> readDataFile(const char* fileName);
StringWithMode* randomItem(std::vector<StringWithMode>* vec);

int main() {
	std::ios::sync_with_stdio(false);

	std::ofstream outfile;
	outfile.open("out.big.dic", std::ios_base::app);

	std::vector<StringWithMode> sentenceStructures = readDataFile("sentence_structures.txt");
	std::vector<StringWithMode> subjects = readDataFile("subjects.txt");
	std::vector<StringWithMode> adjectives = readDataFile("adjectives.txt");
	std::vector<StringWithMode> articlesPrepositions = readDataFile("articles_prepositions.txt");
	std::vector<StringWithMode> nouns = readDataFile("nouns.txt");
	std::vector<StringWithMode> verbs_regular = readDataFile("verbs_regular.txt");

	size_t stringBufferSize = 64;
	size_t bufferSize = stringBufferSize * 100000;

	std::string outBuffer;
	outBuffer.reserve(bufferSize);

	while (true) {
		StringWithMode* sentenceStructure = randomItem(&sentenceStructures);
		StringWithMode* randomSubject = randomItem(&subjects);
		bool hasSubject = false;

		for (char c : sentenceStructure->value) {
			switch (c) {
			case 's':
				hasSubject = true;
				outBuffer.append(randomSubject->value);
				break;
			case 'r':
				outBuffer.append(randomItem(&articlesPrepositions)->value);
				break;
			case 'a':
				outBuffer.append(randomItem(&adjectives)->value);
				break;
			case 'n':
				outBuffer.append(randomItem(&nouns)->value);
				break;
			case 'v':
				outBuffer.append(randomItem(&verbs_regular)->value);

				if (hasSubject && randomSubject->mode == StringMode::AppendS) {
					outBuffer.append("s");
				}
				break;
			default:
				std::cerr << "! Unrecognized sentence structure: " << sentenceStructure->value << '\n';
				return -1;
			}
		}

		outBuffer.append("\n");

		if (outBuffer.length() > bufferSize - stringBufferSize) {
			outfile << outBuffer;

			outBuffer.clear();
		}
	}
}

StringWithMode* randomItem(std::vector<StringWithMode>* vec) {
	return &(vec->at(rand() % vec->size()));
}

std::vector<StringWithMode> readDataFile(const char* fileName) {
	std::string targetFile = "./data/";
	targetFile.append(fileName);

	std::ifstream input = std::ifstream(targetFile);
	std::vector<StringWithMode> lines = std::vector<StringWithMode>();
	if (input) {
		for (std::string line; getline(input, line);)
		{
			if (line.length() == 0 || line.length() && line.at(0) == '#') {
				continue;
			}

			std::vector<std::string> splitString;
			std::istringstream stringStream = std::istringstream(line);
			std::string currentPart;
			while (getline(stringStream, currentPart, ' ')) {
				splitString.push_back(currentPart);
			}


			StringWithMode stringWithMode;
			stringWithMode.value = splitString.at(0);
			stringWithMode.mode = StringMode::None;
			if (splitString.size() > 1) {
				switch (splitString.at(1)[0]) {
				case 's':
					stringWithMode.mode = StringMode::AppendS;
					break;
				}
			}

			lines.push_back(stringWithMode);
		}
	}
	else {
		std::cerr << "! Could not open file: " << fileName << '\n';
	}

	return lines;
}

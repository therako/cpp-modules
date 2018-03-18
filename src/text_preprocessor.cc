#include<iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <regex>

using namespace std;


std::vector<std::string> &split(const std::string &s, char delim,std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        if (item.length() > 0) {
            elems.push_back(item);  
        }
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

std::vector<std::string> resplit(const std::string & s, std::string rgx_str = "\\s+") {
  std::vector<std::string> elems;
  std::regex rgx (rgx_str);
  std::sregex_token_iterator iter(s.begin(), s.end(), rgx, -1);
  std::sregex_token_iterator end;
  while (iter != end)  {
      //std::cout << "S43:" << *iter << std::endl;
      elems.push_back(*iter);
      ++iter;
  }
  return elems;
}

class TextPreprocessor
{
public:
	std::string params;
	TextPreprocessor(std::string _params){
		params = _params;
	}
	std::string preprocess(std::string text) {
		throw std::runtime_error("Sub-classes should implement this method.");
	}
	
};

class NullPreprocessor
{
    // A Preprocessor that outputs the input text as a single token.
 public:
    std::vector<std::string> preprocess(std::string text) {
    	std::vector<std::string> v( 1 );
    	v.push_back(text);
        return v;
    }
};

class SplitBySpacePreprocessor{
    // A Preprocessor that splits by whitespace.
public:
    std::vector<std::string> preprocess(std::string text) {
        return split(text, ' ');
    }
};

class SplitByRegexPreprocessor{
    // A Preprocessor that splits by a given regex.

    // The preprocessor replaces all occurrences of given pattern
    // within a string with spaces. It then performs a split on spaces,
    // including pre-existing ones. The input text is lower-cased.
public:
	std::string rgx_str;
	SplitByRegexPreprocessor(std::string _rgx_str) {
		rgx_str = _rgx_str;
	}
    std::vector<std::string> preprocess(std::string text) {
        return resplit(text, rgx_str);
    }
};

int main(int argc, char *argv[]) {
	const std::string Special = "Hello  World 123";

	NullPreprocessor nullPreprocessor = NullPreprocessor();
	// cout << nullPreprocessor.preprocess(Special)[1];

	SplitBySpacePreprocessor splitBySpacePreprocessor = SplitBySpacePreprocessor();
	// cout << splitBySpacePreprocessor.preprocess(Special)[1];

	std::string rgx_str = "\\W";
	SplitByRegexPreprocessor splitByRegexPreprocessor = SplitByRegexPreprocessor(rgx_str);
	cout << splitByRegexPreprocessor.preprocess(Special)[0];
}

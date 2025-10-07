#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"
#include <set>
#include <string>

using namespace std;

string convToLower(string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
set<string> parseStringToWords(string rawWords)
{
  set<string> return_set;
  string word = "";

  // convert to lowercase
  rawWords = convToLower(rawWords);

  for (size_t i = 0; i < rawWords.size(); i++) {
      char c = rawWords[i];
      if (isalnum(c)) {
          // add letters or numbers to current word
          word += c;
      } else {
          // non-alphanumeric = word boundary
          if (word.size() >= 2) {
              return_set.insert(word);
          }
          word = "";
      }
  }

  // check the final word
  if (word.size() >= 2) {
      return_set.insert(word);
  }

  return return_set;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

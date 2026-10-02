#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{

  set<string> fixedWords;

  string currentWord;

  // go through the entire string 
  for (unsigned int i = 0; i < rawWords.size(); i++) 
  {
    //if it is a lower or upper case leter a-z OR a number 
    if ((rawWords[i] >= 'a' && rawWords[i] <= 'z') || (rawWords[i] >= 'A' && rawWords[i] <= 'Z') || (rawWords[i] >= '0' && rawWords[i] <= '9')) {
      currentWord += rawWords[i];
    }

    else
    {
      //if it is already 2 characters, that ends this word 
      if (currentWord.size() >= 2)
      {
        currentWord = convToLower(currentWord);

        //word is ready to be added to fixedWords because it is lower case 
        //and 2 or more characters in length 
        fixedWords.insert(currentWord); 
      }

      //clear currentWord to start building a new word
      currentWord = "";
    }

  } 

  //before returning loop to make sure it is all correct 
     if (currentWord.size() >= 2)
      {
        currentWord = convToLower(currentWord);
        fixedWords.insert(currentWord); 

      }

  return fixedWords;


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

#include <sstream>
#include <iomanip>
#include "book.h"
#include <string>
#include <set>
#include "util.h"

using namespace std;


// add the constructor
Book::Book(const std::string category, const std::string name, double price, 
            int qty, const std::string isbn, const std::string author)
            : Product(category, name, price, qty),
            isbn_(isbn),
            author_(author)
{
}

Book::~Book()
{}
/**
 * Returns the appropriate keywords that this product should be associated with
*/
set<string> Book::keywords() const
{
  set<string> key_words = parseStringToWords(convToLower(getName()));
  set<string> authorwords = parseStringToWords(convToLower(author_));
  key_words = setUnion(key_words, authorwords);
  key_words.insert(convToLower(isbn_));

  //return 
  return key_words;
}

/**
 * Allows for a more detailed search beyond simple keywords
 */
bool Book::isMatch(std::vector<string>& searchTerms) const
{
  // go through the list of searchTerms
  set<string> key_words = keywords();
  for (std::vector<std::string>::iterator it = searchTerms.begin(); it != searchTerms.end(); ++it)
    {
      if (key_words.find(convToLower(*it)) != key_words.end())
      {
        return true;
      }
    }
  return false;
}

/**
* Returns a string to display the product info for hits of the search
*/
string Book::displayString() const
{
  stringstream ss;
  ss << getName() << '\n' 
     << "Author: " << author_ << " ISBN: " << isbn_ << '\n'
     << fixed << setprecision(2) << getPrice() << " " << getQty() << " left.";
  return ss.str();
}

/**
  * Outputs the product info in the database format
*/
void Book::dump(std::ostream& os) const
{
  os << category_ << '\n' 
     << getName() << '\n' 
     << fixed << setprecision(2) << getPrice() << '\n'
     << getQty() << '\n'
     << isbn_ << '\n'
     << author_ << endl;
}

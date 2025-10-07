#include <sstream>
#include <iomanip>
#include "movie.h"
#include <string>
#include <set>

using namespace std;


// add the constructor
Movie::Movie(const std::string category, const std::string name, double price, 
            int qty, const std::string genre, const std::string rating)
            : Product(category, name, price, qty),
            genre_(genre),
            rating_(rating)
{
}
Movie::~Movie()
{}
/**
 * Returns the appropriate keywords that this product should be associated with
*/
set<string> Movie::keywords() const
{
  set<string> key_words = parseStringToWords(convToLower(getName()));
  key_words.insert(convToLower(genre_));
  key_words.insert(convToLower(rating_));
  return key_words;
}

/**
 * Allows for a more detailed search beyond simple keywords
 */
bool Movie::isMatch(std::vector<string>& searchTerms) const
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
string Movie::displayString() const
{
  stringstream ss;
  ss << getName() << '\n' 
     << "Genre: " << genre_ << " Rating: " << rating_ << '\n'
     << fixed << setprecision(2) << getPrice() << " " << getQty() << " left.";
  return ss.str();
}

/**
  * Outputs the product info in the database format
*/
void Movie::dump(std::ostream& os) const
{
  os << category_ << '\n' 
     << getName() << '\n' 
     << fixed << setprecision(2) << getPrice() << '\n'
     << getQty() << '\n'
     << genre_ << '\n'
     << rating_ << endl;
}

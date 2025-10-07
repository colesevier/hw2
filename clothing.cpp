#include <sstream>
#include <iomanip>
#include "clothing.h"
#include <string>
#include <set>

using namespace std;

// add the constructor
Clothing::Clothing(const std::string category, const std::string name, double price, 
            int qty, const std::string size, const std::string brand)
            : Product(category, name, price, qty),
            size_(size),
            brand_(brand)
{
}
Clothing::~Clothing()
{}
/**
 * Returns the appropriate keywords that this product should be associated with
*/
set<string> Clothing::keywords() const
{
  set<string> key_words = parseStringToWords(convToLower(getName()));
  key_words.insert(convToLower(size_));
  set<string> brand_words = parseStringToWords(convToLower(brand_));
  return setUnion(key_words, brand_words);
}

/**
 * Allows for a more detailed search beyond simple keywords
 */
bool Clothing::isMatch(std::vector<string>& searchTerms) const
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
string Clothing::displayString() const
{
  stringstream ss;
  ss << getName() << '\n' 
     << "Size: " << size_ << " Brand: " << brand_ << '\n'
     << fixed << setprecision(2) << getPrice() << " " << getQty() << " left.";
  return ss.str();
}

/**
  * Outputs the product info in the database format
*/
void Clothing::dump(std::ostream& os) const
{
  os << category_ << '\n' 
     << getName() << '\n' 
     << fixed << setprecision(2) << getPrice() << '\n'
     << getQty() << '\n'
     << size_ << '\n'
     << brand_ << endl;
}

#include "mydatastore.h"
#include "product.h"
#include "util.h"
#include "user.h"
#include <vector>
#include <set>
#include <string>
#include <map>


using namespace std;

MyDataStore::MyDataStore()
{
}

MyDataStore::~MyDataStore()
{
  // delete all the dynamically allocated memory
  for (set<Product*>::iterator it = products_.begin(); it != products_.end(); ++it)
  {
    delete *it;
  }
  for (vector<User*>::iterator it = users_.begin(); it != users_.end(); ++it)
  {
    delete *it;
  }
}

void MyDataStore::addProduct(Product* p)
{
  products_.insert(p);
  // Index by keywords for efficient searching
  set<string> keys = p->keywords();
  for (set<string>::iterator it = keys.begin(); it != keys.end(); ++it) {
    string keyLower = convToLower(*it);
    keywordMap_[keyLower].insert(p);
  } 
}

void MyDataStore::addUser(User* u)
{
  users_.push_back(u);
}

vector<Product*> MyDataStore::search(vector<string>& terms, int type)
{
  // iterate through all of the products
  set<Product*> result;

    if (terms.empty()) return vector<Product*>();

    // Convert all terms to lowercase before searching
    for (size_t i = 0; i < terms.size(); ++i) {
        terms[i] = convToLower(terms[i]);
    }

    if (type == 0) // AND
    {
        if (keywordMap_.find(terms[0]) != keywordMap_.end()) {
            result = keywordMap_[terms[0]];
        }
        for (size_t i = 1; i < terms.size(); ++i) {
            if (keywordMap_.find(terms[i]) != keywordMap_.end()) {
                result = setIntersection(result, keywordMap_[terms[i]]);
            }
            else {
                result.clear();
                break;
            }
        }
    }
    else // OR
    {
        for (size_t i = 0; i < terms.size(); ++i) {
            if (keywordMap_.find(terms[i]) != keywordMap_.end()) {
                result = setUnion(result, keywordMap_[terms[i]]);
            }
        }
    }

    return vector<Product*>(result.begin(), result.end());
}

void MyDataStore::dump(ostream& ofile)
{
  ofile << "<products>" << endl;
  for (set<Product*>::iterator it = products_.begin(); it != products_.end(); ++it)
  {
    // get the dump from all of the individual products within the product list
    Product* product = *it;
    product->dump(ofile);
  }
  ofile << "</products>" << endl;

  ofile << "<users>" << endl;
  for (vector<User*>::iterator it = users_.begin(); it != users_.end(); ++it)
  {
    // get the dump from all of the individual products within the product list
    User* user = *it;
    user->dump(ofile);
  }
  ofile << "</users>" << endl;

}

// add cart item
void MyDataStore::addCartItem(string user, Product* product)
{
  string userLower = convToLower(user);
  User* found = nullptr;
  for (vector<User*>::iterator it = users_.begin(); it != users_.end(); ++it) {
      if (convToLower((*it)->getName()) == userLower) {
          found = *it;
          break;
      }
  }
  if (found == nullptr) {
      cout << "Invalid request" << endl;
      return;
  }
  carts_[userLower].push_back(product);
}

// viewcart function
void MyDataStore::viewCart(string username)
{
  string user = convToLower(username);
  User* foundUser = nullptr;
  for (auto* u : users_) {
      if (convToLower(u->getName()) == user) {
          foundUser = u;
          break;
      }
  }
  if (!foundUser) {
      cout << "Invalid username" << endl;
      return;
  }

  vector<Product*>& cart = carts_[user];
  for (size_t i = 0; i < cart.size(); ++i) {
      cout << "Item " << i + 1 << endl;
      cout << cart[i]->displayString() << endl;
  }

}


// buycart function
void MyDataStore::buyCart(string username)
{
  string user = convToLower(username);
  if (carts_.find(user) == carts_.end())
  {
    cout << "Invalid username" << endl;
    return;
  }

  User* buyer = nullptr;
  for (vector<User*>::iterator it = users_.begin(); it != users_.end(); ++it)
  {
    if (convToLower((*it)->getName()) == user)
    {
      buyer = *it;
      break;
    }
  }
  // check for valid buyer
  if (buyer == nullptr)
  {
    cout << "Invalid username" << endl;
    return;
  }

  vector<Product*> cart = carts_[user];
  // create a remaining cart if the buyer doesn't have enough money
  vector<Product*> remaining;

  for (int i=0; i < cart.size(); i ++)
  {
    Product* product = cart[i];
    if (product->getQty() > 0 && buyer->getBalance() >= product->getPrice())
    {
      buyer->deductAmount(product->getPrice());
      product->subtractQty(1);
    }
    else
    {
      remaining.push_back(product);
    }
  }

  // update the cart
  carts_[user] = remaining;
}


#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include "datastore.h"
#include "product.h"
#include "util.h"
#include "user.h"
#include <vector>
#include <set>
#include <string>
#include <map>

class MyDataStore : public DataStore
{
public:
  MyDataStore();
  virtual ~MyDataStore();
  void addProduct(Product* p);
  void addUser(User* u);
  std::vector<Product*> search(std::vector<std::string>& terms, int type);
  void dump(std::ostream& ofile);
  void addCartItem(std::string user, Product* product);
  void viewCart(std::string username);
  void buyCart(std::string username);




protected:
  // create the variables
  std::set<Product*> products_;
  std::vector<User*> users_;
  std::map<std::string, std::vector<Product*>> carts_;
  std::map<std::string, std::set<Product*>> keywordMap_;

};

#endif
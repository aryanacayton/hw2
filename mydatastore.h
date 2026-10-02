#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include <map>
#include <set> 
#include "datastore.h"

class MyDataStore : public DataStore
{
  public:
    virtual void addProduct(Product* p);

    virtual void addUser(User* u);

    virtual std::vector<Product*> search(std::vector<std::string>& terms, int type);

    virtual void dump(std::ostream& ofile);

    void addToCart(std::string username, Product* product);

    void viewCart(std::string username);

    void checkOut(std::string username);

    virtual ~MyDataStore();


  private:
    std::vector<Product *> products_;
    std::map<std::string, User*> users_; 
    std::map<std::string, std::set<Product*> > keywordData_;
    std::map<std::string, std::vector<Product*> > cart_;

};

#endif
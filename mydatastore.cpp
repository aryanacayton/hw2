#include "mydatastore.h"
#include "util.h"

void MyDataStore::addProduct(Product* p)
{
  products_.push_back(p);

  //s1 contains all keywords for product p
  std::set<std::string> s1 = p->keywords();

  for (std::set<std::string>::iterator it = s1.begin(); it != s1.end(); it++)
  {
    //map where each string relates to a set of Product* pointers
    keywordData_[*it].insert(p);
  }
}


void MyDataStore::addUser(User* u)
{
  //lowercase u is stored in username 
  std::string username = convToLower(u->getName());

  //adds to users_ map, u at the index username 
  users_[username] = u;

}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
  std::set<Product*> findings;

  //empty string 
  if (terms.size() == 0)
  {
    return std::vector<Product*>();
  }

  std::map<std::string, std::set<Product*> >::iterator it = keywordData_.find(terms[0]);

  //AND type == 0 
  if (type == 0)
  {
    
     if (it == keywordData_.end())
    {
      return std::vector<Product*>();
    }
    
     //get the set of products associated with the first keyword
    findings = it->second; 
    
    for (unsigned int i = 1; i < terms.size(); i++)
    {
      it = keywordData_.find(terms[i]);

     if (it == keywordData_.end())
    {
      return std::vector<Product*>();
    }

    findings = setIntersection(findings, it->second);
    }
  }

  //OR type == 1
  else if (type == 1)
  {
    for (unsigned int i = 0; i <terms.size(); i++)
    {

      it = keywordData_.find(terms[i]);

      if (it != keywordData_.end())
      {
        findings = setUnion(findings, it->second);

      }

    }
  }

  std::vector<Product*> temp;

  for(std::set<Product*>::iterator it2 = findings.begin(); it2 != findings.end(); it2++)
  {
    temp.push_back(*it2);
  }

  return temp;

}


void MyDataStore::dump(std::ostream& ofile)
{
  ofile << "<products>" << std::endl;

  for (unsigned int i = 0; i <products_.size(); i++)
  {
    products_[i]->dump(ofile);
  }

  ofile << "</products>" << std::endl;

  ofile << "<users>" << std::endl;

  for (std::map<std::string, User*>::iterator it = users_.begin(); it != users_.end(); it++)
  {
    it->second->dump(ofile);
  }

  ofile << "</users>" << std::endl;

}

void MyDataStore::addToCart(std::string username, Product* product)
{

  username = convToLower(username);

  //if user does not exist
  if (users_.find(username) == users_.end())
  {
    std::cout << "Invalid request" << std::endl;
    return;
  }

  //otherwise:
  cart_[username].push_back(product);

}

void MyDataStore::viewCart(std::string username)
{
   username = convToLower(username);

  if (users_.find(username) == users_.end())
  {
    std::cout << "Invalid username" << std::endl;
    return;
  }

  for (unsigned int i = 0; i < cart_[username].size(); i++)
  {
    std::cout << "Item " << i + 1 << std::endl;
    std::cout << cart_[username][i]->displayString() << std::endl;
  }

}

void MyDataStore::checkOut(std::string username)
{
  username = convToLower(username);

  if (users_.find(username) == users_.end())
  {
    std::cout << "Invalid username" << std::endl;
    return;
  }

  User* user = users_[username];

  std::vector<Product*> temp;

  for (unsigned int i = 0; i < cart_[username].size(); i++)
  {
    Product* p = cart_[username][i];

    if (p->getQty() >0 && user->getBalance() >= p->getPrice())
    {
      p->subtractQty(1);
      user->deductAmount(p->getPrice());
    }

    else
    {
      temp.push_back(p);
    }

  }

  cart_[username] = temp;

}

MyDataStore::~MyDataStore()
{
  for (unsigned int i = 0; i <products_.size(); i++)
  {
    delete products_[i];
  }

  for (std::map<std::string, User*>::iterator it = users_.begin(); it != users_.end(); it++)
  {
    delete it->second;
  }

}
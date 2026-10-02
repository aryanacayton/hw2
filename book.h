#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <set>
#include "product.h"

class Book : public Product
{
  public:
    Book(std::string name, double price, int quantity, std::string isbn, std::string author);

    virtual std::set<std::string> keywords() const;

    virtual std::string displayString() const;

    virtual void dump(std::ostream& os) const;

    private:
    std::string isbn_;
    std::string author_; 
    

};

#endif
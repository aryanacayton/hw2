 #include "book.h"
 #include "util.h"
 #include <sstream> 

  Book::Book(std::string name, double price, int quantity, std::string isbn, std::string author) :  Product("book", name, price, quantity)
  {
    isbn_ = isbn;
    author_ = author; 
  }

  std::set<std::string> Book::keywords() const
  {
    //book name
    std::set<std::string> parsedBookName = parseStringToWords(name_);
    
    //author
    std::set<std::string> parsedAuthorName = parseStringToWords(author_);

    //create a set with all possible keywords
     std::set<std::string> allKeywords = setUnion(parsedBookName, parsedAuthorName);

    //ISBN
    allKeywords.insert(isbn_);

    return allKeywords;
  }

  std::string Book::displayString() const
  {
    std::stringstream formatting;

    formatting << name_ << "\n";

    formatting << "Author: " << author_ << " ISBN: " << isbn_ << "\n";

    formatting << price_ << " " << qty_ << " left.";

    return formatting.str();

  }

  void Book::dump(std::ostream& os) const
  {
    Product::dump(os);

    os << isbn_ << "\n";

    os << author_ << std::endl;
  }

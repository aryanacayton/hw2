 #include "clothing.h"
 #include "util.h"
 #include <sstream> 

  Clothing::Clothing(std::string name, double price, int quantity, std::string size, std::string brand) :  Product("clothing", name, price, quantity)
  {
    brand_ = brand;
    size_ = size; 
  }

  std::set<std::string> Clothing::keywords() const
  {
    //product name
    std::set<std::string> parsedName = parseStringToWords(name_);
    
    //brand name 
    std::set<std::string> parsedBrandName = parseStringToWords(brand_);

    //create a set with all possible keywords
     std::set<std::string> allKeywords = setUnion(parsedName, parsedBrandName);

    return allKeywords;
  }

  std::string Clothing::displayString() const
  {
    std::stringstream formatting;

    formatting << name_ << "\n";

    formatting << "Size: " << size_ << " Brand: " << brand_ << "\n";  

    formatting << price_ << " " << qty_ << " left.";

    return formatting.str();

  }

  void Clothing::dump(std::ostream& os) const
  {
    Product::dump(os);

    os << size_ << "\n";

    os << brand_ << std::endl;
  }

 #include "movie.h"
 #include "util.h"
 #include <sstream> 

  Movie::Movie(std::string name, double price, int quantity, std::string genre, std::string rating) :  Product("movie", name, price, quantity)
  {
    genre_ = genre;
    rating_ = rating; 
  }

  std::set<std::string> Movie::keywords() const
  {
    //product name
    std::set<std::string> parsedName = parseStringToWords(name_);

    //create a set with all possible keywords
     std::set<std::string> allKeywords = parsedName; 

     //genre 
    allKeywords.insert(convToLower(genre_));

    return allKeywords;
  }

  std::string Movie::displayString() const
  {
    std::stringstream formatting;

    formatting << name_ << "\n";

    formatting << "Genre: " << genre_ << " Rating: " << rating_ << "\n";  

    formatting << price_ << " " << qty_ << " left.";

    return formatting.str();

  }

  void Movie::dump(std::ostream& os) const
  {
    Product::dump(os);

    os << genre_ << "\n";

    os << rating_ << std::endl;
  }

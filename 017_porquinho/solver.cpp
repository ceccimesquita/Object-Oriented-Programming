//fiz sozinha com a base que tinha no replit

#include <fn.hpp>
#include <utility>
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;
using namespace fn;


class Coin {
    double value;
    int volume;
    std::string label;
public:

    Coin(double value, int volume, std::string label){
      this->value = value;
      this->volume = volume;
      this->label = label;
    }

    const static Coin C10;
    const static Coin C25;
    const static Coin C50;
    const static Coin C100;

    double getValue() const { 
        return value; 
    }
    int getVolume() const { 
        return volume; 
    }
    std::string getLabel() const { 
        return label; 
    }

    std::string str() const {
        return fn::format("{%.2f}:{}", value, volume);
    }
};

const Coin Coin::C10 {0.10, 1, "C10"};
const Coin Coin::C25 {0.25, 2, "C25"};
const Coin Coin::C50 {0.50, 3, "C50"};
const Coin Coin::C100 {1.00, 4, "C100"};

std::ostream& operator<<(std::ostream& os, const Coin& coin) {
    return os << coin.str();
}

class Item {
    std::string label;
    int volume;
public:
    Item(std::string label, int volume) { 
      this->label = label;
      this->volume = volume;
    }
    int getVolume() const {
        return volume;
    }
    std::string getLabel() const {
        return label;
    }
    void setVolume(int volume) {
        this->volume =  volume;
    }
    void setLabel(std::string label) {
        this->label = label;
    }
    std::string str() const {
        return fn::format("{}:{}", getLabel(), getVolume());
    }
};

std::ostream& operator<<(std::ostream& os, const Item& item) {
    return os << item.str();
}

class Pig {
    std::vector<Item> itens;
    std::vector<Coin> coins;

    int volumeMax {0};
    bool broken {false};

public:
    Pig(int volumeMax = 0) { 
      this -> volumeMax = volumeMax;
    }
    
    bool addCoin(Coin coin) {
        if(broken){
          cout<<"fail: the pig is broken"<<endl;
          return false;
        }else{
          if((getVolume()+coin.getVolume())>=volumeMax){
          cout<<"fail: the pig is full"<<endl;
          return false;
          }else{
          coins.push_back(coin);
          return true;
          }
        }
    }  
    bool addItem(Item item) {
        if(broken){
          cout<<"fail: the pig is broken"<<endl;
          return false;
        }else{
          if((getVolume() + item.getVolume()) >= volumeMax){
              cout<<"fail: the pig is full"<<endl;
              return false;
          }else{
          itens.push_back(item);
          return true;
          }
        }

    }

    bool breakPig() {
        if(broken){
          return false;
        }else{
          broken = true;
          return true;
        }
    }

    std::vector<Coin> extractCoins() {
        if(broken){
          vector<Coin> aux;
          aux = coins;
          coins.clear();
          return aux;
        }else{
          cout<<"fail: you must break the pig first"<<endl;
          return {};
        }
    }

    std::vector<Item> extractItems() {
        if(broken){
          vector<Item> aux;
          aux = itens;
          itens.clear();
          return aux;
        }else{
          cout<<"fail: you must break the pig first"<<endl;
          return {};
        }
    }

    double getValue() const {
        double soma = 0;
        for(auto elem : coins){
          soma +=elem.getValue();
        }
        return soma;
    }

    int getVolume() const {
        int soma = 0;
        if(broken){
          return 0;
        }else{
          for(auto elem : coins){
            soma +=elem.getVolume();
          }
          for(auto elem : itens){
            soma +=elem.getVolume();
          }
          return soma;
        }    
    }

    bool isBroken(){
      if(broken){
        return true;
      }else{
        return false;
      }
    }

    std::string str() const {
      return fn::format("state={} : coins={} : items={} : value={%.2f} : volume={}/{}", (this->broken ? "broken" : "intact"), coins, itens, getValue(), getVolume(), volumeMax);
    }
};

std::ostream& operator<<(std::ostream& os, const Pig& pig) {
    return os << pig.str();
}


int main() {

    Pig pig;
    while (true) {
        auto line = fn::input();
        fn::write("$" + line);
        auto args = fn::split(line);

        if      (args[0] == "end"    ) { break; }
        else if (args[0] == "addCoin") { 
            if      (args[1] == "10" ) pig.addCoin(Coin::C10);
            else if (args[1] == "25" ) pig.addCoin(Coin::C25);
            else if (args[1] == "50" ) pig.addCoin(Coin::C50);
            else if (args[1] == "100") pig.addCoin(Coin::C100);
        }
        else if (args[0] == "init"        ) { pig = Pig( (int) +(args[1]));                 }
        else if (args[0] == "addItem"     ) { pig.addItem(Item(args[1], (int) +(args[2]))); }
        else if (args[0] == "break"       ) { pig.breakPig();                               }
        else if (args[0] == "extractCoins") { fn::write(pig.extractCoins());                }
        else if (args[0] == "extractItems") { fn::write(pig.extractItems());                }
        else if (args[0] == "show"        ) { fn::write(pig);                               }
        else                                { fn::write("fail: invalid command");           }
    }
}
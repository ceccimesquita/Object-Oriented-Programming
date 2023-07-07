#include <fn.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <memory>   
#include <iomanip>
#include <map>


class Valuable {
public:
    virtual std::string getLabel()  const = 0;
    virtual double      getValue()  const = 0;
    virtual int         getVolume() const = 0;
    virtual std::string str()       const = 0;
    virtual ~Valuable() {}
};

std::ostream& operator<<(std::ostream& os, const Valuable& valuable) {
    return os << valuable.str();
}

class Coin : public Valuable {
    Coin(const std::string& label, double value, int volume) : label(label), value(value), volume(volume) {}
public:

    static const Coin C10;
    static const Coin C25;
    static const Coin C50;
    static const Coin C100;

    std::string getLabel() const override {
        return label;
    }

    int getVolume() const override {
        return volume;
    }

    double getValue() const override {
        return value;
    }

    std::string str() const override {
        return fn::format("{}:{%.2f}:{}", label, value, volume);
    }

private:
    std::string label;
    double value;
    int volume;
};

std::ostream& operator<<(std::ostream& os, const Coin& coin) {
    return os << coin.str();
}

const Coin Coin::C10  { "M10", 0.10, 1};
const Coin Coin::C25  { "M25", 0.25, 2};
const Coin Coin::C50  { "M50", 0.50, 3};
const Coin Coin::C100 {"M100", 1.00, 4};


class Item : public Valuable {
public:
    Item(const std::string& label, double value, int volume) : label(label), value(value), volume(volume){}

    std::string getLabel() const override {
        return label;
    }

    int getVolume() const override { 
        return volume;
    }

    double getValue() const override { 
        return value; 
    }

    std::string str() const { 
        return fn::format("{}:{%.2f}:{}", label, value, volume);
    }

private:
    std::string label;
    double value;
    int volume;
};

std::ostream& operator<<(std::ostream& os, const Item& item) {
    return os << item.str();
}

class Pig {
    int volumeMax;
    bool broken;
    std::vector<std::shared_ptr<Valuable>> valuables;
public:
    Pig(int volumeMax) : volumeMax(volumeMax), broken(false) {
    }

    void addValuable(const std::shared_ptr<Valuable>& val) { 
        if(broken) { throw std::string("fail: the pig is broken"); }
        if(getVolume() + val->getVolume() > volumeMax) { throw std::string("fail: the pig is full"); }
        if(getVolume() + val->getVolume() > volumeMax) { return; }
        valuables.push_back(val);
    }

    void breakPig() {
        if(broken) { return; }
        broken = true;
        std::vector<std::shared_ptr<Valuable>> aux;
        for(auto elem : valuables) {
            if(auto coin = std::dynamic_pointer_cast<Coin>(elem)) {
                aux.push_back(coin);
            }
        }

    }

    std::vector<std::shared_ptr<Coin>> extractCoins() {
        int cont = 0;
        if(!broken) { throw std::string("fail: you must break the pig first"); }
        std::vector<std::shared_ptr<Coin>> coins;
        for(auto& valuable : valuables) {
            if(auto coin = std::dynamic_pointer_cast<Coin>(valuable)) {
                coins.push_back(coin);
            }
        }
        for(auto elem : valuables){
            if(auto item = std::dynamic_pointer_cast<Coin>(elem)) {
                cont++;
                valuables.erase(valuables.begin() + cont);
            }
            cont++;
        }
        return coins;
    }

    std::vector<std::shared_ptr<Item>> extractItems() {
        int cont = 0;
        std::vector<std::shared_ptr<Item>> aux;
        if(!broken) { throw std::string("fail: you must break the pig first"); }
        for(auto elem : valuables) {
            if(auto item = std::dynamic_pointer_cast<Item>(elem)) {
                aux.push_back(item);
            }
        }
        for(auto elem : valuables){
            if(auto item = std::dynamic_pointer_cast<Item>(elem)) {
                cont++;
                valuables.erase(valuables.begin() + cont);
            }
            cont++;
        }
        return aux;
    }

    // double calcValue(){
    //     double value = 0;
    //     for(auto elem : valuables){
    //         value += elem->getValue();
    //     }
    //     return value;
    // }

    double getValue() const {
        double value = 0;
        for (auto elem : valuables) {
            value += elem->getValue();
        }
        return value;
    }

    int getVolume() const {
        if(broken) { return 0; }
        double volume = 0;
        for (auto elem : valuables) {
            volume += elem->getVolume();
        }
        return volume;
    }

    int getVolumeMax() const {
        return volumeMax;
    }

    bool isBroken() const {
        return broken;
    }

    std::string str() const{
        std::stringstream ss;
        ss << "[";

        for(auto elem : valuables){
            ss << elem->str();
            if (elem != valuables.back()) {
                ss << ", ";
            }
        }
 
        ss << "] : " << std::setprecision(2) << std::fixed << this->getValue()<< "$ : "  << getVolume() << "/" << getVolumeMax();
        if(broken) { ss << " : broken"; }
        else{ ss << " : intact";}
        return ss.str();
    }
};

std::ostream& operator<<(std::ostream& os, const Pig& pig) {
    return os << pig.str();
}

int main() {
    Pig pig(0);
    while (true) {
        try {
            auto line = fn::input();
            auto args = fn::split(line, ' ');
            fn::write("$" + line);

            if(args[0] == "end" ) {
                break; 
            } 
            else if(args[0] == "init") {
                pig = Pig(+args[1]); 
            }
            else if (args[0] == "addCoin") {
                switch((int) +args[1]) {
                    case  10: pig.addValuable(std::make_shared<Coin>(Coin::C10 )); break;
                    case  25: pig.addValuable(std::make_shared<Coin>(Coin::C25 )); break;
                    case  50: pig.addValuable(std::make_shared<Coin>(Coin::C50 )); break;
                    case 100: pig.addValuable(std::make_shared<Coin>(Coin::C100)); break;
                }
            }
            else if (args[0] == "addItem") {
                pig.addValuable(std::make_shared<Item>(args[1], +args[2], (int) +args[3]));
            }
            else if (args[0] == "break") {
                 pig.breakPig();                              
            }
            else if (args[0] == "extractCoins") {
                 fn::write(pig.extractCoins());               
            }
            else if (args[0] == "extractItems") {
                 fn::write(pig.extractItems());                
            }
            else if (args[0] == "show") {
                 fn::write(pig);                              
            }
            else{ 
                fn::write("fail: invalid command");           
            }
        } catch (std::string s) {
            fn::write(s);
        }
    }

}



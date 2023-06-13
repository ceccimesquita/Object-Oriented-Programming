#include <fn.hpp>
#include <iostream>
#include <sstream>

using namespace fn;
using namespace std;

class Fone{
    std::string id;
    std::string number;
public:
    Fone(std::string id = "", std::string number= ""){
      this->id = id;
      this->number = number;
    }
    std::string getId() {
        return id;// todo
    }
    std::string getNumber() {
        return number; // todo
    }
    bool isValid(string numero) {
         for (char c : numero) {
        // Verifica se o caractere é uma letra
        if (std::isalpha(c)) {
            write("fail: invalid number");
            return false; // Encontrou uma letra, retorna true
        }
    }
      
      return true;
    }
    std::string str() {
        return id + ":" + number;
    }   
};

class Contact{
    std::string name;
    bool favorited;
    std::vector<Fone> fones;
public:
    Contact(std::string name = "") { //todo
      this->name =  name;
      favorited = false;
    }
    void setName(string name){
      this->name = name;
    }

    std::string getName() {
        return this->name;
    }

    std::vector<Fone> getFones() {
        return fones; 
    }

    void addFone(std::string id, std::string number) {
      Fone aux(id, number);
      if(aux.isValid(number)){
        fones.push_back(aux);
      }
    }

    void rmFone(int index) {
      if(index < (int) fones.size() && index >= 0){
        fones.erase(fones.begin() + index);
      }
    }

    void toogleFavorited() {
      if(this->favorited){
        this->favorited = false;
      }else{
        this->favorited = true;
      }
    }

    bool isFavorited() {
      if(this->favorited){
        return true;
      }else{
        return false;        
      }
    }

    std::string str() {
        stringstream ss;
      if(isFavorited()){
        ss << "@ "<< getName();
      }else{
        ss << "- "<< getName();
      }
        ss << " [";
        for(int i = 0; i <(int) fones.size() ; i++){
          ss << fones[i].str();
          ss << ", ";
        }
      auto aux = ss.str();
      if(fones.size() > 0){
        aux.pop_back();
        aux.pop_back();
      }
      aux+= "]";
      return aux;
    }
};

std::ostream& operator<<(std::ostream& out, Contact contato) { return out << contato.str(); }
std::ostream& operator<<(std::ostream& out, Fone fone      ) { return out << fone.str();    }


int main() {
    Contact contato;
    while(true) {
        auto line = fn::input();
        fn::write("$" + line);
        auto args = fn::split(line, ' ');

        if(args[0] == "end") {
            break;
        }
        else if(args[0] == "init") {//name
            contato = Contact(args[1]);
        }
        else if(args[0] == "add") {//id fone
            contato.addFone(args[1], args[2]);
        }
        else if(args[0] == "rm") {//id
            contato.rmFone(+args[1]);
        }
        else if(args[0] == "tfav") {
            contato.toogleFavorited();
        }
        else if(args[0] == "show") {
            fn::write(contato);
        }
        else{
            fn::write("fail: comando invalido");
        }
    }
}
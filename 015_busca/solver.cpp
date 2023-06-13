#include <fn.hpp>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
using namespace fn;

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
        for (char c : numero){
          if (std::isalpha(c)){
            write("fail: invalid number");
            return false; 
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





class Agenda {
    std::vector<Contact> contatos;

    int findContact(std::string id) {
        for(int i = 0 ; i < (int) contatos.size() ; i++){
          if(id == contatos[i].getName()){
            return i;
          }
        }
      return -1;
    }

public:

    //add contato que não existe ou adicionar fones ao contato que existe
    void addContato(std::string name, std::vector<Fone> fones) {
      if(findContact(name) != -1){
        for(int i = 0 ; i < (int) contatos.size() ; i++){
            if(name == contatos[i].getName()){
              for(auto elem : fones){
                contatos[i].addFone(elem.getId(), elem.getNumber());
              }
            }
          }
      }else{
        Contact aux(name);
        for(auto elem : fones){
          aux.addFone(elem.getId(), elem.getNumber());
        }
        contatos.push_back(aux);
      }
      std::sort(contatos.begin(), contatos.end(), [](auto a, auto b) {return a.getName() < b.getName();});
    }

    void rmContact(std::string name) {
      if(findContact(name) != -1){
          contatos.erase(contatos.begin() + findContact(name));
      }
    }

    Contact * getContact(std::string id) {
      if(findContact(id) != -1){
        return &contatos[findContact(id)];
      }
      return NULL;
    }

    std::vector<Contact> getContatos() {
        return contatos; // todo
    }

    std::vector<Contact> search(std::string pattern) {
        vector<Contact> aux;
        aux.clear();
        for(auto elem : contatos){
            size_t found = elem.str().find(pattern);
            //size_t found1 = elem.getFones(elem).find(pattern);
            if (found != std::string::npos) {
              aux.push_back(elem);
          } 
        }
        return aux;
    }

    std::vector<Contact> getFavorited() {
        vector<Contact> aux;
        for(auto elem : contatos){
          if(elem.isFavorited()){
            aux.push_back(elem);
          }
        }
        return aux;
    }

    std::string str() {
      stringstream ss;
      for(auto elem : contatos){
        ss << elem.str();
        ss << endl;
      }
      auto aux = ss.str();
      if(contatos.size() > 0){
        aux.pop_back();
      }
      return aux;
    }
};


std::ostream& operator<<(std::ostream& out, Fone fone      ) { return out << fone.str();    }
std::ostream& operator<<(std::ostream& out, Contact contato) { return out << contato.str(); }
std::ostream& operator<<(std::ostream& out, Agenda agenda  ) { return out << agenda.str();  }

int main() {
    Agenda agenda;
    while(true) {
        auto line = fn::input();
        fn::write("$" + line);
        auto args = fn::split(line, ' ');
        if(args[0] == "end") {
            break;
        }
        else if(args[0] == "add") {//name id:fone id:fone ...
            std::vector<Fone> fones;
            for (int i = 2; i < (int) args.size(); i++) {
                auto parts = fn::split(args[i], ':');
                fones.push_back(Fone(parts[0], parts[1]));
            }
            agenda.addContato(args[1], fones);
        }
        else if(args[0] == "show") {
            fn::write(agenda);
        }
        else if(args[0]== "rmFone") {//id index
            Contact * contato = agenda.getContact(args[1]);
            if(contato != nullptr)
                contato->rmFone((int) +args[2]);
        }
        else if(args[0] == "rm") {//id
            agenda.rmContact(args[1]);
        }
        else if(args[0] == "tfav") {//id 1 ou 0
            Contact * contato = agenda.getContact(args[1]);
            if(contato != nullptr)
                contato->toogleFavorited();
        }
        else if(args[0] == "favs") {
            agenda.getFavorited() | fn::JOIN("\n") | fn::WRITE();
        }
        else if(args[0] == "search") {//pattern
            agenda.search(args[1]) | fn::JOIN("\n") | fn::WRITE();
        }
        else{
            fn::write("fail: comando invalido");
        }
    }
}

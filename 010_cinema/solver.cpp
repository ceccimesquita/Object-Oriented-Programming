#include <fn.hpp>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;
using namespace fn;

struct Cliente {
  std::string id;
  std::string fone;

public:
  Cliente(std::string id = "", std::string fone = "") {
    this->id = id;
    this->fone = fone;
  }

  string getFone() { return fone; }
  string getId() { return id; }

  void setFone(string fone) { this->fone = fone; }

  void setId(string id) { this->id = id; }

  std::string str() { return id + ":" + fone; }
};

std::ostream &operator<<(std::ostream &os, Cliente c) { return os << c.str(); }

class Sala {
  std::vector<std::shared_ptr<Cliente>> cadeiras;

  int procurar(std::string nome) {
    int aux = cadeiras.size();
    for (int i = 0; i < aux; i++) {
      if (cadeiras[i] != nullptr && nome == cadeiras[i]->getId())
        return i;
    }
    return -1;
  }

  bool verifica(int index) {
    int aux = cadeiras.size();
    for (int i = 0; i < aux; i++) {
      if (i == index) {
        return true;
      }
    }
    return false;
  }

public:
  Sala(int qtd = 0) : cadeiras(qtd) {
    // for(int i = 0 ; i < qtd ; i++){
    //   cadeiras.push_back(nullptr);
    // }
  }

  void reservar(string id,string fone, int ind) {
    if(procurar(id) != -1){
      write("fail: cliente ja esta no cinema");
    }else{
      if(verifica(ind)){
        if(cadeiras[ind] == nullptr){
          std::shared_ptr<Cliente> novoObjeto = std::make_shared<Cliente>(id, fone);
          //cadeiras.insert(cadeiras.begin() + ind, novoObjeto);
          cadeiras[ind] = novoObjeto;
        }else{
          write("fail: cadeira ja esta ocupada");
        }
      }else{
        write("fail: cadeira nao existe");
      }
    }
    
  }

  void cancelar(std::string id) {
    if(procurar(id) != -1){
      int a = procurar(id);
      cadeiras[a] = nullptr;
    }else{
      write("fail: cliente nao esta no cinema");
    }
  }

  std::string str() {
    stringstream ss;
    ss << "[";
    for (auto it = cadeiras.begin(); it != cadeiras.end(); it++) {
      if ((*it) != nullptr) {
        ss << (*it)->str();
        ss << " ";
      } else {
        ss << "-";
        ss << " ";
      }
    }
    auto aux = ss.str();
    if (cadeiras.size() > 0) {
      aux.pop_back();
    }
    aux += "]";
    return aux;
  }
};

std::ostream &operator<<(std::ostream &os, Sala c) { return os << c.str(); }

int main() {
  Sala sala;
  while (true) {
    auto line = fn::input();
    auto args = fn::split(line, ' ');
    fn::write("$" + line);

    if (args[0] == "end") {
      break;
    } else if (args[0] == "show") {
      fn::write(sala);
    } else if (args[0] == "init") {
      sala = Sala(+args[1]);
    } else if (args[0] == "reservar") {
      sala.reservar(args[1], args[2], (int)+args[3]);
    } else if (args[0] == "cancelar") {
      sala.cancelar(args[1]);
    } else {
      fn::write("fail: comando invalido");
    }
  }
}

//Fiz sozinha com a base que tinha no replit
#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <string>
#include <utility>
#include <fn.hpp>

using namespace std;

class Pessoa {
    std::string nome;
public:
    Pessoa(std::string nome){ //todo 
      setNome(nome);
    }

    std::string setNome(std::string nome){
      return this->nome = nome;
    } 
    
    std::string getNome() const {
        return this->nome; // todo 
    }
    std::string str() const {
        std::ostringstream os;
        os << nome;
        return os.str();
    }
};

std::ostream& operator<<(std::ostream& os, const Pessoa& p) {
    return (os << p.str());
}
using ptrc = std::shared_ptr<Pessoa>;

class Mercantil {
    std::vector<std::shared_ptr<Pessoa>> caixas; //caixas do supermercado
    std::list  <std::shared_ptr<Pessoa>> esperando; //lista de clientes esperando

    

public:
    bool validarIndice(int indice) {
        if(indice < this->caixas.size()){
          return 1;
        }else{
          return 0;
        }
    }


    Mercantil(int qtd_caixas){ 
      for(int i = 0; i < qtd_caixas; i++)
        this->caixas.push_back(nullptr);
    }
    
    void chegar(const std::shared_ptr<Pessoa>& person) {
      this->esperando.push_back(person);
      return;
    }

    bool chamarNoCaixa(int indice) {
        if(validarIndice(indice)){
            if(this->caixas.at(indice) == nullptr && (!this->esperando.empty())){
              this->caixas.at(indice) = this->esperando.front();
              this->esperando.pop_front();
            }else if(this->caixas.at(indice) != nullptr){
              std::cout<<"fail: caixa ocupado"<<std::endl;
            }else if(this->esperando.empty()){
              std::cout<<"fail: sem clientes"<<std::endl;
            }
        }else{
          std::cout<<"fail: caixa inexistente" << std::endl;
        }
          
      return 1;
    }
    
    std::shared_ptr<Pessoa> finalizar(int indice) {
        if(validarIndice(indice)){
          if(this->caixas[indice] != nullptr){
            this->caixas[indice] = nullptr;
          }else{
            std::cout<<"fail: caixa vazio"<<std::endl;
          }
        }else{
          std::cout<<"fail: caixa inexistente" << std::endl;
        }
      return 0;
    }

    

    std::string str() const {
        auto caixas_str = caixas | fn::MAP(FNT(c, c == nullptr ? "-----" : c->getNome()));
        return "Caixas: " + fn::tostr(caixas_str) + "\n" + "Espera: " + fn::tostr(esperando);
    }
};

std::ostream& operator<<(std::ostream& os, const Mercantil& b) {
    return (os << b.str());
}

int main() {
    Mercantil bank(0);
    while (true) {
        auto line = fn::input();
        auto args = fn::split(line, ' ');
        fn::write("$" + line);

        if      (args[0] == "end"   ) { break;                                          }
        else if (args[0] == "init"  ) { bank = Mercantil(+args[1]);                     }
        else if (args[0] == "call"  ) { bank.chamarNoCaixa(+args[1]);                   }
        else if (args[0] == "finish") { bank.finalizar(+args[1]);                       }
        else if (args[0] == "arrive") { bank.chegar(std::make_shared<Pessoa>(args[1])); }
        else if (args[0] == "show"  ) { fn::write(bank);                                }
        else                          { fn::write("fail: comando invalido");            }
        
    }
}


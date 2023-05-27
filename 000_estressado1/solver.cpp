#include <iostream>
#include <vector>
#include <fn.hpp>
#include <sstream>
#include <algorithm>


using namespace fn;

bool in(std::vector<int> vet, int x) {
  for(auto elem : vet){
    if(elem == x)
      return true;
  }
  return false;
}

int index_of(std::vector<int> vet, int x) {
    int contador = 0;
  for(auto elem : vet){
    if( x == elem){
      return contador;
    }
    contador++;
  }
  return -1;
}

int find_if(const std::vector<int>& vet) {
    int aux;
    for(int i = 0; i < vet.size() ; i++ ){
      if(i < i+1 && vet[i] > 0){
        aux = i;
        return i;
      }
    }
    return -1;
}

int min_element(const std::vector<int>& vet) {
  int aux=0; 
  bool controle = false;
  for(int i = 0; i < vet.size() ; i++){
      if(vet[i] <= vet[aux]){
        aux = i;
        controle = true;
      }
  }
  if(controle){
      return  aux;
  }else
    return -1;
}

int find_min_if(const std::vector<int>& vet) {
    int aux = 0;
    bool controle = false;
    for(int i = 0; i < vet.size() ; i++ ){
      if(i < i+1 && vet[i] > 0){
        aux = i;
        controle = true;
      }
    }

    if(controle){
      return aux;
    }else
      return -1;
}



int main() {

    auto STRTOVET = [](auto s) { return map(split(s.substr(1, s.size() - 2), ','), FNT(x, (int)+x)); };

    while (true) {
        auto line = input();
        write("$" + line);
        auto args = split(line);

        if      (args[0] == "end"        ) { break;                                            }
        else if (args[0] == "in"         ) { write(   tostr(in(STRTOVET(args[1]), +args[2]))); }
        else if (args[0] == "index_of"   ) { write(   index_of(STRTOVET(args[1]), +args[2]));  }
        else if (args[0] == "find_if"    ) { write(    find_if(STRTOVET(args[1])));            }
       else if (args[0] == "min_element") { write(min_element(STRTOVET(args[1])));            }
        else if (args[0] == "find_min_if") { write(find_min_if(STRTOVET(args[1])));            }
        else                               { write("fail: unknown command");                   }
    }     
}
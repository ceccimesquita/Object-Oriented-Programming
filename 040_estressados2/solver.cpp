//fiz sozinha com a base que tinha no replit
#include <iostream>
#include <vector>

using namespace std;

int count(std::vector<int> vet, int x) {
    int contador = 0;
    for(int i = 0; i < vet.size() ; i++){
      if(vet[i] == x)
        contador++;
    }
    return contador; // todo
}

int sum(std::vector<int> vet) {
    int soma {0};
    for(int i = 0; i < vet.size() ; i++){
      if(vet[i] < 0 ){
        vet[i] *= -1;
      }
      soma += vet[i];
    }
    return soma;
    
}

double average(const std::vector<int>& vet) {
    double quantidade  = vet.size();
    return sum(std::vector<int> (vet))/quantidade;
}

std::string more_men(const std::vector<int>& vet) {
    int contaHomem=0, contaMulhe=0;
    for(int i = 0; i < vet.size() ; i++){
      if(vet[i] < 0)
        contaMulhe++;
      else
        contaHomem++;
    }
    if(contaHomem > contaMulhe)
      return "men";
    else if (contaHomem < contaMulhe)
      return "women";
    else 
      return "draw";
}



std::string half_compare(const std::vector<int>& vet) {
    int soma1 = 0, soma2 = 0;
    vector<int> aux;
    for(auto elem : vet){
      if(elem < 0){
        elem *= -1;
      }
      aux.push_back(elem);
    }

    for(int i = 0; i < (vet.size()/2) ; i++){
      soma1 += aux[i];
    }
    for(int i = (vet.size()/2) ; i < vet.size() ; i++){
      soma2 += aux[i];
    }

    if(soma1 < soma2)
      return "second";
    else if(soma1 > soma2)
      return "first";
    else
      return "draw";
}

std::string sex_battle(const std::vector<int>& vet) {
    int somaHomem=0, somaMulher=0, contaHomem=0, contaM=0;
    for(auto elem : vet){
      if(elem < 0 ){
        elem *= -1;
        somaMulher += elem;
        contaM++;
      }
        
      else{
        somaHomem += elem;
        contaHomem++;
      }
    }
    float mediaH=0, mediaM=0;
    mediaH = somaHomem/contaHomem;
    mediaM = somaMulher/contaM;
    if(mediaH > mediaM){
      return "men";
    }else if (mediaH < mediaM){
      return "women";
    }else{
      return "draw";
    }
}


#include <fn.hpp>
using namespace fn;

int main() {

    auto str2vet = [](auto s) { return s.substr(1, s.size() - 2) | SPLIT(',') | MAP(FNT(x, (int)+x)); };

    while (true) {
        auto line = input();
        write("$" + line);
        auto args = split(line);

        if      (args[0] == "end"              ) { break;                                              }
        else if (args[0] == "count"            ) { count(str2vet(args[1]), +args[2])         | WRITE();}
        else if (args[0] == "sum"              ) { sum(str2vet(args[1]))                     | WRITE();}
        else if (args[0] == "more_men"         ) { more_men(str2vet(args[1]))                | WRITE();} 
        else if (args[0] == "half_compare"     ) { half_compare(str2vet(args[1]))            | WRITE();}
        else if (args[0] == "more_men_or_women") { more_men(str2vet(args[1]))                | WRITE();}
        else if (args[0] == "sex_battle"       ) { sex_battle(str2vet(args[1]))              | WRITE();}
        else if (args[0] == "average"          ) { average(str2vet(args[1])) | TOSTR("%.2f") | WRITE();}
        else                                     { "fail: unknown command"                   | WRITE();}
    }     
}


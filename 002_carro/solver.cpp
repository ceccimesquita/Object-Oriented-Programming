/*
fiz sozinha, usei como base o esqueleto que tinha no replit e assistir os videos
das aulas passadas

*/
#include <fn.hpp>
using namespace fn;
using namespace std;

struct Car {
  int pass{0};
  int gas{0};
  int km{0};
  int gasMax{100};
  int passMax{2};

  void entrar() {
    if (pass == passMax || pass > passMax) {
      write("fail: limite de pessoas atingido");
      return;
    } else {
      pass += 1;
    }
  }

  void sair() {
    if (pass == 0) {
      write("fail: nao ha ninguem no carro");
    } else {
      pass -= 1;
    }
  }

  void abastecer(int qtd) {
    gas += qtd;
    if (gas > gasMax) {
      gas = gasMax;
    }
  }

  void dirigir(int distancia) {
    if (pass > 0 && gas >= distancia) {
      gas -= distancia;
      km += distancia;
    }
    if (pass == 0) {
      write("fail: nao ha ninguem no carro");
      return;
    }
    if (gas == 0) {
      write("fail: tanque vazio");
      return;
    }
    if (distancia > gas && pass > 0) {
      write("fail: tanque vazio apos andar " + tostr(gas) + " km");
      km += gas;
      gas = 0;
      
      return;
    }
  }

  string str() {
    return "pass: " + tostr(pass) + ", gas: " + tostr(gas) +
           ", km: " + tostr(km);
  }
};
int main() {
  Car car;

  while (true) {
    string line = input();
    write("$" + line);
    vector<string> args = split(line, ' ');

    if (args[0] == "end") {
      break;
    } else if (args[0] == "show") {
      write(car.str());
    } else if (args[0] == "enter") {
      car.entrar();
    } else if (args[0] == "fuel") {
      car.abastecer(+args[1]);
    } else if (args[0] == "leave") {
      car.sair();
    } else if (args[0] == "drive") {
      car.dirigir(+args[1]);
    }
  }
}
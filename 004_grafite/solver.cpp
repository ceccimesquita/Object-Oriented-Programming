// primeiro fiz a lapiseira e o mercantil e dps usei como base esses algoritimos para
//fazer o grafite e manipular os ponteiros corretamente
#include <iostream>
#include <memory>
#include <sstream>
#include <fn.hpp>

using namespace std;
using namespace fn;

class Lead{

  float calibre;
  std::string dureza;
  int tamanho;

public:

  Lead(float calibre, string dureza, int tamanho){
    this->calibre = calibre;
    this->dureza = dureza;
    this->tamanho = tamanho;
  };

  float getCalibre(){
    return this->calibre;
  }

  string getDureza(){
    return this->dureza;
  }

  int getTamanho(){
    return this->tamanho;
  }

  int setTamanho(int tamanho){
    return this->tamanho = tamanho;
  }

  int desgastePorFolha() {
        if (this->dureza == "HB")
            return 1;
        if (this->dureza == "2B")
            return 2;
        if (this->dureza == "4B")
            return 4;
        return 6;
    }

  string str(){
    stringstream ss;
    ss << "[" << calibre << ":"<< dureza << ":" << tamanho << "]"; 
    return ss.str();
  }  
};

std::ostream& operator<<(std::ostream& os, Lead& l) {
    return os << l.str();
}

using ptrLead = shared_ptr<Lead>;

class Pencil{
  float calibre;
  ptrLead lead {nullptr};
public:
  Pencil(float calibre = 0.0){
    this->calibre = calibre;
    this->lead = nullptr;
  };

  bool hasGrafite(){
    if(this->lead == nullptr){
      return false;
    }else{
       return true;
    }
   
  }

  bool insert(ptrLead lead){
    if(hasGrafite()){
      cout<< "fail: ja existe grafite" << endl;
    }else{
      if(this->calibre == lead->getCalibre()){
        this->lead = lead;
      }else{
        cout<<"fail: calibre incompativel"<< endl;
      }
    }
    return 0;
  }

  ptrLead remove(){
    if(this->lead == nullptr){
        cout <<("sem grafite");
        return {};
    }
    this->lead = nullptr;
    return {};
  }

  void write() {
      if(!hasGrafite()){
        std::cout<< "fail: nao existe grafite" << std::endl;
      }else{
        if(this->lead->getTamanho()<= 10){
          std::cout<< "fail: tamanho insuficiente" << std::endl;
          return;
        }else if(this->lead->getTamanho() > 10 && (this->lead->getTamanho() < this->lead->desgastePorFolha() + 10)){
          std::cout<< "fail: folha incompleta" << std::endl;
          this->lead->setTamanho(10);
        }else{
          this->lead->setTamanho(this->lead->getTamanho() - this->lead->desgastePorFolha());
        }
      }
      
    }

  std::string str() const {
        auto fngr = [](ptrLead g) { return  (g == nullptr ? "null" : g->str()) ; };
        std::ostringstream os;
        os << "calibre: " << calibre 
           << ", grafite: " << fngr(lead);
        return os.str();
    }
};

std::ostream& operator<<(std::ostream& os, Pencil p) {
    return os << p.str();
}

int main() {
    Pencil pencil;
    while (true) {
        auto line = fn::input();
        auto args = fn::split(line, ' ');
        fn::write("$" + line);

        if (args[0] == "end") {
            break;
        } else if (args[0] == "show") {
            fn::write(pencil.str());
        } else if (args[0] == "init") {
            pencil = Pencil((float) +args[1]);
        } else if (args[0] == "insert") {
            pencil.insert(std::make_shared<Lead>((float) +args[1], args[2], +args[3]));
        } else if (args[0] == "remove") {
            pencil.remove();
        } else if (args[0] == "write") {
            pencil.write();
        } else{
            fn::write("fail: comando invalido");
        }
    }
}
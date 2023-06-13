#include <iostream>
#include <list>
#include <sstream>
#include <memory>
#include <vector>
#include <fn.hpp>
using namespace fn;
using namespace std;
class Kid {
private:
    int age;
    std::string name;
public:
    Kid(std::string name, int age) {
        this->age = age;
        this->name = name;
    }
    int getAge() {
        return age;
    }
    std::string getName() {
        return name;
    }
    std::string str() {
        return name + ":" + std::to_string(age);
    }
};

std::ostream& operator<<(std::ostream& os,  Kid kid) {
    return os << kid.str();
}

using PtrKid = std::shared_ptr<Kid>;

class Trampoline {
    std::list<PtrKid> waiting;
    std::list<PtrKid> playing;
    
    // PtrKid removeKid(std::string name, std::list<PtrKid> list) {
    //   PtrKid aux;  
    //   for(auto it : list) {
    //         if(it->getName() == name) {
    //             aux = it;
    //             list.remove(it);
    //         }
    //     }
    //     return 0;
    //   // for(auto it = list.begin(); it != list.end(); it++) {
    //   //       if(PtrKid::it->getName() == name) {
    //   //           PtrKid aux = it;
    //   //           list.erase(it);
    //   //           return kid;
    //   //       }
    //   // }
    // }

public:
    PtrKid removeKid(std::string name, std::list<PtrKid>& list) {
      PtrKid aux;  
      for(auto it = list.begin(); it != list.end();) {
          if ((*it)->getName() == name)
            it = list.erase(it);
          else
            it++;
            
      }
        return 0;

    }
    Trampoline() {
    }
    
    void arrive(PtrKid kid) {
        waiting.push_front(kid);
    }

    void enter() {
        if(!waiting.empty()) {
            auto kid = waiting.back();
            playing.push_front(kid);
            waiting.pop_back();
        }
    }

    void leave() {
      if(!playing.empty()){
        auto aux = playing.back();
        playing.pop_back();
        waiting.push_front(aux);
        
      }
    }

    void removekid(std::string name) {
        PtrKid ki = removeKid(name, this->playing);
        PtrKid ki2 = removeKid(name, this->waiting);
    }

    std::string str() {
        return fn::tostr(waiting) + " => " + fn::tostr(playing);
    }
};

int main() {
    Trampoline tr;

    while (true) {
        auto line = input();
        write("$" + line);
        auto args = split(line);

        if      (args[0] == "end"   ) { break;                                                     }
        else if (args[0] == "arrive") { tr.arrive(std::make_shared<Kid>(args[1], (int) +args[2])); }
        else if (args[0] == "enter" ) { tr.enter();                                                }
        else if (args[0] == "leave" ) { tr.leave();                                                }
        else if (args[0] == "remove") { tr.removekid(args[1]);                                     }
        else if (args[0] == "show"  ) { write(tr.str());                                           }
        else                          { write("fail: invalid command");                            }
    }
}
//fiz com a ajuda de um amg 
#include <iostream>
#include <vector>
#include <sstream>
#include <memory>
#include <utility>
#include <iterator>
#include <fn.hpp>

using namespace std;
using namespace fn;

class Disciplina;

class Aluno{
    string id;
    std::map<string, Disciplina*> disciplinas;

public:
    Aluno(string nome): id(nome){}

    string getId();

    vector<Disciplina*> getDisciplinas();

    void addDisciplina(Disciplina* disciplina);

    void rmDisciplina(string idDisciplina);

    friend std::ostream& operator<<(std::ostream& os, Aluno& aluno);
};

class Disciplina{
    std::string id;
    std::map<std::string, Aluno*> alunos;

public:
    Disciplina(std::string nome): id(nome){}

    string getId(){
        return this->id;
    }

    void addAluno(Aluno* aluno){
        auto aux = alunos.find(aluno->getId());
        if(aux != alunos.end()){
            throw "aluno ja matriculado";
            return;
        }
        this->alunos[aluno->getId()] = aluno;

        aluno->addDisciplina(this);
    }

    void rmAluno(string idAluno){
        auto aux = alunos.find(idAluno);
        if(aux == alunos.end()){
            return;
        }
        Aluno* aluno = aux->second;
        this->alunos.erase(aux);
        aluno->rmDisciplina(this->id);
    }

    vector<Aluno*> getAlunos(){
        vector<Aluno*> ret;
        for(auto& par : alunos){
            ret.push_back(par.second);
        }
        return ret;
    }

    friend std::ostream& operator<<(std::ostream& os, Disciplina& disciplina);
};

    string Aluno::getId(){
        return this->id;
    }

    void Aluno::addDisciplina(Disciplina* disciplina){
        auto aux = disciplinas.find(disciplina->getId());
        if(aux != disciplinas.end()){
            return;
        }
        this->disciplinas[disciplina->getId()] = disciplina;
        disciplina->addAluno(this);
    }

    void Aluno::rmDisciplina(string idDisciplina){
        auto aux = disciplinas.find(idDisciplina);
        if(aux == disciplinas.end()){
            return;
        }
        Disciplina* disciplina = aux->second;
        this->disciplinas.erase(aux);
        disciplina->rmAluno(this->id);
    }

    vector<Disciplina*> Aluno::getDisciplinas(){
        vector<Disciplina*> ret;
        for(auto& par : disciplinas){
            ret.push_back(par.second);
        }
        return ret;
    }

class Sistema{
    std::map<std::string, Aluno*> alunos;
    std::map<std::string, Disciplina*> disciplinas;
    
public:
    Sistema(){}

    void addAluno(string id){
        auto aux = alunos.find(id);
        if(aux != alunos.end()){   
            return;
        }
        this->alunos[id] = new Aluno(id);
    }

    void addDiscp(string id){
        auto aux = disciplinas.find(id);
        if(aux != disciplinas.end()){
            return;
        }
        this->disciplinas[id] = new Disciplina(id);
    }

    void Matricular(string idAluno, string idDisciplina){
        auto aux = alunos.find(idAluno);
        if(aux == alunos.end()){
            return;
        }
        auto aux2 = disciplinas.find(idDisciplina);
        if(aux2 == disciplinas.end()){
            return;
        }
        Aluno* aluno = aux->second;
        Disciplina* disciplina = aux2->second;
        aluno->addDisciplina(disciplina);
    }

    void Desmatricular(string idAluno, string idDisciplina){
        auto aux = alunos.find(idAluno);
        if(aux == alunos.end()){
            return;
        }
        auto aux2 = disciplinas.find(idDisciplina);
        if(aux2 == disciplinas.end()){
            return;
        }
        Aluno* aluno = aux->second;
        aluno->rmDisciplina(idDisciplina);
    }

    void rmAluno(string id){
        auto aux = alunos.find(id);
        if(aux == alunos.end()){
            return;
        }
        Aluno* aluno = aux->second;
        for(auto& par : aluno->getDisciplinas()){
            par->rmAluno(id);
        }
        this->alunos.erase(aux);
    }

    void rmDiscp(string id){
        auto aux = disciplinas.find(id);
        if(aux == disciplinas.end()){
            return;
        }
        Disciplina* disciplina = aux->second;
        for(auto& par : disciplina->getAlunos()){
            par->rmDisciplina(id);
        }
        this->disciplinas.erase(aux);
    }

    friend std::ostream& operator<<(std::ostream& os, Sistema& sistema);
};

    std::ostream& operator<<(std::ostream& os, Disciplina& discp) {
        os << discp.getId() << " [";
        for (auto it = discp.alunos.begin(); it != discp.alunos.end(); it++) {
            os << (it == discp.alunos.begin() ? "" : ", " ) << it->second->getId();
        }
        os << "]";
        return os;
    }
    std::ostream& operator<<(std::ostream& os, Aluno& aluno) {
        os << aluno.getId() << " [";
        for (auto it = aluno.disciplinas.begin(); it != aluno.disciplinas.end(); it++) {
            os << (it == aluno.disciplinas.begin() ? "" : ", " ) << it->second->getId();
        }
        os << "]";
        return os;
    }
    std::ostream& operator<<(std::ostream& os, Sistema& sistema) {
        os << "- alunos\n";
        for (auto& [key, value]: sistema.alunos)
            os << "" << *value << "\n";
        os << "- discps\n";
        for (auto& [key, value]: sistema.disciplinas)
            os << "" << *value << "\n";
        return os;
    }



int main(){
    std::string line, cmd;
    Sistema sistema;
    while(true){
        try{
            getline(std::cin, line);
            std::cout << "$" << line << '\n';
            std::stringstream ss(line);
            //cria um vetor de strings a partir de line
            std::vector<std::string> ui(std::istream_iterator<std::string>{ss}, std::istream_iterator<std::string>());
            std::string cmd = ui[0];
            if(cmd == "end"){
                break;
            }else if(cmd == "nwalu"){
                for(size_t i = 1; i < ui.size(); i++)
                    sistema.addAluno(ui[i]);
            }else if(cmd == "nwdis"){
                for(size_t i = 1; i < ui.size(); i++)
                    sistema.addDiscp(ui[i]);
            }else if(cmd == "show"){
                std::cout << sistema;
            }else if(cmd == "tie"){
                for(size_t i = 2; i < ui.size(); i++)
                    sistema.Matricular(ui[1], ui[i]);
            }else if(cmd == "untie"){
                for(size_t i = 2; i < ui.size(); i++)
                    sistema.Desmatricular(ui[1], ui[i]);
            }else if(cmd == "rmalu"){
                sistema.rmAluno(ui[1]);
            }else{
                std::cout << "comando invalido " << "[" << cmd << "]\n";
            }
        }catch(std::string e){
            std::cout << e << '\n';
        }
    }
}
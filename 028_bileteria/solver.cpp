#include <iostream>
#include <fn.hpp>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip>

using namespace std;
using namespace fn;

class Pessoa{
    string nome;
    bool meia;
public:
    Pessoa(string nome = "", bool meia = false): nome(nome), meia(meia){}

    string getNome() const {

        return nome;
    }

    bool getMeia() const {
        return meia;
    }

    string toString() const{
        stringstream ss;
        ss << nome << ":" << (meia ? "meia" : "inteira");
        return ss.str();
    }
};

class Evento{
    string nome;
    float preco = 0.00;
public:
    Evento(string nome = "", double preco = 0.00): nome(nome), preco(preco){}

    string getNome() const{
        return nome;
    }

    float getPreco() const{
        return preco;
    }

    const string toString() const{
        stringstream ss;
        ss << nome << ":" << setprecision(2) << fixed << preco ;
        return ss.str();
    }
};

class Venda{
    Pessoa* pessoa;
    Evento* evento;
    double valor;

public:
    Venda(Pessoa* pessoa, Evento* evento): pessoa(pessoa), evento(evento){
        valor = evento->getPreco();
        if(pessoa->getMeia()){
            valor /= 2;
        }
    }

    Pessoa getPessoa() const{
        return this->getPessoa();
    }

    Evento getEvento() const{
        return this->getEvento();
    }

    double getValor() const{
        return valor;
    }

    string toString() const{
        stringstream ss;
        ss << pessoa->getNome() << ":" << evento->getNome() << ":" << setprecision(2) << fixed << valor;
        return ss.str();
    }
};



std::ostream& operator<<(std::ostream& os, const Pessoa& pessoa) {
    return os << pessoa.toString();
}

std::ostream& operator<<(std::ostream& os, const Evento& discp) {
    return os << discp.toString();
}

std::ostream& operator<<(std::ostream& os, const Venda& discp) {
    return os << discp.toString();
}


class Bilheteria{
    vector<Venda> vendas;
    std::map<string, Evento> eventos;
    std::map<string, Pessoa> pessoas;

public:
    Bilheteria(){}

    std::vector<Venda> getVendas(){
        std::vector<Venda> vendas;
        for(auto elem : this->vendas){
            vendas.push_back(elem);
        }
        return vendas;
    }

    std::vector<Evento> getEventos(){
        std::vector<Evento> eventos;
        for(auto elem : this->eventos){
            eventos.push_back(elem.second);
        }
        return eventos;
    }

    std::vector<Pessoa> getPessoas(){
        std::vector<Pessoa> pessoas;
        for(auto elem : this->pessoas){
            pessoas.push_back(elem.second);
        }
        return pessoas;
    }

    void addPessoa(string nome, bool meia){
        for(auto elem : this->pessoas){
            if(elem.second.getNome() == nome){
                throw std::runtime_error("fail: pessoa " + nome + " ja existe");
            }
        }
        Pessoa pessoa(nome, meia);
        pessoas.insert(make_pair(nome, pessoa));
    }

    void addEvento(string nome, double preco){
        for(auto elem : this->eventos){
            if(elem.second.getNome() == nome){
                throw std::runtime_error("fail: evento " + nome + " ja existe");
            }
        }
        Evento evento(nome, preco);
        eventos.insert(make_pair(nome, evento));
    }

    void vender(string nomeDaPessoa, string nomeDoEvento){
        if(this->pessoas.find(nomeDaPessoa) == this->pessoas.end()){
            throw std::runtime_error("fail: pessoa " + nomeDaPessoa + " nao existe");
        }
        if(this->eventos.find(nomeDoEvento) == this->eventos.end()){
            throw std::runtime_error("fail: evento " + nomeDoEvento + " nao existe");
        }
        Pessoa *pessoa = &this->pessoas[nomeDaPessoa];
        Evento *evento = &this->eventos[nomeDoEvento];
        Venda venda(pessoa, evento);
        this->vendas.push_back(venda);
    }

};

int main(){
    Bilheteria bilheteria;

    while (true)
    {
        auto line = input();
        write("$" + line);
        auto args = split(line);

        try{
            if (args[0] == "end"){
                break;
            }else if (args[0] == "addPessoa"){
                bilheteria.addPessoa(args[1], args[2] == "meia");   
            }else if(args[0] == "addEvento"){
                bilheteria.addEvento(args[1], stof(args[2]));
            }else if(args[0] == "pessoas"){
                write("["+ join(bilheteria.getPessoas(), ", ") + "]");
            }else if(args[0] == "eventos"){
                write("["+ join(bilheteria.getEventos(), ", ") + "]");
            }else if(args[0] == "vender"){
                bilheteria.vender(args[1], args[2]);
            }else if(args[0] == "vendas"){
                write("["+ join(bilheteria.getVendas(), ", ") + "]");

            }else{
                write("fail: comando invalido");
            }
        }catch(std::exception& e){
            cout << e.what() << endl;

        }
    }
    
}
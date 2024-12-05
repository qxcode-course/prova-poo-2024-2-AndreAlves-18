#include <iostream>
#include "fn.hpp"

class Pessoa{
    std::string nome {};
    int dinheiro;
public:
    Pessoa(std::string nome = "", int dinheiro = 0): nome(nome), dinheiro(dinheiro){}
    std::string str(){
        return fn::format("{}:{}", nome, dinheiro);
    }
    std::string getNome(){
        return this->nome;
    }
    int getDinheiro(){
        return this->dinheiro;
    }
    void setDinheiro(int valor){
        dinheiro += valor;
    }
};

class Moto{
    int custo{0};
    std::shared_ptr<Pessoa> motorista {nullptr};
    std::shared_ptr<Pessoa> passageiro {nullptr};
public:
    Moto(){}
    std::string str(){
        if(motorista == nullptr && passageiro == nullptr){
            return fn::format("Cost: {}, Driver: None, Passenger: None", custo);
            
        }
        if(motorista == nullptr){
            return fn::format("Cost: {}, Driver: None, Passenger: {}", custo, passageiro->str());
            
        }
        if(passageiro == nullptr){
            return fn::format("Cost: {}, Driver: {}, Passenger: None", custo, motorista->str());
        }
        return fn::format("Cost: {}, Driver: {}, Passenger: {}", custo, motorista->str(), passageiro->str());
    }
    void setMotorista(std::shared_ptr<Pessoa> motoris){
        if(motorista == nullptr){
            motorista = motoris;
            return;
        }
    }
    void setPassageiro(std::shared_ptr<Pessoa> pas){
        if(passageiro == nullptr){
            passageiro = pas;
            return;
        }
    }
    void dirigir(int valor){
        custo += valor;
    }
    void descer(){
        if(passageiro != nullptr){
            if(custo > passageiro->getDinheiro()){
                fn::write("fail: Passenger does not have enough money");
                fn::print("{}:0 leave\n", passageiro->getNome());
                motorista->setDinheiro(custo);
                custo = 0;
                passageiro = nullptr;
                return;
            }
            fn::print("{}:{} leave\n", passageiro->getNome(), custo);
            motorista->setDinheiro(custo);
            custo = 0;
            passageiro = nullptr;
            return;
        }
    }

};


class Adapter {
    Moto moto;
public:
    void setDriver(std::string name, int money) {
        (void) name;
        (void) money;
        auto person = std::make_shared<Pessoa>(name, money);
        moto.setMotorista(person);

    }
    void setPass(std::string name, int money) {
        (void) name;
        (void) money;
        auto person = std::make_shared<Pessoa>(name, money);
        moto.setPassageiro(person);
    }
    void drive(int distance) {
        (void) distance;
        moto.dirigir(distance);
    }
    void leavePass() {
        moto.descer();
    }
    void show() {
        std::cout << moto.str() << '\n';
    }
};

int main() {
    Adapter adp;
    while (true) {
        fn::write("$", "");
        auto line = fn::input();
        auto args = fn::split(line, ' ');
        fn::write(line);

        if      (args[0] == "end")       { break;                                  }
        else if (args[0] == "setDriver") { adp.setDriver(args[1], +args[2]);       }
        else if (args[0] == "setPass")   { adp.setPass(args[1], +args[2]);         }
        else if (args[0] == "drive")     { adp.drive(+args[1]);                    }
        else if (args[0] == "leavePass") { adp.leavePass();                        }
        else if (args[0] == "show")      { adp.show();                             }
        else                             { fn::write("fail: command not found\n"); }
    }
}

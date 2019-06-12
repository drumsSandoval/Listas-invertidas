//
//  indices.hpp
//  Practica18-9
//
//  Created by Oscar Sandoval on 3/16/19.
//  Copyright © 2019 Oscar Sandoval. All rights reserved.
//

#ifndef indices_h
#define indices_h
#include <iostream>
#include "list.hpp"
using namespace std;
class Indice{
private:
    long address;
    int key;
public:
    Indice();
    //Setters
    void setAddress(long);
    void setKey(int);
    //Getters
    long getAddress();
    int getKey();
    //Sobre carga de operadores
    bool operator > (Indice&)const;
    bool operator < (const Indice&)const;
    bool operator >= (const Indice&)const;
    bool operator <= (const Indice&)const;
    bool operator == (const Indice&)const;
    Indice operator = (const Indice&);
    void save(List<Indice>&);
    friend std::ostream& operator << (std::ostream& os, Indice& c){
        os<<"Id : "<<c.getKey()<<endl;
        os<<"Direccion : "<<c.getAddress()<<endl<<endl;
        return os;
    }
};
class nodo{
public:
    int first;
    Node<nodo>* second;
    nodo():second(nullptr){}
    bool operator == (const nodo&a)const{
        return first==a.first;
    }
};
class IndiceGenero{
private:
    std::string genero;
    Node<nodo>* address;
public:
    IndiceGenero(List<IndiceGenero>&,List<nodo>&);
    //Setters
    void setAddress(Node<nodo>*);
    void setKey(std::string);
    //Getters
    Node<nodo>* getAddress();
    std::string getKey();
    //Sobre carga de operadores
    bool operator > (IndiceGenero&)const;
    bool operator < (const IndiceGenero&)const;
    bool operator >= (const IndiceGenero&)const;
    bool operator <= (const IndiceGenero&)const;
    bool operator == (const IndiceGenero&)const;
    IndiceGenero operator = (const IndiceGenero&);
    void save(List<IndiceGenero>&,List<nodo>&);
    friend std::ostream& operator << (std::ostream& os, IndiceGenero& c){
        os<<"Genero : "<<c.getKey();
        os<<" | : "<<c.getAddress()<<endl<<endl;
        return os;
    }
};

#endif /* indices_h */

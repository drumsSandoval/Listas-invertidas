//
//  indices.cpp
//  Practica18-9
//
//  Created by Oscar Sandoval on 3/16/19.
//  Copyright © 2019 Oscar Sandoval. All rights reserved.
//

#include "indices.hpp"
#include <fstream>

using namespace std;

Indice::Indice() {
    
}

bool Indice::operator>(Indice &i) const {
    return key>i.key;
}

bool Indice::operator<(const Indice &i) const {
    return key<i.key;
}

bool Indice::operator>=(const Indice &i) const {
    return key>=i.key;
}

bool Indice::operator<=(const Indice &i) const {
    return key<=i.key;
}

bool Indice::operator==(const Indice &i) const {
    return key==i.key;
}

Indice Indice::operator=(const Indice &i) {
    this->key=i.key;
    this->address=i.address;
    return *this;
}

void Indice::save(List<Indice> &list) {
    ofstream archive("/Users/oscarsandoval/Desktop/Practica18-9/IndiceID.txt",ios::out);
    int i=0;
    while(i<=list.size()){
        archive.write((char*)&list[i], sizeof(Indice));
        i++;
    }
    archive.close();
}

void Indice::setAddress(long address) {
    this->address=address;
}

void Indice::setKey(int key) {
    this->key=key;
}

long Indice::getAddress() {
    return address;
}

int Indice::getKey() {
    return key;
}

/////////////////////////////I N D I C E S      G E N E R O////////////////////////////

IndiceGenero::IndiceGenero(List<IndiceGenero>&list,List<nodo>&listaInvertida):address(nullptr) {
    fstream archive("/Users/oscarsandoval/Desktop/Practica18-9/ListaInverrtida.txt",ios::in|ios::out);
    if(!archive.good()){
        return;
    }
    cin.get();
    string myStr;
    nodo aux;
    getline(archive,myStr);
    stringstream stream(myStr);
    while(getline(stream, myStr,'|')){
        aux.first=stoi(myStr);
        listaInvertida.insertData(listaInvertida.getLastPos(),aux);
    }
    getline(archive,myStr);
    stringstream stream2(myStr);
    int i=0;
    while(getline(stream2, myStr,'|')){
        listaInvertida[i].second=listaInvertida.retrieve(stoi(myStr));
        i++;
    }
    archive.close();
    archive.open("/Users/oscarsandoval/Desktop/Practica18-9/IndiceSecundario.txt");
    cin.get();
    getline(archive,myStr);
    stringstream stream3(myStr);
    while(getline(stream3, myStr,'|')){
        setKey(myStr);
        list.insertData(list.getLastPos(),*this);
    }getline(archive,myStr);
    stringstream stream4(myStr);
    i=0;
    while(getline(stream4, myStr,'|')){
        list[i].setAddress(listaInvertida.retrieve(stoi(myStr)));
        i++;
    }
    archive.close();
}

void IndiceGenero::setAddress(Node<nodo>* i) {
    address=i;
}

void IndiceGenero::setKey(string genero)  {
    this->genero=genero;
}

Node<nodo>* IndiceGenero::getAddress() {
    return this->address;
}

string IndiceGenero::getKey() {
    return genero;
}

bool IndiceGenero::operator>(IndiceGenero &i) const {
    return genero>i.genero;
}

bool IndiceGenero::operator<(const IndiceGenero &i) const {
    return genero<i.genero;
}

bool IndiceGenero::operator>=(const IndiceGenero &i) const {
    return genero>=i.genero;
}

bool IndiceGenero::operator<=(const IndiceGenero &i) const {
    return genero<=i.genero;
}

bool IndiceGenero::operator==(const IndiceGenero &i) const {
    return genero==i.genero;
}

IndiceGenero IndiceGenero::operator=(const IndiceGenero &i) {
    genero=i.genero;
    this->address=i.address;
    return *this;
}

void IndiceGenero::save(List<IndiceGenero> &list,List<nodo>& listaInvertida) {
    ofstream save;
    save.open("/Users/oscarsandoval/Desktop/Practica18-9/IndiceSecundario.txt",ios::out);
    int i = 0;
    while(i<=list.size()){
        save<<list[i].getKey()<<"|";
        i++;
    }
    save<<endl;
    i=0;
    while(i<=list.size()){
        save<<listaInvertida[list[i].getAddress()]<<"|";
        i++;
    }
    save<<endl;
    save.close();
}


//
//  libros.hpp
//  Practica18-9
//
//  Created by Oscar Sandoval on 3/16/19.
//  Copyright © 2019 Oscar Sandoval. All rights reserved.
//

#ifndef libros_h
#define libros_h
#include "indices.hpp"
class Libro{
public:
    int id;
    char nombre[20];
    char autor[20];
    char genero[20];
    friend std::ostream& operator << (std::ostream& os, Libro& c){
        os<<"Libro : "<<c.nombre<<std::endl;
        os<<"Genero : "<<c.genero<<std::endl;
        os<<"Codigo : "<<c.id<<std::endl;
        return os;
    }
};
class Libros{
    private :
    Libro libro;
    Indice indice;
    IndiceGenero indiceGenero;
    void insertM(List<Indice>&,List<IndiceGenero>&,List<nodo>&);
public:
    Libros(List<Indice>&,List<IndiceGenero>&,List<nodo>&);
    void setId(std::string&);
    void setNombre(std::string&);
    void setAutor(std::string&);
    void setGenero(std::string&);
    int getId();
    std::string getName();
    std::string getAutor();
    std::string getGenero();
    void insert(List<Indice>&,List<IndiceGenero>&,List<nodo>&);
    void print();
    void save(List<Indice>&,List<IndiceGenero>&,List<nodo>&);
    void buscarGenero(List<Indice>&,List<IndiceGenero>&,List<nodo>&);
    void modify(List<Indice>&,List<IndiceGenero>&,List<nodo>&,std::string);
    void remove(List<Indice>&,List<IndiceGenero>&,List<nodo>&,std::string);
};


#endif /* libros_h */

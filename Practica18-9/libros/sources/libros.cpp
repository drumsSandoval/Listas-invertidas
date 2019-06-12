//
//  libros.cpp
//  Practica18-9
//
//  Created by Oscar Sandoval on 3/16/19.
//  Copyright © 2019 Oscar Sandoval. All rights reserved.
//

#include "libros.hpp"
#include <fstream>
Libros::Libros(List<Indice> &list, List<IndiceGenero> &listGenero, List<nodo> & listaInvertida):indiceGenero(listGenero,listaInvertida){
    ifstream archive("/Users/oscarsandoval/Desktop/Practica18-9/IndiceID.txt");
    list.deleteAll();
    if(!archive.good()){
        libro.id=0;
        return;
    }
    while(!archive.eof()){
        archive.read((char*)&indice,sizeof(Indice));
        if(archive.eof())break;
        list.insertData(list.getLastPos(), indice);
    }
    archive.close();
    libro.id = indice.getKey();
}

void Libros::setId(std::string &id) {
    try{
        this->libro.id=stoi(id);
    }catch(invalid_argument& ex){
        throw invalid_argument("Ingrese un valor valido :`(\n");
    }
}

void Libros::setNombre(std::string &name) {
    for(int i=0;i<20;i++)
        this->libro.nombre[i]='\0';
    for(int i=0;name[i];i++)
        this->libro.nombre[i]=name[i];
}

void Libros::setAutor(std::string &autor) {
    for(int i=0;i<20;i++)
        this->libro.autor[i]='\0';
    for(int i=0;autor[i];i++)
        this->libro.autor[i]=autor[i];
}

void Libros::setGenero(std::string &genero) {
    for(int i=0;i<20;i++)
        this->libro.genero[i]='\0';
    for(int i=0;genero[i];i++)
        this->libro.genero[i]=genero[i];
}

int Libros::getId() {
    return libro.id;
}

std::string Libros::getName() {
    string myStr;
    for(int i =0;libro.nombre[i];i++){
        myStr+=libro.nombre[i];
    }
    return myStr;
}

std::string Libros::getAutor() {
    string myStr;
    for(int i =0;libro.autor[i];i++){
        myStr+=libro.autor[i];
    }
    return myStr;
}

std::string Libros::getGenero() {
    string myStr;
    for(int i =0;libro.genero[i];i++){
        myStr+=libro.genero[i];
    }
    return myStr;
}

void Libros::print() {
    ifstream archive("/Users/oscarsandoval/Desktop/Practica18-9/Libros.txt");
    if(!archive.good()){
        cout<<"No hay Libros registrados"<<endl;
        return;
    }
    cout<<"Libros Registrados"<<endl<<endl;
    while(!archive.eof()){
        archive.read((char*)&libro,sizeof(libro));
        if(archive.eof())break;
        cout<<libro<<endl;
    }
    archive.close();
}

void Libros::insert(List<Indice>&listId,List<IndiceGenero>&listGenero,List<nodo>&listaInvertida){
    ofstream archive("/Users/oscarsandoval/Desktop/Practica18-9/Libros.txt",ios::app);
    nodo node;
    libro.id++;
    indice.setAddress(archive.tellp());
    indice.setKey(getId());
    indiceGenero.setKey(getGenero());
    indiceGenero.setAddress(nullptr);
    listId.insertData(listId.getLastPos(),indice);
    node.first=libro.id;
    if(!listGenero.find(indiceGenero)){
        listaInvertida.insertData(listaInvertida.getLastPos(),node);
        indiceGenero.setAddress(listaInvertida.getLastPos());
        listGenero.insertData(listGenero.getLastPos(),indiceGenero);
    }else{
        int pos = listGenero.findPos(indiceGenero);
        Node<nodo> *aux(listGenero[pos].getAddress());
        pos=listaInvertida[aux];
        if(listaInvertida[pos].second==nullptr){
            listaInvertida.insertData(listaInvertida.getLastPos(), node);
            listaInvertida[pos].second = listaInvertida.getLastPos();
        }else{
            while(listaInvertida[pos].second!=nullptr){
                aux = listaInvertida[pos].second;
                pos = listaInvertida[aux];
            }
            listaInvertida.insertData(listaInvertida.getLastPos(), node);
            listaInvertida[pos].second = listaInvertida.getLastPos();
        }
    }
    archive.write((char*)&libro,sizeof(Libro));
    archive.close();
}

void Libros::remove(List<Indice> &listIndice, List<IndiceGenero> &listGenero, List<nodo> &listaInvertida, std::string user){
    try{
        indice.setKey(stoi(user));
    }catch(invalid_argument&){
        throw invalid_argument("Codigo no valido\n");
    }
    if(!listIndice.find(indice)){
        throw invalid_argument("Libro no encontrado\n");
    }
    int pos = listIndice.findPos(indice);// Lista indices
    ifstream archive("/Users/oscarsandoval/Desktop/Practica18-9/Libros.txt");
    archive.seekg(listIndice[pos].getAddress());
    archive.read((char*)&libro,sizeof(Libro));
    archive.close();
    indiceGenero.setKey(getGenero());
    pos = listGenero.findPos(indiceGenero);// Posicion de la lista de Genero
    Node<nodo>* aux = listGenero[pos].getAddress();//Aux obtiene el primer nodo de la lista invertida
    if(aux->getData().second==nullptr && aux->getData().first==getId()){
        listGenero.deleteData(listGenero.findData(listGenero[pos]));
        listaInvertida.deleteData(aux);
    }else{
        if(aux->getData().first==getId()){
            listGenero[pos].setAddress(aux->getData().second);
            listaInvertida.deleteData(aux);
        }else{
            Node<nodo>* aux2(aux->getData().second);
            while(aux2!=nullptr){
                if(aux2->getData().first==getId()){
                    aux->getData().second=aux2->getData().second;
                    listaInvertida.deleteData(aux2);
                    break;
                }
                aux2 = aux2->getData().second;
                aux = aux->getData().second;
            }
        }
    }
    ofstream archive2("/Users/oscarsandoval/Desktop/Practica18-9/Aux.txt",ios::out);
    archive.open("/Users/oscarsandoval/Desktop/Practica18-9/Libros.txt");
    listIndice.deleteAll();
    while(!archive.eof()){
        archive.read((char*)&libro, sizeof(libro));
        if(archive.eof())break;
        if(libro.id==stoi(user)){
            
        }
        else{
            indice.setKey(getId());
            indice.setAddress(archive2.tellp());
            archive2.write((char*)&libro,sizeof(libro));
            listIndice.insertData(listIndice.getLastPos(), indice);
        }
    }
    archive2.close();
    archive.close();
    std::remove("/Users/oscarsandoval/Desktop/Practica18-9/Libros.txt");
    rename("/Users/oscarsandoval/Desktop/Practica18-9/Aux.txt","/Users/oscarsandoval/Desktop/Practica18-9/Libros.txt");
}

void Libros::modify(List<Indice> &listIndice, List<IndiceGenero> &listGenero, List<nodo> &listaInvertida,string user){
    try{
        indice.setKey(stoi(user));
    }catch(invalid_argument& ex){
        throw invalid_argument(ex.what());
    }
    const int a(indice.getKey());
    if(!listIndice.find(indice)){
        throw invalid_argument("Libro no encontrado\n");
    }
    const int pos(listIndice.findPos(indice));
    ifstream archive("/Users/oscarsandoval/Desktop/Practica18-9/Libros.txt");
    archive.seekg(listIndice[pos].getAddress());
    archive.read((char*)&libro,sizeof(Libro));
    do{
        cout<<"\t\tModificar Aspirante"<<endl
        <<"\t1)Nombre"<<endl
        <<"\t2)Autor"<<endl
        <<"\t3)Genero"<<endl
        <<"\t4)Regresar"<<endl
        <<"\tElige una opcion : ";
        getline(cin,user);
        if(user=="1"){
            system("clear");
            cout<<"\t\tModificar Nombre : "<<endl
            <<"\tNombre actual : "<<getName()<<endl
            <<"Nuevo nombre : ";
            getline(cin,user);
            for(int i = 0;user[i];++i)
                user[i] = toupper(user[i]);
            setNombre(user);
        }else if(user=="2"){
            system("clear");
            cout<<"\t\tModificar Autor : "<<endl
            <<"\tAutor actual : "<<getAutor()<<endl
            <<"Nuevo Autor : ";
            getline(cin,user);
            for(int i = 0;user[i];++i)
                user[i] = toupper(user[i]);
            setAutor(user);
        }else if(user=="3"){
            system("clear");
            cout<<"\t\tModificar Genero : "<<endl
            <<"\tGenero actual : "<<getGenero()<<endl
            <<"Nuevo Genero : ";
            getline(cin,user);
            for(int i = 0;user[i];++i)
                user[i] = toupper(user[i]);
            try{
                remove(listIndice, listGenero, listaInvertida, to_string(a));
            }catch(invalid_argument& ex){
                cerr<<ex.what()<<endl;
                cin.get();
            }
            setGenero(user);
            insertM(listIndice, listGenero, listaInvertida);
            cout<<endl<<endl<<"\t\tLibro Modificado "<<endl;
            cin.get();
            return;
        }else if(user=="4"){
            system("clear");
        }else{
            system("clear");
            cout<<"Opcion no valida"<<endl;
        }
    }while(user!="5");
}

void Libros::save(List<Indice> & listIndice, List<IndiceGenero> & listGenero, List<nodo> & listaInvertida) {
    indice.save(listIndice);
    indiceGenero.save(listGenero, listaInvertida);
    ofstream save;
    save.open("/Users/oscarsandoval/Desktop/Practica18-9/ListaInverrtida.txt");
    int i=0;
    while(i<=listaInvertida.size()){
        save<<listaInvertida[i].first<<"|";
        i++;
    }
    save<<endl;
    i=0;
    while(i<=listaInvertida.size()){
        save<<listaInvertida[listaInvertida[i].second]<<"|";
        i++;
    }
    save<<endl;
    save.close();
}

void Libros::buscarGenero(List<Indice> &listIndice, List<IndiceGenero> & listGenero, List<nodo> &listaInvertida) {
    string myStr;
    ifstream archive("/Users/oscarsandoval/Desktop/Practica18-9/Libros.txt");
    if(!archive.good()){
        cout<<"No hay libros registrados"<<endl;
        return;
    }
    cout<<"\t\t\tBusqueda por genero : "<<endl<<endl
    <<"\tGenero : ";
    getline(cin,myStr);
    for(int i = 0;myStr[i];++i)
        myStr[i] = toupper(myStr[i]);
    indiceGenero.setKey(myStr);
    if(!listGenero.find(indiceGenero)){
        cout<<"\t\t\tNo hay resultados para este genero "<<endl;
        cin.get();
        return;
    }
    int pos = listGenero.findPos(indiceGenero);
    Node<nodo> *a=listGenero[pos].getAddress();
    while(a!=nullptr){
        cout<<a->getData().first<<endl;
        cin.get();
        indice.setKey(a->getData().first);
        pos = listIndice.findPos(indice);
        cout<<pos;
        cin.get();
        archive.seekg(listIndice[pos].getAddress());
        archive.read((char*)&libro,sizeof(Libro));
        cout<<libro<<endl;
        a = a->getData().second;
    }
    libro.id = listIndice.getLastPos()->getData().getKey();
}

void Libros::insertM(List<Indice>&listId,List<IndiceGenero>&listGenero,List<nodo>&listaInvertida){
    ofstream archive("/Users/oscarsandoval/Desktop/Practica18-9/Libros.txt",ios::app);
    nodo node;
    indice.setAddress(archive.tellp());
    indice.setKey(getId());
    indiceGenero.setKey(getGenero());
    indiceGenero.setAddress(nullptr);
    listId.insertData(listId.getLastPos(),indice);
    node.first=libro.id;
    if(!listGenero.find(indiceGenero)){
        listaInvertida.insertData(listaInvertida.getLastPos(),node);
        indiceGenero.setAddress(listaInvertida.getLastPos());
        listGenero.insertData(listGenero.getLastPos(),indiceGenero);
    }else{
        int pos = listGenero.findPos(indiceGenero);
        Node<nodo> *aux(listGenero[pos].getAddress());
        pos=listaInvertida[aux];
        if(listaInvertida[pos].second==nullptr){
            listaInvertida.insertData(listaInvertida.getLastPos(), node);
            listaInvertida[pos].second = listaInvertida.getLastPos();
        }else{
            while(listaInvertida[pos].second!=nullptr){
                aux = listaInvertida[pos].second;
                pos = listaInvertida[aux];
            }
            listaInvertida.insertData(listaInvertida.getLastPos(), node);
            listaInvertida[pos].second = listaInvertida.getLastPos();
        }
    }
    archive.write((char*)&libro,sizeof(Libro));
    archive.close();
}

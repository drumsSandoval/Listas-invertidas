//
//  main.cpp
//  Practica18-9
//
//  Created by Oscar Sandoval on 3/16/19.
//  Copyright © 2019 Oscar Sandoval. All rights reserved.
//

#include "libros.hpp"
using namespace std;
int main(int argc, const char * argv[]) {
    system("clear");
    List<Indice> tdaIndices;
    List<IndiceGenero> tdaindiceGenero;
    List<nodo> listaInvertida;
    Libros libro(tdaIndices,tdaindiceGenero,listaInvertida);
    Console graphics;
    string myStr;
    do{
        cout<<"\t\t\tMenu : "<<endl
        <<"\t1)Crear Libro"<<endl
        <<"\t2)Mostrar todos los libros"<<endl
        <<"\t3)Mostrar por genero"<<endl
        <<"\t4)Mostrar Lista Invertida"<<endl
        <<"\t5)Mostrar Indice Genero"<<endl
        <<"\t6)Mostrar Indice ID"<<endl
        <<"\t7)Modificar datos de libro"<<endl
        <<"\t8)Eliminar libro"<<endl
        <<"\t9)Salir"<<endl
        <<"\tElige una opcion : ";
        getline(cin, myStr);
        if(myStr=="1"){
            system("clear");
            cout<<"\t\t\tAgregar Libro"<<endl<<endl
            <<"\tNombre : ";
            getline(cin,myStr);
            for(int i = 0;myStr[i];++i)
                myStr[i] = toupper(myStr[i]);
            libro.setNombre(myStr);
            cout<<"\tAutor : ";
            getline(cin,myStr);
            for(int i = 0;myStr[i];++i)
                myStr[i] = toupper(myStr[i]);
            libro.setAutor(myStr);
            cout<<"\tGenero : ";
            getline(cin,myStr);
            for(int i = 0;myStr[i];++i)
                myStr[i] = toupper(myStr[i]);
            libro.setGenero(myStr);
            libro.insert(tdaIndices,tdaindiceGenero, listaInvertida);
            cout<<"\tCodigo : "<<libro.getId()<<endl;
        }
        else if(myStr=="2"){
            system("clear");
            libro.print();
        }
        else if(myStr=="3"){
            system("clear");
            libro.buscarGenero(tdaIndices,tdaindiceGenero,listaInvertida);
        }
        else if(myStr=="4"){
            system("clear");
            listaInvertida.printListaInvertida(graphics);
        }
        else if(myStr=="5"){
            system("clear");
            tdaindiceGenero.printData();
        }
        else if(myStr=="6"){
            system("clear");
            tdaIndices.printData();
        }
        else if(myStr=="7"){
            system("clear");
            cout<<"\t\t\tModificar Datos  : "<<endl
            <<"ID LIBRO : ";
            getline(cin, myStr);
            try{
                libro.modify(tdaIndices, tdaindiceGenero, listaInvertida, myStr);
            }catch(invalid_argument& ex){
                system("clear");
                cerr<<ex.what()<<endl;
            }
        }
        else if(myStr=="8"){
            system("clear");
            cout<<"\t\t\tEliminar  : "<<endl
            <<"ID LIBRO : ";
            getline(cin, myStr);
            try{
                libro.remove(tdaIndices, tdaindiceGenero, listaInvertida,myStr);
            }catch(invalid_argument& ex){
                system("clear");
                cerr<<ex.what()<<endl;
            }
            cout<<"Libro eliminado"<<endl;
            cin.get();
        }
        else if(myStr=="9"){
           libro.save(tdaIndices,tdaindiceGenero,listaInvertida);
            cout<<"Adios vaquero"<<endl;
        }
        else{
            system("clear");
            cout<<"Opcion no valida"<<endl;
        }
    }while(myStr!="9");
    return 0;
}

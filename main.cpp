#include <bits/stdc++.h>
#include <conio.h>
#include <random>
#include <windows.h>
using namespace std;
void print(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
class Lista{
private:
    vector<char>lista;
    int index;
    int index_c;
    int maximo=20;
    int productos;
    int turno;

public:
    Lista(){
        for(int i=0;i<maximo;i++){
            lista.push_back('_');
        }
        index=0;
        index_c=0;
        productos=0;
    }
    int get_productos(){
        return productos;
    }
    int get_maximo(){
        return maximo;
    }
    void set_turno(int x){
        turno=x;
    }
    int get_turno(){
        return turno;
    }
    bool vacio() const{
        return (productos == 0);
    }
    void produce(int x){
        while(x>0){
            if(productos==maximo){
                break;
            }
            if(index==maximo){
                index=0;
            }
            lista[index]='#';
            index++;
            productos++;
            x--;
        }
    }
    void consume(int x){
        while(x>0){
            if(productos==0){
                break;
            }
            if(index_c==maximo){
                index_c=0;
            }
            lista[index_c]='_';
            index_c++;
            productos--;
            x--;

        }
    }
    void imprimir() {
        for (int i = 0; i < maximo; i++) {
            print(65 + (3 * i), 5);
            cout << lista[i] << " ";
            print(65 + (3 * i), 6);
            cout << i+1;
        }
        cout<<"     Hay: "<<productos;
    }
};
class Consumidor{
private:
    int a_consumir=0;
    int dormir=1;
    string estado;
public:
    Consumidor(){
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> mimir(3, 5);
        dormir=mimir(gen);
        a_consumir;
        estado="Durmiendo";
    }
    void set_consumir(int x){
        a_consumir=x;
    }
    int get_consumidor(){
        return a_consumir;
    }
    void set_dormir(int x){
        dormir=x;
    }
    int get_restante(){
        return dormir;
    }
    void reduce_dormir(){
        dormir--;
    }
    string get_estado(){
        return estado;
    }
    void set_estado(int n){
        switch (n) {
            case 0:
                estado="Consumiendo";
                break;
            case 1:
                estado="Durmiendo";
                break;
            case 2:
                estado="Entrando";
                break;


        }
    }

};
class Productor{
private:
    int a_producir=0;
    int dormir;
    string estado;
public:
    Productor(){
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> mimir(3, 5);
        a_producir;
        dormir=mimir(gen);
        estado="Durmiendo";
    }

    void set_producir(int x){
        a_producir=x;

    }
    int get_productor(){
        return a_producir;
    }
    void set_dormir(int x){
        dormir=x;
    }
    int get_restante(){
        return dormir;
    }
    void reduce_dormir(){
        dormir--;
    }
    string get_estado(){
        return estado;
    }
    void set_estado(int n){
        switch (n) {
            case 0:
                estado="Produciendo";
                break;
            case 1:
                estado="Durmiendo";
                break;
            case 2:
                estado="Entrando";
                break;

        }
    }
};void consume(Lista& buffer, Consumidor& consumidor) {
    if (buffer.vacio()) return;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribucion(4, 7);

    int n = distribucion(gen);
    consumidor.set_consumir(n);
    buffer.consume(n);

}

void produce(Lista& buffer,Productor& productor) {
    if (buffer.get_productos() >= 19) return;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribucion(4, 7);
    int n = distribucion(gen);
    productor.set_producir(n);
    (buffer.get_productos() + n >= buffer.get_maximo()-1)?(buffer.produce(buffer.get_maximo()-buffer.get_productos())):(buffer.produce(n));

}
void peticion_consumidor(Lista& lista, Consumidor& consumidor, bool& libre){
    random_device rd;
    mt19937 gen(rd());
    int min = 3, max = 5;
    uniform_int_distribution<int> distribucion(min, max);
    uniform_int_distribution<int> dormir(3, 7);
    uniform_int_distribution<int> turn(0, 1);
    consume(lista,consumidor);
    consumidor.set_dormir(dormir(gen));
    consumidor.set_estado(1);
}
void peticion_productor(Lista& lista, Productor& productor, bool& libre){
    random_device rd;
    mt19937 gen(rd());
    int min = 3, max = 5;
    uniform_int_distribution<int> distribucion(min, max);
    uniform_int_distribution<int> dormir(3, 7);
    uniform_int_distribution<int> turn(0, 1);
    produce(lista,productor);
    productor.set_dormir(dormir(gen));
    productor.set_estado(1);


}
int main() {
    system("pause");
    random_device rd;
    mt19937 gen(rd());
    int min = 3, max = 5;
    uniform_int_distribution<int> distribucion(min, max);
    uniform_int_distribution<int> dormir(5, 8);

    uniform_int_distribution<int> turn(0, 1);

    int tecla,aux=0,turno;
    bool libre=true;

    Productor productor;//1
    Consumidor consumidor;//0
    Lista lista;
    lista.set_turno(turn(gen));

    do{
        turno= turn(gen);
        if(aux==1){
            aux=0;
            libre=true;
        }
        if(productor.get_restante()!=0)productor.reduce_dormir();

        if(consumidor.get_restante()!=0)consumidor.reduce_dormir();

        if(productor.get_restante()==2){
            productor.set_estado(2);
        }
        else if(productor.get_restante()==1){
            if(productor.get_restante()==consumidor.get_restante() && turno){
                productor.set_dormir(dormir(gen));
                productor.set_estado(1);
            }else{
                productor.set_estado(0);
            }
        }
        else if(productor.get_restante()==0 && libre){
            libre=false;
            aux++;
            peticion_productor(lista,productor,libre);
        }

        if(consumidor.get_restante()==2){
            consumidor.set_estado(2);

        }
        else if(consumidor.get_restante()==1){
            if(consumidor.get_restante()==productor.get_restante() && !turno){
                consumidor.set_dormir(dormir(gen));
                consumidor.set_estado(1);
            }else{
                consumidor.set_estado(0);
            }


        }
        else if(consumidor.get_restante()==0 && libre){
            libre=false;
            aux++;
            peticion_consumidor(lista,consumidor,libre);
        }




        lista.imprimir();
        cout<<endl;

        cout<<"Estados:"<<endl;
        cout<<"Productor: "<<productor.get_estado();
        if(productor.get_estado()=="Durmiendo")cout<<" "<<productor.get_restante()-2;
        cout<<endl<<"Consumidor: "<<consumidor.get_estado();
        if(consumidor.get_estado()=="Durmiendo")cout<<" "<<consumidor.get_restante()-2<<endl;

        Sleep(1000);

        system("cls");




        if(_kbhit()){
            tecla=_getch();
            if(tecla==27) break;
        }
    }while(true);



    cout<<"Hello world"<<endl;

    return 0;
}
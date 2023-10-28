#include <bits/stdc++.h>
#include <conio.h>
#include <random>
#include <windows.h>
using namespace std;
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
            if(productos==maximo-1){
                break;
            }
            if(index==maximo-1){
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
            if(index_c==maximo-1){
                index_c=0;
            }
            lista[index_c]='_';
            index_c++;
            productos--;
            x--;

        }
    }
    void imprimir(){
        for(int i=0;i<maximo;i++){
            cout<<lista[i];
        }
    }
};
class Consumidor{
private:
    int a_consumir=0;
    int dormir=0;
    string estado;
public:
    Consumidor(){
        a_consumir;
        estado="Dormido";
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
        a_producir;
        dormir=0;
        estado="Dormido";
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
    int min = 3, max = 5;
    uniform_int_distribution<int> distribucion(min, max);
    int n = distribucion(gen);
    productor.set_producir(n);
    (buffer.get_productos() + n >= buffer.get_maximo()-1)?(buffer.produce(buffer.get_maximo()-buffer.get_productos())):(buffer.produce(n));

}
int main() {
    random_device rd;
    mt19937 gen(rd());
    int min = 3, max = 5;
    uniform_int_distribution<int> distribucion(min, max);
    uniform_int_distribution<int> turn(0, 1);

    int tecla,dormir=distribucion(gen),haciendo=3;
    bool ocupado=false;
    Productor productor;//1
    Consumidor consumidor;//0
    Lista lista;
    lista.set_turno(dormir%2);
    if(dormir%2){
        productor.set_estado(0);//Trabajando
        consumidor.set_estado(1);//Dormido
    }else{
        productor.set_estado(1);//Dormido
        consumidor.set_estado(0);//Trabajando
    }
    do{
        lista.set_turno(turn(gen));
        if(lista.get_turno()){
            produce(lista,productor);
        }
        else{
            consume(lista,consumidor);
        }
        system("cls");
        lista.imprimir();
        cout<<endl<<"Turno de: ";(lista.get_turno())?(cout<<"Productor con: "<<productor.get_productor()):(cout<<"Consumidor con: "<<consumidor.get_consumidor());
        Sleep(2000);





        if(_kbhit()){
            tecla=_getch();
            if(tecla==27) break;
        }
    }while(true);



    cout<<"Hello world"<<endl;
    int xd;
    cin >>xd;
    return 0;
}

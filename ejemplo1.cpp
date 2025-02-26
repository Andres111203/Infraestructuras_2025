#include <iostream>
#include <thread>
#include <chrono>
#include <vector> 

using namespace std;
using namespace std::chrono;


const int SIZE = 10000000;
vector<long> v(SIZE);

void fill(int start, int end){
    for(int i = start; i < end; i++){
        v[i] = i;
    }
}
//suma de los elementos del arreglo secuencial 

long suma(int inicio, int fin){
    long suma = 0;
    for(int i = inicio; i < fin; i++){
        suma += v[i];
    }
    return suma;
}



int main(){

    fill(0, SIZE);

    //secuencial
    auto start = chrono::system_clock::now();
    long sum = suma(0, SIZE);
    auto stop = chrono::system_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    printf("la duracion de sumar secuencialmente el arreglo es: %ldms\n", duration.count());
    printf("la suma del arreglo es igual a %ld\n", sum);

    //paralelizando con la libreria thread para lanzar los hilos
    auto partida = chrono::system_clock::now();
    long suma1 = 0,suma2 = 0;
    thread t1([&suma1](){suma1 = suma(0, SIZE/2);});
    thread t2([&suma2](){suma2 = suma(SIZE / 2, SIZE);});

    t1.join();
    t2.join();
    auto llega = chrono::system_clock::now();
    auto dur = duration_cast<milliseconds>(llega - partida);
    printf("el resultado de la suma con dos hilos es: %ld\n", suma1 + suma2);
    printf("el tiempo de realizar la suma en dos partes del arreglo paralelo es: %ldms\n", dur);


}
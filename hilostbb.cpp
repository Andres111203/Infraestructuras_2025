#include <iostream>
#include <chrono>
#include <tbb/blocked_range.h>
#include <tbb/parallel_for.h>
#include <tbb/parallel_reduce.h>
#include <vector>

using namespace std;
using namespace std::chrono;

const long SIZE = 10000000;
vector<long long> v(SIZE);

void fill_tbb(int start, int end){
    tbb::parallel_for(tbb::blocked_range<int>(start, end), [&](tbb::blocked_range<int>r){
        for(int i = r.begin(); i < r.end(); i++){
            v[i] = i;
        }
    });
}

void suma_tbb(int start, int end, long &sum){ //sum es la que va a devolver la suma total de todos los elementos del arreglo cuando los hilos se unen 
    sum = tbb::parallel_reduce(tbb::blocked_range<int>(start, end), 0L, [&](tbb::blocked_range<int>r, long init){
        long sum = init; //suma parcial de los elementos del rengo de cada hilo, diferente a la pasada por referencia
        for(int i = r.begin(); i < r.end(); i++){
            sum += v[i];
        }
        return sum;
    }, std::plus<long>()); 
    
}

int main(){
    fill_tbb(0, SIZE);
    auto inicio = chrono::system_clock::now();
    long sum = 0;
    suma_tbb(0, SIZE, ref(sum));
    auto fin = chrono::system_clock::now();
    auto duration = duration_cast<milliseconds>(fin - inicio);
    printf("la suma paralela es: %ld\n", sum);
    printf("la duracion de la suma paralela es: %ldms\n", duration.count());

}



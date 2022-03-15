#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <time.h>

#define CLOCKS_PER_MS (CLOCKS_PER_SEC / 1000)


using namespace std;

const int N = 50000000;

int main(){
    srand(time(NULL));
    vector<string> keys(N);
    vector<int> values(N);

    for(int i=0;i<N;i++){
        string k = to_string(rand()%10000000);
        keys.push_back(k);
        values.push_back(i);
    }

    double ms=0,is=0;
    unordered_map<string,int> umap;
    map<string,int> omap;

    clock_t x = clock();
    for(int j=0;j<N;j++) umap[keys[j]] = values[j];
    clock_t y = clock();

    for(int j=0;j<N;j++) omap[keys[j]] = values[j];
    clock_t z = clock();

    ms += (y-x)/(double) CLOCKS_PER_MS;
    is += (z-y)/(double) CLOCKS_PER_MS;


    /*unordered_map<int,int> umap;
    map<int,int> omap;
    for(int i=0;i<N;i++){
        int k = rand()%10000000;
        umap[k] = k*2+1;
        omap[k] = k*2+1;
    }



    clock_t x = clock();
    for(int j=0;j<N;j++){
        int k = rand()%10000000;
        umap.find(k);
    }
    clock_t y = clock();

    for(int j=0;j<N;j++){
        int k = rand()%10000000;
        omap.find(k);
    }
    clock_t z = clock();

    double ms=0,is=0;
    ms = (y-x)/(double) CLOCKS_PER_MS;
    is = (z-y)/(double) CLOCKS_PER_MS;*/



    cout<<ms<<","<<is<<endl;


}


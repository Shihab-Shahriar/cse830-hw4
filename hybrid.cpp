#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

#define CLOCKS_PER_MS (CLOCKS_PER_SEC / 1000)

using namespace std;

int N = 1000000;
int* buffer;


void isort(int* arr, int sz){
	for (int i=0;i<sz;i++){
		int current=arr[i];
		int k=i;
		while (k>0 and current<arr[k-1]){
			arr[k]=arr[k-1];
			k--;
		}
		arr[k]=current;
    }
}


void tsort(int* arr,int* finish,int* buffer, int k){
	if(finish-arr<=k) {
        isort(arr, finish-arr);
        return;
	}

	int* mid = arr+(finish-arr)/2;
	tsort(arr,mid,buffer, k);
	tsort(mid,finish,buffer, k);

	//merge both sorted sides
	int* l = arr,*r = mid;
	int* temp = buffer;
	while(true){
		if(*r<*l) {*temp++ = *r++;}
		else {*temp++ = *l++;}
		if(l==mid or r==finish) break;
	}
	while(l!=mid) *temp++ = *l++;
	while(r!=finish) *temp++ = *r++;
	while(arr!=finish) *arr++ = *buffer++; //Copy back to original array
}




bool assert(int* arr, int* sorted){
    for (int i = 0; i < N; ++i){
            if(arr[i]!=sorted[i]) return false;
    }
    return true;
}

void init(int* arr, int* arr3){
    for(int i=0;i<N;i++) {
        arr[i] = rand()%10000000;
        arr3[i]=arr[i];
    }
}

int main(){
	srand(time(NULL));
	int* arr = new int[N];
	int* arr3 = new int[N]; // to check correctness
	buffer = new int[N];

	const int KN = 8;
    int ks[KN] = {10, 20,50, 75, 100, 250, 500, 1000};
    for(int i=0;i<KN;i++){
        init(arr, arr3);

        clock_t x = clock();
        tsort(arr,arr+N,buffer, ks[i]);
        clock_t y = clock();

        sort(arr3,arr3+N);
        if(!assert(arr, arr3)) printf("Trouble with TIM sort");

        auto tt = (y-x)/(double) CLOCKS_PER_MS;

        cout<<tt<<", ";
    }
    cout<<endl;
	return 0;
}


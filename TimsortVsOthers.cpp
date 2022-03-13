#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

#define CLOCKS_PER_MS (CLOCKS_PER_SEC / 1000)

using namespace std;

int N = 5000;
int* buffer;

void msort(int* arr,int* finish,int* buffer){
	if(finish-arr<=1) return ;
	int* mid = arr+(finish-arr)/2;
	msort(arr,mid,buffer);
	msort(mid,finish,buffer);

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

void isort(int* arr, int sz=-1){
    if (sz==-1) sz = N;

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

void init(int* arr, int* arr2, int* arr3){
    for(int i=0;i<N;i++) {
        arr[i] = rand()%10000000;
        arr2[i]=arr[i];
        arr3[i]=arr[i];
    }
}

int main(){
	srand(time(NULL));
	int* arr = new int[N];
	int* arr2 = new int[N];
	int* arr3 = new int[N]; // to check correctness
	buffer = new int[N];


    double ms=0,is=0;
    int loops=100;
    for(int i=0;i<loops;i++){
        init(arr, arr2, arr3);

        clock_t x = clock();
        isort(arr,N);
        clock_t y = clock();
        tsort(arr2, arr2+N,buffer,50);
        clock_t z = clock();

        ms += (y-x)/(double) CLOCKS_PER_MS;
        is += (z-y)/(double) CLOCKS_PER_MS;
    }
    ms /= loops;
    is /= loops;

	sort(arr3,arr3+N);
	if(!assert(arr, arr3)) printf("Trouble with Merge sort");
    if(!assert(arr2, arr3)) printf("Trouble with Insertion sort");

	cout<<ms<<","<<is<<endl;

	return 0;
}


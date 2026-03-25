#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
	static const int N=10;
	double arr[N]={5.5,-3.48,-1.2345,1.1,2.2,10.01,3.3,5.5,6.6,4.4};
	
	//inizializzo min, max e somma
	double min_val=arr[0];
	double max_val=arr[0];
	double sum=arr[0];

	// calcolo
	for (int i=1;i<N;i++){
		min_val=min(min_val,arr[i]);
		max_val=max(max_val,arr[i]);
		sum+=arr[i];
	}
	double avr=sum/N;

	// deviazione standard
	double numeratore=0.0;
	for (int i=0;i<N;i++) {
		numeratore+= (arr[i]-avr)*(arr[i]-avr);
	}
	double dev_st=sqrt(numeratore/N);

	// stampa
	cout << "Minimo: " << min_val << "\n";
	cout << "Massimo: " << max_val << "\n";
	cout << "Media: " << avr << "\n";
	cout << "Deviazione standard: " << dev_st <<"\n";


	//BUBBLESORT
	bool swap=true;
	while (swap){
		swap=false; //reset altrimenti loop
		for (int i=0; i<N-1; i++) { //i<N-1 altrimenti outofrange
			if (arr[i]>arr[i+1]) {
				double prec= arr[i]; //salvo il valore arr[i] altrimenti viene perso
				arr[i]=arr[i+1];
				arr[i+1]=prec;
				swap=true; //se è avvenuto lo scambio
			}
		}
	}
	//cout << arr << "\n"; stampa indirizzo array
	cout << "Array ordinato: ";
	for (int i=0;i<N;i++){
		cout << arr[i]<<" ";
	}
	cout <<"\n";

	
	return 0;
}

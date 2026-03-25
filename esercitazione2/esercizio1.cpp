#include <iostream>

int main(){
	double ad[4]={0.0,1.1,2.2,3.3};
	float af[8]={0.0,1.1,2.2,3.3,4.4,5.5,6.6,7.7};
	int ai[3]={0,1,2};

	int x=1;
	float y=1.1;

	(&y)[1]=0;
	std::cout << x << "\n";
	std::cout << "\n";
	for (int i=0; i<=3; i++) {
		std::cout << "ad["<<i<<"]: "<<&ad[i] << "\n";
	}
	std::cout << "\n";

	for (int i=0;i<=7;i++){
		std::cout <<"af["<<i<<"]: "<< &af[i] << "\n";
	}
	std::cout << "\n";

	for (int i=0;i<=2;i++){
		std::cout << "ai["<<i<<"]: "<< &ai[i] << "\n";
	}
	std::cout << "\n";

	std::cout << &x << "\n";
	std::cout << &y << "\n";

	return 0;
}

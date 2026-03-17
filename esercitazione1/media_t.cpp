#include <fstream>
#include <iostream>

using namespace std;

int main(int argc,char*argv[])
{
   if (argc<2) {
	   cerr << "Errore: specificare il nome del file\n";
	   return 1;
   }
  
   string nomeFile=argv[1];
  
   ifstream ifs(nomeFile);
   if (!ifs.is_open()) {
	   cerr<<"Errore nell'apertura del file "<<nomeFile<<"\n";
	   return 1;
   }
   for (int riga=0;riga<3;riga++) {
		   string location;
		   double temp1;
		   double temp2;
		   double temp3;
		   double temp4;

		   ifs >> location >> temp1 >> temp2 >> temp3 >> temp4;
		   double media_temp=(temp1+temp2+temp3+temp4)/4;

		   cout<<location<<" "<<media_temp<<"\n";
   }
   return 0;
}

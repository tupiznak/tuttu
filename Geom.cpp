#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

void CreateArr(int N,int *&mas)
{
    srand(time(0));
    for(int i=0;i<N;i++)
        mas[i]=rand()%10-5;
}


int main()
{
   cout << "Enter size of Massive" << endl; 
   
   int N;
   cin>>N;
   int *mas = new int[N];
   
   CreateArr(N,mas);
   
   for(int i=0;i<N;i++)
    cout<<mas[i]<<"\t";
   
   delete []mas;
   return 0;
}


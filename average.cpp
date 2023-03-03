#include <iostream>
#include <cstdlib>
using namespace std;

int main(int argc,char* argv[]){
    int sum=0;
    for(int i=1;i<argc;i++)
    {
        sum+=atoi(argv[i]);
    }
    float N=argc-1;
    float result=sum/N;
    if(result >0)
    {
        cout<<"---------------------------------"<<endl;
        cout<<"Average of "<<N<<" numbers = "<<result<<endl;
        cout<<"---------------------------------"<<endl;
    }
    else
        cout<<"Please input numbers to find average.";
}
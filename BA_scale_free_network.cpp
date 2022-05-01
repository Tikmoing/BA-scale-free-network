#include<iostream>
#include<cmath>
#include<ctime>
#include <bits/stdc++.h> 
#include<fstream>

using namespace std;

#define max(A,B) ( A > B ? A : B)
#define LENGTH 1000002
//A random number 
class RandomAES{
    private:
        // unsigned long long MNWZ = 0x100000000;
        // unsigned long long ANWZ = 0x5DEECE66D;
        // unsigned long long CNWZ = 0xB16;
        const unsigned long long MNWZ = 0x100000000;
        const unsigned long long ANWZ = 0x5DEECE66D;
        const unsigned long long CNWZ = 0xB16;
        unsigned long long seed = time(NULL);
        double drand48(void){
            seed = (ANWZ * seed + CNWZ) & 0xFFFFFFFFFFFFLL;
            unsigned int x = seed >> 16;
            return ((double)x / (double)MNWZ);
        }
        void srand48(unsigned int i){
            seed = (((long long int)i) << 16) | rand();
        }
    public:
        double random(){
            double res = drand48();
            srand48( (int ) (res * 11104  + res / 100));
            return res;
        }

        int randbinary(){
            double rand = random();
            return rand >= 0.5 ? 1 : 0;
        }

        int randint(int start , int end){
            return (int) (random() * (end - start)) + start;
        }
};

RandomAES rm;

int maxVector(int* input){
    int res = -1;
    for(int i = 0 ; i < LENGTH ; i ++) res = max(res,input[i]);
    return res;
}

int main(void){
    // unsigned short int nodes[LENGTH];
    int* nodes = new int[LENGTH];
    nodes[0] = nodes[1] = 1;
    int length = 2; //number of nodes
    int alldegree = 2; // sum degree
    
    for(int i = 0 ; i < 1000000 ;i ++){
        if(i % 10000 == 0) cout<<i<<endl;
        int tempdegree = 0; //A New Node
        for(int j = 0 ; j < length ; j ++){
            double p = 1.0 * nodes[j] / alldegree; //p
            if( rm.random() < p ){
                alldegree += 2;
                nodes[j] += 1;
                tempdegree += 1;
            }
        }
        if( tempdegree == 0 ) continue;
        nodes[length] =  tempdegree ;
        length ++;
    }

    //analysis
    int k_max = 0;
    for(int i =0 ; i < length ; i ++) k_max = k_max > nodes[i] ? k_max : nodes[i];
    vector<int> k(k_max,0);
    for(int i = 0 ; i < k.size() ; i ++) k[i] = i+1;
    vector<int> p(k_max,0);
    for(int i = 0 ; i < length ; i ++) p[ nodes[i] - 1 ] ++;

    //free the space
    delete[] nodes;

    //output in the terminal
    for(int i = 0 ; i < k.size() ; i ++){
        cout<<k[i] << " " <<p[i] <<endl;
    }

    //write to the file
    ofstream outfile;
    outfile.open("data.csv");
    for(int i = 0 ; i < k.size() ; i ++){
        outfile<<k[i] << "," <<p[i] <<endl;
    }
    outfile.close();
    return 0;
}
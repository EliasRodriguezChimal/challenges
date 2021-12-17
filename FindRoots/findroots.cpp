//Creado por Elias Rodriguez Chimal

#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    vector <float> raices;
    vector <int> firstRow;
    vector <int> secRow;

    for(int index = 2; index<argc; index++){
        firstRow.push_back(atoi(argv[index]));
    }
    secRow.push_back(firstRow[0]);

    bool answer = false;
    int i=0, aux=0;

    for(int n=argc-1; n>1; n--){
        if(atoi(argv[n])!=0){
            i = -(abs(atoi(argv[n])));
            aux = abs(atoi(argv[n]));
            break;
        }
    }

    if(atoi(argv[5])==0){
        raices.push_back(float(0));
    }
    
    for(;i<=aux && answer==false;i++){
        if(firstRow.back() == 0){
            firstRow.erase(firstRow.end()-1);
        }
        if(i!=0 && firstRow.back()%i==0){
            for(size_t j = 1; j<firstRow.size(); j++){
                secRow.push_back((i*secRow[j-1]) + firstRow[j]);
            }
            if(secRow.back() == 0){
                raices.push_back(float(i));
                if(raices.size() < 2){
                    firstRow.erase(firstRow.begin()+1, firstRow.end());
                    for(size_t j = 1; j<secRow.size(); j++){
                        firstRow.push_back(secRow[j]);
                    }
                    secRow.erase(secRow.begin()+1, secRow.end());
                }else{
                    raices.push_back(((-1.0f)*float(secRow[1]))/float(secRow[0]));
                    answer=true;
                }
            }else{
                secRow.erase(secRow.begin()+1, secRow.end());
            }
        }
    }

    cout << "{";
    for(size_t k = 0; k < raices.size(); k++){
        if(k == raices.size()-1){
            cout << raices[k];
        }else{
            cout << raices[k] << ", ";
        }
    }
    cout << "}";

    return 0;
} 
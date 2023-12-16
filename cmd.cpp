#ifndef CMD_CPP
#define CMD_CPP
#include <iostream>
#include <vector>
#include <string.h>
#include <utility>

using namespace std;

vector<pair<string,int>> load;
vector<pair<string,int>> unload;
// vecPair.push_back(std::make_pair(string,int));
//access elements vec[n].first || vec[n].second

void get_loads(string v, int n){
    load.push_back(make_pair(v, n));
}
void get_unloads(string v, int n){
    unload.push_back(make_pair(v, n));
}

void delete_unloads(string v, int n){
    for(int i = 0; i < unload.size(); i++){
        cout << "Vector (" << unload[i].first << "," << unload[i].second <<")"<< endl;
    }
    for(int i = 0; i < unload.size(); i++){
        if(unload[i].first == v && unload[i].second == n){
            unload.erase(unload.begin()+i);
            i = unload.size();
        }
    }
    cout << "NEW UNLOAD REQUESTS!!!" << endl;
    for(int i = 0; i < unload.size(); i++){
        cout << "Vector (" << unload[i].first << "," << unload[i].second <<")"<< endl;
    }
}

void clear_load(){
    load.clear();
}
void clear_unload(){
    unload.clear();
}
#endif
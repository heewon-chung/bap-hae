#include "generalTools.h"

void generateMsgAndTag(vector<int>& msg, vector<int>& tag, int num){
    msg.clear(); tag.clear();
    
    for(unsigned long i = 0; i < num; i++){
        msg.push_back(rand() % 2);
        tag.push_back(rand() % 10);
    }
}
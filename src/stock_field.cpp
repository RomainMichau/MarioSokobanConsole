#include "stock_field.h"
#include <vector>
#include <unordered_map>

stock_field::stock_field(){
}

stock_field::~stock_field(){
}

void stock_field::push_back(std::vector<unsigned char> field){
    fieldList.insert({fieldToString(field),1});
}

std::string stock_field::fieldToString(std::vector<unsigned char> field){
std::string res="";
for(int i=0;i<field.size();i++){
res+=field[i];
}
return res;
}

bool stock_field::exist(std::vector<unsigned char> field){
    if (fieldList.count(fieldToString(field)) > 0)
{
	return true;
}
return false;
}

void stock_field::resize(int a){
fieldList.clear();
}

int stock_field::size()
{
    return fieldList.size();
}


#ifndef STOCK_FIELD_H_INCLUDED
#define STOCK_FIELD_H_INCLUDED
#include <unordered_map>
#include <vector>

class stock_field{
    public:
        stock_field();
        virtual ~stock_field();
        void push_back(std::vector<unsigned char> field);
        bool exist(std::vector<unsigned char> field);
        void resize(int a);
        int size();

    private:
        std::unordered_map<std::string,int> fieldList;
        std::string fieldToString(std::vector<unsigned char> field);

};

#endif // STOCK_FIELD_H_INCLUDED

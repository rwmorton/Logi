#pragma once

#include <iostream>
#include <initializer_list>
#include <memory>
#include <algorithm>
#include <cassert>
using namespace std;

namespace Logi
{

void makeBC_01()
{
    ofstream out("BC_01.RUN",ios::binary|ios::out);
}

void makeRandomBytecodeFile()
{
    std::ofstream out("random.RUN",std::ios::binary|std::ios::out);
    Logi::U2 magic = 0xDEED;
    Logi::U8 symbolTableSize = 16;
    Logi::U8 stringTableSize = 64;
    Logi::U8 bytecodeSize = 1024;

    out.write((const char*)&magic,sizeof(Logi::U2));
    out.write((const char*)&symbolTableSize,sizeof(Logi::U8));
    out.write((const char*)&stringTableSize,sizeof(Logi::U8));
    out.write((const char*)&bytecodeSize,sizeof(Logi::U8));
    
    //write random bytes
    Logi::U1 byte{};
    for(int i=0; i<bytecodeSize; i++)
    {
        out.put(std::rand() % 255);
    }
    out.close();
}

class vector
{
        public:
        vector() : my_size{0},data{nullptr} {}
        vector(std::initializer_list<double> values) : my_size{values.size()},data{new double [my_size]}
        {
            std::cout << "initializer list constructor" << std::endl;
            std::copy(begin(values),end(values),data);
        }
        vector(vector&& v) noexcept : my_size(v.my_size),data{v.data}
        {
            std::cout << "move constructor" << std::endl;
            v.data = nullptr;
            v.my_size = 0;
        }
        ~vector()
        {
            if(data != nullptr) delete[] data;
            std::cout << "vector destructor called" << std::endl;
        }
        vector& operator=(std::initializer_list<double> values)
        {
            std::cout << "operator= called" << std::endl;
            assert(my_size == values.size());
            std::copy(begin(values),end(values),data);
            return *this;
        }
        vector& operator=(vector&& src) noexcept
        {
            std::cout << "move operator= called" << std::endl;
            assert(my_size == 0 || my_size == src.my_size);
            std::swap(data,src.data);
            std::swap(my_size,src.my_size);
            return *this;
        }
        friend std::ostream& operator<<(std::ostream& out,const vector& v)
        {
            if(v.data != nullptr)
            {
                for(int i=0; i<v.my_size; i++) out << v.data[i] << ' ';
            }
            return out;
        }
    private:
        long unsigned int my_size;
        //std::unique_ptr<double> data;
        double* data;
        //std::unique_ptr<double> data;
};

vector move_f()
{
    vector my_vector {3,6,9};
    return my_vector;
}

} //namespace Logi

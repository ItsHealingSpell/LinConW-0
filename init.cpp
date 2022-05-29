#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>
int main()
{
    srand(time(NULL));
    freopen("robot_1/Weights_0.mld","w",stdout);
    for(int i=0;i<1024;++i)
    {
        for(int j=0;j<1024;++j)
        {
            std::cout<<((long double)rand())*(long double)rand()/1073741824<<" ";
        }
        std::cout<<std::endl;
    }
    freopen("robot_1/Weights_1.mld","w",stdout);
    for(int i=0;i<1024;++i)
    {
        for(int j=0;j<1024;++j)
        {
            std::cout<<((long double)rand())*(long double)rand()/1073741824<<" ";
        }
        std::cout<<std::endl;
    }
    freopen("robot_1/Weights_2.mld","w",stdout);
    for(int i=0;i<1024;++i)
    {
        for(int j=0;j<1024;++j)
        {
            std::cout<<((long double)rand())*(long double)rand()/1073741824<<" ";
        }
        std::cout<<std::endl;
    }
    freopen("robot_1/Weights_3.mld","w",stdout);
    for(int i=0;i<10;++i)
    {
        for(int j=0;j<1024;++j)
        {
            std::cout<<((long double)rand())*(long double)rand()/1073741824<<" ";
        }
        std::cout<<std::endl;
    }
    freopen("robot_1/Biases_1.mld","w",stdout);
    for(int i=0;i<1024;++i)
    {
        std::cout<<((long double)rand())*(long double)rand()/1073741824<<std::endl;
    }
    freopen("robot_1/Biases_2.mld","w",stdout);
    for(int i=0;i<1024;++i)
    {
        std::cout<<((long double)rand())*(long double)rand()/1073741824<<std::endl;
    }
    freopen("robot_1/Biases_3.mld","w",stdout);
    for(int i=0;i<1024;++i)
    {
        std::cout<<((long double)rand())*(long double)rand()/1073741824<<std::endl;
    }
    freopen("robot_1/Biases_4.mld","w",stdout);
    for(int i=0;i<10;++i)
    {
        std::cout<<((long double)rand())*(long double)rand()/1073741824<<std::endl;
    }
}

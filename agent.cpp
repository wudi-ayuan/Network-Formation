//
//  agent.cpp
//  Network_Fromation
//
//  Created by David Lai on 6/22/16.
//  Copyright © 2016 Paul Lai. All rights reserved.
//

#include "agent.hpp"
#include <cstdlib>
#include <random>
using namespace std;
default_random_engine generator(2016);
double number;


inline void agent::settype()
{
    int rnd;
    const float p=0.7;
    rnd=(rand()%100);
    if(rnd<(p*100))
        type='h';
    else
        type='l';
}
inline void agent::setprisignal(int i)
{
    if(type=='h'){
        exponential_distribution<double> distribution(3.5);
        for (int j=0;j<i;j++){
            number=distribution(generator);
            signal.push_back(number);
            
            pribliflik.push_back(2.5/3.5*exp(1*number));

        }
    }
    else if(type=='l'){
        exponential_distribution<double> distribution(2.5);
        for (int j=0;j<i;j++){
            number=distribution(generator);
            signal.push_back(number);
            
            pribliflik.push_back(2.5/3.5*exp(1*number));

        }
        
    }
    
}

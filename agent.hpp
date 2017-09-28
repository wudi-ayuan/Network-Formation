//
//  agent.hpp
//  Network_Fromation
//
//  Created by David Lai on 6/22/16.
//  Copyright © 2016 Paul Lai. All rights reserved.
//

#ifndef agent_hpp
#define agent_hpp

#include <cstdlib>
#include <random>
#include <ctime>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <vector>
using namespace std;

struct agent{
    char type;
    vector<float> signal;
    vector<float> priblif;
    vector<float> pribliflik;
    int action=-1;
    
    void setprisignal(int,vector<agent>);
    void settype(float);
    
};
float number;
float lambdaH=1;
float lambdaL=-1;
float standard_dev=0.1;
//int seed=rand();
default_random_engine generator;



inline void agent::settype(float p)
{
    int rnd;
    rnd=(rand()%100);
    if(rnd<(p*100))
        type='h';
    else
        type='l';
}
inline void agent::setprisignal(int i,vector<agent> agentlist)
{


    normal_distribution<double> distributionL(lambdaL, standard_dev);
    normal_distribution<double> distributionH(lambdaH, standard_dev);
    for (int j=0;j<i;j++){
        if (agentlist[j].type=='h'){
                number=distributionH(generator);
                signal.push_back(number);
                
                //pribliflik.push_back(lambdaL/lambdaH*exp((-lambdaL+lambdaH)*numberA));
            pribliflik.push_back(exp(-(2*number-lambdaH-lambdaL)*(lambdaL-lambdaH)/(2*pow(standard_dev,2))));

        }
        else if (agentlist[j].type=='l'){

            number=distributionL(generator);
            signal.push_back(number);
            
            pribliflik.push_back(exp(-(2*number-lambdaH-lambdaL)*(lambdaL-lambdaH)/(2*pow(standard_dev,2))));
        }
        
    }
    
        
    
    
}

#endif /* agent_hpp */

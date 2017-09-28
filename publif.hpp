//
//  publif.hpp
//  Network_Fromation
//
//  Created by David Lai on 6/22/16.
//  Copyright © 2016 Paul Lai. All rights reserved.
//

#ifndef publif_hpp
#define publif_hpp
#include <cmath>
#include <stdio.h>
#include <vector>
#include "agent.hpp"
using namespace std;

float numberA=0;
float numberP=0;

int trialNum=1000;


//float lambdaH=3.5;
//float lambdaL=2.5;
float threshold=exp(-(lambdaL-lambdaH)*(2*(lambdaH-lambdaL+6*standard_dev))/(2*pow(standard_dev, 2)));

struct publif{
    vector<float> belieflik;
    
    void updatebel(int,vector<agent>);
    
};

double normalCDF(double value)
{
    return 0.5 * erfc(-value * M_SQRT1_2);
}

inline void publif::updatebel(int choice, vector<agent> agentlist){
    srand(static_cast<unsigned int>(time(NULL)));
    default_random_engine generator(rand());
    for(int k=0;k<belieflik.size();k++){
        if(belieflik[k]>*max_element(belieflik.begin(),belieflik.end())/threshold){//only when the public belief is big enough to take max's place.
        vector<float> z_signal(trialNum);
        vector<float> Rupdate(trialNum,1);
        vector<float> DupdateH(trialNum,1);
        vector<float> DupdateL(trialNum,1);
        vector<float> Dupdate(trialNum,1);
        if (k==choice){
            normal_distribution<double> distributionH(lambdaH); //should I decalre it everytime?
            normal_distribution<double> distributionL(lambdaL);
            for(int k_pr=0;k_pr<belieflik.size();k_pr++){
                if(k_pr!=k){
                    if (agentlist[k_pr].type=='h'){
                        for(int trial=0;trial<trialNum;trial++){
                            numberA=distributionH(generator);
                            numberP=exp(-(2*numberA-lambdaH-lambdaL)*(lambdaL-lambdaH)/(2*pow(standard_dev,2)));
                            numberP=numberP*belieflik[k_pr]/belieflik[k];
                            numberP=(-(2*pow(standard_dev,2))*log(numberP)/(lambdaL-lambdaH)+(lambdaH+lambdaL))/2;
                            z_signal[trial]=(numberP);
                        }
                    }
                    else if (agentlist[k_pr].type=='l'){
                        for(int trial=0;trial<trialNum;trial++){
                            numberA=distributionL(generator);
                            numberP=exp(-(2*numberA-lambdaH-lambdaL)*(lambdaL-lambdaH)/(2*pow(standard_dev,2)));
                            numberP=numberP*belieflik[k_pr]/belieflik[k];
                            numberP=(-(2*pow(standard_dev,2))*log(numberP)/(lambdaL-lambdaH)+(lambdaH+lambdaL))/2;
                            z_signal[trial]=(numberP);                                                }
                    }
                    //mutiply each term
                    for (int Find=0;Find<trialNum;Find++){
                        double FHZ_1=1-normalCDF((z_signal[Find]-lambdaH)/(standard_dev*sqrt(2.0)));
                        double FLZ_1=1-normalCDF((z_signal[Find]-lambdaL)/(standard_dev*sqrt(2.0)));
                        if(FLZ_1==0) FLZ_1=0.000001;
                        if(FHZ_1==0) FHZ_1=0.000001;
                        Rupdate[Find]=Rupdate[Find]*(FHZ_1)/(FLZ_1);
                    }
                    
                    
                }
            }
            float R=0;
            
            for (int i=0;i<Rupdate.size();i++){
                R+=Rupdate[i];
                }
            R=R/Rupdate.size();
            cout<<"R is "<<R<<endl;
            if(R<1){
                cout<<"R is wrong.";
            }
            belieflik[k]=belieflik[k]*R;
            
        }
        else{
            normal_distribution<double> distributionH(lambdaH); //should I decalre it everytime?
            normal_distribution<double> distributionL(lambdaL);
            for(int k_pr=0;k_pr<belieflik.size();k_pr++){
                if(k_pr!=k){
                    if (agentlist[k_pr].type=='h'){
                        for(int trial=0;trial<trialNum;trial++){
                            numberA=distributionH(generator);
                            numberP=exp(-(2*numberA-lambdaH-lambdaL)*(lambdaL-lambdaH)/(2*pow(standard_dev,2)));
                            numberP=numberP*belieflik[k_pr]/belieflik[k];
                            numberP=(-(2*pow(standard_dev,2))*log(numberP)/(lambdaL-lambdaH)+(lambdaH+lambdaL))/2;
                            z_signal[trial]=(numberP);
                        }
                    }
                    else if (agentlist[k_pr].type=='l'){
                        for(int trial=0;trial<trialNum;trial++){
                            numberA=distributionL(generator);

                            numberP=exp(-(2*numberA-lambdaH-lambdaL)*(lambdaL-lambdaH)/(2*pow(standard_dev,2)));
                            numberP=numberP*belieflik[k_pr]/belieflik[k];
                            numberP=(-(2*pow(standard_dev,2))*log(numberP)/(lambdaL-lambdaH)+(lambdaH+lambdaL))/2;
                            z_signal[trial]=(numberP);                                                }
                    }
                    //mutiply each term
                    for (int Find=0;Find<trialNum;Find++){
                        double FHZ_1=1-normalCDF((z_signal[Find]-lambdaH)/(standard_dev*sqrt(2.0)));
                        double FLZ_1=1-normalCDF((z_signal[Find]-lambdaL)/(standard_dev*sqrt(2.0)));
                        DupdateH[Find]=DupdateH[Find]*(FHZ_1);
                        DupdateL[Find]=DupdateL[Find]*(FLZ_1);
                        if(FHZ_1<FLZ_1){
                            cout<<"error: "<<FHZ_1<<" < "<<FLZ_1;
                        }
                    }
                    
                    
                    
                }
            }
            float D=0;
            
            for (int i=0;i<DupdateH.size();i++){
                D+=(1-DupdateH[i])/(1-DupdateL[i])/DupdateH.size();
            }
            if(D>1){
                cout<<"D is wrong: "<<D<<endl;
            }
            belieflik[k]=belieflik[k]*D;
            
        }
    }
    }
}


#endif /* publif_hpp */

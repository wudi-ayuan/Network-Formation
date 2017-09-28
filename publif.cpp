//
//  publif.cpp
//  Network_Fromation
//
//  Created by David Lai on 6/22/16.
//  Copyright © 2016 Paul Lai. All rights reserved.
//

#include <cstdlib>
#include <random>
#include <vector>
#include "publif.hpp"

using namespace std;
default_random_engine generator(2016);
float number;
float numberP;

int trialNum=1000;
vector<float> z_signal(trialNum);
float lambdaH=3.5;
float lambdaL=2.5;
vector<float> Rupdate(trialNum,1);
vector<float> DupdateH(trialNum,1);
vector<float> DupdateL(trialNum,1);
vector<float> Dupdate(trialNum,1);


inline void publif::updatebel(int choice, vector<agent> agentlist){
    for(int k=0;k<belieflik.size();k++){
        if (k==choice){
            exponential_distribution<double> distributionH(lambdaH); //should I decalre it everytime?
            exponential_distribution<double> distributionL(lambdaL);
            for(int k_pr=0;k_pr<sizeof(publif);k_pr++){
                if(k_pr!=k){
            if (agentlist[k_pr].type=='h'){
            for(int trial=0;trial<trialNum;trial++){
                number=distributionH(generator);
                numberP=lambdaH/lambdaL*exp((-lambdaH+lambdaL)*number);
                numberP=numberP*belieflik[k_pr]/belieflik[k];
                numberP=log(numberP*lambdaL/lambdaH)/(-lambdaH+lambdaL);
                z_signal[trial]=(numberP);
                                                }
                                            }
            else if (agentlist[k_pr].type=='l'){
            for(int trial=0;trial<trialNum;trial++){
                number=distributionL(generator);
                numberP=lambdaH/lambdaL*exp((-lambdaH+lambdaL)*number);
                numberP=numberP*belieflik[k_pr]/belieflik[k];
                numberP=log(numberP*lambdaL/lambdaH)/(-lambdaH+lambdaL);
                z_signal[trial]=(numberP);                                                }
                                                }
                 //mutiply each term
                    for (int Find=0;Find<trialNum;Find++){
                        float FHZ_1=exp(-lambdaH*z_signal[Find]);
                        float FLZ_1=exp(-lambdaL*z_signal[Find]);
                        Rupdate[Find]=Rupdate[Find]*(FHZ_1)/(FLZ_1);
                    }
                    
                    
                }
            }
            float R;
            
            for (int i=0;i<Rupdate.size();i++){
                R+=Rupdate[i];
            }
            R=R/Rupdate.size();
            belieflik[k]=belieflik[k]*R;

        }
        else{
            exponential_distribution<double> distributionH(lambdaH); //should I decalre it everytime?
            exponential_distribution<double> distributionL(lambdaL);
            for(int k_pr=0;k_pr<sizeof(publif);k_pr++){
                if(k_pr!=k){
                    if (agentlist[k_pr].type=='h'){
                        for(int trial=0;trial<trialNum;trial++){
                            number=distributionH(generator);
                            numberP=lambdaH/lambdaL*exp((-lambdaH+lambdaL)*number);
                            numberP=numberP*belieflik[k_pr]/belieflik[k];
                            numberP=log(numberP*lambdaL/lambdaH)/(-lambdaH+lambdaL);
                            z_signal[trial]=(numberP);
                        }
                    }
                    else if (agentlist[k_pr].type=='l'){
                        for(int trial=0;trial<trialNum;trial++){
                            number=distributionL(generator);
                            numberP=lambdaH/lambdaL*exp((-lambdaH+lambdaL)*number);
                            numberP=numberP*belieflik[k_pr]/belieflik[k];
                            numberP=log(numberP*lambdaL/lambdaH)/(-lambdaH+lambdaL);
                            z_signal[trial]=(numberP);                                                }
                    }
                    //mutiply each term
                    for (int Find=0;Find<trialNum;Find++){
                        float FHZ_1=exp(-lambdaH*z_signal[Find]);
                        float FLZ_1=exp(-lambdaL*z_signal[Find]);
                        DupdateH[Find]=DupdateH[Find]*(FHZ_1);
                        DupdateL[Find]=DupdateL[Find]*(FLZ_1);
                    }
                    

                    
                }
            }
            float D;
            
            for (int i=0;i<DupdateH.size();i++){
                D+=(1-DupdateH[i])/(1-DupdateL[i]);
            }
            D=D/DupdateH.size();
            belieflik[k]=belieflik[k]*D;
            
        }
    }
}


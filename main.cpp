//
//  main.cpp
//  Network_Fromation
//
//  Created by David Lai on 6/9/16.
//  Copyright © 2016 Paul Lai. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <random>
#include "agent.hpp"
#include "publif.hpp"
#include <string>
#include <fstream>
using namespace std;




int main()
{


    ofstream myfile[2];
    string name[]={"/Users/davidlai/Documents/UCLA EE/Job/C++/Network_Fromation/Network_Fromation/graph.txt", "/Users/davidlai/Documents/UCLA EE/Job/C++/Network_Fromation/Network_Fromation/graph_data.txt"};
    myfile[0].open(name[0]);
    myfile[1].open(name[1]);
    myfile[1]<<"priflik\tpublik\tUtil\n";
    
    int timeslot=100;
    int asymTrial=100;
    float high;
    float correct=0;
    vector<float> correct_history;
    const float p=0.01;
    vector<float> h_degree;
    vector<agent> agentlist(timeslot);  //all agent's features
    publif pi;
    //Initialize struct-agent:nowagent

    
    //test asymptotical learning ratio.
    for( int std_incr=0;std_incr<20;std_incr++){
        correct=0;
        standard_dev+=0.3;
    for (int asym=0;asym<asymTrial;asym++){
        high=0;
        agentlist.clear();
        h_degree.clear();
        vector<agent> agentlist(timeslot);  //all agent's features
        publif pi;
    pi.belieflik.push_back(1);
    agentlist[0].settype(p);
        //srand(static_cast<unsigned int>(time(NULL)));

    for (int i=1;i<timeslot;i++){
        //Initialize private belif for player i
        agentlist[i].settype(p);
        agentlist[i].setprisignal(i,agentlist);//his own belief to all other agents.
        cout<< "s of 0 from "<<i<<" is "<<agentlist[i].signal[0]<<endl;
        cout<<"repu(0) "<<pi.belieflik[0]<<endl;
        //take action
        vector<float> utility(i);
        float Mutil;
        for (int j=0;j<i;j++){
            utility[j]=1/(1+((1-p)/p)/pi.belieflik[j]/agentlist[i].pribliflik[j]);
            if(myfile[1].is_open()){
                myfile[1]<<agentlist[i].pribliflik[j]<<"\t"<<pi.belieflik[j]<<"\t"<<utility[j]<<endl;
            }
        }
        Mutil=*max_element(utility.begin(), utility.end());
        int action_flag=0;
        for (int j=0;j<i;j++){
            if (utility[j]==Mutil&&action_flag==0){
                agentlist[i].action=j;
                action_flag=1;
                cout<<"agent "<<i<<" connect to agent "<<j<<endl;
                if(myfile[0].is_open()){
                    myfile[0]<<j<<" "<<i<<endl;
                }
                if(agentlist[agentlist[i].action].type=='h'){
                    high=high+1;
                    h_degree.push_back(high/(timeslot-1));
                }
            }
        }

        
        //Updating public belief
        pi.updatebel(agentlist[i].action, agentlist);
        
        //Initialize new public belief
        pi.belieflik.push_back(1);
        //
        
        //
        
    }
        cout<<"the threshold here is "<<threshold<<endl;
        if(agentlist[agentlist[timeslot-1].action].type=='h'){
            correct+=1;
        }
    }
        cout<<"the standard deviation is "<<standard_dev<<endl;
    cout<<"the last one pick agent "<<agentlist[timeslot-1].action<<endl;
    cout<<"his type is "<<agentlist[agentlist[timeslot-1].action].type<<endl;
    cout<<"the threshold here is "<<threshold<<endl;
    cout<<"htype agent got "<<h_degree.back()<<" of all links."<<endl;
    cout<<"asymptoical learning happended "<<correct<<" times."<<endl;
    correct_history.push_back(correct);
}
    myfile[0].close();
    myfile[1].close();
    for(int cv=0;cv<correct_history.size();cv++)
        cout<< correct_history[cv]<<endl;
    return 0;
}

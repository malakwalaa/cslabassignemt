// CS2labAssignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <queue>

using namespace std;

class patient
{
private:
    string patientId;
    char gender;
    int time;
    char type;
public:
   patient() 
    {
        patientId = "";
        gender = 'M';
        time = "";
        type = 'U';
    }
    void isIDvalidated(string s) // validates the id length is 14 and the numbers are from 0 to 9
    {
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i]<'0' || s[i]>'9')
            {
                cout << "Error: ID is invalid" << endl;
            }
        }
        if (s.length() != 14)
        {
            cout << "Error: ID is not validated. Another Id will be generated" << endl;

        }

    }
    string getPatientId()
    {
        return patientId;
    }
    char getGender()
    {
        return gender;
    }
    char getType()
    {
        return type;

    }
     int  extractTime(string t)
    {
       
       int hours= (t[0] - '0') * 10 + (t[1] - '0');
       int minutes = (t[3] - '0') * 10 + (t[4] - '0');
       return (hours * 60) + minutes;


    }
 void Random()
        {
        patient p;
        if (rand() % 2)
        {
            p.gender = 'M';
        }
        else {
            p.gender = 'F';
        }
        if (rand() % 2)
        {
            p.gender = 'U';
        }
        else {
             p.gender = 'N';
        }
      
        for (int i = 0; i < 14; i++)
        {
            p.patientId[i] = rand()%10;
        }
         
        int hours = rand() % 24;
        int minutes = rand() % 60;
        if (hours < 10)
        {
            p.time = "0" + to_string(hours) + ":" + to_string(minutes);
        }
        else {
            p.time = to_string(hours) + ":" + to_string(minutes);
        }
        
        if (minutes < 10)
        {
            p.time = to_string(hours) + ":" + "0" + to_string(minutes);
        }
        else {
            p.time = to_string(hours) + ":" + to_string(minutes);
        }

    }
};
class queueing_system{
    private:
    queue<patient> urgentqueue; 
    queue<patient> normalqueue;
    int max_time; // when i do it as a const i get an error, why?
   char patient_status;

    public:
    queueing_system(){
        max_time = 10;
    }
    void add_to_list(const patient& p){
        if (patient_status == 'u'|| patient_status == 'U'){
            urgentqueue.push(p);
        }else if (patient_status=='N' || patient_status =='n'){
             normalqueue.push(p);
        }
    }
    // void next (){ // ask if we need this if not delete
    //     if (urgentqueue.empty()== false){
    //         patient next_p = urgentqueue.front();
    //         uregentqueue.pop();
    //         cout<<"current patient of type urgent"<<next.patientId<< "at: "<<next.time<<endl;
    //     }else if (normalqueue.empty()== false){
    //         patient next_p = normalqueue.front();
    //         normalqueue.pop();
    //         cout<<"current patient of type normal"<<next.patientId<< "at: "<<next.time<<endl;

    //     }else{
    //         cout<<"no patients waiting"<<endl;
    //     }
    // }
    // void print(){ // ask if we need this
    //     cout<<"current waiting queue in clinic for urgent patients: "<<endl;
    //     cout<<" urgent patients waiting queue: ";
    //     if (urgentqueue.empty()== true){
    //         cout<<"0"<<endl;
    //     }else{
    //         queue<patient> temp = urgentqueue;
    //         while (temp.empty()== false){
    //             cout<<temp.front().patientId<<" "<<endl;
    //             temp.pop();
    //         }

    //     cout<<"current waiting queue in clinic for normal patients: "<<endl;
    //     if (normalqueue.empty()== true){
    //         cout<<"0"<<endl;
    //     }else{
    //         queue<patient> temp1 = urgentqueue;
    //         while (temp1.empty()== false){
    //             cout<<temp1.front().patientId<<" "<<endl;
    //             temp1.pop();
    //         }


    //     }

    // }


void time_constraints (int current_time ){
    while (current_time>0){
        if (urgentqueue.empty()== false){
            patient new_p = urgentqueue.front();
             urgentqueue.pop();

             int time;
             if (current_time<max_time){
                time = current_time;
             }else{
                time = max_time;
             }
             current_time-=time;
        }else if (normalqueue.empty()== false){
            patient new_p = normalqueue.front();
             normalqueue.pop();

             int time;
             if (current_time<max_time){
                time = current_time;
             }else{
                time = max_time;
             }
             current_time-=time;
        }else{
            break;
        }
    }

}
};
class requirments{
    private:
    vector<patient> p;
     queueing_system system;
     vector<int> wait_time;
     int time_current;
     int total_wait_time;
     int n_served;

     public:
     requirments(){
        time_current =0;
        total_wait_time =0;
        n_served =0;
        
     }
     void generate_patients(int count){
        p.clear();
        for (int i=0;i<count;++i){
            patient p1;
            p1.Random(i+1);
            p.push_back(p1);
        }
     }
     void remove_patient(){
        for (size_t i=0; i<p.size();++i){
            if (p[i].time<=time_current){
                system.add_to_list(p[i]){
                    //i don't know how to continue 
                }
            }
        }
     }
     void serve_patient(){
        int N = (time_current % 6)+5;
        int served = 0;

        while (urgentqueue.empty()== false && served<N){
            patient p1 = urgentqueue.front();
            urgentqueue.pop();

            int wait_time = time_current - p.time;
            total_wait_time += wait_time;

            cout<<"serving urgent patient: "<<endl;
            cout<<"Arrival time: "<<p.time<<endl;
            cout<<"waiting time: "<<wait_time<<endl;

            ++served;
            

        }
     
      while (normalqueue.empty()== false && served<N){
            patient p1 = normalqueue.front();
            normalqueue.pop();

            int wait_time = time_current - p.time;
            total_wait_time += wait_time;

            cout<<"serving normal patient: "<<endl;
            cout<<"Arrival time: "<<p.time<<endl;
            cout<<"waiting time: "<<wait_time<<endl;

            ++served;
            

        }
        n_served += served;
     }
     void simulation(int step){
        for(time_current =0; time_current<step;++time_current){
            serve_patient();
            remove_patient();
        }
     }
     void stat()const{
        cout<<"total patient served: "<<n_served<<endl;
        cout<<"average wait time: "<< n_served/total_wait_time<<endl;
        
     }

};

// CS2labAssignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <queue>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<chrono>

using namespace std;
using namespace std::chrono;

class patient
{
private:
    string patientId;
    char gender;
    string time;
    char type;
    //int depTIME;
    time_point<steady_clock> arrived_time;
     time_point<steady_clock> depart_time;
public:
    patient(string p, char g,string t,char ty)
    {
        patientId = p;
        gender = g;
        time = t;
        type = ty;
        //depTIME = d;

    }
    void set_arrived_time(){
        arrived_time = steady_clock::now(); 
    }
    void set_departure_time(){
        depart_time = steady_clock::now();
    }
    int wait_time()const{
        return duration_cast<seconds>(depart_time - arrived_time).count();
    }
    void isIDvalidated(string s){
        try{
        if (s.length()!=14){
            throw invalid_argument("ID lenght must be 14");
        }
        for (char c:s){
             if (c < '0' || c > '9'){
                throw invalid_argument("ID should only contain digits from 0 to 9");
             }
        }
        }catch (const invalid_argument& e ){
            cout<<"error: "<<e.what()<<endl;
        }
    }
    // void isIDvalidated(string s) // validates the id length is 14 and the numbers are from 0 to 9
    // {
    //     for (int i = 0; i < s.length(); i++)
    //     {
    //         if (s[i] < '0' || s[i]>'9')
    //         {
    //             cout << "Error: ID is invalid" << endl;
    //         }
    //     }
    //     if (s.length() != 14)
    //     {
    //         cout << "Error: ID is not validated. Another Id will be generated" << endl;

    //     }

    // }
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
    int extractTime(string t)
    {

        int hours = (t[0] - '0') * 10 + (t[1] - '0');
        int minutes = (t[3] - '0') * 10 + (t[4] - '0');
        return (hours * 60) + minutes;


    }
    string getTime()
    {
        return time;
    }
    // void setdepTIME(int s)
    // {    
    //     depTIME = s;
    // }
    // int getdepTIME() 
    // {
    //     return depTIME;
    // }
    patient Random()
    {
      
        if (rand() % 2)
        {
           gender = 'M';
        }
        else {
            gender = 'F';
        }
        if (rand() % 2)
        {
            type = 'U';
        }
        else {
           type = 'N';
        }
        patientId = string(14, '0');

        for (int i = 0; i < 14; i++)
        {
           patientId[i] = '0'+(rand() % 10);
        }

        int hours = rand() % 24;
        int minutes = rand() % 60;
        if (hours < 10)
        {
           time = "0" + to_string(hours) + ":" + to_string(minutes);
        }
        else {
           time = to_string(hours) + ":" + to_string(minutes);
        }

        if (minutes < 10)
        {
           time = to_string(hours) + ":" + "0" + to_string(minutes);
        }
        else {
           time = to_string(hours) + ":" + to_string(minutes);
        }
        set_arrived_time();
        patient p(patientId,gender,time,type);
        return p;
    }
};
class queueing_system {
private:
    queue<patient> urgentqueue;
    queue<patient> normalqueue;
    const int max_time=10; // when i do it as a const i get an error, why?
   

public:
    // queueing_system() {
    //     max_time = 10;
    // }
    void add_to_list( patient& p) {
        if ( p.getType() == 'U') {
            urgentqueue.push(p);
        }
        else if (p.getType() == 'N') {
            normalqueue.push(p);
        }
        
    }
    // It first serves patients from the urgent queue, recording their departure time, and then serves patients from the normal queue, recording their arrival time
//Each served patient is added to the healedPatients vector. The function stops when n patients have been served or when both queues are empty. The resulting vector of healed patients is then returned.
    vector<patient> Serving(int n)
    {
        //cout<<"in serving"<<endl;
        vector <patient> healedPatients;
        while (!urgentqueue.empty() && n > 0)
        {
            patient healed = urgentqueue.front();
            healed.set_departure_time(); // takes the current time
            healedPatients.push_back(healed);
            urgentqueue.pop();
            n--;
        }
        while (!normalqueue.empty() && n > 0)
        {
            patient healed = normalqueue.front();
            healed.set_arrived_time(); // takes the current time
            healedPatients.push_back(healed);
            normalqueue.pop();
            n--;

        }
        return healedPatients;

    }
    int getsizeUrgent()
    {
        return urgentqueue.size();
    }
    int getsizeNormal()
    {
        return normalqueue.size();

    }
    void printUrgentqueue()
    {
        queue<patient> temp=urgentqueue;

        
         while (!temp.empty())
        {
            cout << "urgent patients id's = "<< temp.front().getPatientId() << " " << endl;
            temp.pop();
        }
           
        
    }
    void printNormalqueue()
    {
        queue<patient> temp = normalqueue;


        while (!temp.empty())
        {
            cout << "normal patient id's = "<<temp.front().getPatientId() << " " << endl;
            temp.pop();
        }


    }

};
class wholeProgram {
private:
    vector<patient> p;
    vector<patient> finalp;
    queueing_system system;
    vector<int> wait_time;
    //int time_current;
    int total_wait_time;
    int n_served;
    double avg;

public:
    wholeProgram() {
        //time_current = 0;
        total_wait_time = 0;
        n_served = 0;
        avg = 0.0;

    }
    // static bool checktime(patient p1, patient p2) //we check to the arrival time of patients to see how arrived first
    // {
    //     return (p1.extractTime(p1.getTime()) < p2.extractTime(p2.getTime()));

    // }
    void generate_patients(int count) {
        for (int i = 0; i < count; ++i) 
        {
            patient p1("",'F',"",'U');// this is dummy data
            p1.Random();
            p.push_back(p1);
            
            //cout<<i;
        }
        
        //sort(p.begin(), p.end(), checktime);
    }
    
//The simulation function simulates a cycle of patient service
//It adds patients from the list p to the system, then serves n patients using the Serving function
//For each served patient, it calculates and displays their waiting time, updates the total wait time, and tracks the total number of served patients
//it computes the average wait time and prints the status of the urgent and normal queues.
    void simulation(int n) {
        
        for(int i=0;i<p.size();i++)
        { system.add_to_list(p[i]);}
        finalp= system.Serving(n);
        if(finalp.empty()){
            cout<<"no patients served in this cycle"<<endl;
        }
        cout<<"number of served patients "<<finalp.size()<<endl;
        for (auto& p:finalp)
        {
            int waiting_time = p.wait_time();
            total_wait_time+=waiting_time;
            cout<<"served patient ID: "<<p.getPatientId()<<" , wait time: "<<waiting_time<< " seconds"<<endl;
            // total_wait_time+= finalp[i].getdepTIME() - finalp[i].extractTime(finalp[i].getTime());
            // cout << "served patient id: " << finalp[i].getPatientId() << endl;
        }
        n_served += finalp.size();
        avg=total_wait_time / n_served;
        system.printUrgentqueue();
        system.printNormalqueue();
    }

    
    
    void display() 
    { // we need to print avg waiting time, total number of patients, number of urgent cases,and number of normal cases.
        cout << "average waiting time= " << avg <<" seconds" <<endl;
        cout << "total number of patients= " << n_served << endl;
        cout << "number of urgent cases= " << system.getsizeUrgent() << endl;
        cout << "number of normal cases= " << system.getsizeNormal() << endl;
       
    }


};


int main()
{
    cout << "which scenario do you want??" << endl;
    cout << "enter 1 for simple scenrio, 2 for moderate, and 3 for crowded" << endl;
    int value;
    cin >> value;
    wholeProgram p;
    if (value == 1)
    {

        p.generate_patients(100);
      


    }
    else if (value == 2)
    {

        p.generate_patients(300);
    }
    else if (value == 3)
    {
        p.generate_patients(700);
    }
    else {
        cout << "invalid input !!!" << endl;
    }
   
    while (1)
    {
        p.simulation(rand() % 6 + 5);
        cout << "press enter to advance time or enter 0 to stop the program" << endl;
        int c;
        cin >> c;
        if (c == 0)
        {
            p.display();
            break;
        }
       
    }
     
        

}


#include<bits/stdc++.h>
using namespace std;
struct round_robin{
    int at;
    int bt;
    int dup_bt;
    int ct;
    int wt;
    int tat;
    int pronum;
};
bool compare(round_robin a,round_robin b){
    if(a.at<b.at)
    return 1;
    return 0;
}
int main(){
    int n;
    cout<<"Enter number of processes :";
    cin>>n;
    round_robin p[n];
    cout<<"Enter data (AT , BT) :"<<endl;
    //cout<<"Process\tAT\tBT"<<endl;
    for(int i=0 ; i<n ; i++)
    {
        p[i].pronum=i+1;
        cin>>p[i].at>>p[i].bt;
        p[i].dup_bt=p[i].bt;
    }
    cout<<endl;
    cout<<"-------------------------"<<endl;
    cout<<"|Process| AT\t| BT\t|"<<endl;
    cout<<"-------------------------"<<endl;
    //cout<<"Process\tAT\tBT\tCT\tWT\tTAT"<<endl;
    for(int i=0; i<n; i++)
    {
        cout<<"| "<<p[i].pronum<<"\t| "<<p[i].at<<"\t| "<<p[i].bt<<"\t|"<<endl;
    }
    cout<<"-------------------------"<<endl;
    //if arrival times aren't sorted
    //Sort in ascending order of arrival times
    vector<int> gantt_process;
    vector<int> gantt_time;
    sort(p,p+n,compare);
    //instead of using sort function using bubble sort may help in case of already sorted processes
    queue <int> ready_q;
    int y=p[0].at;
    gantt_time.push_back(y);
    //int prev;
    int ind_new;
    int max_bt=0;
    int index=INT_MAX,time_quantum;
    set<int>s;
    int q_size=0;
    for(int i=0 ;i<n;i++)
    {
        if(p[i].at<=y && p[i].dup_bt!=0)
        {
            ready_q.push(p[i].pronum);
            q_size++;
            s.insert(p[i].pronum);
            if(p[i].dup_bt>max_bt)
            max_bt=p[i].dup_bt;
        }
        else if(p[i].at>y)
        break;
    }
    int flag=0,flag_1;
    while(!ready_q.empty())
    {
        int x=ready_q.front();
        if(x!=index)
        {
            time_quantum=0.8*max_bt;
        }
        else if(x==index)
        {
            time_quantum=max_bt;
            flag_1=1;
        }
        if((p[x-1].dup_bt<=time_quantum)||q_size==1)
        {
            if(p[x-1].dup_bt>time_quantum)
            {
                y+=time_quantum;
                gantt_time.push_back(y);
                gantt_process.push_back(x);
                p[x-1].dup_bt-=time_quantum;
            }
            else if(p[x-1].dup_bt<=time_quantum)
            {
                y+=p[x-1].dup_bt;
                gantt_time.push_back(y);
                gantt_process.push_back(x);
                p[x-1].dup_bt=0;
            }
            if(p[x-1].dup_bt==0)
            p[x-1].ct=y;
        }
        else
        {
            ready_q.push(x);
            q_size++;
            if(flag==0)
            {
                index=x;
                flag=1;
                flag_1=0;
            }
        }
        if(x==index && flag_1==1)
        {
            ind_new=1;
        }
        ready_q.pop();
        if(ind_new==1)
        {
            index=ready_q.front();
        }
        q_size--;
        max_bt=0;
        for(int i=0;i<n;i++)
        {
            if(p[i].at<=y && p[i].dup_bt!=0)
            {
                if ( s.size() < n)
                {
                    ready_q.push(p[i].pronum);
                    q_size++;
                }
                s.insert(p[i].pronum);
                if(p[i].dup_bt>max_bt)
                max_bt=p[i].dup_bt;
            }
            else if(p[i].at>y)
            break;
        }
    }
    float tat_sum=0.0,wt_sum=0.0;
    for(int i=0;i<n;i++)
    {
        p[i].tat=p[i].ct-p[i].at;
        p[i].wt=p[i].tat-p[i].bt;
        tat_sum+=p[i].tat;
        wt_sum+=p[i].wt;
    }
    cout<<endl;
    cout<<"-------------------------------------------------"<<endl;
    cout<<"|Process| AT\t| BT\t| CT\t| WT\t| TAT\t|"<<endl;
    cout<<"-------------------------------------------------"<<endl;
    for(int i=0; i<n; i++)
    {
        cout<<"| "<<p[i].pronum<<"\t| "<<p[i].at<<"\t| "<<p[i].bt<<"\t| "<<p[i].ct<<"\t| "<<p[i].wt<<"\t| "<<p[i].tat<<"\t|"<<endl;
    }
    cout<<"-------------------------------------------------"<<endl;
    cout<<endl;
    cout<<"*******************************"<<endl;
    cout<<endl;
    cout<<"Average TAT : "<<tat_sum/n<<endl;
    cout<<"Average WT : "<<wt_sum/n<<endl;
    cout<<endl;
    cout<<"*******************************"<<endl;
    cout<<endl<<"*****GANTT CHART*****"<<endl;
    for(int i=0;i<gantt_process.size();i++)
    {
        cout<<"|\tP"<<gantt_process[i]<<"\t|";
    }
    cout<<endl;
    for(int i=0;i<gantt_time.size();i++)
    {
        cout<<gantt_time[i]<<"\t\t";
    }
    return 0;
}
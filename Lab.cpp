#include<iostream>
using namespace std;

const int Max_applicant=25;
const int Max_total=100;
const int visaTypes=4;
const int counters=4;
int Token=1;
int totalApplicants=0;
int servedByVisa[visaTypes]={};
int counterServed[counters+1][visaTypes]={};

struct visaLine
{
    string name;
    string line[Max_applicant];
    int start=0;
    int end=0;
};

visaLine visaNames[visaTypes]={"TR","MED","BS","GO"};

void GenerateToken(string visaType)
{
    if (totalApplicants>=Max_total)
    {
        cout << "Total applicant limit reached"<<endl;
        return;
    }

    int count = -1;
    for(int i=0;i<visaTypes;i++)
    {
        if(visaNames[i].name==visaType)
        {
            count=i;
            break;
        }
    }
    if (count==-1||visaNames[count].end>=Max_applicant)
    {
        cout <<"Daily limit reached for "<<visaType<<endl;
        return;
    }
    string token=visaType+"-" +to_string(Token);

     int lastperson=visaNames[count].end;
     visaNames[count].line[lastperson]=token;
     visaNames[count].end=lastperson+1;
     totalApplicants++;
     cout<<"Token number is: "<<token<<endl;
}


bool ServeTheQueue(int counter,string visaType)
{
    string token  ;
    int index =-1;

    for (int i=0;i<visaTypes;i++)
    {
        if (visaNames[i].name==visaType)
        {
            index=i;
            break;
        }
    }

    if (index!=-1&&visaNames[index].start<visaNames[index].end)
    {
        int firstperson=visaNames[index].start;
        token=visaNames[index].line[firstperson];
        visaNames[index].start=firstperson+1;

        servedByVisa[index]++;
        counterServed[counter][index]++;
        cout << "Counter"<<counter<<" , please serve token: "<<token<< endl;
        return true;
    }
    return false;
}
int getLongQueue()
{
    int MaxIndex=-1,MaxSize=0;
    for (int i=0;i<visaTypes;++i)
    {
        int size =visaNames[i].end-visaNames[i].start;
        if (size>MaxSize)
        {
            MaxSize=size;
            MaxIndex=i;
        }
    }
    return MaxIndex;
}
void ServeNextApplicant(int counter)
{
    string primary_Visa=visaNames[counter-1].name;
    if (!ServeTheQueue(counter,primary_Visa))
        {
        int x=getLongQueue();
        if (x==-1)
        {
            cout <<"Counter"<<counter <<" is now idle"<<endl;
        }
        else
        {
            ServeTheQueue(counter,visaNames[x].name);
        }
    }
}

void CounterAvailability()
{
    cout << "Counter Availability (Day summary)"<<endl;
    for (int i=0;i<visaTypes;i++)
    {
        cout<<visaNames[i].name<<": "<<visaNames[i].end <<"applicants"<<endl;
    }
}
void DailyReport()
{
    cout <<"Applicants served by Visa Type:"<<endl;
    for (int i =0;i<visaTypes;i++)
    {
        cout <<visaNames[i].name<<": "<<servedByVisa[i]<<endl;
    }

    cout <<"Applicants served by Counter:"<<endl;
    for (int i=1;i<=counters;i++)
    {
        cout <<"Counter"<<i<<": ";
        for (int j=0;j <visaTypes;j++)
        {
            if (counterServed[i][j]>0)
            {
                cout <<visaNames[j].name<<":"<<counterServed[i][j]<<" ";
            }
        }
        cout << endl;
    }

    cout <<"The Idle Counters:"<<endl;
    for (int i=1;i<=counters;i++)
    {
        bool idle=true;
        for (int j=0;j<visaTypes;j++)
        {
            if(counterServed[i][j]>0)
            {
                idle=false;
                break;
            }
        }
        if(idle)
        {
            cout <<"Counter"<<i<< endl;
        }
    }

    int totalServed =0;
    for (int i=0;i<visaTypes;i++)
    {
        totalServed+=servedByVisa[i];
    }
    cout <<"Total Applicants Served:"<<totalServed<< endl;
}

int main()

{
    int input;

    while(true)
    {
        cout<<"Welcome to Visa Embassy Line system"<<endl;
        cout<<"----------------------------------"<<endl;
        cout<<"1. Request for a token "<<endl;
        cout<<"2. serve the next applicant"<<endl;
        cout<<"3. counter availability (Day summary)"<<endl;
        cout<<"4. View Daily report"<<endl;
        cout<<endl;
        cout<<"Enter the choice:";
        cin>>input;

        switch(input)
        {
            case 1:
                {
                    string vtype;
                    cout << "Enter Visa Type in Capital (TR,MED,BS,GO): ";
                    cin >> vtype;
                    GenerateToken(vtype);
                    break;
                }
            case 2:
                {
                    int counterNumber;
                    cout << "Enter Counter Number (1-4): ";
                    cin >> counterNumber;
                    if(counterNumber>=1 && counterNumber<=4)
                    {
                        ServeNextApplicant(counterNumber);
                    }
                    else
                    {
                        cout<<"Invalid counter number"<<endl;
                    }
                    break;
                 }
            case 3:
                {
                    CounterAvailability();
                    break;
                }
            case 4:
                {
                    DailyReport();
                    break;
                }
            case 5:
                {
                    cout<<"Exiting the system"<<endl;
                    return 1;
                }
            default:
                {
                    cout<<"Try again!"<<endl;
                }
    }

   }
}

#include<bits/stdc++.h>
#define int long long
#define pii pair<int, int>
#define ppii pair<pii, int>
#define inf 1e18
#define Not_Responsed -1
using namespace std;
const int N = 1e5;
int n, TQ;
int ArrivalTime[N], BurstTime[N], Priority[N], gantt[N], Response[N], SaveBurst[N];
void PrintMenu()
{
	for (int i = 1; i <= 12; i++)
	{
		if (i == 1) cout << i << ": " << "FCFS" << endl;
		else if (i == 2) cout << i << ": " << "Non-Preemptive-SJF" << endl;
		else if (i == 3) cout << i << ": " << "Preemptive-SJF" << endl;
		else if (i == 4) cout << i << ": " << "Non-Preemptive-Priority" << endl;
		else if (i == 5) cout << i << ": " << "Preemptive-Priority" << endl;
		else if (i == 6) cout << i << ": " << "Round-Robin" << endl;
		else if (i == 7) cout << i << ": " << "Our-Proposed-AverageMean-Algorithm" << endl;
		else if (i == 8) cout << i << ": " << "Our-Proposed-WeightedAverageMean-Algorithm" << endl;
		else if (i == 9) cout << i << ": " << "Our-Proposed-HarmonicMean-Algorithm" << endl;
		else if (i == 10) cout << i << ": " << "Our-Proposed-WeightedHarmonicMean-Algorithm" << endl;
		else if (i == 11) cout << i << ": " << "Our-Proposed-MeanOfAllMeans-Algorithm" << endl;
		else if (i == 12) cout << i << ": " << "Compare-All" << endl;
		else cout << i << ": " << "Exit" << endl;
	}
}
void TakeInput(int option)
{
	if (option < 4||option==7||option==9 )
	{
		cout << "Number of Process: ";
		cin >> n;
		for (int i = 0; i < n; i++)
		{
			cout << "Enter the arrival time of P" << i + 1 << ':';
			cin >> ArrivalTime[i];
			cout << "Enter the burst time of P" << i + 1 << ':';
			cin >> BurstTime[i];
			SaveBurst[i] = BurstTime[i];
			Response[i] = -1;
		}
	}
	else if (option == 4 || option == 5|| option == 8||option==10||option==11)
	{
		cout << "Number of Process: ";
		cin >> n;
		for (int i = 0; i < n; i++)
		{
			cout << "Enter the priority of P" << i + 1 << ':';
			cin >> Priority[i];
			cout << "Enter the arrival time of P" << i + 1 << ':';
			cin >> ArrivalTime[i];
			cout << "Enter the burst time of P" << i + 1 << ':';
			cin >> BurstTime[i];

			SaveBurst[i] = BurstTime[i];
			Response[i] = -1;
		}
	}
	else if (option == 6)
	{
		cout << "Number of Process: ";
		cin >> n;
		for (int i = 0; i < n; i++)
		{
			cout << "Enter the arrival time of P" << i + 1 << ':';
			cin >> ArrivalTime[i];
			cout << "Enter the burst time of P" << i + 1 << ':';
			cin >> BurstTime[i];

			SaveBurst[i] = BurstTime[i];
			Response[i] = -1;
		}
		cout << "Enter the time quantum TQ for Round Robin Algorithm: ";
		cin >> TQ;
	}
	else if (option == 12)
	{
		cout << "Number of Process: ";
		cin >> n;
		for (int i = 0; i < n; i++)
		{
			cout << "Enter the priority of P" << i + 1 << ':';
			cin >> Priority[i];
			cout << "Enter the arrival time of P" << i + 1 << ':';
			cin >> ArrivalTime[i];
			cout << "Enter the burst time of P" << i + 1 << ':';
			cin >> BurstTime[i];

			SaveBurst[i] = BurstTime[i];
			Response[i] = -1;
		}
		cout << "Enter the time quantum TQ for Round Robin Algorithm: ";
		cin >> TQ;
	}
}

void PrintResult(vector<int>order, int idleTime)
{
	int AT, BT, WT, TT, FT, RT;
	int WT_sum = 0;
	int TT_sum = 0;
	for (int i = 0; i < n; i++)
	{
		int id = order[i];
		FT = gantt[id];
		AT = ArrivalTime[id];
		BT = BurstTime[id];
		RT = Response[id] - AT;//Response[id] is just telling the time at which the process responded first having ID=id
		TT = FT - AT;
		WT = TT - BT;
		WT_sum += WT;
		TT_sum += TT;
		cout << "Process:P" << id + 1 << "  Finish Time: " << FT << "  Response Time: " << RT << "  Waiting Time: " << WT << "  Turnaround Time: " << TT << endl;
	}
	double avg_WT = WT_sum / (double) n;
	double avg_TT = TT_sum / (double) n;

	cout << "\nAverage waiting time: " << avg_WT << endl;
	cout << "Average Turnaround time: " << avg_TT << endl;
	cout << "Idle Time: " << idleTime << endl;
}


void FindAverage()
{
	int AT, BT, WT, TT, FT;
	int WT_sum = 0;
	int TT_sum = 0;
	for (int i = 0; i < n; i++)
	{
		FT = gantt[i];
		AT = ArrivalTime[i];
		BT = BurstTime[i];
		TT = FT - AT;
		WT = TT - BT;
		WT_sum += WT;
		TT_sum += TT;
	}
	double avg_WT = WT_sum / (double) n;
	double avg_TT = TT_sum / (double) n;
	cout << "  \tAverage waiting time: " << avg_WT << "  \tAverage Turnaround time: " << avg_TT << endl;
}
#include "otheralgos.h"
double Calculate_TQ_Average_Mean()
{
    double Asum = 0;
    for(int i = 0; i < n; i++)
    {
        Asum += BurstTime[i];
    }
    double Amean = Asum / n;
    return Amean;
}
double Calculate_TQ_Weighted_Average_Mean()
{
    double sumBTdotP=0;
    double sumP=0;
    for(int i = 0; i < n; i++)
    {
        sumBTdotP+=(BurstTime[i]*Priority[i]);
        sumP+=Priority[i];
    }
    double TQ = sumBTdotP/sumP;
    return TQ;
}
double Calculate_TQ_Harmonic_Mean()
{
    double Hsum = 0;
    for(int i = 0; i < n; i++)
    {
        Hsum += 1.0 / BurstTime[i];
    }
    double Hmean = n / Hsum;
    return Hmean;
}
double Calculate_TQ_Weighted_Harmonic_Mean()
{
    int Asum = 0, mxBurst = 0;
    double Psum=0;
    double PbB = 0;
    for(int i = 0; i < n; i++)
    {
        Psum+=Priority[i];
        PbB += (1.0 / BurstTime[i])*Priority[i];
    }
    double TQ = Psum/PbB;
    return TQ;
}
void ProposedAverageMean(bool cmp = false)
{
    deque<pii>arrivalQ;
    for(int i = 0; i < n; i++) arrivalQ.emplace_back(ArrivalTime[i], i);
    sort(arrivalQ.begin(), arrivalQ.end());

	int curTime = 0, idleTime = 0;
    TQ = round(Calculate_TQ_Average_Mean());
    set<pii>ReadyQ;
	vector<int>order;

	if (cmp == 0) {
		cout<<"\nWe are going to take TQ="<<TQ<<endl;
		cout << "\nGantt Chart" << endl;
	}

	while(!ReadyQ.empty() || !arrivalQ.empty())
	{
		if (!ReadyQ.empty())
		{
            pii cur_process = *ReadyQ.begin();
            ReadyQ.erase(ReadyQ.find(cur_process));

			int id = cur_process.second;
			int BT = cur_process.first;
			int dur = (TQ < BT) ? TQ : BT; // assuming duration

			if (Response[id] == Not_Responsed) Response[id] = curTime; // response for the first time

			curTime += dur;
			BT -= dur;
            while(!arrivalQ.empty())
            {
                pii new_process = arrivalQ.front();
                int AT = new_process.first;
                int PID = new_process.second;

                if (AT <= curTime)
                {
                    new_process = make_pair(BurstTime[PID], PID);
                    ReadyQ.insert(new_process);
                    arrivalQ.pop_front();
                }
                else break;
            }
			if (BT != 0)
            {
                 cur_process = make_pair(BT, id);
                 ReadyQ.insert(cur_process);
            }
			else
			{
				order.push_back(id);
				gantt[id] = curTime;
			}
			if (cmp == 0) cout << curTime - dur << " P" << id + 1 << " ";
		}
		else if(!arrivalQ.empty())
		{
            // when CPU is idle
            pii new_process = arrivalQ.front();
            int mnAT = new_process.first;
            int mnID = new_process.second;
            arrivalQ.pop_front();

			idleTime += mnAT - curTime;
			curTime = mnAT;

            new_process = make_pair(BurstTime[mnID], mnID);
			ReadyQ.insert(new_process);
		}
	}
	if (cmp == 0)
	{
		cout << endl << endl;
		PrintResult(order, idleTime);
	}
	else FindAverage();
	//cout<<"printing the result for gantt chart:";
	//for(int i=0;i<n;i++)cout<<gantt[i]<<" ";
}
void ProposedWeightedAverageMean(bool cmp = false)
{
    deque<pii>arrivalQ;
    for(int i = 0; i < n; i++) arrivalQ.emplace_back(ArrivalTime[i], i);
    sort(arrivalQ.begin(), arrivalQ.end());

	int curTime = 0, idleTime = 0;
    TQ = round(Calculate_TQ_Weighted_Average_Mean());

    set<pii>ReadyQ;
	vector<int>order;

	if (cmp == 0) {
		cout<<"\nWe are going to take TQ="<<TQ<<endl;
		cout << "\nGantt Chart" << endl;
	}
	while(!ReadyQ.empty() || !arrivalQ.empty())
	{
		if (!ReadyQ.empty())
		{
            pii cur_process = *ReadyQ.begin();
            ReadyQ.erase(ReadyQ.find(cur_process));

			int id = cur_process.second;
			int BT = cur_process.first;
			int dur = (TQ < BT) ? TQ : BT; // assuming duration

			if (Response[id] == Not_Responsed) Response[id] = curTime; // response for the first time

			curTime += dur;
			BT -= dur;
            while(!arrivalQ.empty())
            {
                pii new_process = arrivalQ.front();
                int AT = new_process.first;
                int PID = new_process.second;

                if (AT <= curTime)
                {
                    new_process = make_pair(BurstTime[PID], PID);
                    ReadyQ.insert(new_process);
                    arrivalQ.pop_front();
                }
                else break;
            }
			if (BT != 0)
            {
                 cur_process = make_pair(BT, id);
                 ReadyQ.insert(cur_process);
            }
			else
			{
				order.push_back(id);
				gantt[id] = curTime;
			}
			if (cmp == 0) cout << curTime - dur << " P" << id + 1 << " ";
		}
		else if(!arrivalQ.empty())
		{

            // when CPU is idle
            pii new_process = arrivalQ.front();
            int mnAT = new_process.first;
            int mnID = new_process.second;
            arrivalQ.pop_front();

			idleTime += mnAT - curTime;
			curTime = mnAT;

            new_process = make_pair(BurstTime[mnID], mnID);
			ReadyQ.insert(new_process);
		}
	}
	if (cmp == 0)
	{
		cout << endl << endl;
		PrintResult(order, idleTime);
	}
	else FindAverage();
}
void ProposedHarmonicMean(bool cmp = false)
{
    deque<pii>arrivalQ;
    for(int i = 0; i < n; i++) arrivalQ.emplace_back(ArrivalTime[i], i);
    sort(arrivalQ.begin(), arrivalQ.end());

	int curTime = 0, idleTime = 0;
    TQ = round(Calculate_TQ_Harmonic_Mean());

    set<pii>ReadyQ;
	vector<int>order;

	if (cmp == 0) {
		cout<<"\nWe are going to take TQ="<<TQ<<endl;
		cout << "\nGantt Chart" << endl;
	}
	while(!ReadyQ.empty() || !arrivalQ.empty())
	{
		if (!ReadyQ.empty())
		{
            pii cur_process = *ReadyQ.begin();
            ReadyQ.erase(ReadyQ.find(cur_process));

			int id = cur_process.second;
			int BT = cur_process.first;
			int dur = (TQ < BT) ? TQ : BT; // assuming duration

			if (Response[id] == Not_Responsed) Response[id] = curTime; // response for the first time

			curTime += dur;
			BT -= dur;
            while(!arrivalQ.empty())
            {
                pii new_process = arrivalQ.front();
                int AT = new_process.first;
                int PID = new_process.second;

                if (AT <= curTime)
                {
                    new_process = make_pair(BurstTime[PID], PID);
                    ReadyQ.insert(new_process);
                    arrivalQ.pop_front();
                }
                else break;
            }
			if (BT != 0)
            {
                 cur_process = make_pair(BT, id);
                 ReadyQ.insert(cur_process);
            }
			else
			{
				order.push_back(id);
				gantt[id] = curTime;
			}
			if (cmp == 0) cout << curTime - dur << " P" << id + 1 << " ";
		}
		else if(!arrivalQ.empty())
		{
            // when CPU is idle
            pii new_process = arrivalQ.front();
            int mnAT = new_process.first;
            int mnID = new_process.second;
            arrivalQ.pop_front();

			idleTime += mnAT - curTime;
			curTime = mnAT;

            new_process = make_pair(BurstTime[mnID], mnID);
			ReadyQ.insert(new_process);
		}
	}
	if (cmp == 0)
	{
		cout << endl << endl;
		PrintResult(order, idleTime);
	}
	else FindAverage();
}
void ProposedWeightedHarmonicMean(bool cmp = false)
{
    deque<pii>arrivalQ;
    for(int i = 0; i < n; i++) arrivalQ.emplace_back(ArrivalTime[i], i);
    sort(arrivalQ.begin(), arrivalQ.end());

	int curTime = 0, idleTime = 0;
    TQ = round(Calculate_TQ_Weighted_Harmonic_Mean());

    set<pii>ReadyQ;
	vector<int>order;

	if (cmp == 0) {
		cout<<"\nWe are going to take TQ="<<TQ<<endl;
		cout << "\nGantt Chart" << endl;
	}
	while(!ReadyQ.empty() || !arrivalQ.empty())
	{
		if (!ReadyQ.empty())
		{
            pii cur_process = *ReadyQ.begin();
            ReadyQ.erase(ReadyQ.find(cur_process));

			int id = cur_process.second;
			int BT = cur_process.first;
			int dur = (TQ < BT) ? TQ : BT; // assuming duration

			if (Response[id] == Not_Responsed) Response[id] = curTime; // response for the first time

			curTime += dur;
			BT -= dur;
            while(!arrivalQ.empty())
            {
                pii new_process = arrivalQ.front();
                int AT = new_process.first;
                int PID = new_process.second;

                if (AT <= curTime)
                {
                    new_process = make_pair(BurstTime[PID], PID);
                    ReadyQ.insert(new_process);
                    arrivalQ.pop_front();
                }
                else break;
            }
			if (BT != 0)
            {
                 cur_process = make_pair(BT, id);
                 ReadyQ.insert(cur_process);
            }
			else
			{
				order.push_back(id);
				gantt[id] = curTime;
			}
			if (cmp == 0) cout << curTime - dur << " P" << id + 1 << " ";
		}
		else if(!arrivalQ.empty())
		{
            // when CPU is idle
            pii new_process = arrivalQ.front();
            int mnAT = new_process.first;
            int mnID = new_process.second;
            arrivalQ.pop_front();

			idleTime += mnAT - curTime;
			curTime = mnAT;

            new_process = make_pair(BurstTime[mnID], mnID);
			ReadyQ.insert(new_process);
		}
	}
	if (cmp == 0)
	{
		cout << endl << endl;
		PrintResult(order, idleTime);
	}
	else FindAverage();
}
void ProposedMeanOfAllMeans(bool cmp = false)
{
    deque<pii>arrivalQ;
    for(int i = 0; i < n; i++) arrivalQ.emplace_back(ArrivalTime[i], i);
    sort(arrivalQ.begin(), arrivalQ.end());

	int curTime = 0, idleTime = 0;
    double TQ1 = Calculate_TQ_Average_Mean();
    double TQ2 = Calculate_TQ_Weighted_Average_Mean();
    double TQ3 = Calculate_TQ_Harmonic_Mean();
    double TQ4 = Calculate_TQ_Weighted_Harmonic_Mean();
	 TQ=round((TQ1+TQ2+TQ3+TQ4)/4.0);
    set<pii>ReadyQ;
	vector<int>order;
	if (cmp == 0) {
		cout<<"\nWe are going to take TQ="<<TQ<<endl;
		cout << "\nGantt Chart" << endl;
	}
	while(!ReadyQ.empty() || !arrivalQ.empty())
	{
		if (!ReadyQ.empty())
		{
            pii cur_process = *ReadyQ.begin();
            ReadyQ.erase(ReadyQ.find(cur_process));

			int id = cur_process.second;
			int BT = cur_process.first;
			int dur = (TQ < BT) ? TQ : BT; // assuming duration

			if (Response[id] == Not_Responsed) Response[id] = curTime; // response for the first time

			curTime += dur;
			BT -= dur;
            while(!arrivalQ.empty())
            {
                pii new_process = arrivalQ.front();
                int AT = new_process.first;
                int PID = new_process.second;

                if (AT <= curTime)
                {
                    new_process = make_pair(BurstTime[PID], PID);
                    ReadyQ.insert(new_process);
                    arrivalQ.pop_front();
                }
                else break;
            }
			if (BT != 0)
            {
                 cur_process = make_pair(BT, id);
                 ReadyQ.insert(cur_process);
            }
			else
			{
				order.push_back(id);
				gantt[id] = curTime;
			}
			if (cmp == 0) cout << curTime - dur << " P" << id + 1 << " ";
		}
		else if(!arrivalQ.empty())
		{

            // when CPU is idle
            pii new_process = arrivalQ.front();
            int mnAT = new_process.first;
            int mnID = new_process.second;
            arrivalQ.pop_front();

			idleTime += mnAT - curTime;
			curTime = mnAT;

            new_process = make_pair(BurstTime[mnID], mnID);
			ReadyQ.insert(new_process);
		}
	}
	if (cmp == 0)
	{
		cout << endl << endl;
		PrintResult(order, idleTime);
	}
	else FindAverage();
}

signed main()
{
	double avg_WT, avg_TT;

	PrintMenu();

	cout << "Choose Option: ";
	int option; cin >> option;

	TakeInput(option);

    auto GoToHome = []()
    {
        cout << "\nPress Any Key for home page" << endl;
        string anykey = "";
        cin >> anykey;
        if(anykey.size())
        {
            main();
        }
    };

	if (option == 1)
    {
        FCFS();
        GoToHome();
    }
	else if (option == 2)
    {
        SJF();
        GoToHome();
    }
	else if (option == 3)
    {
        SRTF();
        GoToHome();
    }
	else if (option == 4)
	{
		cout << "1: Higher Number Higher Priority" << endl;
		cout << "2: Lower Number Higher Priority" << endl;
		cout << "Choose Option: ";
		int type; cin >> type;
		if (type == 1) Priority_Non_Preemptive_1();
		else Priority_Non_Preemptive_2();
		GoToHome();
	}
	else if (option == 5)
	{
		cout << "1: Higher Number Higher Priority" << endl;
		cout << "2: Lower Number Higher Priority" << endl;
		cout << "Choose Option: ";
		int type; cin >> type;
		if (type == 1) Priority_Preemptive_1();
		else  Priority_Preemptive_2();
		GoToHome();
	}
	else if (option == 6)
    {
        RoundRobin();
        GoToHome();
    }
	else if (option == 7)
    {
        ProposedAverageMean();
        GoToHome();
    }
	else if (option == 8)
    {
        ProposedWeightedAverageMean();
        GoToHome();
    }
	else if (option == 9)
    {
        ProposedHarmonicMean();
        GoToHome();
    }
	else if (option == 10)
	{
        ProposedWeightedHarmonicMean();
        GoToHome();
	}
	else if (option == 11)
    {
        ProposedMeanOfAllMeans();
        GoToHome();
    }

	else if (option == 12)
	{
		for (int i = 1; i <= 12; i++)
		{
			if (i == 1)
			{
				cout << "Algorithm: " << i;
				FCFS(true);
			}
			else if (i == 2)
			{
				cout << "Algorithm: " << i;
				SJF(true);
			}
			else if (i == 3)
			{
				cout << "Algorithm: " << i;
				SRTF(true);
			}
			else if (i == 4)
			{
				cout << "Algorithm: " << i;
				Priority_Non_Preemptive_2(true);
			}
			else if (i == 5)
			{
				cout << "Algorithm: " << i;
				Priority_Preemptive_2(true);
			}
			else if (i == 6)
			{
				cout << "Algorithm: " << i;
				RoundRobin(true);
			}
            else if(i==7)
            {
                cout << "Algorithm: " << i;
                ProposedAverageMean(true);
            }
            else if(i==8)
            {
                cout << "Algorithm: " << i;
                ProposedWeightedAverageMean(true);
            }
            else if(i==9)
            {
                cout << "Algorithm: " << i;
                ProposedHarmonicMean(true);
            }
            else if(i==10)
            {
                cout << "Algorithm: " << i;
                ProposedWeightedHarmonicMean(true);
            }
			else if(i==11)
            {
                cout << "Algorithm: " << i;
                ProposedMeanOfAllMeans(true);
            }
		}
		GoToHome();
	}
	else
	{
		exit(0);
	}
	return 0;
}
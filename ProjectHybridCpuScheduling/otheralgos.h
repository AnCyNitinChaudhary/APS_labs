void FCFS(bool cmp = false)
{
	int curTime = 0, idleTime = 0, cnt = 0;
	int vis[n] = {};
	vector<int>order;
	priority_queue<pii>pq;
	if (cmp == 0) cout << "\nGantt Chart" << endl;
	do
	{
		if (pq.empty() == false)
		{
			pii process = pq.top();
			pq.pop();
			int AT = -process.first;
			int id = -process.second;
			int dur = BurstTime[id];

			if (Response[id] == Not_Responsed) Response[id] = curTime;

			curTime += dur;

			order.push_back(id);
			gantt[id] = curTime;

			if (cmp == 0) cout << curTime - dur << " P" << id + 1 << " ";
		}
		if (cnt != n)
		{
			bool got = 0;
			for (int i = 0; i < n; i++)
			{
				if (vis[i] == 0 && ArrivalTime[i] <= curTime)
				{
					pii process = make_pair(-ArrivalTime[i], -i);
					pq.push(process);
					vis[i] = 1, got = 1;
					cnt += 1;
				}
			}
			if (got == 0)
			{
				int mnAT = inf, mnID;
				for (int i = 0; i < n; i++)
				{
					if (vis[i] == 0 && ArrivalTime[i] < mnAT)
					{
						mnAT = ArrivalTime[i];
						mnID = i;
					}
				}
				vis[mnID] = 1;
				cnt += 1;
				idleTime += mnAT - curTime;
				curTime = mnAT;

				pii process = make_pair(-mnAT, -mnID);
				pq.push(process);
			}
		}

	} while (!pq.empty());

	if (cmp == 0)
	{
		cout << endl << endl;
		PrintResult(order, idleTime);
	}
	else FindAverage();
}

void SJF(bool cmp = false)
{
	int curTime = 0, idleTime = 0, cnt = 0;
	int vis[n] = {};
	priority_queue<ppii>pq;
	vector<int>order;
	if (cmp == 0) cout << "\nGantt Chart:" << endl;
	do
	{
		if (!pq.empty())
		{
			ppii process = pq.top();
			pq.pop();
			int AT = -process.first.second;
			int BT = -process.first.first;
			int id = -process.second;

			if (Response[id] == Not_Responsed) Response[id] = curTime;

			curTime += BT;

			order.push_back(id);
			gantt[id] = curTime;

			if (cmp == 0) cout << curTime - BT << " P" << id + 1 << " ";
		}
		if (cnt != n)
		{
			int got = 0;
			for (int i = 0; i < n; i++)
			{
				if (vis[i] == 0 && ArrivalTime[i] <= curTime)
				{
					ppii process = make_pair(pii(-BurstTime[i], -ArrivalTime[i]), -i);
					pq.push(process);
					vis[i] = 1, got = 1;
					cnt += 1;
				}
			}
			if (got == 0)
			{
				int mnAT = 1e18, mnBT = 1e18, mnID;
				for (int i = 0; i < n; i++)
				{
					if (vis[i]) continue;

					if (ArrivalTime[i] < mnAT)
					{
						mnAT = ArrivalTime[i];
						mnBT = BurstTime[i];
						mnID = i;
					}
					else if (ArrivalTime[i] == mnAT)
					{
						if (BurstTime[i] < mnBT)
						{
							mnBT = BurstTime[i];
							mnID = i;
						}
					}
				}
				vis[mnID] = 1;
				cnt += 1;
				idleTime += mnAT - curTime;
				curTime = mnAT;

				ppii process = make_pair(pii(-BurstTime[mnID], -mnAT), -mnID);
				pq.push(process);
			}
		}

	} while (!pq.empty());

	if (cmp == 0)
	{
		cout << endl << endl;
		PrintResult(order, idleTime);
	}
	else FindAverage();
}


void SRTF(bool cmp = false)
{
	int curTime = 0, idleTime = 0, cnt = 0;
	int vis[n] = {};
	priority_queue<ppii>pq;
	vector<int>order;//This will help to print the output in a order such that- The process which comes first will got printed first.
	if (cmp == 0) cout << "\nGantt Chart:" << endl;
	do
	{
		if (!pq.empty())
		{
			ppii process = pq.top();
			pq.pop();
			int AT = -process.first.second;
			int BT = -process.first.first;
			int id = -process.second;
			int dur = (cnt != n) ? 1 : BT;

			if (Response[id] == Not_Responsed) Response[id] = curTime;

			curTime += dur;
			BT -= dur;
			if (BT != 0)
			{
				process = make_pair(pii(-BT, -AT), -id);
				pq.push(process);
			}
			else
			{
				// if(order[order.size()-1]!=id)
				order.push_back(id);
				gantt[id] = curTime;//gantt id is just storing the finishing time of the process.
			}
			if (cmp == 0) cout << curTime - dur << " P" << id + 1 << " ";
		}
		if (cnt != n)
		{
			int got = 0;
			for (int i = 0; i < n; i++)
			{
				if (vis[i] == 0 && ArrivalTime[i] <= curTime)
				{
					ppii process = make_pair(pii(-BurstTime[i], -ArrivalTime[i]), -i);
					pq.push(process);
					vis[i] = 1, got = 1;//got tells whether entered in if or not
					cnt += 1;
				}
			}
			if (got == 0)
			{
				int mnAT = 1e18, mnBT = 1e18, mnID;
				for (int i = 0; i < n; i++)
				{
					if (vis[i]) continue;//if the process got visited already

					if (ArrivalTime[i] < mnAT)
					{
						mnAT = ArrivalTime[i];
						mnBT = BurstTime[i];
						mnID = i;
					}
					else if (ArrivalTime[i] == mnAT)
					{
						if (BurstTime[i] < mnBT)
						{
							mnBT = BurstTime[i];
							mnID = i;
						}
					}
				}
				vis[mnID] = 1;
				cnt += 1;
				idleTime += mnAT - curTime;
				curTime = mnAT;

				ppii process = make_pair(pii(-BurstTime[mnID], -mnAT), -mnID);
				pq.push(process);
			}
		}
	} while (!pq.empty());
	if (cmp == 0)
	{
		cout << endl << endl;
		PrintResult(order, idleTime);
	}
	else FindAverage();
}
void Priority_Non_Preemptive_1(bool cmp = false)
{
	int curTime = 0, idleTime = 0, cnt = 0;
	int vis[n] = {};
	priority_queue<ppii>pq;
	vector<int>order;
	if (cmp == 0) cout << "\nGantt Chart:" << endl;
	do
	{
		if (!pq.empty())
		{
			ppii process = pq.top();
			pq.pop();

			int Prio = process.first.first;
			int AT = -process.first.second;
			int id = -process.second;
			int BT = BurstTime[id];

			if (Response[id] == Not_Responsed) Response[id] = curTime;

			curTime += BT;

			order.push_back(id);
			gantt[id] = curTime;

			if (cmp == 0) cout << curTime - BT << " P" << id + 1 << " ";
		}
		if (cnt != n)
		{
			int got = 0;
			for (int i = 0; i < n; i++)
			{
				if (vis[i] == 0 && ArrivalTime[i] <= curTime)
				{
					ppii process = make_pair(pii(Priority[i], -ArrivalTime[i]), -i);
					pq.push(process);
					vis[i] = 1, got = 1;
					cnt += 1;
				}
			}
			if (got == 0)
			{
				int mnAT = 1e18, HighPrio = 0, mnID;
				for (int i = 0; i < n; i++)
				{
					if (vis[i]) continue;

					if (ArrivalTime[i] < mnAT)
					{
						mnAT = ArrivalTime[i];
						HighPrio = Priority[i];
						mnID = i;
					}
					else if (ArrivalTime[i] == mnAT)
					{
						if (Priority[i] > HighPrio)
						{
							HighPrio = Priority[i];
							mnID = i;
						}
					}
				}
				vis[mnID] = 1;
				cnt += 1;
				idleTime += mnAT - curTime;
				curTime = mnAT;

				ppii process = make_pair(pii(HighPrio, -mnAT), -mnID);
				pq.push(process);
			}
		}

	} while (!pq.empty());

	if (cmp == 0)
	{
		cout << endl << endl;
		PrintResult(order, idleTime);
	}
	else FindAverage();
}
void Priority_Non_Preemptive_2(bool cmp = false)
{
	int curTime = 0, idleTime = 0, cnt = 0;
	int vis[n] = {};
	priority_queue<ppii>pq;
	vector<int>order;
	if (cmp == 0) cout << "\nGantt Chart:" << endl;
	do
	{
		if (!pq.empty())
		{
			ppii process = pq.top();
			pq.pop();

			int Prio = -process.first.first;
			int AT = -process.first.second;
			int id = -process.second;
			int BT = BurstTime[id];

			if (Response[id] == Not_Responsed) Response[id] = curTime;

			curTime += BT;

			order.push_back(id);
			gantt[id] = curTime;

			if (cmp == 0) cout << curTime - BT << " P" << id + 1 << " ";
		}
		if (cnt != n)
		{
			int got = 0;
			for (int i = 0; i < n; i++)
			{
				if (vis[i] == 0 && ArrivalTime[i] <= curTime)
				{
					ppii process = make_pair(pii(-Priority[i], -ArrivalTime[i]), -i);
					pq.push(process);
					vis[i] = 1, got = 1;
					cnt += 1;
				}
			}
			if (got == 0)
			{
				int mnAT = 1e18, HighPrio = inf, mnID;
				for (int i = 0; i < n; i++)
				{
					if (vis[i]) continue;

					if (ArrivalTime[i] < mnAT)
					{
						mnAT = ArrivalTime[i];
						HighPrio = Priority[i];
						mnID = i;
					}
					else if (ArrivalTime[i] == mnAT)
					{
						if (Priority[i] < HighPrio)
						{
							HighPrio = Priority[i];
							mnID = i;
						}
					}
				}
				vis[mnID] = 1;
				cnt += 1;
				idleTime += mnAT - curTime;
				curTime = mnAT;

				ppii process = make_pair(pii(-HighPrio, -mnAT), -mnID);
				pq.push(process);
			}
		}

	} while (!pq.empty());

	if (cmp == 0)
	{
		cout << endl << endl;
		PrintResult(order, idleTime);
	}
	else FindAverage();
}
void Priority_Preemptive_1(bool cmp = false)
{
    for(int i = 0; i < n; i++) SaveBurst[i] = BurstTime[i];

	int curTime = 0, idleTime = 0, cnt = 0;
	int vis[n] = {};
	priority_queue<ppii>pq;
	vector<int>order;
	if (cmp == 0) cout << "\nGantt Chart:" << endl;
	do
	{
		if (!pq.empty())
		{
			ppii process = pq.top();
			pq.pop();

			int Prio = process.first.first;
			int AT = -process.first.second;
			int id = -process.second;
			int &BT = SaveBurst[id];

			int dur = (cnt != n) ? 1 : BT;

			if (Response[id] == Not_Responsed) Response[id] = curTime;

			curTime += dur;
			BT -= dur;

			if (BT != 0)
			{
				process = make_pair(pii(Prio, -AT), -id);
				pq.push(process);
			}
			else
			{
				order.push_back(id);
				gantt[id] = curTime;
			}

			if (cmp == 0) cout << curTime - dur << " P" << id + 1 << " ";
		}
		if (cnt != n)
		{
			int got = 0;
			for (int i = 0; i < n; i++)
			{
				if (vis[i] == 0 && ArrivalTime[i] <= curTime)
				{
					ppii process = make_pair(pii(Priority[i], -ArrivalTime[i]), -i);
					pq.push(process);
					vis[i] = 1, got = 1;
					cnt += 1;
				}
			}
			if (got == 0)
			{
				int mnAT = 1e18, HighPrio = 0, mnID;
				for (int i = 0; i < n; i++)
				{
					if (vis[i]) continue;

					if (ArrivalTime[i] < mnAT)
					{
						mnAT = ArrivalTime[i];
						HighPrio = Priority[i];
						mnID = i;
					}
					else if (ArrivalTime[i] == mnAT)
					{
						if (Priority[i] > HighPrio)
						{
							HighPrio = Priority[i];
							mnID = i;
						}
					}
				}
				vis[mnID] = 1;
				cnt += 1;
				idleTime += mnAT - curTime;
				curTime = mnAT;

				ppii process = make_pair(pii(HighPrio, -mnAT), -mnID);
				pq.push(process);
			}
		}

	} while (!pq.empty());

	if (cmp == 0)
	{
		cout << endl << endl;
		PrintResult(order, idleTime);
	}
	else FindAverage();
}
void Priority_Preemptive_2(bool cmp = false)
{
    for(int i = 0; i < n; i++) SaveBurst[i] = BurstTime[i];

	int curTime = 0, idleTime = 0, cnt = 0;
	int vis[n] = {};
	priority_queue<ppii>pq;
	vector<int>order;
	if (cmp == 0) cout << "\nGantt Chart:" << endl;
	do
	{
		if (!pq.empty())
		{
			ppii process = pq.top();
			pq.pop();

			int Prio = -process.first.first;
			int AT = -process.first.second;
			int id = -process.second;
			int &BT = SaveBurst[id];

			int dur = (cnt != n) ? 1 : BT;

			if (Response[id] == Not_Responsed) Response[id] = curTime;

			curTime += dur;
			BT -= dur;

			if (BT != 0)
			{
				process = make_pair(pii(-Prio, -AT), -id);
				pq.push(process);
			}
			else
			{
				order.push_back(id);
				gantt[id] = curTime;
			}

			if (cmp == 0) cout << curTime - dur << " P" << id + 1 << " ";
		}
		if (cnt != n)
		{
			int got = 0;
			for (int i = 0; i < n; i++)
			{
				if (vis[i] == 0 && ArrivalTime[i] <= curTime)
				{
					ppii process = make_pair(pii(-Priority[i], -ArrivalTime[i]), -i);
					pq.push(process);
					vis[i] = 1, got = 1;
					cnt += 1;
				}
			}
			if (got == 0)
			{
				int mnAT = 1e18, HighPrio = inf, mnID;
				for (int i = 0; i < n; i++)
				{
					if (vis[i]) continue;

					if (ArrivalTime[i] < mnAT)
					{
						mnAT = ArrivalTime[i];
						HighPrio = Priority[i];
						mnID = i;
					}
					else if (ArrivalTime[i] == mnAT)
					{
						if (Priority[i] < HighPrio)
						{
							HighPrio = Priority[i];
							mnID = i;
						}
					}
				}
				vis[mnID] = 1;
				cnt += 1;
				idleTime += mnAT - curTime;
				curTime = mnAT;

				ppii process = make_pair(pii(-HighPrio, -mnAT), -mnID);
				pq.push(process);
			}
		}

	} while (!pq.empty());

	if (cmp == 0)
	{
		cout << endl << endl;
		PrintResult(order, idleTime);
	}
	else FindAverage();
}
void RoundRobin(bool cmp = false)
{
    for(int i = 0; i < n; i++) SaveBurst[i] = BurstTime[i];
	int curTime = 0, idleTime = 0, cnt = 0;
	int vis[n] = {};

	queue<int>q;
	vector<int>order;

	if (cmp == 0) cout << "\nGantt Chart" << endl;
	while (!q.empty() || cnt != n)
	{
		if (!q.empty())
		{
			int id = q.front();
			q.pop();

			int &BT = SaveBurst[id]; // remaining burst time
			int dur = (TQ < BT) ? TQ : BT;

			if (Response[id] == Not_Responsed) Response[id] = curTime;
			curTime += dur;
			BT -= dur;
			if (cnt != n)
			{
				for (int i = 0; i < n; i++)
				{
					if (vis[i] == 0 && ArrivalTime[i] <= curTime)
					{
						q.push(i);
						vis[i] = 1;
						cnt += 1;
					}
				}
			}
			if (BT != 0) q.push(id);
			else
			{
				order.push_back(id);
				gantt[id] = curTime;
			}
			if (cmp == 0) cout << curTime - dur << " P" << id + 1 << " ";
		}
		else
		{
			int mnAT = 1e18, mnID;
			for (int i = 0; i < n; i++)
			{
				if (vis[i]) continue;

				if (ArrivalTime[i] < mnAT)
				{
					mnID = i;
					mnAT = ArrivalTime[i];
				}
			}
			vis[mnID] = 1;
			cnt += 1;
			idleTime += mnAT - curTime;
			curTime = mnAT;
			q.push(mnID);
		}
	}
	if (cmp == 0)
	{
		cout << endl << endl;
		PrintResult(order, idleTime);
	}
	else FindAverage();
}
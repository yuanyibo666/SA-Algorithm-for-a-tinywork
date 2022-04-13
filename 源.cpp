#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<stdlib.h>
using namespace std;
//Ϊÿ����������һ������
class workpiece
{
public:
	int time_cost[500];
	void inite(int m)
	{
		int temp;
			for (int i = 1; i <= m; i++)
			{
				cin >> temp;
				cin >> time_cost[i];
			}
	}
};

int workpiece_num, machine_num;//�������ͻ�����
workpiece workpiece_list[500] ;//���й����ļ���

double GetRand()
{
	srand(time(0));
	double r = rand() % 100 / (double)101;
	return r;
}

//��̬�滮��ʱ��
int dp_time(int* a)
{
	int dp[500][500];
	dp[0][1] = dp[1][0] = 0;
	//��ʼ����һ��
	memset(dp, 0, sizeof(dp));
	//��ʼ��̬�滮
	for (int i = 1; i <= machine_num; i++)
	{
		for (int j = 1; j <= workpiece_num; j++)
		{
			dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + workpiece_list[a[j]].time_cost[i];
		}
	}
	return dp[machine_num][workpiece_num];
}

int main()
{
	cin >> workpiece_num >> machine_num;
	//��ʼ��workpiece_list
	for (int i = 1; i <= workpiece_num; i++)
	{
		workpiece_list[i].inite(machine_num);
	}
	//�����ʼ�������ӹ���˳��
	srand(time(0));
	int order[500],next[500];
	for (int i = 1; i <= workpiece_num; i++)
	{
		order[i]  = i;
		next[i] = i;
	}
	//�¶�
	double T=1000;
	//�¶��½����ٶ�
	const double rate = 0.999;
	//��ʼ�˻�
	double E;
	int current_value, next_value;
	int num = 1;
	while (1)
	{
		T *= rate;
		if (T < 0.00001)
		{
			break;
		}
		cout << "try" << num << endl;
		num++;
		//ʹ�����������rand1 �� rand2 ���������ӹ���˳��
		int rand1 , rand2;
		while (1)
		{
			rand1 = rand() % workpiece_num + 1;
			rand2 = rand() % workpiece_num + 1;
			if (rand1 != rand2)
				break;
		}
		int temp = next[rand1];
		next[rand1] = next[rand2];
		next[rand2] = temp;
		//�õ����ַ�����ʱ��
		next_value = dp_time(next);
		current_value = dp_time(order);

		/*cout << "current value is " << current_value<<endl;
		cout << "next:";
		for (int i = 1; i <= workpiece_num; i++)
			cout << next[i]<<"  ";
		cout << endl;*/

		E = -(next_value - current_value);
		if (E > 0)
		{
			for (int i = 1; i <= workpiece_num; i++)
				order[i] = next[i];
		}
		else
		{
			//�����˻�ĸ���
			double probability = exp(E/T);
			double rand3 = rand() % 100 / (double)101;
			if (rand3 <= probability)
			{
				for (int i = 1; i <= workpiece_num; i++)
					order[i] = next[i];
			}
			else
			{
				for (int i = 1; i <= workpiece_num; i++)
					next[i] = order[i];
			}
		}
		cout << endl;
	}
	cout << "the shortest time is :" << dp_time(order) << endl;
}

#include <iostream>		//표준 입출력

using namespace std;

void main()
{
	int k = 0, flag = 0, t = 0, i, processNum, j, resourceNum, count = 0;	//반복문과 계산을 위한 변수
	int Process[10];		//각각의 프로세스 배열
	int MAX[10][5];			//할당량의 최대값 배열
	int Need[10][5];		//필요값(요구량) 배열
	int Allocation[10][5];	//실제 할당량 배열
	int Available[5];		//남은 자원 배열(이용가능한 자원)
	int Instance[5];		//초기 조건 인스턴스 배열
	int output[10];			//Safety 알고리즘을 만족하는 순서를 담는 배열

	int isInfinite = 0;		//알고리즘을 만족하지 못하여 무한루프에 빠졌는지 판단해주는 변수

	cout << "Resource의 수(3개~5개) : ";
	cin >> resourceNum;	//초기 자원의 개수를 입력함(A, B, C, ...)
	cout << endl;

	cout << "각 Resource의 최대 인스턴스를 입력하세요." << endl;
	for (i = 0; i < resourceNum; i++)
	{
		Available[i] = 0;
		cout << char(i + 65) << " : ";	//해당 자원의 이름(A, B, C, ...)
		cin >> Instance[i];			//초기 조건 인스턴스를 입력해줌(초기값, 설정값)
	}

	cout << endl;

	cout << "Process의 수(3개~10개) : ";
	cin >> processNum;				//프로세스 수(3개 이상 10개 이하)

	cout << endl;

	for (int i = 0; i < processNum; i++)
	{
		Process[i] = i;	//각 프로세스 초기화

		for (int j = 0; j < resourceNum; j++)
		{
			//주어진 인스턴스 보다 최대값이 크면 알고리즘의 의미가 없어진다.
			//따라서 예외처리로 처리하여 조건에 부합되지 않으면 break
			do
			{
				cout << "P[" << Process[i] << "]의 " << char(j + 65) << "의 Max 입력 : ";
				cin >> MAX[i][j];

				if (MAX[i][j] <= Instance[j])	//예외처리 부분
					break;

			} while (1);
		}
		cout << endl;
	}

	//Max 출력
	cout << endl << "[Max]" << endl;
	cout << "    ";

	//자원(A,B,C...)의 개수 만큼 
	for (int i = 0; i < resourceNum; i++)
	{
		cout << " " << char(i + 65);

	}
	cout << endl;
	for (int i = 0; i < processNum; i++)
	{
		Process[i] = i;	//각 프로세스 초기화
		cout << "P[" << Process[i] << "] ";

		for (int j = 0; j < resourceNum; j++)
		{
			cout << MAX[i][j] << " ";//최대값 출력
		}
		cout << endl;
	}
	cout << endl;


	for (int i = 0; i < processNum; i++)
	{

		for (int j = 0; j < resourceNum; j++)
		{
			//최대값 보다 할당량이 많을 순 없다.
			//따라서 예외처리로 처리하여 조건에 부합되지 않으면
			//또한, MAX값이 0일때는 0으로 나눌 수 없기 때문에 예외처리
			do
			{
				cout << "P[" << Process[i] << "]의 " << char(j + 65) << "의 Allocation 입력 : ";
				cin >> Allocation[i][j];

				if (Allocation[i][j] <= MAX[i][j])	//예외처리 부분
					break;

			} while (1);

			Available[j] += Allocation[i][j];	//사용가능 자원에 할당량 추가

		}
		cout << endl;
	}

	//Allocation 출력
	cout << "[Allocation]" << endl;
	cout << "    ";
	for (int i = 0; i < resourceNum; i++)
	{
		cout << " " << char(i + 65);

	}
	cout << endl;
	for (int i = 0; i < processNum; i++)
	{
		Process[i] = i;	//각 프로세스 초기화
		cout << "P[" << Process[i] << "] ";

		for (int j = 0; j < resourceNum; j++)
		{
			cout << Allocation[i][j] << " ";
		}
		cout << endl;
	}

	//Available 출력
	cout << endl << endl << "[Available]" << endl;
	for (int i = 0; i < resourceNum; i++)
	{
		cout << " " << char(i + 65);

	}
	cout << endl << endl << " ";

	for (int i = 0; i < resourceNum; i++)
	{
		cout << Available[i] << " ";
	}

	/*Max에서 Allocation을 빼서 Need를 출력함*/
	cout << endl << "[Need]" << endl;
	cout << "    ";
	for (int i = 0; i < resourceNum; i++)
	{
		cout << " " << char(i + 65);
		Available[i] = Instance[i] - Available[i];		//사용가능한 양을 계산
	}
	cout << endl;
	for (int i = 0; i < processNum; i++)
	{
		cout << "P[" << Process[i] << "] ";

		for (int j = 0; j < resourceNum; j++)
		{
			Need[i][j] = MAX[i][j] - Allocation[i][j];	//Max에서 Allocatio을 빼면 Need
			cout << Need[i][j] << " ";	//Need 출력
		}
		cout << endl;
	}


	/*실제 안전한 시퀀스인지 판별하는 부분*/
A:
	flag = -1;			//체크하기 위함
	isInfinite++;	//무한루프방지
	for (int i = 0; i < processNum; i++)
	{
		count = 0;
		t = Process[i];

		for (int j = 0; j < resourceNum; j++)
		{
			Need[t][j] = MAX[t][j] - Allocation[t][j];

			//필요한 양이 사용가능한 양보다 작으면 카운트
			if (Need[t][j] <= Available[j])
				count++;
		}


		if (count == resourceNum)
		{
			output[k++] = Process[i];	//알고리즘을 만족하면 안전 시퀀스에 인덱스 값 삽입

			//Available 출력
			cout << endl << endl << "[Available]" << endl;
			for (int i = 0; i < resourceNum; i++)
			{
				cout << " " << char(i + 65);

			}
			cout << endl << " ";

			for (int i = 0; i < resourceNum; i++)
			{
				cout << Available[i] << " ";
			}

			cout << endl << endl << "P[" << Process[i] << "]의 Allocation이 풀림";

			for (j = 0; j < resourceNum; j++)
			{
				Available[j] += Allocation[t][j];	//끝난 프로세스의 자원은 Available배열에 풀어줌
			}
		}
		else
			Process[++flag] = Process[i];
	}

	//알고리즘을 만족하지 못 할땐, 무한루프에 빠짐.따라서 'Not safe'를 출력하고 종료
	if (isInfinite > 50)
	{
		cout << "\tNot safe" << endl;
		return;
	}

	if (flag != -1)
	{
		processNum = flag + 1;
		goto A;	//윗 단계를 다시 거치기 위해 GoTo문 사용
	}

	//Available 출력
	cout << endl << endl << "[Available]" << endl;
	for (int i = 0; i < resourceNum; i++)
	{
		cout << " " << char(i + 65);

	}
	cout << endl << " ";

	for (int i = 0; i < resourceNum; i++)
	{
		cout << Available[i] << " ";	//Available 출력
	}

	cout << endl << endl;
	cout << "\t";


	//safe sequence를 찾아냈으므로 출력함
	for (int i = 0; i < k; i++)
	{
		cout << " P[" << output[i] << "]";
		if (i != k - 1)
			cout << " =>";
	}

	cout << endl << endl;

}

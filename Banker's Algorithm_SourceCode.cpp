#include <iostream>		//ǥ�� �����

using namespace std;

void main()
{
	int k = 0, flag = 0, t = 0, i, processNum, j, resourceNum, count = 0;	//�ݺ����� ����� ���� ����
	int Process[10];		//������ ���μ��� �迭
	int MAX[10][5];			//�Ҵ緮�� �ִ밪 �迭
	int Need[10][5];		//�ʿ䰪(�䱸��) �迭
	int Allocation[10][5];	//���� �Ҵ緮 �迭
	int Available[5];		//���� �ڿ� �迭(�̿밡���� �ڿ�)
	int Instance[5];		//�ʱ� ���� �ν��Ͻ� �迭
	int output[10];			//Safety �˰����� �����ϴ� ������ ��� �迭

	int isInfinite = 0;		//�˰����� �������� ���Ͽ� ���ѷ����� �������� �Ǵ����ִ� ����

	cout << "Resource�� ��(3��~5��) : ";
	cin >> resourceNum;	//�ʱ� �ڿ��� ������ �Է���(A, B, C, ...)
	cout << endl;

	cout << "�� Resource�� �ִ� �ν��Ͻ��� �Է��ϼ���." << endl;
	for (i = 0; i < resourceNum; i++)
	{
		Available[i] = 0;
		cout << char(i + 65) << " : ";	//�ش� �ڿ��� �̸�(A, B, C, ...)
		cin >> Instance[i];			//�ʱ� ���� �ν��Ͻ��� �Է�����(�ʱⰪ, ������)
	}

	cout << endl;

	cout << "Process�� ��(3��~10��) : ";
	cin >> processNum;				//���μ��� ��(3�� �̻� 10�� ����)

	cout << endl;

	for (int i = 0; i < processNum; i++)
	{
		Process[i] = i;	//�� ���μ��� �ʱ�ȭ

		for (int j = 0; j < resourceNum; j++)
		{
			//�־��� �ν��Ͻ� ���� �ִ밪�� ũ�� �˰����� �ǹ̰� ��������.
			//���� ����ó���� ó���Ͽ� ���ǿ� ���յ��� ������ break
			do
			{
				cout << "P[" << Process[i] << "]�� " << char(j + 65) << "�� Max �Է� : ";
				cin >> MAX[i][j];

				if (MAX[i][j] <= Instance[j])	//����ó�� �κ�
					break;

			} while (1);
		}
		cout << endl;
	}

	//Max ���
	cout << endl << "[Max]" << endl;
	cout << "    ";

	//�ڿ�(A,B,C...)�� ���� ��ŭ 
	for (int i = 0; i < resourceNum; i++)
	{
		cout << " " << char(i + 65);

	}
	cout << endl;
	for (int i = 0; i < processNum; i++)
	{
		Process[i] = i;	//�� ���μ��� �ʱ�ȭ
		cout << "P[" << Process[i] << "] ";

		for (int j = 0; j < resourceNum; j++)
		{
			cout << MAX[i][j] << " ";//�ִ밪 ���
		}
		cout << endl;
	}
	cout << endl;


	for (int i = 0; i < processNum; i++)
	{

		for (int j = 0; j < resourceNum; j++)
		{
			//�ִ밪 ���� �Ҵ緮�� ���� �� ����.
			//���� ����ó���� ó���Ͽ� ���ǿ� ���յ��� ������
			//����, MAX���� 0�϶��� 0���� ���� �� ���� ������ ����ó��
			do
			{
				cout << "P[" << Process[i] << "]�� " << char(j + 65) << "�� Allocation �Է� : ";
				cin >> Allocation[i][j];

				if (Allocation[i][j] <= MAX[i][j])	//����ó�� �κ�
					break;

			} while (1);

			Available[j] += Allocation[i][j];	//��밡�� �ڿ��� �Ҵ緮 �߰�

		}
		cout << endl;
	}

	//Allocation ���
	cout << "[Allocation]" << endl;
	cout << "    ";
	for (int i = 0; i < resourceNum; i++)
	{
		cout << " " << char(i + 65);

	}
	cout << endl;
	for (int i = 0; i < processNum; i++)
	{
		Process[i] = i;	//�� ���μ��� �ʱ�ȭ
		cout << "P[" << Process[i] << "] ";

		for (int j = 0; j < resourceNum; j++)
		{
			cout << Allocation[i][j] << " ";
		}
		cout << endl;
	}

	//Available ���
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

	/*Max���� Allocation�� ���� Need�� �����*/
	cout << endl << "[Need]" << endl;
	cout << "    ";
	for (int i = 0; i < resourceNum; i++)
	{
		cout << " " << char(i + 65);
		Available[i] = Instance[i] - Available[i];		//��밡���� ���� ���
	}
	cout << endl;
	for (int i = 0; i < processNum; i++)
	{
		cout << "P[" << Process[i] << "] ";

		for (int j = 0; j < resourceNum; j++)
		{
			Need[i][j] = MAX[i][j] - Allocation[i][j];	//Max���� Allocatio�� ���� Need
			cout << Need[i][j] << " ";	//Need ���
		}
		cout << endl;
	}


	/*���� ������ ���������� �Ǻ��ϴ� �κ�*/
A:
	flag = -1;			//üũ�ϱ� ����
	isInfinite++;	//���ѷ�������
	for (int i = 0; i < processNum; i++)
	{
		count = 0;
		t = Process[i];

		for (int j = 0; j < resourceNum; j++)
		{
			Need[t][j] = MAX[t][j] - Allocation[t][j];

			//�ʿ��� ���� ��밡���� �纸�� ������ ī��Ʈ
			if (Need[t][j] <= Available[j])
				count++;
		}


		if (count == resourceNum)
		{
			output[k++] = Process[i];	//�˰����� �����ϸ� ���� �������� �ε��� �� ����

			//Available ���
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

			cout << endl << endl << "P[" << Process[i] << "]�� Allocation�� Ǯ��";

			for (j = 0; j < resourceNum; j++)
			{
				Available[j] += Allocation[t][j];	//���� ���μ����� �ڿ��� Available�迭�� Ǯ����
			}
		}
		else
			Process[++flag] = Process[i];
	}

	//�˰����� �������� �� �Ҷ�, ���ѷ����� ����.���� 'Not safe'�� ����ϰ� ����
	if (isInfinite > 50)
	{
		cout << "\tNot safe" << endl;
		return;
	}

	if (flag != -1)
	{
		processNum = flag + 1;
		goto A;	//�� �ܰ踦 �ٽ� ��ġ�� ���� GoTo�� ���
	}

	//Available ���
	cout << endl << endl << "[Available]" << endl;
	for (int i = 0; i < resourceNum; i++)
	{
		cout << " " << char(i + 65);

	}
	cout << endl << " ";

	for (int i = 0; i < resourceNum; i++)
	{
		cout << Available[i] << " ";	//Available ���
	}

	cout << endl << endl;
	cout << "\t";


	//safe sequence�� ã�Ƴ����Ƿ� �����
	for (int i = 0; i < k; i++)
	{
		cout << " P[" << output[i] << "]";
		if (i != k - 1)
			cout << " =>";
	}

	cout << endl << endl;

}

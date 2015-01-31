#include<iostream>
#include<fstream>
#include<time.h>

using namespace std;
#define filename "file.txt"
#define SIZE 1000
int A[SIZE],B[SIZE*SIZE][4],K=0,sol=0,count=0,A2[SIZE][2],K2=1,loc;
int x=0;

void show()
{
	for (int i = 0; i < loc; ++i)
	{
		cout<<A2[i][0]<<" ";
	}
	cout<<endl<<endl<<endl;
}

void sort()
{
	int flag;
	A2[0][0]=A[0];
	for (int i = 1; i < K; ++i)
	{
		flag=1;
		for (int j = 0; j < K2; ++j)
		{
			if (A[i]==A2[j][0])
			{
				A2[j][1]++;
				flag=0;
				break;
			}
		}
		if (flag)
		{
			A2[K2++][0]=A[i];
		}

	}
}

void arrange()
{
	loc=K2;
	for (int i = 0; i < K2; ++i)
	{
		if (A2[i][1]>3)
		{
			A2[i][1]=3;
		}
	}
	for (int i = 0; i < K2; ++i)
	{
		if (A2[i][1]>0)
		{
			for (int j = 0; j < A2[i][1]; ++j)
			{
				A2[loc++][0]=A2[i][0];
			}
		}
	}
}

void read_file()
{
	char ch;
	ifstream infile(filename);
	if (!infile)
	{
		cout<<"File not found with name "<<filename<<endl;
		return;
	}
	while(infile>>A[K++])
	{
		infile>>ch;
		if(ch!=',')
		{
			cout<<"File not found in correct format missing ,"<<endl;
			return;
		}
	}
	K=K-2;
	if (K<4)
	{
		cout<<"OOPS!!"<<endl<<"File is too short!!"<<endl;
		return;
	}
	infile.close();
}

int check(int i,int j,int k,int l)
{
	for (int m = 0; m < sol; ++m)
	{
		if ((A2[i][0]==B[m][0])&&(A2[j][0]==B[m][1])&&(A2[k][0]==B[m][2])&&(A2[l][0]==B[m][3]))
		{
			return 0;
		}
	}
	return 1;
}

void subset()
{K2=loc;x=0;
	for (int i = 0; i < K2; ++i)
	{
		count++;
		//if(A2[i][0]>=A[K])
			//continue;

		for (int j = 0; j < K2; ++j)
		{
			count++;
			if(j==i)
				continue;

			//count++;
			//if(A2[i][0]*A2[j][0]>=A[K])
				//continue;

			for (int k = 0; k < K2; ++k)
			{
				count++;
				if(k==i||k==j)
					continue;

				//count++;
				//if(A2[i][0]*A2[j][0]+A2[k][0]>=A[K])
					//continue;

				for (int l = 0; l < K2; ++l)
				{
					count++;
					if(l==i||l==j||l==k)
						continue;

					//count++;
					if((A2[i][0]*A2[j][0]+A2[k][0]+A2[l][0])>A[K])
						continue;
					
					if(check(l,k,j,i))
					{
						cout<<A2[l][0]<<" "<<A2[k][0]<<" "<<A2[j][0]<<" "<<A2[i][0]<<" "<<endl;
						B[sol][0]=A2[l][0];
						B[sol][1]=A2[k][0];
						B[sol][2]=A2[j][0];
						B[sol++][3]=A2[i][0];
					}
				}
			}
		}
	}
}

int  main()
{
	clock_t t1,t2;
    t1=clock();
	read_file();
	sort();
	arrange();
	subset();
	cout<<count<<" "<<sol<<" "<<K2<<endl;
	t2=clock();
    float diff ((float)t2-(float)t1);
    cout<<diff/CLOCKS_PER_SEC<<endl;
    return 0;
}
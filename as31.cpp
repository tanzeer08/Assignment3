#include<iostream>
#include<fstream>
#include<time.h>

using namespace std;
#define filename "file.txt"
#define SIZE 1000
int A[SIZE],B[SIZE*SIZE][4],K=0,sol=0,count=0;

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
		if ((A[i]==B[m][0])&&(A[j]==B[m][1])&&(A[k]==B[m][2])&&(A[l]==B[m][3]))
		{
			return 0;
		}
	}
	return 1;
}

void subset()
{
	for (int i = 0; i < K; ++i)
	{
		count++;
		for (int j = 0; j < K; ++j)
		{
			count++;
			if(j==i)
				continue;

			for (int k = 0; k < K; ++k)
			{
				count++;
				if(k==i||k==j)
					continue;

				for (int l = 0; l < K; ++l)
				{
					count++;
					if(l==i||l==j||l==k)
						continue;

					//count++;
					if((A[i]+A[j]+A[k]*A[l])<=A[K])
					{
						//count++;
						if(check(i,j,k,l))
						{
							cout<<A[i]<<" "<<A[j]<<" "<<A[k]<<" "<<A[l]<<" "<<endl;
							B[sol][0]=A[i];
							B[sol][1]=A[j];
							B[sol][2]=A[k];
							B[sol++][3]=A[l];
						}
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
	subset();
	cout<<count<<" "<<sol<<endl;
	t2=clock();
    float diff ((float)t2-(float)t1);
    cout<<diff/CLOCKS_PER_SEC<<endl;
    return 0;
}
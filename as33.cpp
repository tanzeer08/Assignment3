#include<iostream>
#include<fstream>
#include<time.h>

using namespace std;
#define filename "file.txt"
#define SIZE 1000
int x=0;

int A[SIZE],B[SIZE*SIZE][4],K=0,sol=0,count=0,A2[SIZE][2],K2=1,loc;

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
{
	//4-0
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

			//if(A2[i][0]*A2[j][0]>=A[K])
				//continue;

			for (int k = 0; k < K2; ++k)
			{
				count++;
				if(k==i||k==j)
					continue;

				//if(A2[i][0]*A2[j][0]+A2[k][0]>=A[K])
					//continue;

				for (int l = 0; l < K2; ++l)
				{
					count++;
					if(l==i||l==j||l==k)
						continue;

					if((A2[i][0]*A2[j][0]+A2[k][0]+A2[l][0])>A[K])
						continue;

					//if(check(l,k,j,i))
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

	//0-4
	if((loc-K2)>3)
	for (int i = K2; i < loc; ++i)
	{
		count++;
		//if(A2[i][0]>=A[K])
			//continue;

		for (int j = K2; j < loc; ++j)
		{
			count++;
			if(j==i)
				continue;

			//if(A2[i][0]*A2[j][0]>=A[K])
				//continue;

			for (int k = K2; k < loc; ++k)
			{
				count++;
				if(k==i||k==j)
					continue;

				//if(A2[i][0]*A2[j][0]+A2[k][0]>=A[K])
					//continue;

				for (int l = K2; l < loc; ++l)
				{
					count++;
					if(l==i||l==j||l==k)
						continue;

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

	//2-2
	int I1,I2,I3,I4,L1,L2,L3,L4;
	if(loc-K2>1)
	for (int i1 = 0; i1 < 6; ++i1)
	{
		switch(i1)
		{
			case 0: I1=0;L1=K2; I2=0;L2=K2; I3=K2;L3=loc; I4=K2;L4=loc; break;
			case 1: I1=0;L1=K2; I2=K2;L2=loc; I3=0;L3=K2; I4=K2;L4=loc; break;
			case 2: I1=K2;L1=loc; I2=0;L2=K2; I3=K2;L3=loc; I4=0;L4=K2; break;
			case 3: I1=K2;L1=loc; I2=K2;L2=loc; I3=0;L3=K2; I4=0;L4=K2; break;
			case 4: I1=0;L1=K2; I2=K2;L2=loc; I3=K2;L3=loc; I4=0;L4=K2; break;
			case 5: I1=K2;L1=loc; I2=0;L2=K2; I3=0;L3=K2; I4=K2;L4=loc; break;
		}
		for (int i = I1; i < L1; ++i)
		{
			count++;
			//if(A2[i][0]>=A[K])
				//continue;

			for (int j = I2; j < L2; ++j)
			{
				count++;
				if(j==i)
					continue;

				//if(A2[i][0]*A2[j][0]>=A[K])
					//continue;

				for (int k = I3; k < L3; ++k)
				{
					count++;
					if(k==i||k==j)
						continue;

					//if(A2[i][0]*A2[j][0]+A2[k][0]>=A[K])
						///continue;

					for (int l = I4; l < L4; ++l)
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
	
	if(loc-K2>2)
	for (int i1 = 0; i1 < 4; ++i1)
	{
		switch(i1)
		{
			case 0: I1=0;L1=K2; I2=K2;L2=loc; I3=K2;L3=loc; I4=K2;L4=loc; break;
			case 1: I1=K2;L1=loc; I2=0;L2=K2; I3=K2;L3=loc; I4=K2;L4=loc; break;
			case 2: I1=K2;L1=loc; I2=K2;L2=loc; I3=0;L3=K2; I4=K2;L4=loc; break;
			case 3: I1=K2;L1=loc; I2=K2;L2=loc; I3=K2;L3=loc; I4=0;L4=K2; break;
		}
		//3-1
		//if(loc-K2>0)
		for (int i = I1; i < L1; ++i)
		{
			count++;
			//if(A2[i][0]>=A[K])
				//continue;

			for (int j = I2; j < L2; ++j)
			{
				count++;
				if(j==i)
					continue;

				//count++;
				//if(A2[i][0]*A2[j][0]>=A[K])
					//continue;

				for (int k = I3; k < L3; ++k)
				{
					count++;
					if(k==i||k==j)
						continue;

					//if(A2[i][0]*A2[j][0]+A2[k][0]>=A[K])
						//continue;

					for (int l = I4; l < L4; ++l)
					{
						count++;
						if(l==i||l==j||l==k)
							continue;

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

	if(loc-K2>0)
	for (int i1 = 0; i1 < 4; ++i1)
	{
		switch(i1)
		{
			case 0: I1=K2;L1=loc; I2=0;L2=K2; I3=0;L3=K2; I4=0;L4=K2; break;
			case 1: I1=0;L1=K2; I2=K2;L2=loc; I3=0;L3=K2; I4=0;L4=K2; break;
			case 2: I1=0;L1=K2; I2=0;L2=K2; I3=K2;L3=loc; I4=0;L4=K2; break;
			case 3: I1=0;L1=K2; I2=0;L2=K2; I3=0;L3=K2; I4=K2;L4=loc; break;
		}
		//3-1
		//if(loc-K2>0)
		for (int i = I1; i < L1; ++i)
		{
			count++;
			//if(A2[i][0]>=A[K])
				//continue;

			for (int j = I2; j < L2; ++j)
			{
				count++;
				if(j==i)
					continue;

				//count++;
				//if(A2[i][0]*A2[j][0]>=A[K])
					//continue;

				for (int k = I3; k < L3; ++k)
				{
					count++;
					if(k==i||k==j)
						continue;

					//if(A2[i][0]*A2[j][0]+A2[k][0]>=A[K])
						//continue;

					for (int l = I4; l < L4; ++l)
					{
						count++;
						if(l==i||l==j||l==k)
							continue;

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
	//show();
	t2=clock();
    float diff ((float)t2-(float)t1);
    cout<<diff/CLOCKS_PER_SEC<<endl;
    return 0;
}
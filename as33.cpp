/*! \mainpage Assignment 3
 *
 */

/** @file as33.cpp
 *  @brief Program 3 that seperately counts unqique integer solutions and for the repetetive integers it apply Brute Force.
 *
 *  @author Tanzeer Zarar
 *
 *  @bug No know bugs.
 */



#include<iostream>
#include<fstream>
#include<time.h>

using namespace std;
#define filename "input.txt"
#define filenameout "output.txt"
#define SIZE 1000
int x=0;

int A[SIZE],B[SIZE*SIZE][4],K=0,sol=0,count=0,A2[SIZE][2],K2=1,loc;

/** @brief It counts repetitive integers.
 *
 * This function sort() counts the repetitive numbers
 * and stores it frequency.
 *
 *  @param A2 This array contains integers with frequency.
 *  @param K Size of the input set.
 *  @param A Array storing all integers
 *  @param K2 Size of the array containing unique integers.
 *  @param A2 Array storing all unique integers and their frequency.
 *  @return Void
 */

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

/** @brief It trims the extra integers.
 *
 * This function arrange() trims extra integers which does not
 * affect the total possible tuples.
 *
 *  @param A2 Array storing all unique integers and trimmed repetetive integers.
 *  @param loc It will contain size of A2.
 *  @return Void
 */

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

/** @brief Reading input file.
 *
 * This function read_file() read input.txt file and save
 * all the integers in array A. Last index of A will contain k.
 *
 *  @param ch It will read , character.
 *  @param K Size of the set.
 *  @param A Array storing all integers
 *  @return Void
 */

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

/** @brief Check for occurence of same tuple.
 *
 * It will compare the current tuple with  the premade tuples.
 * It  returns 0 if same tuple found in the premade solutions
 * else it will return 1.
 *
 *  @param i Index for a.
 *  @param j Index for b.
 *  @param k Index for c.
 *  @param k Index for d.
 *  @param B Array that contains all premade tuples.
 *  @return Int
 */

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

/** @brief Find all possible tuples.
 *
 * It will find all the possible tuples.
 * It finds tuples in 2 ways, first for the
 * uniques integers without checking premade tuples.
 * Then for the rest repetetive integers it applies Brute Force.
 * It takes array A2 as input and then finds all
 * possible tuples that can be made.
 *
 *  @param outfile Output file pointer.
 *  @param B Array of tuples to be made.
 *  @param K2 Size of input array till unique integrs
 *  @param loc Size of input array till last integers including all repetetive integers.
 *  @return Void
 */

void subset()
{
    //4-0
    ofstream outfile(filenameout);
    for (int i = 0; i < K2; ++i)
    {
        for (int j = 0; j < K2; ++j)
        {
            count++;
            if(j==i)
                continue;

            for (int k = 0; k < K2; ++k)
            {
                count++;
                if(k==i||k==j)
                    continue;

                for (int l = 0; l < K2; ++l)
                {
                    count++;
                    if(l==i||l==j||l==k)
                        continue;

                    if((A2[i][0]*A2[j][0]+A2[k][0]+A2[l][0])>A[K])
                        continue;

                    {
                        B[sol][0]=A2[l][0];
                        B[sol][1]=A2[k][0];
                        B[sol][2]=A2[j][0];
                        B[sol++][3]=A2[i][0];
                        outfile<<A[i];
                        outfile<<" ";
                        outfile<<A[j];
                        outfile<<" ";
                        outfile<<A[k];
                        outfile<<" ";
                        outfile<<A[l];
                        outfile<<"\n";
                    }
                }
            }
        }
    }

    //0-4
    if((loc-K2)>3)
        for (int i = K2; i < loc; ++i)
        {

            for (int j = K2; j < loc; ++j)
            {
                count++;
                if(j==i)
                    continue;

                for (int k = K2; k < loc; ++k)
                {
                    count++;
                    if(k==i||k==j)
                        continue;

                    for (int l = K2; l < loc; ++l)
                    {
                        count++;
                        if(l==i||l==j||l==k)
                            continue;

                        if((A2[i][0]*A2[j][0]+A2[k][0]+A2[l][0])>A[K])
                            continue;

                        if(check(l,k,j,i))
                        {
                            B[sol][0]=A2[l][0];
                            B[sol][1]=A2[k][0];
                            B[sol][2]=A2[j][0];
                            B[sol++][3]=A2[i][0];
                            outfile<<A[i];
                            outfile<<" ";
                            outfile<<A[j];
                            outfile<<" ";
                            outfile<<A[k];
                            outfile<<" ";
                            outfile<<A[l];
                            outfile<<"\n";
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
            case 0:
                I1=0;
                L1=K2;
                I2=0;
                L2=K2;
                I3=K2;
                L3=loc;
                I4=K2;
                L4=loc;
                break;
            case 1:
                I1=0;
                L1=K2;
                I2=K2;
                L2=loc;
                I3=0;
                L3=K2;
                I4=K2;
                L4=loc;
                break;
            case 2:
                I1=K2;
                L1=loc;
                I2=0;
                L2=K2;
                I3=K2;
                L3=loc;
                I4=0;
                L4=K2;
                break;
            case 3:
                I1=K2;
                L1=loc;
                I2=K2;
                L2=loc;
                I3=0;
                L3=K2;
                I4=0;
                L4=K2;
                break;
            case 4:
                I1=0;
                L1=K2;
                I2=K2;
                L2=loc;
                I3=K2;
                L3=loc;
                I4=0;
                L4=K2;
                break;
            case 5:
                I1=K2;
                L1=loc;
                I2=0;
                L2=K2;
                I3=0;
                L3=K2;
                I4=K2;
                L4=loc;
                break;
            }
            for (int i = I1; i < L1; ++i)
            {

                for (int j = I2; j < L2; ++j)
                {
                    count++;
                    if(j==i)
                        continue;

                    for (int k = I3; k < L3; ++k)
                    {
                        count++;
                        if(k==i||k==j)
                            continue;

                        for (int l = I4; l < L4; ++l)
                        {
                            count++;
                            if(l==i||l==j||l==k)
                                continue;

                            if((A2[i][0]*A2[j][0]+A2[k][0]+A2[l][0])>A[K])
                                continue;

                            if(check(l,k,j,i))
                            {
                                B[sol][0]=A2[l][0];
                                B[sol][1]=A2[k][0];
                                B[sol][2]=A2[j][0];
                                B[sol++][3]=A2[i][0];
                                outfile<<A[i];
                                outfile<<" ";
                                outfile<<A[j];
                                outfile<<" ";
                                outfile<<A[k];
                                outfile<<" ";
                                outfile<<A[l];
                                outfile<<"\n";
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
            case 0:
                I1=0;
                L1=K2;
                I2=K2;
                L2=loc;
                I3=K2;
                L3=loc;
                I4=K2;
                L4=loc;
                break;
            case 1:
                I1=K2;
                L1=loc;
                I2=0;
                L2=K2;
                I3=K2;
                L3=loc;
                I4=K2;
                L4=loc;
                break;
            case 2:
                I1=K2;
                L1=loc;
                I2=K2;
                L2=loc;
                I3=0;
                L3=K2;
                I4=K2;
                L4=loc;
                break;
            case 3:
                I1=K2;
                L1=loc;
                I2=K2;
                L2=loc;
                I3=K2;
                L3=loc;
                I4=0;
                L4=K2;
                break;
            }
            //3-1
            for (int i = I1; i < L1; ++i)
            {
                for (int j = I2; j < L2; ++j)
                {
                    count++;
                    if(j==i)
                        continue;

                    for (int k = I3; k < L3; ++k)
                    {
                        count++;
                        if(k==i||k==j)
                            continue;

                        for (int l = I4; l < L4; ++l)
                        {
                            count++;
                            if(l==i||l==j||l==k)
                                continue;

                            if((A2[i][0]*A2[j][0]+A2[k][0]+A2[l][0])>A[K])
                                continue;

                            if(check(l,k,j,i))
                            {
                                B[sol][0]=A2[l][0];
                                B[sol][1]=A2[k][0];
                                B[sol][2]=A2[j][0];
                                B[sol++][3]=A2[i][0];
                                outfile<<A[i];
                                outfile<<" ";
                                outfile<<A[j];
                                outfile<<" ";
                                outfile<<A[k];
                                outfile<<" ";
                                outfile<<A[l];
                                outfile<<"\n";
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
            case 0:
                I1=K2;
                L1=loc;
                I2=0;
                L2=K2;
                I3=0;
                L3=K2;
                I4=0;
                L4=K2;
                break;
            case 1:
                I1=0;
                L1=K2;
                I2=K2;
                L2=loc;
                I3=0;
                L3=K2;
                I4=0;
                L4=K2;
                break;
            case 2:
                I1=0;
                L1=K2;
                I2=0;
                L2=K2;
                I3=K2;
                L3=loc;
                I4=0;
                L4=K2;
                break;
            case 3:
                I1=0;
                L1=K2;
                I2=0;
                L2=K2;
                I3=0;
                L3=K2;
                I4=K2;
                L4=loc;
                break;
            }
            //3-1
            for (int i = I1; i < L1; ++i)
            {

                for (int j = I2; j < L2; ++j)
                {
                    count++;
                    if(j==i)
                        continue;

                    for (int k = I3; k < L3; ++k)
                    {
                        count++;
                        if(k==i||k==j)
                            continue;

                        for (int l = I4; l < L4; ++l)
                        {
                            count++;
                            if(l==i||l==j||l==k)
                                continue;

                            if((A2[i][0]*A2[j][0]+A2[k][0]+A2[l][0])>A[K])
                                continue;

                            if(check(l,k,j,i))
                            {
                                B[sol][0]=A2[l][0];
                                B[sol][1]=A2[k][0];
                                B[sol][2]=A2[j][0];
                                B[sol++][3]=A2[i][0];
                                outfile<<A[i];
                                outfile<<" ";
                                outfile<<A[j];
                                outfile<<" ";
                                outfile<<A[k];
                                outfile<<" ";
                                outfile<<A[l];
                                outfile<<"\n";
                            }
                        }
                    }
                }
            }
        }
    outfile.close();
}

/** @brief Main function.
 *
 * It will first call read_file() to read input file
 * then it will call sort() to count the repetitive numbers.
 * After this arrange() is called which trim the array A to A2.
 * Then it will call subset() to find possible tuples.
 *
 * @param t1 It saves starting time of program.
 * @param t2 It saves end time of program.
 * @param diff It contains time in seconds.
 * @return Int
 */

int  main()
{
    clock_t t1,t2;
    t1=clock();
    read_file();
    sort();
    arrange();
    subset();
    t2=clock();
    float diff ((float)t2-(float)t1);
    cout<<"Time taken: "<<diff/CLOCKS_PER_SEC<<" seconds"<<endl;
    return 0;
}

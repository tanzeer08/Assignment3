/*! \mainpage Assignment 3
 *
 * \section intro Introduction
 *
 * This documentation consists of code documentation
 * for the problem statement to find 4 tuple from
 * a given set of any numbers satisfyig a linear equation.
 * It also documents various cpu utilisation time 
 * for the 3 different programs on various optimisation levels.
 *
 * \section problem Problem Statement
 *
 *  This file contains 3 different codes for implementating
 *  the following problem.
 *  Given a set S and a number k find all 4 tuples a,b,c,d 
 *  such that a+b+c*d<=k.
 *
 *
 * \section compare_sec Comparisons
 *
 * There are 3 different programs which takes different execution time
 * as per the given inputs. 
 * This comparison is based on a test case of set
 * containing number 1 to 100 and value of k as 60.
 * <table border="2" style="width:100%">
 * <tr>
 *   <th>Program</th>
 *   <th>CPU time (Optimistation Level: O0)</th>
 *   <th>CPU time (Optimistation Level: O1)</th>
 *   <th>CPU time (Optimistation Level: O2)</th>
 *   <th>CPU time (Optimistation Level: O3)</th>
 *   <th>CPU time (Optimistation Level: Ofast)</th>
 *   <th>CPU time (Optimistation Level: Os)</th>
 * </tr>
 * <tr>
 *   <td>Program 1 (as31.cpp)</td>
 *   <td>17.7664</td>  
 *   <td>5.3317</td>  
 *   <td>5.2396</td>  
 *   <td>5.1984</td> 
 *   <td>5.2942</td>    
 *   <td>7.0212</td>    
 * </tr>
 * <tr>
 *   <td>Program 2 (as32.cpp)</td>
 *   <td>17.6115</td> 
 *   <td>8.3043</td> 
 *   <td>6.3996</td>
 *   <td>6.5050</td>
 *   <td>7.1522</td>
 *   <td>9.9443</td> 
 * </tr>
 * <tr>
 *   <td>Program 3 (as33.cpp)</td>
 *   <td>0.7510</td> 
 *   <td>0.6024</td> 
 *   <td>0.5684</td> 
 *   <td>0.5155</td> 
 *   <td>0.5305</td> 
 *   <td>0.6607</td>      
 * </tr>
 * </table>
 * \section obv Observation
 *
 * It is observed that since prgm1 is completely based on Brute Forece
 * method thus when integers are unique then it will take maximum time,
 * prgm2 will also take the same time as it includes trimming which does
 * not affect the integers followed by prgm3 which takes least time as
 * for the unique integers it does not check premade tuples.
 * If all the integers are repetetive then prgm1 will take
 * more time but prgm2 & prgm3 will take less time comparatively
 * as they include trimming of extra integers and for the unique
 * integers prgm3 will not check for premade tuples thus it will again
 * take least time.
 * The time taken by all the 3 programs will vary depending on number 
 * of integers which are unique and repetetive. 
 * 
 * \section res Result
 *
 * The solution of the given problem has been successfully checked
 for all the 3 programs which are giving desired results. The programs 
 has been tested for different optimistation levels showing various 
 time taken by the programs on different optimisation levels.
 * 
 */

/** @file as31.cpp
 *  @brief Program 1 using Brute Force.
 *
 *  This file contains the code for implementating following problem.
 *  Given a set Sand a number k find all 4 tuples a,b,c,d 
 *  such that a+b+c*d<=k. There are 4 functions in this program 
 *  including main, which are read_file(), subset() & check().
 *  First of all, input array is saved in array A,
 *  and last index contains the value of k.
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
int A[SIZE],B[SIZE*SIZE][4],K=0,sol=0,count=0;


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
        if ((A[i]==B[m][0])&&(A[j]==B[m][1])&&(A[k]==B[m][2])&&(A[l]==B[m][3]))
        {
            return 0;
        }
    }
    return 1;
}

/** @brief Find all possible tuples.
 *
 * It will find all the possible tuples.
 * It takes array A as input and then finds all 
 * possible tuples that can be made.
 *
 *  @param outfile Output file pointer.
 *  @param B Array of tuples to be made.
 *  @param K Size of input array
 *  @return Void
 */

void subset()
{
    ofstream outfile(filenameout);
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

                    if((A[i]+A[j]+A[k]*A[l])<=A[K])
                    {
                        if(check(i,j,k,l))
                        {
                            B[sol][0]=A[i];
                            B[sol][1]=A[j];
                            B[sol][2]=A[k];
                            B[sol++][3]=A[l];
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
 * then it will call subset to find possible tuples
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
    subset();
    t2=clock();
    float diff ((float)t2-(float)t1);
    cout<<"Time taken: "<<diff/CLOCKS_PER_SEC<<" seconds"<<endl;
    return 0;
}

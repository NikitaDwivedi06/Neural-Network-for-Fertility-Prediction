#include<iostream>
#define N 9
#include<cmath>
#include<fstream>
using namespace std;
void update_v(float v[][N],float change_v[][N])
{
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			v[i][j]+=change_v[i][j];
		}
	}
}
void update_w(float w[],float change_w[])
{
	for(int i=0;i<N;i++)
	{
		w[i] += change_w[i];
	}
}
float f(float x)
{
	float answer = (1/(1 + exp(-1 * x)));
	return answer;
}
float differentiation(float x)
{
	float answer=f(x)*(1-f(x));
	return answer;
}
float calculate_zin(int j,float inp[],float v[][N],float bv[])
{
	float answer = bv[j];
	for(int i=0;i<N;i++)
	{
		//for(int k=0;k<N;k++)
		//{
			answer += inp[i]*v[i][j];
		//}
	}
	return answer;
}
void calculate_zop(float z[],float inp[],float v[][N],float bv[])
{
	for(int j=0;j<N;j++)
	{
		z[j]=f(calculate_zin(j,inp,v,bv));
	}
}
float calculateyin(float z[],float w[],float bw)
{
	float answer = bw;
	for(int i=0;i<N;i++)
	{
		//for(int k=0;k<N;k++)
		//{
			answer += z[i]*w[i];
		//}
	}
	//cout<<"y in"<<answer<<endl;
	return answer;
}
float calculateyop(float z[],float w[],int bw)
{
	return f(calculateyin(z,w,bw));
}
void calculate_deltav(float change_v[][N],float rate,float inp[],float v[][N],float w[],float bv[],float delk)
{
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			change_v[i][j]=rate * (delk*w[j]*differentiation(calculate_zin(j,inp,v,bv))) * inp[i];
		}
	}
}
void calculate_deltaw(float change_w[],float rate,float delk,float z[])
{
	for(int i=0;i<N;i++)
	{
		change_w[i] = rate * delk * z[i];
	}
}

float calculate_t(int inp[])//calcuating xor
{
	int a=inp[0];
	int b=inp[1];
	if(a != b)
	return 1;
	else
	return 0;
}
int main()
{
	     
	//----------------------------------DATA REQUIRED------------------------------------------------------//
	float inp[9],t;
	float v[N][N]={{0.05,0.05,0.05,0.05,0.05,0.05,0.05,0.05,0.05},{0.05,0.05,0.05,0.05,0.05,0.05,0.05,0.05,0.05}};
	float w[N]={0.05,0.05,0.05,0.05,0.05,0.05,0.05,0.05,0.05};
	float bv[N]={1,1,0,0,0,0,0,0,0};
	float bw=1,y,delk,rate;
	int num_ip=100;
	float z[N];
	float change_v[N][N],change_w[N];
	int c=1,i,j,index=0;         
	cout<<"Learning rate : ";
	cin>>rate;
	cout<<"\nEnter x1 and x2 : \n\n";
	//------------------------------------MAKING ONLY 4 ITERATIONS---------------------------------------------//
	while(c<=10000)
	{
		cout<<c<<endl;
		ifstream file("dataset.txt",std::ios_base::in);
		num_ip=100;
		while(num_ip>0)
		{
			index=0;
			float ip_value;
			while(file>>ip_value)
			{
				
				if(index < 9)
				{
					
					inp[index]=ip_value;
					index++;
				}
				else
				{
					
					t=ip_value;
					break;
				}
				
			}
		
			calculate_zop(z,inp,v,bv);
		
			y=calculateyop(z,w,bw);
			
			delk=(t-y)*differentiation(calculateyin(z,w,bw));
			calculate_deltaw(change_w,rate,delk,z);
			calculate_deltav(change_v,rate,inp,v,w,bv,delk);
			update_w(w,change_w);
			update_v(v,change_v);
			
			if(c==10000)
			{
			cout<<c<<" iteration number "<<endl;
			cout<<"input number "<<num_ip<<endl;
			cout<<"y out is"<<y<<"expected is"<<t<<endl;
		
			}
			num_ip--;
		}
		
		c++;
		file.close();	
	}
	cout<<"Enter the number of testing inputs";
	int test=0;
	float array[N],testY=0,testZ[N];
	cin>>test;
	while(test--)
	{
		cout<<"Enter the input set";
		for(int var=0 ; var<N ; var++)
			cin>>array[var];	
		calculate_zop(testZ,array,v,bv);
		testY=calculateyop(testZ,w,bw);
		cout<<"The NN output is : "<<testY<<endl;
	
	}
	
	
}

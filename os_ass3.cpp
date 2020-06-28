#include<bits/stdc++.h>
#define heap_size 100
#define magic 515
using namespace std;
int curr=0;
int domalloc(int size,int arr[],int **headptr)
{
	int temp;
	int temp1,prev,flag,prevcurr;
	if(curr==0)
	{
		if(size<=heap_size)
		{
			temp=curr+2;
			arr[0]=size;
			arr[1]=magic;
			curr=curr+size+2;
			arr[curr+1]=-1;
			arr[curr]=heap_size-(4+size);
			*headptr=&arr[curr];
		}
	}
	else
	{
		temp1=curr;
		flag=0;
		prevcurr=curr;
		while(arr[temp1]<size && arr[temp1+1]!=-1)
		{
			prev=temp1+1;
			temp1=arr[temp1+1];
			if(flag==0)
			flag=1;
		}
		if(flag==0)
		{
			if(arr[temp1]==size)
			curr=arr[temp1+1];
			else
			curr=temp1+2+size;
		}
		if(arr[temp1+1]==-1 && arr[temp1]<size)
		{
			cout<<"Allocation not possible";
			return -1;
		}
		else
		{
			temp=temp1+2;
			if(arr[temp1]==size)
			{
				if(flag==1)
				arr[prev]=arr[temp1+1];
			}
			else
			{
				curr=temp1+2+size;
				if(curr<100)
				{
					arr[curr]=arr[temp1]-size-2;
					arr[curr+1]=arr[temp1+1];
					arr[temp1]=size;
					if(flag==1)
					{
						arr[prev]=curr;
						curr=prevcurr;
					}
					*headptr=&arr[curr];
				}
				arr[temp1+1]=magic;
			}
		}
	}

	return temp;
}
void dofree(int top,int arr[],int **headptr)
{
	top-=2;
	*headptr=&arr[top];
	arr[top+1]=curr;
	curr=top;
}
void coalesce_memory(int arr[])
{
	int sum,f=0,temp1=curr,start,prev,prevprev=-1,s1=0;
	while(temp1!=-1 && arr[temp1+1]!=-1)
	{
		if(arr[temp1+1]!=-1)
		{
			if(arr[temp1+1]<temp1)
			{
				if(arr[temp1+1]==temp1-2-arr[temp1])
				{
					s1+=2;
					f=1;
					if(temp1==curr)
					{
						prev=temp1;
						curr=arr[temp1+1];
						arr[curr]+=(arr[prev]+2);
						temp1=curr;
					}
					else
					{
						prev=temp1;
						temp1=arr[temp1+1];
						arr[temp1]+=(arr[prev]+2);
						if(prevprev!=-1)
						arr[prevprev+1]=temp1;
						prevprev=temp1;
					}
				}
				else
				temp1=arr[temp1+1];
			}
			else if(arr[temp1+1]>temp1)
			{
				if(arr[temp1+1]==temp1+2+arr[temp1])
				{
					f=1;
					s1+=2;
					int next=arr[temp1+1];
					arr[temp1]+=(arr[next]+2);
					arr[temp1+1]=arr[next+1];
				}
				else
				temp1=arr[temp1+1];
			}
		}
	}
	if(f==0)
	cout<<"No adjacent free chunk available"<<endl;
	else
	{
		cout<<"Memory Coalesced successfully with saving "<<s1<<" units"<<endl;
	}
}
int main()
{
	int arr[heap_size],temp1;
	int *head=&arr[0],*a;
	int t=1,totalfree;
	string str;
	vector<pair<char,int>> v1;
	while(t!=0)
	{
		cout<<"Enter 1 to continue,0 to exit the terminal, -1 to see status of memory and -2 to coalesce memory"<<endl;
		cin>>t;
		if(t==-1)
		{
				cout<<"Free memory track:"<<endl;
				cout<<"Head: "<<curr<<endl;
				temp1=curr;
				totalfree=0;
				while(temp1!=-1)
				{
					cout<<temp1<<"("<<arr[temp1]<<")"<<" "<<"->"<<" ";
					totalfree+=arr[temp1];
					temp1=arr[temp1+1];
				}
				cout<<"Total free memory: "<<totalfree<<endl;
				cout<<"User pointers: "<<endl;

				for(auto it=v1.begin();it!=v1.end();it++)
				{
					cout<<(*it).first<<"="<<(*it).second<<"("<<arr[(*it).second-2]<<")"<<endl;
				}



		}
		if(t==1)
		{
			cin>>str;
			if(str[2]=='m' && str[3]=='a')
			{
				int x=str[9]-'0';
				x*=10;
				x+=(str[10]-'0');
				v1.push_back({str[0],domalloc(x,arr,&head)});
				cout<<curr<<" "<<arr[curr]<<" "<<arr[curr+1]<<endl;
				cout<<"*"<<t<<endl;
			}
			else if(str[0]=='f')
			{
				int f1=0;
				for(auto it=v1.begin();it!=v1.end() && f1==0;it++)
				{
					if((*it).first==str[5])
					{
						f1=1;
						dofree((*it).second,arr,&head);
						v1.erase(it);
						cout<<curr<<" "<<arr[curr]<<" "<<arr[curr+1]<<endl;
					}
				}
			}
		}
		if(t==-2)
		{
			coalesce_memory(arr);
		}
	}
	return 0;
}


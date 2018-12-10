#include "updown_extern.h"

#include<iostream>
#include<cstdlib>
#include<vector>
#include<fstream>
#include<string.h>
using namespace std;
#define MAX_LINE 1024;
int source[1000],destination[1000];
int **adjMatrix,**crossedgeMatrix,*levelarray,*numoflistarray,**samelevelcrossedgenodematrix, **commonancestormatrix;
int ***ancestormatrix;
int numofsrclist,numofdestlist,src_id_list,dest_id_list, commonancestor;
int row,col;
int county=0;
int value;
////////////////////////////////////////////////////////////////////////////////

void initalizeadjMatrix()
{
adjMatrix=new int*[num];
for(int i=0; i<num; i++)
adjMatrix[i] = new int[num];
for(int i=0;i<num;i++)
for(int j=0;j<num;j++)
adjMatrix[i][j]=0;
}
///////////////////////////////////////////////////////////////////////////////////

void updateadjMatrix(int s, int d)
{
adjMatrix[s][d]=1;
}
/////////////////////////////////////////////////////////////////////////////
void computelevel(node *a)
{
a[0].level=0;
a[0].visited=true;
for(int k=0;k<num;k++)
{
	for(int i=0;i<num;i++)
	{
		if(adjMatrix[k][i]==1)
		{
			if(a[i].visited==false)
			{
				a[i].level=a[k].level+1;
				a[i].visited=true;
			}
		}
	}
}
}
//////////////////////////////////////////////////////////////////////////////////////

void createcrossedgeMatrix(node *a)
{
int x,y,d,p,k,m,childsize,parentsize,s,s1;
node *b,*c;
b=new node[num];
c=new node[num];
	for(int i=0;i<num;i++)
	{
		s=childsize=a[i].child.size();
		s1=parentsize=a[i].parent.size();
		for(int j=0;j<childsize;)
			{
				k=a[i].level;
				b[j].vertex=a[i].child[j];
				for(int l=0;l<num;l++)
				{
				if(a[l].vertex==b[j].vertex)
				{
				m=a[l].level;
				break;
				}
				}
				if(k==m)
				{
				 x=a[i].vertex;
				 y=a[i].child[j];
				 a[i].child.erase(a[i].child.begin()+j);
		  		childsize=a[i].child.size();
				j++;
				if(childsize!=0)
				j--;
				crossedgeMatrix[x][y]=1;		
				s--;
				}
				else 
				{
				s--;
				j++;
				}
			if(s==0)
			break;
			}
		for(int j=0;j<parentsize;)
			{
				d=a[i].level;
				c[j].vertex=a[i].parent[j];
				for(int t=0;t<num;t++)
				{
				if(a[t].vertex==c[j].vertex)
				{
				p=a[t].level;
				break;
				}
				}
				if(d==p)
				{
				 x=a[i].vertex;
				 y=a[i].parent[j];
				 a[i].parent.erase(a[i].parent.begin()+j);
				parentsize=a[i].parent.size();
				j++;
				if(parentsize!=0)
				j--;
				 crossedgeMatrix[x][y]=1;		
				s1--;
				}
				else 
				{
				s1--;
				j++;
				}
			if(s1==0)
			break;
			}
	}
}
////////////////////////////////////////////////////////////////////////////////////

void createsamelevelcrossedgenodematrix(int *newvtx)
{
samelevelcrossedgenodematrix=new int*[num];
for(int i=0; i<num; i++)
samelevelcrossedgenodematrix[i] = new int[num];
for(int i=0;i<num;i++)
for(int j=0;j<num;j++)
samelevelcrossedgenodematrix[newvtx[i]][newvtx[j]]=crossedgeMatrix[i][j];
}
//////////////////////////////////////////////////////////////////////////////////////

void updatelist(node *a)
{
int s,id,id1;
node *b,*c;
	for(int i=0;i<num;i++)
	{
s=0;
row=0;
		if(a[i].parent.size()==0)
		{
		a[i].numoflist=1;
		
		a[i].ancestorlist = new int*[1];
		for(int x=0;x<1;x++)
		a[i].ancestorlist[x]=new int[num];
		for(int k=0; k<1;k++)
		for(int d=0; d<1;d++)
		a[i].ancestorlist[k][d]=a[i].vertex;
		for(int h=0;h<1;h++)
		for(int y=1;y<num;y++)
		a[i].ancestorlist[h][y]=-1;
		}

		else if(a[i].parent.size()>=1)
		{

			for(int j=0;j<a[i].parent.size();j++)
			{
			id=a[i].parent[j];		
			a[i].numoflist+=a[id].numoflist;
			}

			row=a[i].numoflist;	
			a[i].ancestorlist=new int*[row];
			for(int k=0;k<row;k++)
			a[i].ancestorlist[k]=new int[num];

			for(int l=0;l<row;l++)
			for(int t=0;t<num;t++)
			a[i].ancestorlist[l][0]=a[i].vertex;
			for(int l=0;l<row;l++)
			for(int t=1;t<num;t++)
			a[i].ancestorlist[l][t]=-1;
			for(int f=0;f<a[i].parent.size();f++)
			{
				id1=a[i].parent[f];
				int countlist = a[id1].numoflist;
				
				for(int g=s,z=0;g<row,z<countlist;g++,z++)
				{

					for(int v=1,b=0;v<num,b<num;v++,b++)
					{	

						a[i].ancestorlist[g][v]=a[id1].ancestorlist[z][b];
					}
				s++;
				}
			}					
					
		}

	}
}
//////////////////////////////////////////////////////////////////////////////////////

void initilaizeancestormatrix()
{
ancestormatrix=new int**[num];
for(int i=0;i<num;i++)
ancestormatrix[i]=new int*[num];
for(int i=0;i<num;i++)
for(int j=0;j<num;j++)
ancestormatrix[i][j]=new int[num];
for(int i=0;i<num;i++)
for(int j=0;j<num;j++)
for(int k=0;k<num;k++)
{
ancestormatrix[i][j][k]=-1;
}
}
//////////////////////////////////////////////////////////////////////////////
void buildancestormatrix(node *a, int *newvtx)
{
	int nidd,pid;
	for(int i=0;i<num;i++)
	{		pid=newvtx[i];
		for(int j=0;j<a[i].numoflist;j++)
			{
				for(int k=0;k<num;k++)
				{
					nidd=a[i].ancestorlist[j][k];
					if(nidd==-1)
					break;
					else
					ancestormatrix[pid][j][k]=newvtx[nidd];
				}
			}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////

void deleteancestormatrix(int n)
{
for(int i=0;i<n;i++)
for(int j=0;j<n;j++)
delete ancestormatrix[i][j];
for(int i=0;i<n;i++)
delete ancestormatrix[i];
delete ancestormatrix;
}

////////////////////////////////////////////////////////////////////////////////////////////

void createlevelarray(node *a, int *newvtx)
{
levelarray=new int[num];
for(int i=0;i<num;i++)
{
levelarray[newvtx[i]]=a[i].level;
}
}

//////////////////////////////////////////////////////////////////////////////////////////

void createnumoflistarray(node *a, int n, int *newvtx)
{
numoflistarray=new int[n];
for(int i=0;i<n;i++)
numoflistarray[newvtx[i]]=a[i].numoflist;
}

///////////////////////////////////////////////////////////////////////////////////////

void check(int s, int d, int *newvtx)
{
int seqcount=0;
int seqcount1=0;
	for(int p=0;p<num;p++)
	{
		if(newvtx[p]==s)
		{
		seqcount++;
		}
	}

	for(int p=0;p<num;p++)
	{
		if(newvtx[p]==d)
		seqcount1++;
	}

		if(seqcount==0)
			{
			newvtx[county]=s;
			county++;
			}

		if(seqcount1==0)
			{
			newvtx[county]=d;
			county++;
			}
}
/////////////////////////////////////////////////////////////////////////////////////////////

void initializecrossedgeMatrix()
{
crossedgeMatrix=new int*[num];
for(int i=0; i<num; i++)
crossedgeMatrix[i] = new int[num];

for(int i=0;i<num;i++)
for(int j=0;j<num;j++)
crossedgeMatrix[i][j]=0;
}
//////////////////////////////////////////////////////////////////////////////////////////

int find_common_ancestor(int start, int end)
{
numofsrclist=numoflistarray[start];
numofdestlist=numoflistarray[end];

int lvl=-1;
int temp;
for(int s=0;s<numofsrclist;s++)
	{
		for(int d=0;d<numofdestlist;d++)	
		{
			for(int m=0;m<num;m++)
			{
				for(int k=0;k<num;k++)
				{


					if(ancestormatrix[end][d][k]==-1)
					break;
					if(ancestormatrix[start][s][m]==-1)
					break;
					if(ancestormatrix[start][s][m]==ancestormatrix[end][d][k])
					{
					temp=ancestormatrix[end][d][k];

						if(levelarray[temp]>lvl)
						{
						commonancestor=temp;
						lvl=levelarray[temp];	
						src_id_list=s;
						dest_id_list=d;
						}
					}
				}
			}
		}
	}

commonancestormatrix[start][end]=commonancestor;
return src_id_list;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

void initilaizecommonancestormatrix()
{
commonancestormatrix=new int*[num];
for(int i=0; i<num; i++)
commonancestormatrix[i] = new int[num];
for(int i=0;i<num;i++)
for(int j=0;j<num;j++)
commonancestormatrix[i][j]=-1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////

void buildcommonancestormatrix(node *a,int *newvtx)
{
	for(int i=0;i<num;i++)
	{
		for(int j=0;j<num;j++)
		{
			int k=0,p=0;			
			if(i==j)
			continue;
			for(int m=0;m<a[i].child.size();m++)
			if(newvtx[j]==newvtx[a[i].child[m]])
			{
			k++;
			break;
			}
			if(k>0)
			continue;
			for(int l=0;l<a[i].parent.size();l++)
			if(newvtx[j]==newvtx[a[i].parent[l]])
			{
			p++;
			break;
			}
			if(p>0)
			continue;
			if(samelevelcrossedgenodematrix[newvtx[i]][newvtx[j]]==1)
			{
			continue;
			}
			find_common_ancestor(newvtx[i],newvtx[j]);
		}
	}
	
}

/////////////////////////////////////////////////////////////////////////////////////////////

void deletecommonancestormatrix(int n)
{
for(int i=0;i<n;i++)
delete commonancestormatrix[i];
delete commonancestormatrix;
}
////////////////////////////////////////////////////////////////////////////////
int updown(int ssss, int dddd)
{
int next,found=0,row,tmpssss=-1,tmpdddd=-1,pos;
if(levelarray[ssss]==levelarray[dddd])
{
	if(samelevelcrossedgenodematrix[ssss][dddd]==1)
	{
	next=dddd;
	found=1;
	} 
	if(found==0)
			{

tmpdddd=commonancestormatrix[ssss][dddd];

				for(int i=0;i<numoflistarray[ssss];i++)
				{
				for(int j=0;j<num;j++)
					{
						if(ancestormatrix[ssss][i][j]==-1)
						continue;
						if(ancestormatrix[ssss][i][j]==tmpdddd)
						{
						 found=1;
						 break;
						}
					}
					if(found==1)
					{
					row=i;

					next=ancestormatrix[ssss][row][1];

					break;			
					}	
				}			
			}

return next;
}
if(levelarray[ssss]>levelarray[dddd])
{	

for(int i=0;i<numoflistarray[ssss];i++)
		{
			for(int j=0;j<num;j++)
				{

					if(ancestormatrix[ssss][i][j]==-1)
					continue;
					if(ancestormatrix[ssss][i][j]==dddd)
					{

					 found=1;
					 break;
					}
				}
			if(found==1)
			{
			row=i;

			next=ancestormatrix[ssss][row][1];

			break;
			}
		}
			if(found==0)
			{

tmpdddd=commonancestormatrix[ssss][dddd];

				for(int i=0;i<numoflistarray[ssss];i++)
				{
				for(int j=0;j<num;j++)
					{
						if(ancestormatrix[ssss][i][j]==-1)
						continue;
						if(ancestormatrix[ssss][i][j]==tmpdddd)
						{
						 found=1;
						 break;
						}
					}
					if(found==1)
					{
					row=i;

					next=ancestormatrix[ssss][row][1];

					break;			
					}	
				}			
			}

return next;
}
if(levelarray[ssss]<levelarray[dddd])
{
	for(int i=0;i<numoflistarray[dddd];i++)
		{
			for(int j=0;j<num;j++)
				{
					if(ancestormatrix[dddd][i][j]==-1)
					continue;
					if(ancestormatrix[dddd][i][j]==ssss)
					{
					 pos=j-1;
					 found=1;
					 break;
					}
				}
					if(found==1)
					{
					row=i;



					next=ancestormatrix[dddd][row][pos];

					break;			
					}	
		}
			if(found==0)
			{

tmpdddd=commonancestormatrix[ssss][dddd];

				for(int i=0;i<numoflistarray[ssss];i++)
				{
				for(int j=0;j<num;j++)
					{
						if(ancestormatrix[ssss][i][j]==-1)
						continue;
						if(ancestormatrix[ssss][i][j]==tmpdddd)
						{
						 found=1;
						 break;
						}
					}
					if(found==1)
					{
					row=i;

					next=ancestormatrix[ssss][row][1];

					break;			
					}	
				}			
			}			
return next;
}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////


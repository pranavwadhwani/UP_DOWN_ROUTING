#include "updown_extern.h"
#include<iostream>
#include<cstdlib>
#include<vector>
#include<fstream>
#include<string.h>
using namespace std;
int sender[1000],receiver[1000],traffic_count,num,numofentities[200];
char traffic_file[50];

///////////////////////////////////////////////////////////////////
void computenumofentites()
{
int **matrix=NULL;
int s,d;
//cin>>num;
for(int i=0;i<200;i++)
numofentities[i]=-1;
matrix=new int*[200];
for(int i=0;i<200;i++)
matrix[i]=new int[200];
ifstream fil2;
string topology_filename = string("config/topology");
fil2.open(topology_filename.c_str());
	
if(!fil2.is_open()) 
{
cout<<"failed to open"<<endl;
exit(-1);
}

else 
{
for(int i=0; i< 200; i++)
for(int j=0; j< 200; j++)
matrix[i][j] = -1;
fil2 >> s;			
while(!fil2.eof())
{
	while(1)
	{
	if(s == -1)
	 {
						
	cout<<"Illegal specification inputfile...exiting";
	exit(-1);
	}
	fil2 >> d;					
	if(d == -1)
	break;
	else
{			

matrix[s][d] = 1;
	matrix[d][s] = 1;
numofentities[s]=1;
numofentities[d]=1;

}						
	}
fil2>>s;	
}
}

for(int i=0;i<200;i++)
{
if(numofentities[i]==-1)
break;
num=num+numofentities[i];
}
}
///////////////////////////////////////////////////////////////
bool parse_traffic(char * filename)
{
int i=0;
traffic_count=0;
    char inputline[1024];
int s,d;
    ifstream inputfile(filename);
    if (!inputfile) 
{
        cerr<<"Error in openning file "<<filename<<endl;
        return false;
    }
	 
    while (inputfile.getline(inputline, 1024, '\n'))
 {
	
        if (strchr(inputline, '#'))
            continue;
        if (strlen(inputline) == 0)
            continue;
        if (inputline[0] == '\r' || inputline[0] == '\n')
            continue;
        if (!sscanf(inputline, "%d\t%d", &s, &d)) 
            return false;
	sender[i]=s;
	receiver[i]=d;
	i++;
	traffic_count++;
}
}

/////////////////////////////////////////////////////////////////////////////

void up_down_initialize()
{
cout<<"Constructing Data Structure for UP_DOWN"<<endl;
int count=0,id=0;
int src,dest,src1,dest1;
int *vtx;
ifstream topofile;
computenumofentites();
//col=num;
node *a;
a=new node[num];
vtx=new int[num];
for(int i=0;i<num;i++)
{
a[i].vertex=i;
vtx[i]=-1;
a[i].numoflist=0;
a[i].visited=false;
}
initalizeadjMatrix();
parse_traffic("config/traffic.txt");
string topology_filename = string("config/topology");
topofile.open(topology_filename.c_str());
if(!topofile.is_open()) 
{
cout<<"failed to open"<<endl;
exit(-1);
}
else
{
	topofile >> src;			
		while(!topofile.eof())
		{
			while(1)
			{
				if(src == -1)
				{
				cout<<"Illegal specification topofile...exiting";
				exit(-1);
				}
				topofile >> dest;					
				if(dest == -1)
				break;				
				check(src,dest,vtx);
				for(int iii=0;iii<num;iii++)
				{
				if(vtx[iii]==src)
				src1=iii;
				}
				for(int jjj=0;jjj<num;jjj++)
				{
				if(vtx[jjj]==dest)
				dest1=jjj;
				}
				a[src1].child.push_back(dest1);
				a[dest1].parent.push_back(src1);
				updateadjMatrix(src1,dest1);
				count++;
			}
		topofile>>src;	
	   }
}							

						
for(int i=0;i<num;i++)
a[i].idnum=vtx[i];
computelevel(a);
initializecrossedgeMatrix();
createcrossedgeMatrix(a);
updatelist(a);
initilaizeancestormatrix();
buildancestormatrix(a,vtx);
//deleteancestormatrix(num);
createlevelarray(a,vtx);
createnumoflistarray(a,num,vtx); 
createsamelevelcrossedgenodematrix(vtx);
initilaizecommonancestormatrix();
buildcommonancestormatrix(a,vtx);
//deletecommonancestormatrix(num);


cout<<"--------------------------UP-DOWN ROUTER ACTIVE---------------------------------"<<endl<<endl;
for(int i=0;i<traffic_count;i++)
{
cout<<"Path between node-"<<sender[i]<<" and node-"<<receiver[i]<<" is : ";
int x=sender[i];
int y=receiver[i];
while(x!=y)
{
int currsrc;
cout<<x<<"->";
currsrc=x;
currsrc=updown(currsrc,y);
x=currsrc;
if(x==y)
{
cout<<y;
}
}
cout<<endl;
}
cout<<endl<<"--------------------------------ROUTING COMPLETED-------------------------------"<<endl;

cout<<"Done Constructing Data Structure for UP_DOWN"<<endl;
}

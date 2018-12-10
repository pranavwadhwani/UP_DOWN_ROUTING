#ifndef updown_extern_h
#define updown_extern_h
#include<vector>
using namespace std;
extern int *levelarray;
extern int *numoflistarray;
extern int **samelevelcrossedgenodematrix;
extern int **commonancestormatrix;
extern int ***ancestormatrix;
extern int *vtx;
extern int num;
struct node
{
int vertex;
int idnum;
vector<int> parent;
vector<int> child;
int numoflist;
int **ancestorlist;
int level;
bool visited;
};
typedef struct node node;
extern node *a,*b,*c;
extern int commonancestor;
void up_down_initialize();
bool parse_traffic(char *);
void initalizeadjMatrix();
void updateadjMatrix(int,int);
void createcrossedgeMatrix(node *);
void createsamelevelcrossedgenodematrix(int *);
void updatelist(node *);
void initilaizeancestormatrix();
void buildancestormatrix(node *, int *);
void createlevelarray(node *, int *);
void createnumoflistarray(node *,int, int *);
void check(int, int, int *);
void initializecrossedgeMatrix();
int find_common_ancestor(int, int);
void initilaizecommonancestormatrix();
void buildcommonancestormatrix(node *,int *);
int updown(int, int);
int updown1(int, int);
void computelevel(node *);
void access_ancestormatrix();
void computenumofentites();
#endif

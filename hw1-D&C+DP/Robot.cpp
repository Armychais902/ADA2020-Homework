//ask TA
#include <iostream>
#include <vector>
#include <utility>
#include <climits>
using namespace std;
class mvtype{
	public:
		int r;
		int c;
		bool j;
};
void refresh_currmax(long long int *c_max,int *c_maxr,int *c_maxc,long long int cmp,int r,long long int c){
	if(cmp>*c_max){
		*c_max=cmp;
		*c_maxr=r;
		*c_maxc=c;
	}
}
int comp3(long long int jump,long long int up,long long int left){
	if(jump>=up && jump>=left)
		return 0;
	if(up>=jump && up>=left)
		return 1;
	return 2;
}
void build_dp(int **sweet,long long int ***total,mvtype ***record,int n,int m,int k,long long int c){
	long long int l_max=LLONG_MIN;
	long long int c_max=LLONG_MIN;
	int l_maxr,l_maxc;
	int c_maxr,c_maxc;

	//initial
	for(int i=0;i<=n;i++)
		for(int l=0;l<=k;l++)
			total[i][0][l]=LLONG_MIN;
	for(int i=0;i<=m;i++)
		for(int l=0;l<=k;l++)
			total[0][i][l]=LLONG_MIN;

	for(int l=0;l<=k;l++){
		c_max=LLONG_MIN;
		if(l==0){
			total[1][1][l]=sweet[1][1];
			mvtype curr;	curr.r=-1;curr.c=-1;curr.j=false;
			record[1][1][l]=curr;
		}
		else{
			total[1][1][l]=l_max+sweet[1][1]-c*l;
			mvtype curr;	curr.r=l_maxr;curr.c=l_maxc;curr.j=true;
			record[1][1][l]=curr;	
		}

		refresh_currmax(&c_max,&c_maxr,&c_maxc,total[1][1][l],1,1);

		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(i==1 && j==1)
					continue;
				int which=comp3(l_max,total[i-1][j][l],total[i][j-1][l]);
				mvtype curr;
				switch(which){
					case 0:{		//jump
						total[i][j][l]=l_max+sweet[i][j]-c*l;
						curr.r=l_maxr;	curr.c=l_maxc;	curr.j=true;
						break;}
					case 1:{		//up
						total[i][j][l]=total[i-1][j][l]+sweet[i][j]-c*l;
						curr.r=i-1;	curr.c=j;	curr.j=false;
						break;}
					case 2:{		//left
						total[i][j][l]=total[i][j-1][l]+sweet[i][j]-c*l;
						curr.r=i;	curr.c=j-1;	curr.j=false;
						break;}
				}
				refresh_currmax(&c_max,&c_maxr,&c_maxc,total[i][j][l],i,j);
				record[i][j][l]=curr;	
			}
		}
		l_max=c_max;
		l_maxr=c_maxr;
		l_maxc=c_maxc;
	}
}
void backtrack(mvtype ***record,long long int ***total,int n,int m,int k){
	long long int maxpro=LLONG_MIN;
	int layer;
	for(int i=0;i<=k;i++){
		if(total[n][m][i]>maxpro){
			maxpro=total[n][m][i];
			layer=i;
		}
	}
	//cout<<"layer:"<<layer<<endl;
	cout<<maxpro<<endl;
	vector<mvtype> path;
	mvtype strt;	strt.r=n;	strt.c=m;	strt.j=false;
	path.push_back(strt);
	int num=0;
	int bi=n,bj=m,bl=layer;
	while(bi>0 &&  bj>0 && bl>=0){
		num++;
		mvtype tmp=record[bi][bj][bl];
		bi=tmp.r;
		bj=tmp.c;
		path.push_back(tmp);
		if(tmp.j==true)
			bl--;
		//cout<<num<<":"<<i<<" "<<j<<" "<<tmp.j<<endl;
		//cout<<"i:"<<i<<" j:"<<j<<" l:"<<l<<endl;
	}
	cout<<num-1<<endl;
	for(int i=num-2;i>=0;i--){
		if(path[i+1].j==true)
			cout<<"Jump "<<path[i].r-1<<" "<<path[i].c-1<<endl;
		else
			cout<<"Move "<<path[i].r-1<<" "<<path[i].c-1<<endl;

	}
}

int main()
{
	int n,m,k;
	long long int c;
	cin>>n>>m>>k>>c;
	int **sweet=new int *[n+1];
	long long int ***total=new long long int **[n+1];
	mvtype ***record=new mvtype **[n+1];
	for(int i=0;i<=n;i++){
		sweet[i]=new int [m+1];
		total[i]=new long long int *[m+1];
		record[i]=new mvtype *[m+1];
		for(int j=0;j<=m;j++){
			total[i][j]=new long long int [k+1];
			record[i][j]=new mvtype [k+1];
		}
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>sweet[i][j];
	
	build_dp(sweet,total,record,n,m,k,c);

	backtrack(record,total,n,m,k);

	return 0;
}

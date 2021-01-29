#include <iostream>
#include <climits>
#include <cmath>
using namespace std;
long long int exist(long long int ***dp,int i,int j,int s){
    if(s<0)
        return -1;
    else{
        return dp[i][j][s];
    }
}
int min(int a,int b){
    if(a<b)
        return a;
    else
        return b;
}
int among5case(long long int *e){
    long long int min=LLONG_MAX;
    int mini=-1;
    for(int i=0;i<5;i++){
        if(e[i]!=-1 && e[i]<min){
            min=e[i];
            mini=i;
	    }
    }
    return mini;
}
void backtrace(int maxi,int maxj,int maxs,int ***record,int *a,int *c,int *s){
    int op_pos[605]={0};
    int op_val[605]={0};
    int op_n=0;
    int bi=maxi,bj=maxj,bk=maxs;
    int rec=record[bi][bj][bk];
    int x[200]={0}; int y[200]={0};
    int length=0,lenx=0,leny=0;
    //cout<<"result"<<endl;
    while(rec!=-1){
        //cout<<bi<<" "<<bj<<" "<<bk<<endl;
        switch(rec){
            case 0:{
                bi++;
                break;
            }
            case 1:{
                bj--;
                break;
            }
            case 2:{
                x[lenx]=bi;  lenx++;
                y[leny]=bj;  leny++;
                bk-=(s[bi]+s[bj]);
                bi++;    bj--;    
                length+=2;
                break;
            }
            case 3:{
                bi++;    bj--;
                break;
            }
            case 4:{
                if(c[bi]<c[bj]){
                    op_pos[op_n]=bi; op_val[op_n]=a[bj];
                }
                else{
                    op_pos[op_n]=bj; op_val[op_n]=a[bi];
                }
                op_n++;
                x[lenx]=bi;  lenx++;
                y[leny]=bj;  leny++;
                bk-=(s[bi]+s[bj]);
                bi++;    bj--;  
                length+=2;
                break;
            }
        }
        rec=record[bi][bj][bk];
    }
    cout<<maxs<<'\n';
    cout<<op_n<<'\n';
    for(int i=0;i<op_n;i++){
        cout<<op_pos[i]<<" "<<op_val[i]<<'\n';
    }
    //rec==-1 and while loop break, but the last element isn't stored.
    length++;
    x[lenx]=bi;  lenx++;
    if(bi>bj){
        lenx--;
        length--;
    }
    cout<<length<<'\n';
    for(int i=0;i<lenx;i++){
        if(i==0)    cout<<x[0];
        else    cout<<" "<<x[i];
    }
    for(int i=leny-1;i>=0;i--)
        cout<<" "<<y[i];
    cout<<'\n';
}
void fill_in_dp(int *a,int *c,int *s,long long int ***dp,int ***record,int N,int S,int K,int D){
    int maxs=s[1],maxi=1,maxj=1;
    //dp[i][j][0] should not be zero! because dp[i][j][k] means the minimum cost for selecting candidates between [i,j] which si+...+sj=k.
    //select candidates and form s=0 is irrational (si>=1)
    
    for(int i=1;i<=N;i++){
        //j=i-1
        dp[i][i-1][0]=0;
    }
    for(int i=1;i<=N;i++){
        dp[i][i][s[i]]=0;
        if(s[i]>maxs){
            maxs=s[i];  maxi=i; maxj=i;
        }
    }
    for(int k=1;k<=S;k++){
        for(int d=1;d<N;d++){
            for(int i=1;i<=N-d;i++){
                //j=i+d
                //cout<<i<<" "<<i+d<<" "<<k<<endl;
                long long int cases[5]={-1,-1,-1,-1,-1};
                cases[0]=exist(dp,i+1,i+d,k);
                cases[1]=exist(dp,i,i+d-1,k);
                if(abs(a[i]-a[i+d])<=D){
                    cases[2]=exist(dp,i+1,i+d-1,k-s[i]-s[i+d]);
                }
                else{ 
                    cases[3]=exist(dp,i+1,i+d-1,k);
                    long long int tmp=exist(dp,i+1,i+d-1,k-s[i]-s[i+d]);
                    if(tmp!=-1)
                        cases[4]=tmp+min(c[i],c[i+d]);
                }
                int which=among5case(cases);
                if(which==-1)
                    dp[i][i+d][k]=-1;
                else
                    dp[i][i+d][k]=cases[which];
                //process operation in backtrace(): operation only in OPT solution 
                //record
                record[i][i+d][k]=which;
                
                //find cost<=K, maxscore
                if(which!=-1){
                    if(dp[i][i+d][k]<=K && k>=maxs){
                        maxs=k; maxi=i; maxj=i+d;
                    }
                }
            }
        }
    }
    backtrace(maxi,maxj,maxs,record,a,c,s);
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N,K,D;
    cin>>N>>K>>D;
    int a[N+1],c[N+1],s[N+1];
    for(int i=0;i<=N;i++){
        a[i]=0; c[i]=0; s[i]=0;
    }
    for(int i=1;i<=N;i++)
        cin>>a[i];
    for(int i=1;i<=N;i++)
        cin>>c[i];
    int score_sum=0;
    for(int i=1;i<=N;i++){
        cin>>s[i];
        score_sum+=s[i];
    }
    long long int ***dp=new long long int **[N+1];
    for(int i=0;i<N+1;i++){
        dp[i]=new long long int *[N+1];
        for(int j=0;j<N+1;j++){
            dp[i][j]=new long long int [605];
            for(int k=0;k<605;k++)
                dp[i][j][k]=-1;
        }
    }
    int ***record=new int **[N+1];
    for(int i=0;i<N+1;i++){
        record[i]=new int *[N+1];
        for(int j=0;j<N+1;j++){
            record[i][j]=new int [605];
            for(int k=0;k<605;k++)
                record[i][j][k]=-1;
        }
    }
    fill_in_dp(a,c,s,dp,record,N,score_sum,K,D);
    return 0;
}

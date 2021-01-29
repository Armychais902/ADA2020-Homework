//discuss with b08902037
#include <iostream>
#include <vector>
using namespace std;
int min(int a,int b){
    if(a<b)
        return a;
    else
        return b;
}
int eliminate(int a,int b){
    int eli=min(a,b)-1;
    if(eli>0)
        return eli;
    else
        return 0;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n=0;
    cin>>n;
    int *c1=new int [n+1];
    int *c2=new int [n+1];
    c1[0]=0;    c2[0]=0;
    for(int i=1;i<=n;i++){
        c1[i]=0;    c2[i]=0;
        cin>>c1[i];
        c2[i]=c1[i];
    }
    int strt=0;
    for(int i=1;i<=n;i++){
        if(c1[i]!=0){
            strt=i;
            break;
        }
    }
    int end=0;
    for(int i=n;i>=1;i--){
        if(c1[i]!=0){
            end=i;
            break;
        }
    }
    int flag=0;
    cin>>flag;
    vector <int> solution1;
    vector <int> solution2;
    int *cnt1=new int[n+1];    //store eli
    int *cnt2=new int[n+1];
    for(int i=0;i<=n;i++){
        cnt1[i]=0;  cnt2[i]=0;
    }
    //cout<<strt<<" "<<end<<endl;
    for(int i=strt;i<=end-1;i++){
        int eli1=eliminate(c1[i],c1[i+1]); //eli>=0
        c1[i]-=eli1;  c1[i+1]-=eli1;
        cnt1[i]+=eli1;  //store in former
    }
    for(int i=end-1;i>=strt;i--){
        int eli2=eliminate(c2[i],c2[i+1]);
        c2[i]-=eli2;  c2[i+1]-=eli2;
        cnt2[i]+=eli2;  //store in former
    }

    //part 1
    if(end-strt>=1 && c1[strt+1]>=2){
        c1[strt+1]--;
        if(flag)
            solution1.push_back(strt+1);
    }
    long long int insert1=0;
    int lminus1=0;   int minus1=0;
    for(int i=strt;i<=end;i++){
        if(flag){
            if(cnt1[i]>0){
                for(int j=0;j<cnt1[i];j++){
                    solution1.push_back(i);
                    solution1.push_back(i+1);
                }
            }
        }
        if(c1[i]>1){
            if(i==end-1)
                minus1=1;
            insert1+=c1[i]-1-minus1;
            if(flag){
                for(int j=0;j<c1[i]-1-minus1;j++){
                    if(i!=end){
                        solution1.push_back(i);
                        solution1.push_back(i+1);
                    }
                    else{
                        if(end==n){
                            solution1.push_back(i);
                            solution1.push_back(i-1);
                        }
                        else{
                            solution1.push_back(i);
                            solution1.push_back(i+1);
                        }
                    }
                }
                solution1.push_back(i);
            }
            if(minus1==1){
                minus1=0;
                lminus1=1;
            }
        }
        else if(c1[i]==1){
            if(flag)
                solution1.push_back(i);
        }
        else if(c1[i]==0){
            insert1++;
            if(flag)
                solution1.push_back(i);
        }
    }
    if(lminus1 && flag)
        solution1.push_back(end-1);
    

    //part 2
    if(end-strt>=1 && c2[strt+1]>=2){
        c2[strt+1]--;
        if(flag)
            solution2.push_back(strt+1);
    }
    long long int insert2=0;
    int lminus2=0;  int minus2=0;
    for(int i=strt;i<=end;i++){
        if(flag){
            if(cnt2[i]>0){
                for(int j=0;j<cnt2[i];j++){
                    solution2.push_back(i);
                    solution2.push_back(i+1);
                }
            }
        }
        if(c2[i]>1){
            if(i==end-1)
                minus2=1;
            insert2+=c2[i]-1-minus2;
            if(flag){
                for(int j=0;j<c2[i]-1-minus2;j++){
                    if(i!=end){
                        solution2.push_back(i);
                        solution2.push_back(i+1);
                    }
                    else{
                        if(end==n){
                            solution2.push_back(i);
                            solution2.push_back(i-1);
                        }
                        else{
                            solution2.push_back(i);
                            solution2.push_back(i+1);
                        }
                    }
                }
                solution2.push_back(i);
            }
            if(minus2==1){
                minus2=0;
                lminus2=1;
            }
        }
        else if(c2[i]==1){
            if(flag)
                solution2.push_back(i);
        }
        else if(c2[i]==0){
            insert2++;
            if(flag)
                solution2.push_back(i);
        }
    }
    if(lminus2 && flag)
        solution2.push_back(end-1);
    
    if(insert1<insert2){
        cout<<insert1<<endl;
        for(int i=0;i<solution1.size();i++){
            if(i==0)
                cout<<solution1[i];
            else
                cout<<" "<<solution1[i];
        }cout<<'\n';
    }
    else{
        cout<<insert2<<endl;
        for(int i=0;i<solution2.size();i++){
            if(i==0)
                cout<<solution2[i];
            else
                cout<<" "<<solution2[i];
        }cout<<'\n';
    }

    return 0;
}

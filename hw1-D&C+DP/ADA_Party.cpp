//discuss with b08902037
#include <iostream>
#include <climits>
#include <vector>
using namespace std;
void prefix_sum(vector<int>& bag,vector<int>& p_mod,int N,int K){
    p_mod.push_back(0);
    for(int i=1;i<=N;i++){
        int tmp=(p_mod[i-1]+bag[i]%K)%K;
		p_mod.push_back(tmp);
	}
}
long long int max_min_cases(vector<int>& bag,vector<int>& p_mod,vector<long long int>& same_mod,int front,int mid,int end,int K){
    long long int mgood=0;

    //left: max, min
    int lmax=INT_MIN, lmin=INT_MAX;
    int j=mid+1;
    for(int i=mid;i>=front;i--){
        lmax=(bag[i]>lmax)?bag[i]:lmax;
        lmin=(bag[i]<lmin)?bag[i]:lmin;
        while(j<=end && bag[j]<=lmax && bag[j]>=lmin){
            same_mod[p_mod[j]]++;
            j++;
        }
        int tar=(p_mod[i-1]+lmax%K+lmin%K)%K;
        mgood+=same_mod[tar];
    }
    for(int clr=mid+1;clr<j;clr++)
        same_mod[p_mod[clr]]=0;
    
    //right: max,min
    int rmax=INT_MIN, rmin=INT_MAX;
    j=mid;
    for(int i=mid+1;i<=end;i++){
        rmax=(bag[i]>rmax)?bag[i]:rmax;
        rmin=(bag[i]<rmin)?bag[i]:rmin;
        while(j>=front && bag[j]<rmax && bag[j]>rmin){
            same_mod[p_mod[j-1]]++;
            j--;
        }
        //same_mod[p_mod[j]]++;
        int tar=(p_mod[i]-rmax%K-rmin%K+2*K)%K;
        mgood+=same_mod[tar];
    }
    for(int clr=mid;clr>j;clr--)
        same_mod[p_mod[clr-1]]=0;
    
    //left: max, right: min
    lmax=INT_MIN;
    lmin=INT_MAX;   rmin=INT_MAX;
    int crmin=INT_MAX;
    j=mid+1;    int k=mid+1;
    for(int i=mid;i>=front;i--){
        lmax=(bag[i]>lmax)?bag[i]:lmax;
        lmin=(bag[i]<lmin)?bag[i]:lmin;
        while(j<=end && bag[j]<=lmax){
            rmin=(bag[j]<rmin)?bag[j]:rmin;
            int tmp_mod=(p_mod[j]-rmin%K+K)%K;
            same_mod[tmp_mod]++;
            j++;
        }
        while(k<j && bag[k]>=lmin){
            crmin=(bag[k]<crmin)?bag[k]:crmin;
            int tmp_mod=(p_mod[k]-crmin%K+K)%K;
            same_mod[tmp_mod]--;
            k++;
        }
        if(k<j){
            int tar=(p_mod[i-1]+lmax%K)%K;
            mgood+=same_mod[tar];
        }
    }
    for(int clr=k;clr<j;clr++){
        crmin=(bag[clr]<crmin)?bag[clr]:crmin;
        int tmp_mod=(p_mod[clr]-crmin%K+K)%K;
        same_mod[tmp_mod]=0;
    }

    //right: max, left: min
    rmax=INT_MIN;
    rmin=INT_MAX;   lmin=INT_MAX;
    int clmin=INT_MAX;
    j=mid;    k=mid;
    for(int i=mid+1;i<=end;i++){
        rmax=(bag[i]>rmax)?bag[i]:rmax;
        rmin=(bag[i]<rmin)?bag[i]:rmin;
        while(j>=front && bag[j]<rmax){
            lmin=(bag[j]<lmin)?bag[j]:lmin;
            int tmp_mod=(p_mod[j-1]+lmin%K)%K;
            same_mod[tmp_mod]++;
            j--;
        }
        while(k>j && bag[k]>rmin){
            clmin=(bag[k]<clmin)?bag[k]:clmin;
            int tmp_mod=(p_mod[k-1]+clmin%K)%K;
            same_mod[tmp_mod]--;
            k--;
        }
        if(k>j){
            int tar=(p_mod[i]-rmax%K+K)%K;
            mgood+=same_mod[tar];
        }
    }
    for(int clr=k;clr>j;clr--){
        clmin=(bag[clr]<clmin)?bag[clr]:clmin;
        int tmp_mod=(p_mod[clr-1]+clmin%K)%K;
        same_mod[tmp_mod]=0;
    }

    return mgood;
}
long long int good_pair(vector<int>& bag,vector<int>& p_mod,vector<long long int>& same_mod,int front,int end,int K){
    if(front==end)
        return 0;
    if(front+1==end)
        return 1;
    int mid=(front+end)/2;
    long long int lgood=good_pair(bag,p_mod,same_mod,front,mid,K);
	long long int rgood=good_pair(bag,p_mod,same_mod,mid+1,end,K);
    long long int mgood=max_min_cases(bag,p_mod,same_mod,front,mid,end,K);
    return lgood+mgood+rgood;
}
int main()
{
    ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int N,K;
	cin>>N>>K;
	vector<int> bag;
	bag.push_back(-1);
	for(int i=1;i<=N;i++){
		int a;
		cin>>a;
		bag.push_back(a);
	}
    vector<int> p_mod;
    prefix_sum(bag,p_mod,N,K);
    vector<long long int> same_mod(K,0);
    /*for(int i=0;i<=N;i++)
	    cout<<p_mod[i]<<endl;
    cout<<"----"<<endl;
    for(int i=0;i<K;i++)
	    cout<<same_mod[i]<<endl;
	*/
    //cout<<"result: ";
    long long int goods=good_pair(bag,p_mod,same_mod,1,N,K);
    cout<<goods<<endl;
    return 0;
}

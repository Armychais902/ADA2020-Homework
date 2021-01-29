#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class segment{
    public:
        int index;
        int L;
        int R;
        long long int W;
};
bool cmpL(segment a,segment b){
    if(a.L<b.L)
        return true;
    else
        return false;
}
bool cmpR(segment a,segment b){
    if(a.R<b.R)
        return true;
    else
        return false;
}
//return value need not be the exact covering K: if OK:<=K, if not:-1
long long int cover_enough(int M,int N,long long int V,long long int lK,const vector <segment>& each_segs,vector<long long int>& usage){
    long long int K=lK;
    long long int *record=new long long int[M+1]; //0~M
    for(int i=0;i<=M;i++)
        record[i]=0;
    vector<segment> maxh;
    int seg_num=0;  //current type_num of segment pushed into heap
    for(int i=0;i<=M;i++){
        if(i==M){
            if(lK>=0)   return K-lK;
        }
        if(i==0){
            while(seg_num<N && each_segs[seg_num].L==i){
                maxh.push_back(each_segs[seg_num]);
                seg_num++;
            }
            if(seg_num==0)  //don't has L=0 => fail
                return -1;
            //make_heap at first time
            make_heap(maxh.begin(),maxh.end(),cmpR);
            //pop v segment, segment may be different
            long long int pi=0; //used seg
            while(pi<V){
                //maxh if empty?
                if(maxh.size()==0)
                    return -1;
                segment tmp=maxh.front();   //front to check, not pop
                //cout<<tmp.L<<" "<<tmp.R<<" "<<tmp.W-usage[tmp.index]<<endl;
                if( (tmp.W-usage[tmp.index]) <= (V-pi) ){    //remaining W
                    pi+=(tmp.W-usage[tmp.index]);
                    record[tmp.R]+=(tmp.W-usage[tmp.index]);
                    lK-=(tmp.W-usage[tmp.index]);
                    usage[tmp.index]+=(tmp.W-usage[tmp.index]);
                    pop_heap(maxh.begin(),maxh.end(),cmpR);
                    maxh.pop_back();
                }else{
                    usage[tmp.index]+=(V-pi);
                    record[tmp.R]+=(V-pi);
                    lK-=(V-pi);
                    pi+=(V-pi);
                }
            }
        }
        while(seg_num<N && each_segs[seg_num].L==i){
            maxh.push_back(each_segs[seg_num]);
            seg_num++;
            push_heap(maxh.begin(), maxh.end(),cmpR);
        }
        if(record[i]>0){    //pop record[i] segment, segment may be different
            long long int pi=0; //used seg
            while(pi<record[i]){
                if(maxh.size()==0)
                    return -1;
                segment tmp=maxh.front();   //front to check, not pop
                //cout<<tmp.L<<" "<<tmp.R<<" "<<tmp.W-usage[tmp.index]<<endl;
                if(tmp.R<=i){
                    return -1;
                }
                if( (tmp.W-usage[tmp.index]) <= (record[i]-pi) ){    //remaining W
                    lK-=(tmp.W-usage[tmp.index]);
                    pi+=(tmp.W-usage[tmp.index]);
                    record[tmp.R]+=(tmp.W-usage[tmp.index]);
                    usage[tmp.index]+=(tmp.W-usage[tmp.index]);
                    pop_heap(maxh.begin(),maxh.end(),cmpR);
                    maxh.pop_back();
                }else{
                    lK-=(record[i]-pi);
                    usage[tmp.index]+=(record[i]-pi);
                    record[tmp.R]+=(record[i]-pi);
                    pi+=(record[i]-pi);
                }
            }
        }
        if(lK<0)
            return -1;
    }
}
void binary_searchV(long long int K,long long int sumV,int M,int N,vector<segment> segs){
    if(K==0){
        cout<<"0"<<endl;
        for(int i=0;i<N;i++){
            cout<<"0 ";
        }cout<<endl;
        return;
    }
    //check V=1 and V=maxV
    vector<long long int> usage(N,0);
    long long int k1=cover_enough(M,N,1,K,segs,usage);
    if(k1==-1){
        cout<<"0"<<endl;
        for(int i=0;i<N;i++){
            cout<<"0 ";
        }cout<<endl;
        return;
    }
    for(int i=0;i<N;i++)
        usage[i]=0;
    long long int ksum=cover_enough(M,N,sumV,K,segs,usage);
    if(ksum<=K && ksum!=-1){
        cout<<sumV<<endl;
        for(int i=0;i<N;i++){
            cout<<usage[i]<<" ";
        }cout<<endl;
        return;
    }
    for(int i=0;i<N;i++)
        usage[i]=0;
    
    //start binary search
    long long int l=1,r=sumV;
    long long int finmid=0;
    vector<long long int> finusage(N,0);
    while(r>=l){
        long long int mid=(l+r)/2;
        for(int i=0;i<N;i++)
            usage[i]=0;
        long long int result=cover_enough(M,N,mid,K,segs,usage);
        if(result!=-1 && result<=K){    //don't use == K since there might not be a solution or it might have larger score with same K
            l=mid+1;
            finmid=mid;
            for(int i=0;i<N;i++){
                finusage[i]=usage[i];
            }
        }
        else if(result==-1){
            r=mid-1;
        }
    }
    cout<<finmid<<endl;
    for(int i=0;i<N;i++){
        if(i==0)
            cout<<finusage[i];
        else
            cout<<" "<<finusage[i];
    }cout<<endl;
    return;

}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N,M;
    long long int K;
    cin>>N>>M>>K;
    vector<segment> segs;
    long long int sumV=0;
    for(int i=0;i<N;i++){
        segment tmp;
        cin>>tmp.L>>tmp.R>>tmp.W;
        tmp.index=i;
        segs.push_back(tmp);
        sumV+=tmp.W;
    }
    sort(segs.begin(),segs.end(),cmpL);
    binary_searchV(K,sumV,M,N,segs);
    
    return 0;
}

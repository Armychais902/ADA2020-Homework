//reference:
//lecture slides and site:https://www.geeksforgeeks.org/closest-pair-of-points-using-divide-and-conquer-algorithm/
#include <iostream>
#include<algorithm>
#include<climits>
#include<vector>
using namespace std;
class point{
    public:
        long long int x;
        long long int y;
};
bool cmp_x(point a,point b){
    return (a.x<b.x);
}
bool cmp_y(point a,point b){
    return (a.y<b.y);
}
long long int distance(point a,point b){
    return ((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
long long int brutal(vector<point>& cx,int strt,int n){
    long long int min=LLONG_MAX;
    long long int dist=0;
    for(int i=strt;i<strt+n;i++){
        for(int j=i+1;j<strt+n;j++){
            dist=distance(cx[i],cx[j]);
            if(dist<min)
                min=dist;
        }
    }
    return min;
}
long long int strip_closest(vector<point>& strip,int n,long long int min_d){
    long long int min=min_d;
    sort(strip.begin(),strip.end(),cmp_y);
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n && j<i+8 && (strip[j].y-strip[i].y)*(strip[j].y-strip[i].y)<min;j++){
            long long int dist=distance(strip[i],strip[j]);
            if(dist<min)
                min=dist;
        }
    }
    return min;
}
long long int closest(vector<point>& cx,int strt,int n){
    if(n<=3)
        return brutal(cx,strt,n);
    int mid=n/2;
    int mid_x=cx[strt+mid].x;
    long long int l_min=closest(cx,strt,mid);
    //cout<<"l="<<l_min<<endl;
    long long int r_min=closest(cx,strt+mid,n-mid);
    //cout<<"r="<<r_min<<endl;
    long long int min_d=(l_min<r_min)?l_min:r_min;
    //process strip
    vector<point> strip;
    int sn=0;
    for(int i=strt;i<strt+n;i++){
        if((cx[i].x-mid_x)*(cx[i].x-mid_x)<min_d){
	strip.push_back(cx[i]);
            sn++;
        }
    }
    long long int strip_min=strip_closest(strip,sn,min_d);
    min_d=(strip_min<min_d)?strip_min:min_d;
    return min_d;
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
    int N;
    vector<point> cx;
    cin>>N;
    for(int i=0;i<N;i++){
	point tmp;
	cin>>tmp.x>>tmp.y;
	cx.push_back(tmp);
    }
    /*cout<<"***"<<endl;
    for(int i=0;i<N;i++){
        cout<<"?"<<endl;
        cout<<cx[i].x<<" "<<cx[i].y<<endl;
    }*/
    sort(cx.begin(),cx.end(),cmp_x);
    /*cout<<"---"<<endl;
    for(int i=0;i<N;i++){
        cout<<cx[i].x<<" "<<cx[i].y<<endl;
    }
    cout<<"OK"<<endl;*/
    long long int max_rev=-closest(cx,0,N);
    cout<<max_rev<<'\n';
    return 0;
}

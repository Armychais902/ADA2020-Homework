//discuss with b08902056
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "helper.h"
using namespace std;
class event{
	public:
		string type;
		long long int pd;
		int c;
		long long int k;
		int l,r;
		event(){
			k=0;
		}
};
bool cmp(event *a,event *b){
	if(a->pd<b->pd)
		return true;
	if(a->pd==b->pd && a->type=="P")
		return true;
	return false;
}
void merge(event **sort_event,int front,int mid,int end){
	int ln=mid-front+1;
	int rn=end-mid;
	event **left=new event*[ln];
	event **right=new event*[rn];
	for(int i=0;i<ln;i++)
		left[i]=sort_event[front+i];
	for(int i=0;i<rn;i++)
		right[i]=sort_event[mid+1+i];
	int i=0,j=0,k=front;
	while(i<ln && j<rn){
		if(left[i]->pd<right[j]->pd){
			sort_event[k++]=left[i++];
		}
		else if(left[i]->pd==right[j]->pd && left[i]->type=="P"){
			sort_event[k++]=left[i++];
		}
		else if(left[i]->pd==right[j]->pd && right[j]->type=="P"){
			sort_event[k++]=right[j++];
		}
		else{
			sort_event[k++]=right[j++];
			
		}
	}
	while(i<ln)
		sort_event[k++]=left[i++];
	while(j<rn)
		sort_event[k++]=right[j++];
	delete [] left;
	delete [] right;

}
void merge_sort(event **sort_event,int front,int end){
	if(front<end){
		int mid=(front+end)/2;
		merge_sort(sort_event,front,mid);
		merge_sort(sort_event,mid+1,end);
		merge(sort_event,front,mid,end);
	}
}
void process_event(vector<event>& game,int front,int mid,int end){
	//sort according to pd
	//cout<<"process event:"<<front<<" "<<mid<<" "<<end<<endl;
	event **sort_event=new event*[end-front+1];
	for(int i=0;i<end-front+1;i++){
		sort_event[i]=NULL;
	}
	int si=0;
	for(int i=front;i<=mid;i++){
		if(game[i].type=="P"){
			sort_event[si]=&game[i];
			si++;
		}
	}
	for(int i=mid+1;i<=end;i++){
		if(game[i].type=="A"){
			sort_event[si]=&game[i];
			si++;
		}
	}
	//cout<<"after collect"<<endl;
	if(si==0)
		return;
	//cout<<"before sort"<<endl;
	merge_sort(sort_event,0,si-1);
	//sort(sort_event,sort_event+si,cmp);
	//cout<<"after sort"<<endl;
	//attack
	vector<long long int> player_prev;
	for(int i=0;i<si;i++){
		event curr=*sort_event[i];
		if( curr.type=="P" ){
			player_prev.push_back(Memory::get(curr.c));
		}
		else{
			player_prev.push_back(0);
			Memory::add(curr.l,curr.r,curr.k);
		}
	}
	for(int i=0;i<si;i++){
		if( sort_event[i]->type=="P" ){
			sort_event[i]->k+=Memory::get(sort_event[i]->c)-player_prev[i];
			//cout<<sort_event[i]->c<<" user:"<<sort_event[i]->k<<endl;
		}
	}
	delete [] sort_event;
}
void divide_conquer(vector<event>& game,int front,int end){
	if(front==end)
		return;
	int mid=(front+end)/2;
	//cout<<front<<" "<<mid<<" "<<end<<endl;
	divide_conquer(game,front,mid);
	divide_conquer(game,mid+1,end);
	process_event(game,front,mid,end);
}
int main(){
	int N,M;
	string type;
	cin>>N>>M;
	vector<event> game;
	Memory::reset();
	for(int i=0;i<M;i++){
		cin>>type;
		event tmp;
		if(type=="P"){
			cin>>tmp.c>>tmp.pd;
		}
		else{
			cin>>tmp.l>>tmp.r>>tmp.pd>>tmp.k;

		}
		tmp.type=type;
		game.push_back(tmp);
	}
	divide_conquer(game,0,M-1);
	for(int i=0;i<M;i++){
		if(game[i].type=="P"){
			cout<<game[i].k<<endl;
		}
	}
	return 0;
}

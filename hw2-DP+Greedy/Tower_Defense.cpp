//discuss with b08902056
#include <iostream>
using namespace std;
int main()
{
    long long int N,K;
    long long int A,B;
    cin>>N>>K>>A>>B;
    long long int *s= new long long int[N+1];
    long long int **record= new long long int* [2];
    for(int i=0;i<2;i++)
        record[i]= new long long int [N+1];
    for(int i=0;i<2;i++){
        for(long long int j=0;j<=N;j++){
            record[i][j]=0;
        }
    }
    s[0]=0;
    for(long long int i=1;i<=N;i++)
        cin>>s[i];
    
    //bool cnt=false;
    long long int c1max=0;
    long long int c2max=0;

    //boundary
    //although if all the s[i] is negative, our col 0 is always 0. So the case "take none of them" would be considered.
    long long int Max=0;
    for(long long int i=1;i<=N;i++){
        record[0][i]=s[i];
	Max=(record[0][i]>Max)?record[0][i]:Max;
    }

    //i must be choosed or the 'i' of A*i might not be the same as record[0][i]
    long long int l=0;
    for(l=1;l<K;l++){
	    //cout<<l<<endl;
        if(l%2==0){
            record[0][1]=s[1];
	    Max=(record[0][1]>Max)?record[0][1]:Max;
            c1max=record[1][1];
            c2max=record[1][1]+A;
            for(long long int i=2;i<=N;i++){
                //case 1
                if(i-B>=1)
                    c1max=(record[1][i-B]>c1max)?record[1][i-B]:c1max;
                
                //case 2
                long long int tmp2=c2max+A*B-A*i;
                c2max=(record[1][i]+A*i>c2max)?record[1][i]+A*i:c2max;
                
                if(i-B>=1){
                    if(tmp2>c1max)
                        record[0][i]=tmp2+s[i];
                    else
                        record[0][i]=c1max+s[i];
                }
                else
                    record[0][i]=tmp2+s[i]; 
		if(record[0][i]>Max)
			Max=record[0][i];
	    }
	    /*for(int i=0;i<=N;i++)
		    cout<<record[0][i]<<" ";
	    cout<<endl;*/
        }
        else{
            record[1][1]=s[1];
	    Max=(record[1][1]>Max)?record[1][1]:Max;
            c1max=record[0][1];
            c2max=record[0][1]+A;
            for(long long int i=2;i<=N;i++){
                //case 1
                if(i-B>=1)
                    c1max=(record[0][i-B]>c1max)?record[0][i-B]:c1max;
                
                //case 2
                long long int tmp2=c2max+A*B-A*i;
                c2max=(record[0][i]+A*i>c2max)?record[0][i]+A*i:c2max;
                
                if(i-B>=1){
                    if(tmp2>c1max)
                        record[1][i]=tmp2+s[i];
                    else
                        record[1][i]=c1max+s[i];
                }
                else
                    record[1][i]=tmp2+s[i];
		if(record[1][i]>Max)
			Max=record[1][i];
            }
	    /*for(int i=0;i<=N;i++)
		    cout<<record[1][i]<<" ";
	    cout<<endl;*/
        }
    }
    cout<<Max<<endl;
    
    delete [] s;
    for(int i=0;i<2;i++)
	    delete [] record[i];
    delete [] record;
    return 0;
}

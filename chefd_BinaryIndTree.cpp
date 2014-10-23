/*
Chef has an array containing N integers. You have to make M queries. Each query has one of the two types:
 
1 l r p - Select all the numbers having indices between l and r (inclusive) that are divisible by p and divide them by p,
where p is in set {2, 3, 5}.
2 l d - Modify the l-th number in the array to d.
 
Please help Chef in finding out the array after all the M queries.
Input

The first line of the input contains a single integer N denoting the number of integers in given array.
The second line contains N space-separated integers A1, A2, ..., AN denoting the given array.
Next line contains a single integer M denoting the number of queries.
Each of the following M lines describes a single query in the format given in the statement.
Output

Output a single line containing N integers denoting the array after all the M queries.
Constraints

1 ≤ M ≤ 105
1 ≤ l ≤ r ≤ N
1 ≤ Ai ≤ 109
In each query of first type, p is in set {2, 3, 5}
Subtask 1 (20 points): 1 ≤ N ≤ 100
Subtask 2 (35 points): 1 ≤ N ≤ 105, there is no query of second type
Subtask 3 (45 points): 1 ≤ N ≤ 105
Example

Input:
3
1 2 3
5
1 2 2 2
1 2 2 2
2 2 3
1 2 3 3
2 1 5

Output:
5 1 1

*/

//implemente chefd using binary indexed tree
#include<bits/stdc++.h>
using namespace std;

template<class X>
class BinaryIndexedTree{

	private: 
	X  niu(X S){
		return ( S &(-S));
	}
	X Insert(vector<int> &Vec,int a, X val){
		while(a < Vec.size()){
			Vec[a] +=val;
			a += niu(a);
		}
	}
	X Query(int a){
		X aa = X(a);
		X first =X(0);
		while(aa){
			first += Tab1[aa];
			aa -= niu(aa);
		}
		first *= X(a);
		aa =X(a);
		X second =X(0);
		while(aa){
			second += Tab2[aa];
			aa -= niu(aa);
		}
		return first-second;
	}
	public:
	vector<X> Tab1;
	vector<X> Tab2;
	BinaryIndexedTree(int n){
		Tab1.assign(n+1,X(0));
		Tab2.assign(n+1,X(0));
	}
	X query(int a,int b){
		return Query(b)-Query(a-1);
	}
	X insert(int a, int b, X val){
	Insert(Tab1,a,val);
	Insert(Tab1,b+1,-val);
	Insert(Tab2,a,val*(a-1));
	Insert(Tab2,b+1,-val*b);
	
	}
};



int main()
{
	ios_base::sync_with_stdio(0);
	int n;
	cin >>n;
	vector<int> arr(n+1);
	for(int i=0; i<n ; i++)
		cin >>arr[i+1];
	int m;
	cin >> m;
	BinaryIndexedTree<int>BIT2(n+10);
	BinaryIndexedTree<int>Bit3(n+10);
	BinaryIndexedTree<int>Bit5(n+10);
	for(int i=0 ; i<m; i++){
		int q;
		cin >>q;
		if(q ==1){
		int l,r,p;
		cin >>l>>r>>p;
		if(p==2)
			BIT2.insert(l,r,1);
		else if(p==3)
			Bit3.insert(l,r,1);
		else if(p==5)
			Bit5.insert(l,r,1);	
		}
		else
		{
		 int a,d;
		 cin >>a>>d;
		 int x= BIT2.query(a,a);
		 BIT2.insert(a,a,-x);
		 x=Bit3.query(a,a);
		 Bit3.insert(a,a,-x);
		 Bit5.insert(a,a,-x);
		 x=Bit5.query(a,a);
		 arr[a]=d;
		}
	}
	for (int i=1;i<=n;i++){
	   int tmp[3]={BIT2.query(i,i),Bit3.query(i,i),Bit5.query(i,i)};
	   while(arr[i]%2==0 &&tmp[0]){
		arr[i]/=2;
		tmp[0]--;
	   }
	   while ( arr[i]%3==0 &&tmp[1]){
		arr[i]/=3;
		tmp[1]--;
	   }
	   while(arr[i]%3==0 &&tmp[2]){
	    arr[i]/=5;
		tmp[2]--;
	   }
	   cout<<arr[i]<<" ";
	}
	cout<<endl;
		
}
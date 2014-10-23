/*

Pre-requisites :
Binary Indexed Tree or Sets in C++[Balanced Binary Search Trees]

Problem:
You are given an array of N integers. You have to make M queries. Each query has one of the two types:

(1, l, r, p) - choose all numbers with indexes between l to r. Divide all numbers by p, that are divisible by p.
(2, l, d) - assign l-th number in array to d
Also p is in [ 2 3 5]

Explanation
Let us assume that we have a data structure which can give us the next number divisible by p in the range [l r] in O(t) time, t is what we will find out later.

Can you give an estimate of total amortised cost on the total time complexity using the above data structure ?

If we forget that there is any query of type 2, then what will be the total amortised cost ? As each number is less than 109, in the worst case a number can be divided by p by at most 30 times (when p is 2 and number is 109). So total time complexity would be O(t) * 30 * N

Now Let us add queries of type 2. Each number which is replaced will require at most 30 steps to reach 1. So at most M numbers are added. So total time complexity is O(t) * 30 * (M + N) + Time required to change the data structure for query 2.

Now, if t = O(log N), then we are done.

The Data Structure
We will make 3 balanced binary search trees [ one for p = 2, other for p=3 and the last one for p=5 ]. Balanced Binary search trees to keep numbers in the sorted is implemented in C++ as "set" and in Java as HashSet or TreeSet.

In our set , we will keep index of the numbers which are divisible by p.

Let us solve for p = 2, rest primes are analogous to this case.

Query of First Type : l r p 
Find in the balanced binary search tree [i.e. set ] for index which is just greater than or equal to l and less than or equal to r. Divide the number on that index with p. If after division it is no longer divisible by p then remove that index from the binary search tree and proceed to find another index which is greater than this index and less than or equal to r. We will continue this again and again till it terminates.

Query of Second Type : l d 
We first remove index l from all 3 set if it is present in them. Then we'll add index l in the set if d is divisible by p.

Pseudo Code

    //Declaring the Data Structure
    set<int> myset6

    //Building the Data Structure
    for(int i=1;i<=N;i++)
        Read( arr[i] )
        if( arr[i]%2 == 0 ) myset[ 2 ].insert(i);
        if( arr[i]%3 == 0 ) myset[ 3 ].insert(i);
        if(arr[i]%5  == 0 ) myset[ 5 ].insert(i);

    //Report Query
    scanf("%d%d%d",&l,&r,&p);   //taking the input.
    a = lower_bound(myset[p].begin(),myset[p].end(),l);//finding the first index
    vector<int> del;    //to store the index which are needed to be deleted
    for(set<int>::iterator it = a;it!=myset[p].end();it++)  //iterating the set from the found index
        if( it > r)    break;      //breaking the loop when you encounter index greater than r
        arr[it]/=p;            //dividing the number by p
        if ( arr[it] %p )
            del.push_back(it); //if number is no more divisible by p, then we need to remove this from the set
    for(vector<int>::iterator it = del.begin();it!=del.end();it++)
        myset[p].erase(*it);        //deleting the numbers


    //Update Query
    scanf("%d%d",&l,&d);
    //Delete them if already in set.
    if( arr[l] %2 == 0 )    myset[ 2 ].erase(l);
    if( arr[l] %3 == 0 )    myset[ 3 ].erase(l);
    if( arr[l] %5 == 0 )    myset[ 5 ].erase(l);
    //Add them
    if ( d%2 == 0 ) myset[ 2 ].insert(l);
    if ( d%3 == 0 ) myset[ 3 ].insert(l);
    if ( d%5 == 0 ) myset[ 5 ].insert(l);
    arr[l] = d;

Other Data Structure
We can use Binary Indexed trees to solve this problem. We will make 3 binary indexed trees[p=2 ,3 and 5] of size N . We will keep 1 at index i if number in that index is divisible by p.

Updating in Binary Indexed Tree 
If a[l] is divisible by p=2 , then we will add -1 in Binary Indexed tree for p=2. If d is divisible by 2 , we will add +1 in Binary Indexed tree for p=2. We will do it similarly for other Binary Indexed Tree.

Reporting in Binary Indexed Tree 
We will find the sum of the values stored till l-1 for Binary Indexed tree of p. We will find the index of the next value which is just greater than the sum found. We will divide that index of the array by p. We will update our sum to this new sum. We will continue to do this till our index just exceeds r. We will keep track of the numbers which are no more divisible by p. We will add -1 there at the end.

Thus Overall time complexity of querying from both the structure is O(log N)













*/



#include<vector>
#include<cstdio>
#include<set>

using namespace std;
int ar[100005];
set<int> ss[6];
set<int>::iterator itr;

void update_1(int l,int r, int p)
{
	vector<int> vec;
	for(itr=ss[p].lower_bound(l); *itr <=r && itr!=ss[p].end();itr++){
		ar[*itr]/=p;
		if(ar[*itr]%p==0){vec.push_back(*itr);}
	}
	for(int i=0;i<vec.size();i++){
	ss[p].erase(vec[i]);
	}
	vec.clear();
}

void update_2(int l,int d)
{
	if(ar[l]%2==0)ss[2].erase(l);
	if(ar[l]%3==0)ss[3].erase(l);
	if(ar[l]%5==0)ss[5].erase(l);
	ar[l]=d;
	if(ar[l]%2==0)ss[2].insert(l);
	if(ar[l]%3==0)ss[3].insert(l);
    if(ar[l]%5==0)ss[5].insert(l);
}

int main()
{
	int n;scanf("%d",&n);
	for (int i=0; i<n; i++){
	 scanf("%d",&ar[i]);
	 if(ar[i]%2==0)ss[2].insert(i);
	 if(ar[i]%3==0)ss[3].insert(i);
	 if(ar[i]%5==0)ss[5].insert(i);
	}
	int m;scanf("%d",&m);
	for(int i=0; i<m; i++)
	{
		int q,l,r,p,d;
		scanf("%d",q);
		if(q==1){
		scanf("%d %d %d",&l,&r,&p);
		update_1(l-1,r-1,p);
		}
		else{
		scanf("%d %d",&l,&d);
		update_2(l,d);
		
		}
	}
}
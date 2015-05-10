#include<cstdio>
/*
There are N coins kept on the table, numbered from 0 to N - 1. Initially, each coin is kept tails up. You have to perform two types of operations :
1) Flip all coins numbered between A and B inclusive. This is represented by the command "0 A B"
2) Answer how many coins numbered between A and B inclusive are heads up. This is represented by the command "1 A B".

*/




struct SegmentTreeNode {
	int start, end;
	int count;
	bool pendingUpdate;

	SegmentTreeNode(): count(0),pendingUpdate(false) {}

	void merge(SegmentTreeNode& left, SegmentTreeNode& right) {
		//count = left.count + right.count;
		count = (left.pendingUpdate ? (left.end - left.start + 1  -left.count): left.count) + (right.pendingUpdate ? ( right.end - right.start +1 - right.count) : right.count);
	}
	
	void assignLeaf (bool value) {
		
	}
	int query() {
		return count;
	}
	
	bool hasPendingUpdate() {
		return pendingUpdate;
	}

	void applyPendingUpdate() {
		count = ( end - start + 1) -count;
		pendingUpdate = false;
	}

	void addUpdate(bool value) {
		pendingUpdate = !pendingUpdate;
	//count  = ( end - start +1) - count;
	}
	bool getPendingUpdate() {
		return true;
	}
	
};


class SegmentTree {
	SegmentTreeNode * nodes;
	int N;
	private:
		void buildTree (bool arr[], int stIndex, int start, int end) {
			nodes[stIndex].start =start, nodes[stIndex].end = end;
			if (start == end) {
				nodes[stIndex].assignLeaf(arr[start]);
				return;
			}
			int mid = (start + end) /2,
			  leftChildIndex = 2 * stIndex,
			  rightChildIndex = leftChildIndex + 1;
			  buildTree(arr,leftChildIndex, start,mid);
			  buildTree(arr,rightChildIndex,mid+1,end);
			  nodes[stIndex].merge(nodes[leftChildIndex],nodes[rightChildIndex]);
		}
		int getSegmentTreeSize(int N) {
			int size = 1;
			for(; size <N; size <<=1);
			return size << 1;
		}

	/* each node can be overlapping */	
		void update (int stIndex, int start,int end, bool value) {
		  if (nodes[stIndex].start == start && nodes[stIndex].end == end ) {
		  	nodes[stIndex].addUpdate(value);
			return;
		  }
		  int leftChildIndex =  stIndex <<1,
		  	rightChildIndex = leftChildIndex + 1,
			mid = ( nodes[stIndex].start + nodes[stIndex].end) >>1;
		 if ( start > mid) 
		 	update(rightChildIndex,start,end, value);
		 else if ( end <= mid)
		 	update(leftChildIndex,start,end,value);
		 else { // as each can be overlapping need to check for both
			update(leftChildIndex,start,mid,value);
			update(rightChildIndex,mid+1,end,value);
			}
			nodes[stIndex].merge(nodes[leftChildIndex],nodes[rightChildIndex]);
		
		}
		
		
		/* private query function */
		
	SegmentTreeNode query(int stIndex, int start,int end) {
		if (nodes[stIndex].start == start && nodes[stIndex].end == end) {
			SegmentTreeNode result = nodes[stIndex];
			if (result.hasPendingUpdate())
	   			result.applyPendingUpdate();
			return result;	
			}
			int leftChildIndex = 2 * stIndex,
				rightChildIndex = leftChildIndex +1,
				mid = (nodes[stIndex].start + nodes[stIndex].end)>>1;
		
			SegmentTreeNode result;
			if (start > mid)
				result = query(rightChildIndex,start,end);
			else if (end <= mid)
				result = query(leftChildIndex,start,end);
			else {
				SegmentTreeNode leftResult =query(leftChildIndex,start,mid),
								rightResult = query(rightChildIndex,mid +1,end);
				result.start = leftResult.start;
				result.end = rightResult.end;
				result.merge(leftResult,rightResult);
			}	
				
				if (nodes[stIndex].hasPendingUpdate()) {
					result.addUpdate(nodes[stIndex].getPendingUpdate());
					result.applyPendingUpdate();
				}	

			return result;	
		}
	// expose the update the, query function, segmentTree constructor and 
	// segmentTree destructor
	public:
		SegmentTree (bool arr[], int N) {
			this->N = N;
			nodes = new SegmentTreeNode[getSegmentTreeSize(N)];
			buildTree(arr,1,0,N-1);
		}
		~SegmentTree() {
			delete[] nodes;
		}
		//range update
		void update(int start,int end, bool value) {
			update(1,start,end,value);
		}
		//range query
        int query(int start, int end) {
			SegmentTreeNode result = query(1,start,end);
			return result.query();
		}

};


bool tailsUp[100005];

int main() {
	int N, Q, cmd, A, B;
	scanf("%d %d", &N, &Q);
	SegmentTree st(tailsUp,N);
	while (Q--) {
		scanf("%d %d %d",&cmd, &A, &B);
		if (cmd == 0)
			st.update(A,B,true);
		else
			printf("%d\n",st.query(A,B));
	}
	return 0;
}



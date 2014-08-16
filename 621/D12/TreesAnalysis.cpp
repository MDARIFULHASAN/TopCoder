#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <iostream>
#include <sstream>
#include <iomanip>

#include <bitset>
#include <string>
#include <vector>
#include <stack>
#include <deque>
#include <queue>
#include <set>
#include <map>

#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <cstring>
#include <ctime>
#include <climits>
using namespace std;
// BEGIN CUT HERE
#define ARRSIZE(x) (sizeof(x)/sizeof(x[0]))
template<typename T> void print( T a ) {
	cerr << a;
}
static void print( long long a ) {
	cerr << a << "L";
}
static void print( string a ) {
	cerr << '"' << a << '"';
}
template<typename T> void print( vector<T> a ) {
	cerr << "{";
	for ( int i = 0 ; i != a.size() ; i++ ) {
		if ( i != 0 ) cerr << ", ";
		print( a[i] );
	}
	cerr << "}" << endl;
}
template<typename T> void eq( int n, T have, T need ) {
	if ( have == need ) {
		cerr << "Case " << n << " passed." << endl;
	} else {
		cerr << "Case " << n << " failed: expected ";
		print( need );
		cerr << " received ";
		print( have );
		cerr << "." << endl;
	}
}
template<typename T> void eq( int n, vector<T> have, vector<T> need ) {
	if( have.size() != need.size() ) {
		cerr << "Case " << n << " failed: returned " << have.size() << " elements; expected " << need.size() << " elements.";
		print( have );
		print( need );
		return;
	}
	for( int i= 0; i < have.size(); i++ ) {
		if( have[i] != need[i] ) {
			cerr << "Case " << n << " failed. Expected and returned array differ in position " << i << ".";
			print( have );
			print( need );
			return;
		}
	}
	cerr << "Case " << n << " passed." << endl;
}
static void eq( int n, string have, string need ) {
	if ( have == need ) {
		cerr << "Case " << n << " passed." << endl;
	} else {
		cerr << "Case " << n << " failed: expected ";
		print( need );
		cerr << " received ";
		print( have );
		cerr << "." << endl;
	}
}
// END CUT HERE

#define CHECKTIME() printf("%.2lf\n", (double)clock() / CLOCKS_PER_SEC)
typedef pair<int, int> pii;
typedef long long llong;
typedef pair<llong, llong> pll;
#define mkp make_pair
#define FOREACH(it, X) for(__typeof((X).begin()) it = (X).begin(); it != (X).end(); ++it)

/*************** Program Begin **********************/
class TreesAnalysis {
public:
	vector <int> T1[4001], T2[4001];
	int cntA[4001], cntB[4001];
	bool visited[4001], isA[4001];

	void dfs(int v, int v1, int v2)
	{
		visited[v] = true;
		isA[v] = true;
		for (int i = 0; i < T1[v].size(); i++) {
			int a = T1[v][i];
			if (visited[a]) {
				continue;
			}
			if ((v == v1 && a == v2) || 
				(v == v2 && a == v1) ) {
				continue;
			}
			dfs(a, v1, v2);
		}
	}

	void dfs2(int v)
	{
		visited[v] = true;
		if (isA[v]) {
			++cntA[v];
		} else {
			++cntB[v];
		}
		for (int i = 0; i < T2[v].size(); i++) {
			int a = T2[v][i];
			if (visited[a]) {
				continue;
			}
			dfs2(a);
			cntA[v] += cntA[a];
			cntB[v] += cntB[a];
		}		
	}

	long long treeSimilarity(vector <int> tree1, vector <int> tree2) {
		long long res = 0;
		int n = tree1.size() + 1;

		for (int i = 0; i < n - 1; i++) {
			T1[i].push_back(tree1[i]);
			T1[tree1[i]].push_back(i);
			T2[i].push_back(tree2[i]);
			T2[tree2[i]].push_back(i);
		}

		for (int i = 0; i < n - 1; i++) {
			int v1 = i, v2 = tree1[i];

			memset(visited, 0, sizeof(visited));
			memset(isA, 0, sizeof(isA));
			dfs(v1, v1, v2);
			int sumA = accumulate(isA, isA + n, 0);

			memset(visited, 0, sizeof(visited));
			memset(cntA, 0, sizeof(cntA));
			memset(cntB, 0, sizeof(cntB));
			dfs2(0);
			
			for (int j = 0; j < n - 1; j++) {
				int v3 = j, v4 = tree2[j];
				long long x = 0;
				long long a, b, c, d;

				if (cntA[v3] + cntB[v3] > cntA[v4] + cntB[v4]) {
					a = cntA[v4];
					b = cntB[v4];
					c = sumA - cntA[v4];
					d = n - a - b - c;
				} else {
					a = cntA[v3];
					b = cntB[v3];
					c = sumA - cntA[v3];
					d = n - a - b - c;
				}

				x = max(a, b);
				x = max(x, c);
				x = max(x, d);
				res += x * x;
			}
		}
		return res;
	}

};

/************** Program End ************************/

// BEGIN CUT HERE
int main( int argc, char* argv[] ) {
	{
		int tree1ARRAY[] = {1};
		vector <int> tree1( tree1ARRAY, tree1ARRAY+ARRSIZE(tree1ARRAY) );
		int tree2ARRAY[] = {1};
		vector <int> tree2( tree2ARRAY, tree2ARRAY+ARRSIZE(tree2ARRAY) );
		TreesAnalysis theObject;
		eq(0, theObject.treeSimilarity(tree1, tree2),1LL);
	}
	{
		int tree1ARRAY[] = {2, 4, 1, 0};
		vector <int> tree1( tree1ARRAY, tree1ARRAY+ARRSIZE(tree1ARRAY) );
		int tree2ARRAY[] = {1, 4, 4, 4};
		vector <int> tree2( tree2ARRAY, tree2ARRAY+ARRSIZE(tree2ARRAY) );
		TreesAnalysis theObject;
		eq(1, theObject.treeSimilarity(tree1, tree2),111LL);
	}
	{
		int tree1ARRAY[] = {1, 2, 3, 4};
		vector <int> tree1( tree1ARRAY, tree1ARRAY+ARRSIZE(tree1ARRAY) );
		int tree2ARRAY[] = {1, 2, 3, 4}
		   ;
		vector <int> tree2( tree2ARRAY, tree2ARRAY+ARRSIZE(tree2ARRAY) );
		TreesAnalysis theObject;
		eq(2, theObject.treeSimilarity(tree1, tree2),128LL);
	}
	{
		int tree1ARRAY[] = {2, 3, 4, 4, 5, 8, 5, 6, 10, 8};
		vector <int> tree1( tree1ARRAY, tree1ARRAY+ARRSIZE(tree1ARRAY) );
		int tree2ARRAY[] = {9, 0, 1, 0, 3, 0, 5, 0, 7, 10};
		vector <int> tree2( tree2ARRAY, tree2ARRAY+ARRSIZE(tree2ARRAY) );
		TreesAnalysis theObject;
		eq(3, theObject.treeSimilarity(tree1, tree2),6306LL);
	}
	{
		int tree1ARRAY[] = {222, 261, 167, 133, 174, 150, 165, 311, 208, 268, 111, 222, 154, 277, 282, 201, 46, 124, 194, 331, 4, 216, 111, 
		   275, 72, 322, 137, 216, 241, 48, 72, 101, 232, 165, 151, 263, 139, 16, 122, 140, 84, 135, 314, 106, 309, 126, 102, 
		   151, 208, 27, 242, 93, 83, 314, 136, 77, 82, 215, 16, 232, 286, 156, 294, 38, 67, 204, 206, 137, 174, 282, 188, 
		   143, 84, 279, 236, 136, 158, 10, 65, 332, 122, 44, 329, 62, 174, 67, 102, 216, 245, 296, 287, 307, 93, 197, 169, 
		   268, 266, 294, 157, 277, 95, 68, 214, 135, 211, 127, 82, 108, 212, 161, 243, 212, 207, 119, 119, 158, 97, 290, 21, 
		   217, 230, 85, 171, 13, 138, 294, 304, 204, 318, 115, 70, 210, 195, 223, 37, 164, 149, 3, 164, 328, 316, 108, 330, 
		   48, 38, 324, 222, 193, 50, 41, 184, 93, 148, 41, 151, 139, 106, 301, 264, 80, 249, 110, 244, 109, 212, 223, 279, 
		   330, 67, 27, 301, 165, 236, 194, 3, 157, 1, 217, 311, 87, 105, 4, 286, 37, 6, 31, 111, 66, 230, 227, 244, 322, 
		   196, 65, 69, 305, 112, 133, 231, 68, 153, 206, 309, 248, 329, 58, 69, 69, 328, 0, 29, 233, 243, 305, 167, 80, 65, 
		   194, 190, 179, 142, 196, 324, 206, 134, 50, 272, 261, 10, 147, 329, 322, 14, 142, 169, 21, 296, 284, 241, 55, 304, 
		   150, 166, 230, 167, 304, 87, 156, 156, 97, 274, 324, 196, 101, 82, 106, 260, 242, 233, 207, 305, 10, 166, 53, 18, 
		   154, 233, 217, 296, 263, 168, 138, 30, 115, 135, 188, 98, 309, 292, 204, 150, 210, 332, 330, 166, 96, 70, 24, 229, 
		   215, 201, 285, 40, 287, 142, 68, 133, 208, 268, 161, 310, 41, 203, 73, 275, 184, 163, 227, 89, 110, 328, 108, 112, 
		   125, 164, 127, 179, 267, 221, 49, 139, 1, 84, 136, 38, 6, 70, 246, 243, 3, 188, 297};
		vector <int> tree1( tree1ARRAY, tree1ARRAY+ARRSIZE(tree1ARRAY) );
		int tree2ARRAY[] = {174, 262, 195, 288, 157, 278, 36, 133, 230, 273, 222, 138, 97, 23, 189, 141, 296, 55, 45, 301, 81, 199, 188, 289, 
		   187, 164, 113, 58, 138, 300, 289, 282, 329, 91, 130, 178, 92, 143, 48, 81, 311, 133, 151, 286, 171, 196, 199, 80, 
		   83, 121, 65, 151, 277, 136, 49, 111, 58, 36, 259, 14, 31, 9, 136, 181, 122, 324, 249, 114, 9, 37, 259, 242, 165, 
		   174, 34, 36, 298, 92, 301, 237, 178, 82, 65, 295, 110, 311, 274, 235, 68, 56, 259, 180, 195, 52, 110, 68, 140, 71, 
		   52, 296, 290, 115, 213, 82, 209, 209, 74, 178, 302, 131, 99, 205, 296, 309, 288, 180, 329, 71, 143, 58, 152, 273, 
		   196, 7, 169, 88, 231, 331, 213, 181, 80, 249, 170, 246, 16, 127, 75, 276, 332, 174, 21, 180, 163, 78, 242, 312, 
		   295, 199, 89, 142, 85, 195, 115, 119, 95, 94, 279, 290, 3, 33, 93, 284, 20, 47, 47, 78, 331, 271, 113, 179, 249, 
		   331, 92, 324, 9, 71, 232, 46, 28, 289, 80, 28, 80, 134, 20, 280, 277, 48, 205, 107, 52, 320, 4, 191, 160, 182, 
		   189, 227, 295, 115, 54, 195, 78, 292, 189, 273, 301, 69, 305, 36, 222, 167, 326, 106, 48, 45, 74, 61, 181, 311, 
		   292, 270, 201, 34, 314, 218, 214, 92, 269, 18, 37, 151, 142, 209, 11, 227, 327, 198, 28, 272, 152, 22, 47, 143, 
		   332, 253, 273, 35, 78, 130, 295, 223, 181, 329, 18, 238, 300, 186, 274, 99, 300, 322, 41, 185, 311, 288, 198, 2, 
		   37, 83, 238, 133, 122, 178, 107, 106, 66, 238, 69, 90, 38, 109, 246, 278, 288, 250, 321, 269, 130, 28, 115, 122, 
		   33, 185, 275, 99, 130, 99, 152, 268, 133, 249, 180, 30, 210, 201, 324, 29, 290, 143, 3, 269, 68, 106, 230, 1, 
		   269, 29, 120, 259, 324, 328, 23, 243, 9, 61, 14, 118, 199, 146, 237, 14};
		vector <int> tree2( tree2ARRAY, tree2ARRAY+ARRSIZE(tree2ARRAY) );
		TreesAnalysis theObject;
		eq(4, theObject.treeSimilarity(tree1, tree2),11478648052LL);
	}
	return 0;
}
// END CUT HERE

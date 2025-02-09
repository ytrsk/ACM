/* This is sample grader for the contestant */
#include "lcs.h"
#include <stdio.h>
#include <assert.h>
#include <cstring>
#include <algorithm>

#define N 110

static int p[N];
static int tot_query;
static int max_lcs[N][N];
static int n;
const int maxn=100007;
#define rep(i,x,y) for(auto i=(x);i<=(y);++i)
#define dep(i,x,y) for(auto i=(x);i>=(y);--i)
int A[maxn];
void find_permutation(int n,int res[]){
    res[0]=1;
    rep(i,2,n){
        int l=0,r=i-2,ans=-1;
        while(l<=r){
            int mid=(l+r)>>1;
            A[0]=i;A[1]=res[mid];
            if(get_lcs(2,A)==2){
                r=mid-1;ans=mid;
            }
            else l=mid+1;
        }
        if(ans==-1) res[i-1]=i;
        else{
            dep(k,i,ans+1) res[k]=res[k-1];
            res[ans]=i;
        }
    }
}
int get_lcs(int len, int A[]) {
	assert(len <= 100);
	for (int i = 0; i < len; ++i) {
		assert(A[i] >= 1 && A[i] <= n);
	}
	++tot_query;
	memset(max_lcs, 0x00, sizeof max_lcs);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= len; ++j)
			if (p[i] == A[j - 1]) {
				max_lcs[i][j] = max_lcs[i-1][j-1] + 1;
			} else {
				max_lcs[i][j] = std::max(max_lcs[i-1][j], max_lcs[i][j-1]);
			}
	return max_lcs[n][len];
}

int main()
{
	int used[N];

	assert(scanf("%d", &n) == 1);
	memset(used, 0x00, sizeof used);
	for (int i = 1; i <= n; ++i) {
		assert(scanf("%d", &p[i]));
		assert(1 <= p[i] && p[i] <= n && used[p[i]] == 0);
		used[p[i]] = 1;
	}
	fclose(stdin);

	tot_query = 0;
	int result[N];
	find_permutation(n, result);
	for (int i = 0; i < n; ++i) printf("%d ", result[i]); puts("");
	printf("%d\n", tot_query);
	return 0;
}

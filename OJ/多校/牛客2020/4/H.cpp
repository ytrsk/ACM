#include <bits/stdc++.h>
using namespace std;
const int maxn = 100007;
int head[maxn],nex[maxn],to[maxn],n;
int mate[maxn],link[maxn],vis[maxn], fa[maxn];
int que[maxn],hd,tl,e1;
int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return x*f;
}
void addedge(int u,int v) {
    ++e1;nex[e1]=head[u];head[u]=e1;to[e1]=v;
}
int find(int x) {
    return fa[x]==x?x:fa[x]=find(fa[x]);
}
int LCA(int x,int y){
    static int ss[maxn],tim;
    ++tim;
    while(ss[x]!=tim){
        if(x) {ss[x]=tim;x=find(link[mate[x]]);}
        swap(x,y);
    }
    return x;
}
void Flower(int x,int y,int p){
    while(find(x)!=p){
        link[x]=y;
        fa[y=mate[x]]=(fa[x]=p);
        if(vis[y]==1) vis[que[++tl]=y]=2;
        x=link[y];
    }
}
bool match(int x) {
    hd=1;tl=0;
    for(int i=1;i<=n;i++) vis[fa[i]=i]=0;
    vis[que[++tl]=x]=2;
    while(hd<=tl){
        x=que[hd++];
        for(int i=head[x];i;i=nex[i]) {
            int u=to[i];
            if(!vis[u]){
                vis[u]=1;
                link[u]=x;
                if(!mate[u]){
                    while(x){
                        x=mate[link[u]];
                        mate[mate[u]=link[u]]=u;
                        u=x;
                    }
                    return true;
                }else vis[que[++tl]=mate[u]] = 2;
            }else if(vis[u]==2&&find(u)!=find(x)) {
                int p=LCA(x,u);
                Flower(x,u,p);
                Flower(u,x,p);
            }
        }
    }
    return false;
}
int d[maxn],ans;
void init(){
    for(int i=1;i<=n;i++) head[i]=mate[i]=0;
    e1=ans=0;
}
void add(int u,int v){
    addedge(u,v);addedge(v,u);
    if(!mate[u]&&!mate[v])
    mate[mate[u]=v]=u,++ans;
}
int main(){
    for(int nn=21;nn<=21;nn++){
        n=nn;
        init();
        ans=0;
        for(int i=1;i<=n;i++){
            for(int k=i+1;k<=n;k++){
                if(__gcd(i,k)>1) add(i,k);
            }
        }
        for(int i=1;i<=n;++i)
        if(!mate[i]&&match(i)) ++ans;
        for(int i=1;i<=n;i++){
            if(i<mate[i]){
                printf("%d %d\n",i,mate[i]);
            }
        }
        printf("%d %d\n",nn,ans);
      //  for (int i = 1; i <= n; ++i)
    //    printf("%d ",mate[i]);
    }
    return 0;
}
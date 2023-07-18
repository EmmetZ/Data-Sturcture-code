#ifndef ADJLISTGRAPH_INCLUDED
#define ADJLISTGRAPH_INCLUDED

#include<iostream>
#include"abstract.h"
#include"../Queue/linkQueue.h"
using namespace std;

template<class TypeOfVer, class TypeOfEdge>
class adjListGraph: public graph<TypeOfVer, TypeOfEdge>
{
public:
    adjListGraph(int vSize, const TypeOfVer d[]);
    void insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w);
    void remove(TypeOfVer x, TypeOfVer y);
    bool exist(TypeOfVer x, TypeOfVer y);
    ~adjListGraph();

    void dfs() const;
    void dfs(int start, bool visited[]) const;

    void bfs() const;

    void EulerCircuit(TypeOfVer start);

    void topSort() const;

    void criticalPath() const;



private:
    int Vers;
    int Edges;

    struct edgeNode
    {
        int end;
        TypeOfEdge weight;   //边的权值
        edgeNode *next;

        edgeNode(int e, TypeOfEdge w, edgeNode *n = NULL)
        {end = e; weight = w; next = n;}
    };

    struct verNode
    {
        TypeOfVer ver;
        edgeNode *head;
        
        verNode(edgeNode *h = NULL) {head = h;}
    };
    
    verNode *verList;

    int find(TypeOfVer v) const
    {
        for(int i=0; i<Vers; ++i) 
            if(verList[i] == v) return i;
    }



    struct EulerNode
    {
        int NodeNum;
        EulerNode *next;
        EulerNode(int ver) {NodeNum = ver; next = NULL;}
    };

    verNode *clone() const;
    void EulerCircuit(int start, EulerNode *&beg, EulerNode *&end);
};






template<class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::adjListGraph(int vSize, const TypeOfVer d[])
{
    Vers = vSize;
    Edges = 0;

    verList = new verNode[vSize];
    for(int i=0; i<Vers; ++i) verList[i].ver = d[i];
}


template<class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::~adjListGraph()
{
    int i;
    edgeNode *p;

    for(i=0; i<Vers; ++i)
        while((p = verList[i])!=NULL) {
            verList->head = p->next;
            delete p;
        }

    delete []verList;
}


template<class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w)
{
    int u = find(x), v = find(y);\
    verList[u].head = new edgeNode(v, w, verList[u].head);   //在结点x, y之间插入权值为w的边
    ++Edges;
}


template<class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::remove(TypeOfVer x, TypeOfVer y)
{
    int u = find(x), v = find(y);
    edgeNode *p = verList[u].head, *q;

    if(p == NULL) return;

    if(p->end == v) {
        verList[u].head = p->next;
        delete p;
        --Edges;
        return;
    }

    while(p->next!=NULL && p->next->end!=v) p = p->next;
    if(p->next!=NULL) {
        q = p->next;
        p->next = q->next;
        delete q;
        --Edges;
    }
}



template<class TypeOfVer, class TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::exist(TypeOfVer x, TypeOfVer y)
{
    int u = find(x), v = find(y);
    edgeNode *p = verList[u].head;

    while(p!=NULL && p->end!=v) p = p ->next;
    if(p==NULL) return false;
    else return true;
}



template<class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::dfs() const
{
    bool *visited = new bool[Vers];

    for(int i=0; i<Vers; ++i) visited[i] = false;

    cout<<"当前图的深度优先遍历序列为："<<endl;

    for(int i=0; i<Vers; ++i) {
        if(visited[i] == true) continue;
        dfs(i, visited);
        cout<<endl; 
    }
}


template<class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::dfs(int start, bool visited[]) const
{
    edgeNode *p = verList[start].head;

    cout<<verList[start].ver<<'\t';
    visited[start] = true;

    while(p!=NULL) {
        if(visited[p->end] == false) dfs(p->end, visited);
        p = p->next;
    }
}


template<class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::bfs() const
{
    bool *visited = new bool[Vers];
    int currentNode;
    linkQueue<int> q;
    edgeNode *p;

    for(int i=0; i<Vers; ++i) visited[i] = false;

    cout<<"当前图的广度优先遍历序列为："<<endl;

    for(int i=0; i<Vers; ++i) {
        if(visited[i] == true) continue;
        q.enQueue(i);
        while(!q.isEmpty()) {
            currentNode = q.deQueue();
            if(visited[currentNode] == true) continue;
            cout<<verList[currentNode].ver<<'\t';
            visited[currentNode] = true;
            p = verList[currentNode].head;
            while(p!=NULL) {
                if(visited[p->end] == false) q.enQueue(p->end);
                p = p->next;
            }
        }
        cout<<endl;
    }
}



template<class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::EulerCircuit(TypeOfVer start)
{
    EulerNode *beg, *end, *p, *q, *tb, *te;
    int numOfDegree;
    edgeNode *r;
    verNode *tmp; //检查是否有欧拉回路

    if(Edges == 0) {
        cout << "不存在欧拉回路"<<endl;
        return;
    }
    for(int i=0; i<Vers; ++i) {
        numOfDegree = 0;
        r = verList[i].head;
        while(r!=0) {
            ++numOfDegree;
            r = r->next;
        }
        if(numOfDegree%2) {
            cout << "不存在欧拉回路"<<endl;
            return;
        }
    }

    //寻找起始结点的编号
    int i = find(start);

    tmp = clone();

    //寻找从i出发的路径，路径的七点和终点地址分别为beg和end
    EulerCircuit(i, beg, end);
    while(true) {
        p = beg;
        while(p->next!=NULL)
            if(verList[p->next->NodeNum].head!=NULL) break;
            else p = p->next;

        if(p->next == NULL) break;  //所有边都被访问
        q = p->next;
        EulerCircuit(q->NodeNum, tb, te);
        te->next = q->next;
        delete q;8
    }

    delete []verList; //回复原图
    verList = tmp;

    cout<<"欧拉回路是："<<endl;
    while(beg!=NULL) {
        cout<<verList[beg->NodeNum].ver<<'\t';
        p = beg;
        beg = beg->next;
        delete p;
    }
    cout<<endl;
}


template<class TypeOfVer, class TypeOfEdge>
class adjListGraph<TypeOfVer, TypeOfEdge>::verNode *adjListGraph<TypeOfVer, TypeOfEdge>::clone() const
{   
    verNode *tmp = new verNode[Vers];
    edgeNode *p;

    for(int i=0; i<Vers; ++i) {
        tmp[i].ver = verList[i].ver;
        p = verList[i].head;
        while(p!=NULL) {
            tmp[i].head = new edgeNode(p->end, p->weight, tmp[i].head);
            p = p->next;
        }
    }

    return tmp;
}   


template<class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::EulerCircuit(int start, EulerNode *&beg, EulerNode *&end)
{
    int nextNode;

    beg = end = new EulerNode(start);
    while(verList[start].head!=NULL) {
        nextNode = verList[start].head->end;
        remove(start, nextNode);   //无向图，删边要删两次
        remove(nextNode, start);
        start = nextNode;
        end->next = new EulerNode(start);
        end = end->next;
    }
}


template<class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::topSort() const
{
    linkQueue<int> q;
    edgeNode *p;
    int current;
    int *intDegree = new int[Vers];

    for(int i=0; i<Vers; ++i) intDegree[i] = 0;
    for(int i=0; i<Vers; ++i) {    //计算每个结点的入度
        for(p=verList[i].head; p!=NULL; p = p->next)
            ++intDegree[p->end];
    }

    for(int i=0; i<Vers; ++i)
        if(intDegree[i] == 0) q.enQueue(i);

    cout<<"拓扑排序为：";<<endl;
    while (!q.isEmpty())    
    {
        current = q.deQueue();
        cout<<verList[current].ver<<'\t';
        for(p=verList[current].head; P!=NULL; p = p->next)
            if(--intDegree[p->end] == 0)
                q.enQueue(p->end);
    }
    cout<<endl;
}



template<class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::criticalPath() const
{
    TypeOfEdge *ee = new TypeOfEdge[Vers], *le = new TypeOfEdge[Vers];
    int *top = new int[Vers];   //top保存拓扑序列
    int *inDegree = new int[Vers];
    linkQueue<int> q;
    int i;
    edgeNode *p;

    //找出拓扑序列， 放入数组top
    for(int i=0; i<Vers; ++i) inDegree[i] = 0;
    for(int i=0; i<Vers; ++i) {
        for(p=verList[i].head;p!=NULL; p=p->next)
            ++inDegree[p->end];
    }

    for(i=0; i<Vers; ++i)
        if(inDegree[i]==0) q.enQueue(i);

    i = 0;
    while(!q.isEmpty()) {
        top[i] = q.deQueue();
        for(p=verList[top[i]].head; p!=NULL; p=p->next)
            if(--inDegree[p->end]==0) q.enQueue(p->end);
                ++i;
    }

    //找最早发生时间
    for(i=0; i<Vers; ++i) ee[i] = 0;
    for(i=0; i<Vers; ++i) {
        for(p=verList[top[i]].head; p=NULL; p=p->next)
            if(ee[p->end]<ee[top[i]]+p->weight) 
                ee[p->end] = ee[top[i]]+p->weight;
    }

    //找最晚发生时间
    for(i=0; i<Vers; ++i) le[i] = ee[top[Vers-1]];
    for(i=0; i<Vers; ++i) {
        for(p=verList[top[i]].head; p!=NULL; p=p->next)
            if(le[p->end]-p->weight<le[top[i]]) 
                le[top[i]] = le[p->end]-p->weight;
    }

    //找关键路径
    for(i=0; i<Vers; ++i)
        if(le[top[i]]==ee[top[i]]) 
            cout<<"("<<verList[i].ver<<", "<<ee[top[i]]<<")";
}




#endif //ADJLISTGRAPH_INCLUDED
 
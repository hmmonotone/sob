#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
// #include <sstream>
#include <queue>
#include <deque>
// #include <bitset>
#include <iterator>
#include <list>
#include <stack>
#include <map>
#include <set>
#include <functional>
#include <numeric>
#include <utility>
// #include <limits>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

using namespace std;
class tran{
    public:
    string txid;
    int fees,weight;
    vector<string> parents;
};
bool compare(tran* a, tran* b){
    if((a->fees)==(b->fees))
    {
        return (a->weight)<(b->weight);
    }
    return (a->fees)>(b->fees);
}
int main() {
	// std::ios::sync_with_stdio(false);
  freopen("mempool.txt","r",stdin);
  freopen("block.txt","w",stdout);
    int no_of_tran=5214;
    vector<tran*> mempool;
    for(int i=0;i<no_of_tran;i++)
    {
        string txid;
        int fees,weight;
        vector<string> parents;
        string parents_with_comma;
        tran* temp=new tran();
        cin>>txid>>fees>>weight>>parents_with_comma;
        temp->txid=txid;
        temp->fees=fees;
        temp->weight=weight;
        string t="";
        if(parents_with_comma!="N"){
        for(int j=0;j<parents_with_comma.size();j++)
        {
            if(parents_with_comma[j]!=',')
            {
                t+=parents_with_comma[j];
            }
            else{
                parents.push_back(t);
                t="";
            }
        }
        parents.push_back(t);
        }
        temp->parents=parents;
        mempool.push_back(temp);
    }
    // for(int i=0;i<no_of_tran;i++)
    // {
    //   cout<<mempool[i]->txid<<" "<<mempool[i]->fees<<" "<<mempool[i]->weight<<endl;
    // }
    sort(mempool.begin(),mempool.end(),compare);
    long weight_till_now=0;
    vector<string> block;
    set<string> is_included;
    int i;
    for(i=0;i<mempool.size()&&(weight_till_now+mempool[i]->weight)<=4000000;i++)
    {
        if(mempool[i]->parents.size()==0)
        {
            is_included.insert(mempool[i]->txid);
            block.push_back(mempool[i]->txid);
            weight_till_now+=mempool[i]->weight;
        }
    }
    if(i==mempool.size())
    {
        while(1){
            int flag=0;
        for(i=0;i<mempool.size();i++)
        {
            if(mempool[i]->parents.size()!=0)
            {
                if(is_included.find(mempool[i]->txid)!=is_included.end()||(weight_till_now+mempool[i]->weight)>4000000)
                {
                    continue;
                }
                int flag1=1;
                for(int j=0;j<mempool[i]->parents.size();j++){
                    if(is_included.find(mempool[i]->parents[j])==is_included.end())
                    {
                        flag1=0;
                        break;
                    }
                }
                if(flag1==1&&(weight_till_now+mempool[i]->weight)<=4000000)
                {
                    flag++;
                    is_included.insert(mempool[i]->txid);
                    block.push_back(mempool[i]->txid);
                    weight_till_now+=mempool[i]->weight;
                }
            }

        }
        if(flag==0)
        {
            break;
        }
        }
    }
    for(i=0;i<block.size();i++)
    {
        cout<<block[i]<<endl;
    }
	return 0;
}

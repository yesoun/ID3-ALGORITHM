/*
 Read raw data from test.txt

 Powered by fenglinglu.

*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include "ID3.h"
using namespace std;


void show_data(const My_Data &data)
{
    for(vector<string>::const_iterator iter = data.attributes.begin();iter != data.attributes.end();++iter)
        cout <<*iter<<" ";
    cout<<endl;
    cout<<data.col<<endl;
    for(vector< vector<string> >::const_iterator iter1=data.items.begin();iter1!=data.items.end();++iter1)
    {
        for(vector<string>::const_iterator iter2 = (*iter1).begin();iter2 != (*iter1).end();++iter2)
            cout<<*iter2<<" ";
        cout<<endl;
    }
    cout<<data.row<<endl;
}
vector<string> att_val(const string &att,const My_Data &data)
{
    vector<string> val;
    string value;
    vector<string>::const_iterator iter_temp;
    for(vector< vector<string> >::const_iterator iter=data.items.begin();iter!=data.items.end();++iter)
    {
        iter_temp=find(data.attributes.begin(),data.attributes.end(),att);
        value=(*iter)[iter_temp-data.attributes.begin()];
        if(find(val.begin(),val.end(),value)==val.end())
            val.push_back(value);
    }
    return val;
}
My_Data read_data(const string &fname)
{
    My_Data my_data;
    ifstream data_file;
    data_file.open(fname.c_str(),ios::in);
    if(!data_file)
        cout << "ERROR!" <<endl;
    else
    {
        string line,word;
        getline(data_file,line);
        istringstream stream(line);
        while(stream>>word)
            my_data.attributes.push_back(word);
        my_data.col = my_data.attributes.size();
        while(getline(data_file,line))
        {
            vector<string> v_str;
            istringstream stream(line);
            while(stream>>word)
                v_str.push_back(word);
            my_data.items.push_back(v_str);
        }
        my_data.row = my_data.items.size();
        data_file.close();
    }
    return my_data;
}
My_Data pick_items(const string &att,const string &val,const My_Data &data)
{
    My_Data new_data;
    vector<string> item;
    vector<string>::const_iterator iter_temp;
    iter_temp=find(data.attributes.begin(),data.attributes.end(),att);
    if(iter_temp==data.attributes.end())
        cout<<"ERROR!"<<endl;
    else
    {
        int num=iter_temp-data.attributes.begin();
        for(vector< vector<string> >::const_iterator iter=data.items.begin();iter!=data.items.end();++iter)
            if((*iter)[num]==val)
                new_data.items.push_back(*iter);
        new_data.attributes=data.attributes;
        new_data.col=data.col;
        new_data.row=new_data.items.size();
    }
    return new_data;
}
double val_entropy(const My_Data &data)
{
    vector<string> S;
    vector<string>::const_iterator iter_temp;
    vector<int> S_Count;
    int S_Sum=data.items.size();
    for(vector< vector<string> >::const_iterator iter=data.items.begin();iter!=data.items.end();++iter)
    {
        iter_temp=find(S.begin(),S.end(),(*iter)[data.col-1]);
        if(iter_temp==S.end())
        {
            S.push_back((*iter)[data.col-1]);
            S_Count.push_back(1);
        }
        else
            ++S_Count[iter_temp-S.begin()];
    }
    vector<double> P(S_Count.size(),0.0);
    double I=0.0;
    for(int i=0;i!=P.size();++i)
    {
        P[i]=static_cast<double>(S_Count[i])/S_Sum;
        I=I-P[i]*log2(P[i]);
    }
    return I;
}
double att_entropy(const string &att,const My_Data &data)
{
    vector<string> val=att_val(att,data);
    My_Data new_data;
    double I=0.0,Val_E=0.0;
    for(vector<string>::const_iterator iter=val.begin();iter!=val.end();++iter)
    {
        new_data=pick_items(att,*iter,data);
        Val_E=val_entropy(new_data);
        I=I+Val_E*new_data.row/data.row;
    }
    return I;
}
Decision_Tree ID3(const My_Data &data)
{
    Decision_Tree tree,tree_temp;
    double entropy=val_entropy(data);
    double gain,Att_E,temp=0.0;
    for(vector<string>::const_iterator iter=data.attributes.begin();iter!=data.attributes.end()-1;++iter)
    {
        Att_E=att_entropy(*iter,data);
        gain=entropy-Att_E;
        if(gain>temp)
        {
            temp=gain;
            tree.set_root(*iter);
        }
    }
    if(tree.get_root()!="ROOT")
    {
        vector<string> branchs=att_val(tree.get_root(),data);
        for(vector<string>::const_iterator iter=branchs.begin();iter!=branchs.end();++iter)
        {
            My_Data new_data=pick_items(tree.get_root(),*iter,data);
            tree_temp=ID3(new_data);
            tree.set_branch(*iter,tree_temp);
        }
    }
    else
    {
        tree.set_leaf(true);
        tree.set_root((data.items[0])[data.col-1]);
    }
    return tree;
}

int main()
{
    My_Data data=read_data("test.txt");
    show_data(data);
    Decision_Tree tree=ID3(data);
    tree.show();
    return 1;
}

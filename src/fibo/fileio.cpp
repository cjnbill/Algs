#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include "fiboheap.cpp"
using namespace std;

unordered_map<string, fibonode<int>*> hashtable;
unordered_map<fibonode<int>*, string> reversed;
fiboheap<int>* hb=new fiboheap<int>();
unordered_map<string, fibonode<int>*>::iterator it;
ifstream infile;
ofstream ofile("output_file.txt",ios::app);

void reversehash(std::unordered_map<std::string, fibonode<int>*> &hashtable,unordered_map<fibonode<int>*, string> &reversed){
    for (it = hashtable.begin(); it != hashtable.end(); ++it)
        reversed[it->second] = it->first;
}

void ioprocess(string name){
    infile.open(name);
    string line;
    while (std::getline(infile, line)){
        istringstream iss(line);
        string a;
        int b;

        if (iss >> a >> b) {
            //the hashtag haven't store
            if ( hashtable.find(a) == hashtable.end() ) {
                fibonode<int>* pn=new fibonode<int>(b);
                hashtable[a]=pn;
                hb->insert(pn);
            } else {//already have this hashtag
                hb->increaseKey(hashtable[a],hashtable[a]->key+b);
            }
        }
        else
        {
            istringstream i(line);
            if(i >> b){//query
                reversehash(hashtable,reversed);
                string out;
                string maxhashtag;
                vector<fibonode<int>*> vf;

                while(b--){
                    fibonode<int>* pn=new fibonode<int>(hb->getMax()->key);
                    maxhashtag=reversed[hb->getMax()];
                    hashtable[maxhashtag]=pn;
                    vf.push_back(pn);
                    out=out+maxhashtag.substr(1)+',';
                    hb->removeMax();
                }
                out = out.substr(0,out.size()-1);
                ofile<<out<<std::endl;
                for(int i=0;i<vf.size();i++){
                    hb->insert(vf[i]);
                }
            }
            else{//stop
                break;
            }
        }
    }
    ofile.close();
    infile.close();
}

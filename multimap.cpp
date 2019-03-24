#include <iostream>
#include <map>
#include <cstdlib> 
#include <time.h>
#include <string>
#include <fstream>

using namespace std;

int main(){
	string key = "春天";//启动词
	string passage,learnData,check,check2;
	srand(int(time(0))); //随机种子 
	multimap<string,string> wordData;//字词库 
	typedef multimap<string,string>::iterator wordItor;
	string keyTmp,wordTmp; 
	ifstream fin;
	fin.open("wordData.txt");
	fin>>learnData;
	/* 创造字词库 */ 
	for(int i=0;i<learnData.length()-4;i+=2){
		check = learnData.substr(i,2);
		check2 = learnData.substr(i+2,2);
		if(check=="。"||check=="，"||check2=="。"||check2=="，"){
			keyTmp = learnData.substr(i,2);
			wordTmp = learnData.substr(i+2,4);
		}
		else{
			keyTmp = learnData.substr(i,4);
			wordTmp = learnData.substr(i+4,2);
		}
		wordData.insert(pair<string,string>(keyTmp,wordTmp));
	}
	while(cin>>key){
		if(wordData.find(key)==wordData.end()){
			cout<<"字词库暂时不支持该字，请重新输入！"<<endl;
			continue;
		}
		else{
			passage+=key;
			break;
		}
	}
	/* 遍历字词库
	string s="春天";
	pair<wordItor, wordItor> pos = wordData.equal_range(s);
	for(wordItor i=wordData.begin();i!=wordData.end();i++)
 	{
  		cout<<(*i).first<<" "
  		 <<(*i).second<<endl;
 	} */
    wordItor upper,lower;
    int cntRand=0;
    //****开始生成句子 **** 
    do{
    	int cntKey = wordData.count(key);
   		lower = wordData.find(key);
        while(1){
        	if(rand()%2&&rand()%2&&rand()%2){
        		passage+=(*lower).second;
        		wordData.erase(lower);
        	//	cout<<key<<" "<<(*lower).second<<" "<<cntKey<<" "<<cntRand<<endl;
        		cntRand=0;
        		break;
        	}
        	lower++;
        	if(++cntRand==cntKey){
        		lower=wordData.find(key);
        		cntRand=0;
        	} 
        }
   		key = passage.substr(passage.length()-4,passage.length()-1);
   		check = key.substr(2,2);
   		/* 结束/标点符号判断器 */ 
		if(check=="。"||check=="，"){
			if(rand()%2&&check=="。")break;
			key=check; 
		}	
   		if(wordData.find(key)==wordData.end())break;
    }while(1);
	cout<<passage<<endl; 
	fin.close();
	return 0; 
} 

#include <iostream>
#include <map>
#include <cstdlib> 
#include <time.h>
#include <string>
#include <fstream>

using namespace std;

int main(){
	//启动词
	string key="春天";
	string passage=key,learnData,check,check2;
	//随机种子 
	srand(int(time(0)));
	//使用multimap作为字词库的载体 
	multimap<string,string> wordData; 
	typedef multimap<string,string>::iterator wordItor;
	string keyTmp,wordTmp; 
	ifstream fin;
	fin.open("wordData.txt");
	while(fin>>keyTmp>>wordTmp){
		wordData.insert(pair<string,string>(keyTmp,wordTmp));
	} 
	fin.close();。 
	cout<<"******************************************"<<endl;
	cout<<"欢迎使用自动文章/句子生成器！             "<<endl;
	cout<<"请输入两个中文汉字作为启动字！            "<<endl;
	cout<<"******************************************"<<endl;
	cout<<"请输入: "<<endl; 
/*	while(cin>>key){
		if(wordData.find(key)==wordData.end()){
			cout<<"字词库暂时不支持该字，请重新输入！"<<endl;
			continue;
		}
		else{
			passage+=key;
			break;
		}
	}*/ 
    wordItor upper,lower;
    int cntRand=0;
    //开始生成句子（后测循环） 
    do{
    	//计算有多少个对应的value 
    	int cntKey=wordData.count(key);
    	//寻找对应的value(第一个地址) 
   		lower=wordData.find(key);
        while(1){
        	//如果值为真的话，则把value拼接到文章上 
        	if(rand()%2){
        		passage+=(*lower).second;
        		cntRand=0;
        		break;
        	}
        	//随机一个value 
			for(int i=0;i<rand()%100;i++){
				lower++;
        		if(++cntRand==cntKey){
        			lower=wordData.find(key);
        			cntRand=0;
        		} 
			} 
        }
        //key=文章的最后两个字 
   		key=passage.substr(passage.length()-4,passage.length()-1);
   		//检查key的后一个中文字 
   		check=key.substr(2,2); 
   		//标点符号判断器
		if(check=="。"||check=="，"||check=="！"||check=="？"||check=="："||check=="；"||check=="、"){
			//随机结束
			if(rand()%2&&check=="。")break;
			key=check;
		}
		//当找不到对应的key的时候，结束
   		if(wordData.find(key)==wordData.end())break;
    }while(1);
    
    int cntText=0;
	for(int i=0;i<passage.length();i++){
		cout<<passage[i];
		cntText++;
		if(cntText==42){
			cout<<endl;
			cntText=0;
		} 
	}
	cout<<endl;
	system("pause");
	return 0; 
} 

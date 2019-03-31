#include <iostream>
#include <map>
#include <cstdlib> 
#include <time.h>
#include <string>
#include <fstream>

using namespace std;

int main(){
	string key = "";//启动词
	string passage=key,learnData,check,check2;
	srand(int(time(0))); //随机种子 
	multimap<string,string> wordData;//字词库 
	typedef multimap<string,string>::iterator wordItor;
	string keyTmp,wordTmp; 
	ifstream fin;
	fin.open("wordData.txt");
	while(fin>>keyTmp>>wordTmp){
		wordData.insert(pair<string,string>(keyTmp,wordTmp));
	} 
	fin.close();
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
    //****开始生成句子 **** 
    do{
    	int cntKey=wordData.count(key);
   		lower=wordData.find(key);
        while(1){
        	if(rand()%2){
        		passage+=(*lower).second;
        		cntRand=0;
        		break;
        	}
        	lower++;
        	if(++cntRand==cntKey){
        		lower=wordData.find(key);
        		cntRand=0;
        	} 
        }
   		key=passage.substr(passage.length()-4,passage.length()-1);
   		check=key.substr(2,2);
   		/* 结束/标点符号判断器 */ 
		if(check=="。"||check=="，"){
			if(rand()%2&&check=="。")break;
			key=check; 
		}	
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
	return 0; 
} 

#include <iostream>
#include <map>
#include <cstdlib> 
#include <time.h>
#include <string>
#include <fstream>
#include <string.h>
using namespace std;

//文本库默认打开text.txt 
const string addressConst="wordData.txt";

//文本库 
class TextLib{
	public:
		//构造函数
		TextLib(string address); 
		//寻找输入的前缀对应的后缀的数量 
		int search(string key);
		//随机输出一个前缀中对应的后缀
		string output(string key);
		//扩充文本库 
		void extent(string address); 
		//友元文本生成器
		friend class TextGenerator; 
	private:
		//使用一对多的映射关系作为数据的载体 
		multimap<string,string> TextData;
		//地址
		string fileAddress;
};

//文本生成器 
class TextGenerator{
	public:
		//构造函数，输入一个key 
		TextGenerator(string key,string address=addressConst);
		//输出文章 
		void printPassage(); 
	private:
		//启动关键字 
		string key;
		//文章 
		string passage; 
		//使用组合形式结合文本库和文本生成器 
		TextLib *lib; 
}; 

int main(){
	string key;
	cout<<"请输入一个关键字以创造一个文章"<<endl; 
	cin>>key; 
	TextGenerator text(key);
	text.printPassage();
	return 0;
} 

//此处开始定义TextGenerator类函数
TextGenerator::TextGenerator(string key,string address){
	passage+=key; 
	//初始化文本库
	lib=new TextLib(address); 
	typedef multimap<string,string>::iterator wordItor;
	wordItor word;
	string check;
	do{
        passage+=(*lib).output(key);
        //key=文章的最后两个字 
   		key=passage.substr(passage.length()-4,passage.length()-1);
   		//检查key的后一个中文字 
   		check=key.substr(2,2); 
   		//标点符号判断器
		if(check=="。"||check=="，"||check=="！"||check=="？"||check=="："||check=="；"||check=="、"){
			//随机结束
		//	if(rand()%2&&check=="。")break;
			key=check;
		}
		//当找不到对应的key的时候，随机找一个值 
   		if((*lib).TextData.find(key)==(*lib).TextData.end()){
		   word=(*lib).TextData.begin();
		   while(word!=(*lib).TextData.end()){
		   		word++;
		   		if(rand()%2){
		   			key=(*word).second;
		   			break;
				}
		   }
		} 
   		if(passage.length()>2000){
   			passage+="。";
   			break;
		}
    }while(1);
}

void TextGenerator::printPassage(){
	cout<<passage;
}

//此处开始定义TextLib类函数
TextLib::TextLib(string address){
	char file[200];
	strcpy(file,address.c_str());
	fileAddress=address;
	//初始化前缀后缀 
	string keyTmp,wordTmp; 
	ifstream fin;
	fin.open(file);
	//从文件中读取前缀后缀直到没有 
	while(fin>>keyTmp>>wordTmp){
		TextData.insert(pair<string,string>(keyTmp,wordTmp));
	} 
	fin.close();
}

int TextLib::search(string key){
	return TextData.count(key);
}

string TextLib::output(string key){
	//声明一个迭代器 
	typedef multimap<string,string>::iterator wordItor;
	//如果没有数据，返回结束符号 
	int cntKey=TextData.count(key),cntRand=0;
	if(!cntKey) return "\n";
	wordItor word;
	word=TextData.find(key);
	//创造一个死循环作为随机之用 
	while(1){
        	//如果值为真的话，输出value 
        	if(rand()%2){
        		return (*word).second;
        	}
        	//随机一个value 
			for(int i=0;i<rand()%100;i++){
				word++;
        		if(++cntRand==cntKey){
        			word=TextData.find(key);
        			cntRand=0;
        		} 
			} 
    }
}

//扩充文本库 
void TextLib::extent(string address){
	char file[200];
	strcpy(file,address.c_str());
	ifstream fin;
	//依次为 临时key，临时字，检查器1，检查器2，要学习的数据 
	string keyTmp,wordTmp,check,learnData; 
	typedef multimap<string,string>::iterator wordItor;
	fin.open(file);
	while(fin>>learnData){ 
	for(int i=0;i<learnData.length()-4;i+=2){
			//检测器，截取一个字节检查是否为英语标点符号
			check=learnData.substr(i,1);
			//遇到一切英文标点符号，一律变成句号
			if(ispunct(check[0])){
				keyTmp="。" ;
				i++;
				wordTmp=learnData.substr(i,4);
				TextData.insert(pair<string,string>(keyTmp,wordTmp));
				continue; 
			}
			//检测器 ，截取一个中文字符后的一个字节是否为英语标点符号，如果是，直接跳过
			check=learnData.substr(i+2,1);
			if(ispunct(check[0]))continue; 
			//检查器，截取第二个中文字符 
	 		check=learnData.substr(i+2,2);
	 		//如果检查器为标点符号，跳过 
	 		if(check=="。"||check=="，"||check=="！"||check=="？"||check=="："||check=="；"||check=="、")continue;
	 		//检测器，截取第一个中文字符 
			check=learnData.substr(i,2);
			//如果检查为标点符号，则标点符号作为key 
			if(check=="。"||check=="，"||check=="！"||check=="？"||check=="："||check=="；"||check=="、"){
				keyTmp=learnData.substr(i,2);
				//检查后一个字节是否为英文字符，是的话默认为句号 
				check=learnData.substr(i+2,1);
				if(ispunct(check[0])){
					wordTmp="。" ;
				}
				else{
					wordTmp=learnData.substr(i+2,4);
				}
			}
			//否则默认前两个中文字符作为key 
			else{
				keyTmp=learnData.substr(i,4);
				//检查后一个字节是否为英文字符，是的话默认为句号 
				check=learnData.substr(i+4,1);
				if(ispunct(check[0])){
					wordTmp="。" ;
				}
				else{
					wordTmp=learnData.substr(i+4,2);
				}
			}
			TextData.insert(pair<string,string>(keyTmp,wordTmp));
		}
	}
	fin.close(); 
	ofstream fout;
	fout.open("wordData.txt",ios::app);
	//开始追加字词到字词库 
}

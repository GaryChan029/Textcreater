#include <iostream>
#include <map>
#include <cstdlib> 
#include <time.h>
#include <string>
#include <fstream>

using namespace std;

int main(){
	ifstream fin;
	//依次为 临时key，临时字，检查器1，检查器2，要学习的数据 
	string keyTmp,wordTmp,check,learnData; 
	char file[200];
	cout<<"请输入要变成字词库的文章的路径（文章不能含有任何的英文字符！）:" ;
	cin>>file;
	//使用multimap作为字词库的载体 
	multimap<string,string> wordData;
	//设置一个迭代器 
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
				wordData.insert(pair<string,string>(keyTmp,wordTmp));
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
			wordData.insert(pair<string,string>(keyTmp,wordTmp));
		}
	}
	fin.close(); 
	ofstream fout;
	fout.open("wordData.txt",ios::app);
	//开始追加字词到字词库 
	for(wordItor i=wordData.begin();i!=wordData.end();i++)
 	{
  		fout<<(*i).first<<" "<<(*i).second<<endl;
 	}
	fout.close();
	system("pause");
	return 0;	
}

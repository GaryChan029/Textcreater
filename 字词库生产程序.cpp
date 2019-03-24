#include <iostream>
#include <map>
#include <cstdlib> 
#include <time.h>
#include <string>
#include <fstream>

using namespace std;

int main(){
	ifstream fin;
	string keyTmp,wordTmp,check,check2,learnData; 
	char file[200];
	cout<<"请输入要变成字词库的文章的路径:" ;
	cin>>file;
	multimap<string,string> wordData;
	typedef multimap<string,string>::iterator wordItor;
	fin.open(file);
	fin>>learnData; 
	for(int i=0;i<learnData.length()-4;i+=2){
		check=learnData.substr(i,2);
		check2=learnData.substr(i+2,2);
		if(check=="。"||check=="，"||check2=="。"||check2=="，"){
			keyTmp=learnData.substr(i,2);
			wordTmp=learnData.substr(i+2,4);
		}
		else{
			keyTmp=learnData.substr(i,4);
			wordTmp=learnData.substr(i+4,2);
		}
		wordData.insert(pair<string,string>(keyTmp,wordTmp));
	}
	fin.close();
	ofstream fout;
	fout.open("wordData.txt",ios::app);
	for(wordItor i=wordData.begin();i!=wordData.end();i++)
 	{
  		fout<<(*i).first<<" "
  		 <<(*i).second<<endl;
 	}
	fout.close();
	return 0;	
}

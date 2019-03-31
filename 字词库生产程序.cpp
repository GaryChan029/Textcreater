#include <iostream>
#include <map>
#include <cstdlib> 
#include <time.h>
#include <string>
#include <fstream>

using namespace std;

int main(){
	ifstream fin;
	//����Ϊ ��ʱkey����ʱ�֣������1�������2��Ҫѧϰ������ 
	string keyTmp,wordTmp,check,learnData; 
	char file[200];
	cout<<"������Ҫ����ִʿ�����µ�·�������²��ܺ����κε�Ӣ���ַ�����:" ;
	cin>>file;
	//ʹ��multimap��Ϊ�ִʿ������ 
	multimap<string,string> wordData;
	//����һ�������� 
	typedef multimap<string,string>::iterator wordItor;
	fin.open(file);
	while(fin>>learnData){ 
	for(int i=0;i<learnData.length()-4;i+=2){
			//���������ȡһ���ֽڼ���Ƿ�ΪӢ�������
			check=learnData.substr(i,1);
			//����һ��Ӣ�ı����ţ�һ�ɱ�ɾ��
			if(ispunct(check[0])){
				keyTmp="��" ;
				i++;
				wordTmp=learnData.substr(i,4);
				wordData.insert(pair<string,string>(keyTmp,wordTmp));
				continue; 
			}
			//����� ����ȡһ�������ַ����һ���ֽ��Ƿ�ΪӢ������ţ�����ǣ�ֱ������
			check=learnData.substr(i+2,1);
			if(ispunct(check[0]))continue; 
			//���������ȡ�ڶ��������ַ� 
	 		check=learnData.substr(i+2,2);
	 		//��������Ϊ�����ţ����� 
	 		if(check=="��"||check=="��"||check=="��"||check=="��"||check=="��"||check=="��"||check=="��")continue;
	 		//���������ȡ��һ�������ַ� 
			check=learnData.substr(i,2);
			//������Ϊ�����ţ����������Ϊkey 
			if(check=="��"||check=="��"||check=="��"||check=="��"||check=="��"||check=="��"||check=="��"){
				keyTmp=learnData.substr(i,2);
				//����һ���ֽ��Ƿ�ΪӢ���ַ����ǵĻ�Ĭ��Ϊ��� 
				check=learnData.substr(i+2,1);
				if(ispunct(check[0])){
					wordTmp="��" ;
				}
				else{
					wordTmp=learnData.substr(i+2,4);
				}
			}
			//����Ĭ��ǰ���������ַ���Ϊkey 
			else{
				keyTmp=learnData.substr(i,4);
				//����һ���ֽ��Ƿ�ΪӢ���ַ����ǵĻ�Ĭ��Ϊ��� 
				check=learnData.substr(i+4,1);
				if(ispunct(check[0])){
					wordTmp="��" ;
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
	//��ʼ׷���ִʵ��ִʿ� 
	for(wordItor i=wordData.begin();i!=wordData.end();i++)
 	{
  		fout<<(*i).first<<" "<<(*i).second<<endl;
 	}
	fout.close();
	system("pause");
	return 0;	
}

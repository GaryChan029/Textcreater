#include <iostream>
#include <map>
#include <cstdlib> 
#include <time.h>
#include <string>
#include <fstream>

using namespace std;

int main(){
	//������
	string key="����";
	string passage=key,learnData,check,check2;
	//������� 
	srand(int(time(0)));
	//ʹ��multimap��Ϊ�ִʿ������ 
	multimap<string,string> wordData; 
	typedef multimap<string,string>::iterator wordItor;
	string keyTmp,wordTmp; 
	ifstream fin;
	fin.open("wordData.txt");
	while(fin>>keyTmp>>wordTmp){
		wordData.insert(pair<string,string>(keyTmp,wordTmp));
	} 
	fin.close();
	cout<<"******************************************"<<endl;
	cout<<"��ӭʹ���Զ�����/������������             "<<endl;
	cout<<"�������������ĺ�����Ϊ�����֣�            "<<endl;
	cout<<"******************************************"<<endl;
	cout<<"������: "<<endl; 
    wordItor upper,lower;
    int cntRand=0;
    //��ʼ���ɾ��ӣ����ѭ���� 
    do{
    	//�����ж��ٸ���Ӧ��value 
    	int cntKey=wordData.count(key);
    	//Ѱ�Ҷ�Ӧ��value(��һ����ַ) 
   		lower=wordData.find(key);
        while(1){
        	//���ֵΪ��Ļ������valueƴ�ӵ������� 
        	if(rand()%2){
        		passage+=(*lower).second;
        		cntRand=0;
        		break;
        	}
        	//���һ��value 
			for(int i=0;i<rand()%100;i++){
				lower++;
        		if(++cntRand==cntKey){
        			lower=wordData.find(key);
        			cntRand=0;
        		} 
			} 
        }
        //key=���µ���������� 
   		key=passage.substr(passage.length()-4,passage.length()-1);
   		//���key�ĺ�һ�������� 
   		check=key.substr(2,2); 
   		//�������ж���
		if(check=="��"||check=="��"||check=="��"||check=="��"||check=="��"||check=="��"||check=="��"){
			//�������
			if(rand()%2&&check=="��")break;
			key=check;
		}
		//���Ҳ�����Ӧ��key��ʱ�򣬽���
   		if(wordData.find(key)==wordData.end())break;
    }while(1);
    
    
	cout<<endl;
	system("pause");
	return 0; 
} 

#include <iostream>
#include <map>
#include <cstdlib> 
#include <time.h>
#include <string>
#include <fstream>

using namespace std;

int main(){
	string key = "����";//������ 
	string passage,learnData;
	passage+=key;//���� 
	char * checkKey = &key[0];
	srand(int(time(0))); //������� 
	multimap<string,string> wordData;//�ִʿ� 
	typedef multimap<string,string>::iterator wordItor;
	string keyTmp,wordTmp; 
	ifstream fin;
	fin.open("wordData.txt");
	fin>>learnData;
	/* �����ִʿ� */ 
	for(int i=0;i<learnData.length()-4;i+=2){
		keyTmp = learnData.substr(i+0,4);
		wordTmp = learnData.substr(i+4,2);
		wordData.insert(pair<string,string>(keyTmp,wordTmp));
	}
	/*�����ִʿ�
	string s="����";
	pair<wordItor, wordItor> pos = wordData.equal_range(s);
	for(wordItor i=wordData.begin();i!=wordData.end();i++)
 	{
  		cout<<(*i).first<<" "
  		 <<(*i).second<<endl;
 	} */
    wordItor upper,lower;
    int cntRand=0;
    //****��ʼ���ɾ��� **** 
    do{
    	cout<<key<<endl;
    	int cntKey = wordData.count(key);
   		lower = wordData.lower_bound(key);
		string check = key.substr(0,2);	
		if(check=="��")break;
        while(1){
        	if(rand()%2){
        		passage+=(*lower).second;
        		break;
        	}
        	lower++;
        	if(cntRand++==cntKey){
        		lower=wordData.lower_bound(key);
        	}
        }
   		key = passage.substr(passage.length()-4,passage.length()-1);
   		if(wordData.find(key)==wordData.end())break;
    }while(1);
	cout<<passage<<endl; 
	fin.close();
	return 0; 
} 

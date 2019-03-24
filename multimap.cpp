#include <iostream>
#include <map>
#include <cstdlib> 
#include <time.h>
#include <string>
#include <fstream>

using namespace std;

int main(){
	string key = "����";//������
	string passage,learnData,check,check2;
	srand(int(time(0))); //������� 
	multimap<string,string> wordData;//�ִʿ� 
	typedef multimap<string,string>::iterator wordItor;
	string keyTmp,wordTmp; 
	ifstream fin;
	fin.open("wordData.txt");
	/* �����ִʿ�  
	for(int i=0;i<learnData.length()-4;i+=2){
		check=learnData.substr(i,2);
		check2=learnData.substr(i+2,2);
		if(check=="��"||check=="��"||check2=="��"||check2=="��"){
			keyTmp=learnData.substr(i,2);
			wordTmp=learnData.substr(i+2,4);
		}
		else{
			keyTmp=learnData.substr(i,4);
			wordTmp=learnData.substr(i+4,2);
		}
		wordData.insert(pair<string,string>(keyTmp,wordTmp));
	}
	 */
	while(fin>>keyTmp>>wordTmp){
		wordData.insert(pair<string,string>(keyTmp,wordTmp));
	} 
	fin.close();
	while(cin>>key){
		if(wordData.find(key)==wordData.end()){
			cout<<"�ִʿ���ʱ��֧�ָ��֣����������룡"<<endl;
			continue;
		}
		else{
			passage+=key;
			break;
		}
	}
	/* �����ִʿ�
	for(wordItor i=wordData.begin();i!=wordData.end();i++)
 	{
  		cout<<(*i).first<<" "
  		 <<(*i).second<<endl;
 	} */ 
    wordItor upper,lower;
    int cntRand=0;
    //****��ʼ���ɾ��� **** 
    do{
    	int cntKey=wordData.count(key);
   		lower=wordData.find(key);
        while(1){
        	if(rand()%2&&rand()%2&&rand()%2){
        		passage+=(*lower).second;
        	//	wordData.erase(lower);
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
   		key=passage.substr(passage.length()-4,passage.length()-1);
   		check=key.substr(2,2);
   		/* ����/�������ж��� */ 
		if(check=="��"||check=="��"){
			if(rand()%2&&check=="��")break;
			key=check; 
		}	
   		if(wordData.find(key)==wordData.end())break;
    }while(1);
	cout<<passage<<endl; 
	ofstream fout;
	fout.open("wordData.txt");
	for(wordItor i=wordData.begin();i!=wordData.end();i++)
 	{
  		fout<<(*i).first<<" "
  		 <<(*i).second<<endl;
 	}
	fout.close();
	return 0; 
} 

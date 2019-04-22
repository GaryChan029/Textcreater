#include <iostream>
#include <map>
#include <cstdlib> 
#include <time.h>
#include <string>
#include <fstream>
#include <string.h>
using namespace std;

//�ı���Ĭ�ϴ�text.txt 
const string addressConst="wordData.txt";

//�ı��� 
class TextLib{
	public:
		//���캯��
		TextLib(string address); 
		//Ѱ�������ǰ׺��Ӧ�ĺ�׺������ 
		int search(string key);
		//������һ��ǰ׺�ж�Ӧ�ĺ�׺
		string output(string key);
		//�����ı��� 
		void extent(string address); 
		//��Ԫ�ı�������
		friend class TextGenerator; 
	private:
		//ʹ��һ�Զ��ӳ���ϵ��Ϊ���ݵ����� 
		multimap<string,string> TextData;
		//��ַ
		string fileAddress;
};

//�ı������� 
class TextGenerator{
	public:
		//���캯��������һ��key 
		TextGenerator(string key,string address=addressConst);
		//������� 
		void printPassage(); 
	private:
		//�����ؼ��� 
		string key;
		//���� 
		string passage; 
		//ʹ�������ʽ����ı�����ı������� 
		TextLib *lib; 
}; 

int main(){
	string key;
	cout<<"������һ���ؼ����Դ���һ������"<<endl; 
	cin>>key; 
	TextGenerator text(key);
	text.printPassage();
	return 0;
} 

//�˴���ʼ����TextGenerator�ຯ��
TextGenerator::TextGenerator(string key,string address){
	passage+=key; 
	//��ʼ���ı���
	lib=new TextLib(address); 
	typedef multimap<string,string>::iterator wordItor;
	wordItor word;
	string check;
	do{
        passage+=(*lib).output(key);
        //key=���µ���������� 
   		key=passage.substr(passage.length()-4,passage.length()-1);
   		//���key�ĺ�һ�������� 
   		check=key.substr(2,2); 
   		//�������ж���
		if(check=="��"||check=="��"||check=="��"||check=="��"||check=="��"||check=="��"||check=="��"){
			//�������
		//	if(rand()%2&&check=="��")break;
			key=check;
		}
		//���Ҳ�����Ӧ��key��ʱ�������һ��ֵ 
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
   			passage+="��";
   			break;
		}
    }while(1);
}

void TextGenerator::printPassage(){
	cout<<passage;
}

//�˴���ʼ����TextLib�ຯ��
TextLib::TextLib(string address){
	char file[200];
	strcpy(file,address.c_str());
	fileAddress=address;
	//��ʼ��ǰ׺��׺ 
	string keyTmp,wordTmp; 
	ifstream fin;
	fin.open(file);
	//���ļ��ж�ȡǰ׺��׺ֱ��û�� 
	while(fin>>keyTmp>>wordTmp){
		TextData.insert(pair<string,string>(keyTmp,wordTmp));
	} 
	fin.close();
}

int TextLib::search(string key){
	return TextData.count(key);
}

string TextLib::output(string key){
	//����һ�������� 
	typedef multimap<string,string>::iterator wordItor;
	//���û�����ݣ����ؽ������� 
	int cntKey=TextData.count(key),cntRand=0;
	if(!cntKey) return "\n";
	wordItor word;
	word=TextData.find(key);
	//����һ����ѭ����Ϊ���֮�� 
	while(1){
        	//���ֵΪ��Ļ������value 
        	if(rand()%2){
        		return (*word).second;
        	}
        	//���һ��value 
			for(int i=0;i<rand()%100;i++){
				word++;
        		if(++cntRand==cntKey){
        			word=TextData.find(key);
        			cntRand=0;
        		} 
			} 
    }
}

//�����ı��� 
void TextLib::extent(string address){
	char file[200];
	strcpy(file,address.c_str());
	ifstream fin;
	//����Ϊ ��ʱkey����ʱ�֣������1�������2��Ҫѧϰ������ 
	string keyTmp,wordTmp,check,learnData; 
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
				TextData.insert(pair<string,string>(keyTmp,wordTmp));
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
			TextData.insert(pair<string,string>(keyTmp,wordTmp));
		}
	}
	fin.close(); 
	ofstream fout;
	fout.open("wordData.txt",ios::app);
	//��ʼ׷���ִʵ��ִʿ� 
}

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <vector>
#include <windows.h>
#include <stdio.h>

using namespace std;
//biblioteka inpout32.dll

HMODULE Module = LoadLibraryA("inpout32.dll");

typedef short (WINAPI * ptrInp32)(short PortAddress);
ptrInp32 Inp32=(ptrInp32)GetProcAddress(Module, TEXT("Inp32"));

typedef short (WINAPI * pfnOut32)(short PortAddress, short data);
pfnOut32 Out32=(pfnOut32)GetProcAddress(Module, TEXT("Out32"));

HINSTANCE hLib;

int LPT=0x378;
int dane=0;
int delay=0;
BYTE b=0x00;

ptrInp32 in;
pfnOut32 out;

vector <int> sekwencja;

//void sendData(int, int);
void import(vector <int>&);
int biblioteka();

int main(){
	
	biblioteka();
	import(sekwencja);
	
	do{
		int cykl=0;
		for(int i=0;i<sekwencja.size();i++){
			if(i%9==0 && i!=0)cout<<"\n";
			cout<<sekwencja[i]<<" ";
			
		}
		
	for(int j=0;j<sekwencja.size()/9;j++){
		
		int bin=0;
		dane=0;
		for(int i=(cykl*9); i<((cykl*9)+9);i++){
			if(i%9==0)delay=sekwencja[i];
			if(sekwencja[i]==1)dane+=bin;
			
			if(bin<=1){
				bin++;
			}else{
				bin*=2;
			}
			if(i==sekwencja.size())break;
		}
	cout<<"\nbin: " <<bin<<" cykl: "<<cykl<<" dane: "<<dane<<" dane hex: "<< std::hex<<dane<<std::dec<<"\n";
		cykl++;
		b=(byte)dane;
		out(LPT, b);
		cout<<"\nTick...\n";	
		Sleep(delay);
	}
		
	
	
	}while(GetAsyncKeyState(VK_ESCAPE)==0);
	
	FreeLibrary(hLib);
	cout<<"\n\n\n";
	system("PAUSE");
	return 0;	
}

void import(vector <int> &sekwencja){	
		ifstream rej("rejestr.txt");
		while (true)			
		{
			
			int x;
			rej>>x;		
			sekwencja.push_back(x);
			if (rej.eof())break;	
		}
}

int biblioteka(){
	hLib = LoadLibrary("inpout32.dll");
	if (hLib == NULL) {
	cout<<"LoadLibrary Failed.\n";
	cin.get();
	return -1;
	}
	in = (ptrInp32) GetProcAddress(hLib, "Inp32");
	if (in == NULL) {
	cout<<"GetProcAddress for Inp32 Failed.\n";
	cin.get();
	return -1;
	}
	out = (pfnOut32) GetProcAddress(hLib, "Out32");
	if (out == NULL) {
	cout<<"GetProcAddress for Oup32 Failed.\n";
	cin.get();
	return -1;
	}
}

//void sendData(int LPT, BYTE dane){
//	
//	asm(".intel_syntax noprefix");
//	asm("mov dx, _LPT");
//	asm("mov al, _dane");
//	asm("out dx, al");
//	asm(".att_syntax prefix");
//
//
//}


#include <iostream>
#include "veri.h"
#include <stack> 
#include <queue> 
#include <string> 
#include <chrono>

using namespace std;
void yazdir(Dugum*);//Mevcut agaci yazdirir

int main()
{
	 string arama;
	 int aranan,choice,choice2;
	 IkiliSiralamaAgaci bst;

	 cout << endl;
	 cout << "\tArama yapacaginiz agaci secin (1,2,3)" << endl;
	 cout << "\t" << ""; cin >> choice; cout<< endl;
	 if (choice == 1)
		 bst.agacKur(dizi1);
	 else if (choice == 2)
		 bst.agacKur(dizi2);
	 else if (choice == 3)
		 bst.agacKur(dizi3);
	 else
		 cout << "hata" << endl;
	 cout << "\tAgac "<<choice<<" icin arama yontemi seciniz (DFS:1, BFS:2)" << endl;
	 cout << "\t" << "";cin >> choice2;cout << endl;
	 if (choice2 == 1)
		 arama = "DFS";
	 else if (choice2 == 2)
		 arama = "BFS";
	 else
		 cout << "hata" << endl;
	 cout << "\tAgac " << choice << " uzerinde "<<arama<<" ile arayacaginiz degeri giriniz" << endl;
	 cout << "\t" << ""; cin >> aranan; cout << endl;

     if (choice2 == 1) {
		 auto begin1 = std::chrono::high_resolution_clock::now();
		 if (DFS(bst.kok, aranan) == true) {
		     auto end1 = std::chrono::high_resolution_clock::now();
			 cout << "\t" << "SONUC => VERI BULUNDU!"<<endl;
			 auto elapsed1 = std::chrono::duration_cast<std::chrono::nanoseconds>(end1 - begin1);
			 cout << "\t" << "GECEN SURE => "<<elapsed1.count() << endl;

		 }else
			 cout << "\t" << "SONUC => VERI BULUNAMADI!" << endl;

	 }
	 else if (choice2 == 2) {
		 auto begin2 = std::chrono::high_resolution_clock::now();
		 if (BFS(bst.kok, aranan) == true) {
			 auto end2 = std::chrono::high_resolution_clock::now();
			 cout << "\t" << "SONUC => VERI BULUNDU!" << endl;
			 auto elapsed2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - begin2);
			 cout << "\t" << "GECEN SURE => " << elapsed2.count() << endl;
		 }else
			 cout << "\t" << "SONUC => VERI BULUNAMADI!" << endl;

	 }
	 bst.agacKapat();
}
void IkiliSiralamaAgaci::agacKur(int* dizi) {
	Dugum* tp = NULL;
	kok = NULL;
	if (!kok) {
		kok = new Dugum;
		kok->veri = dizi[0];
		kok->sag = kok->sol = NULL;
		tp = kok;
	}
	for (int i = 1; i < UZUNLUK; i++)
	{
		if (dizi[i] < tp->veri) {
			if (!tp->sol) {
				tp->sol = new Dugum;
				tp->sol->sag = tp->sol->sol = NULL;
				tp->sol->veri = dizi[i];
				tp = kok;
			}
			else
			{
				tp = tp->sol; i--;
			}
		}
		else
		{
			if (!tp->sag)
			{
				tp->sag = new Dugum;
				tp->sag->sol = tp->sag->sag = NULL;
				tp->sag->veri = dizi[i];
				tp = kok;
			}
			else
			{
				tp = tp->sag; i--;
			}
		}
	}
}
void IkiliSiralamaAgaci::agacKapat() {
	if (kok) {
		if (kok->sol != NULL)
		{ 
			kok->sol = NULL; 
		}
		if (kok->sag != NULL) 
		{
		    kok->sag = NULL; 
		}
		delete kok;
	}
}
void yazdir(Dugum* node)
{
	if (node == NULL) {
		return;
	}
	cout << node->veri << " ";
	yazdir(node->sol);
	yazdir(node->sag);
}
bool DFS(Dugum* dgm, int aranan) {
	Dugum* p;
	stack<Dugum*> yigin;
	yigin.push(dgm);
	while (!yigin.empty()) {
		p = yigin.top();
		yigin.pop();
		if (aranan == p->veri) {
			return true;
		}
		if (p->sag)
			yigin.push(p->sag);
		if (p->sol)
			yigin.push(p->sol);
	}
	return false;
}
bool BFS(Dugum* dgm, int aranan) {
	Dugum* p;
	queue<Dugum*> kuyruk;
	kuyruk.push(dgm);
	while (!kuyruk.empty()) {
		p = kuyruk.front();
		kuyruk.pop();
		if (aranan == p->veri) {
			return true;
		}
		if (p->sag)
			kuyruk.push(p->sag);
		if (p->sol)
			kuyruk.push(p->sol);
	}
	return false;
}
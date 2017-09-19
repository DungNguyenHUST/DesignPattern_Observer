#include <iostream>
#include <vector>
#include <Windows.h>
using namespace std;

class Subject
{
	// tao mot list Observer
	vector <class Observer *> views;
	int value;
public:
	// dang kis Observer
	void attach(Observer *obs) {
		views.push_back(obs);
	}
	// det gia tri va notify tat ca cac Ob
	void setVal(int val) {
		value = val;
		notify();
	}
	// lay ra gia tri hien tai
	int getVal() {
		return value;
	}
	void notify();
};
class Observer
{
	Subject *model;
	int denom;
public:
	//dang ki Ob vao list
	Observer(Subject *mod, int div) {
		model = mod;
		denom = div;
		model->attach(this);
	}
	// tao ham update
	virtual void update() = 0;
protected:
	// tao mot con tro tro ham tro toi Subject
	Subject *getSubject() {
		return model;
	}
	int getDivisor() {
		return denom;
	}

};
// tao ham notify
void Subject::notify() {
		for (int i = 0; i < views.size(); i++)
		views[i]->update();
}
class DivObserver :public Observer {
public :
	DivObserver(Subject *mod, int div) :Observer(mod, div){}
	// lay ra gia tri bi thay doi de thuc hien cong viec khac
	void update() {
		int v = getSubject()->getVal();
		int d = getDivisor();
		cout << v << " div " << d << " is " << v / d << '\n';
	}
};
class ModObserver :public Observer {
public:
	ModObserver(Subject *mod, int div) :Observer(mod, div) {

	}
	void update() {
	int v = getSubject()->getVal(), d = getDivisor();
	cout << v << " mod " << d << " is " << v % d << '\n';
	}
};
int main() {
	Subject subj;
	DivObserver divObs1(&subj, 10); // 7. Client configures the number and
	DivObserver divObs2(&subj, 3); //    type of Observers
	ModObserver modObs3(&subj, 3);
	subj.setVal(1000);
	system("pause");
	return 0;
}
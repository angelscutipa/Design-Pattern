#include <iostream>
#include <vector>
using namespace std;

class Subject {
    // 1. funcionalidades independientes....
    vector < class Observer * > observers;
    int value;
  public:
    void enlazarobservers(Observer *obs) {
        observers.push_back(obs);
    }
    void setVal(int val) {
        value = val;
        notify();
    }
    int getVal() {
        return value;
    }
    void notify();
};

class Observer {
    // 2. funcionalidades dependientes...
    Subject *model;
    int dat;
  public:
    Observer(Subject *mod, int div) {
        model = mod;
        dat = div;
        // 4. los observadores se registran con el sujeto....
        model->enlazarobservers(this);
    }
    virtual void update() = 0;
  protected:
    Subject *getSubject() {
        return model;
    }
    int getDivisor() {
        return dat;
    }
};

void Subject::notify() {
  for (int i = 0; i < observers.size(); i++)
    observers[i]->update();
}

class DivObserver: public Observer {
  public:
    DivObserver(Subject *mod, int div): Observer(mod, div){}
    void update() {
        int v = getSubject()->getVal(), d = getDivisor();
        cout << v << " / " << d << " is " << v / d << '\n';
    }
};

class ModObserver: public Observer {
  public:
    ModObserver(Subject *mod, int div): Observer(mod, div){}
    void update() {
        int v = getSubject()->getVal(), d = getDivisor();
        cout << v << " % " << d << " is " << v % d << '\n';
    }
};

int main() {
  Subject subj;
  DivObserver a(&subj, 4);
  DivObserver b(&subj, 3);
  ModObserver c(&subj, 3);
  subj.setVal(14);
  cout<<endl;
  cout<<"probamos con otro..."<<endl;
  subj.setVal(20);

}

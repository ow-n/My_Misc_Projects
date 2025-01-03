#include <iostream>

using namespace std;

class I {
	public:
		virtual void play() = 0;
};

class Toy: public I {
  public:
    void play() {
        cout << "play ";
    }
};

class Scope: public I {
  public:
	Scope(I *p) {
		this->p = p;
	}
    void play() {
        p->play();
        cout << "accurately ";
    };
  private:
    I* p;
};

class Muffler: public I {
  public:
    Muffler(I *p) {
		this->p = p;
	}
    void play() {
        p->play();
        cout << "quietly ";
    };
  private:
    I* p;
};

int main() {
  I *toy = new Scope(new Muffler(new Toy()));
  toy->play();
  cout << '\n';
}

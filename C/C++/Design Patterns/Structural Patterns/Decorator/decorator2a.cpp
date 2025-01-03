#include <iostream>

using namespace std;

class Toy {
  public:
    virtual void play() {
        cout << "play ";
    }
};

class ToyWithScope: public Toy {
  public:
    void play() {
        Toy::play();
        improveAccuracy();
    };
  private:
    void improveAccuracy() {
        cout << "accurately ";
    }
};

class ToyWithMuffler: public Toy {
  public:
    void play() {
        Toy::play();
        reduceSound();
    };
  private:
    void reduceSound() {
        cout << "quietly ";
    }
};

int main() {
  Toy toy1;
  ToyWithScope toy2;
  ToyWithMuffler toy3;
  toy1.play();
  cout << '\n';
  toy2.play();
  cout << '\n';
  toy3.play();
  cout << '\n';
}

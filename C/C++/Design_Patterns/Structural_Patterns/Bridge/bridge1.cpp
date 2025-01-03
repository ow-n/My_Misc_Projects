#include <iostream>

using namespace std;

class DrawAPI {
   public:
    virtual void drawColor() = 0;
};

class DrawRed: public DrawAPI {
   public:
    void drawColor() {
        cout << "[ color: red]" << endl;
   }
};

class DrawGreen: public DrawAPI {
   public:
    void drawColor() {
        cout << "[ color: green]" << endl;
   }
};

class Shape {
   protected:
    DrawAPI *drawAPI;
    Shape(DrawAPI *drawAPI){
      this->drawAPI = drawAPI;
    }
   public:
    virtual void draw() = 0;	
};

class Circle: public Shape {
   private:
    int x, y, radius;
   public:
    Circle(int x, int y, int radius, DrawAPI *drawAPI):Shape(drawAPI) {
        this->x = x;  
        this->y = y;  
        this->radius = radius;
    }
    void draw() {
        cout << "Drawing Circle with radius: " << radius << ", at x: " << x << ", y: " << y << " ";
        drawAPI->drawColor();
    }
};

class Square: public Shape {
   private:
    int x, y, x2, y2;
   public:
    Square(int x, int y, int x2, int y2, DrawAPI *drawAPI):Shape(drawAPI) {
        this->x = x;  
        this->y = y;  
        this->x2 = x2;  
        this->y2 = y2;
    }
    void draw() {
        cout << "Drawing Square at x1: " << x << ", y1: " << y << ", x2: " << x2 << ", y2: " << y2 << " ";
        drawAPI->drawColor();
    }
};

int main() {
   cout << "Hello World" << endl; 
   Shape *redCircle = new Circle(100,100, 10, new DrawRed());
   Shape *greenCircle = new Circle(100,100, 10, new DrawGreen());
   redCircle->draw();
   greenCircle->draw();
   Shape *redSquare = new Square(100,100, 200, 200, new DrawRed());
   redSquare->draw();
   return 0;
}












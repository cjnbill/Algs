//
// Created by cjn on 2018/4/16.
//

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

class Rectangle {
public:
    int x1, x2, y1, y2; //top left (x1, y1), bottom right (x2, y2)
    Rectangle(int x1,int x2,int y1,int y2):x1(x1),x2(x2),y1(y1),y2(y2){}
    int GetArea(){
        return abs(x1-x2)*abs(y1-y2);
    }
};

class Point_ {
public:
    int x, y;
    Point_(int a, int b) {
        x = a;
        y = b;
    }
};
static Point_* RandomSelectFrom(Rectangle rectangle) {
    srand(std::time(0));
    auto x=rectangle.x1 + rand()%(rectangle.x2 - rectangle.x1 + 1);
    auto y=rectangle.y2 + rand()%(rectangle.y1 - rectangle.y2 + 1);
    return new Point_(x,y);
}

static Point_* RandomSelectFrom(std::vector<Rectangle*> rectangles) {
    int n=rectangles.size();
    std::vector<int> sum(n+1,0);
    for(int i=1;i<=n;i++){
        sum[i]=sum[i-1]+rectangles[i-1]->GetArea();
    }
    srand(time(0));
    int x=rand()%sum.back(),selected=0;
    for(int i=1;i<sum.size();i++){
        if(x<sum[i]) {
            selected = i - 1;
            break;
        }
    }
    return RandomSelectFrom(*rectangles[selected]);
}
#include <iostream>
 
using namespace std;
 
// 基类
class Shape 
{
public:
   Shape()
   {
      cout<<"spape"<<endl;
   }
   // 提供接口框架的纯虚函数
   virtual int getArea() = 0;
   void setWidth(int w)
   {
      width = w;
   }
   void setHeight(int h)
   {
      height = h;
   }
protected:
   int width;
   int height;
};

// 派生类
class Rectangle: public Shape
{
private:
   int factor;
public:
   Rectangle()
   {
      factor = 2;      
   }
   int getArea()
   {

      return (width * height*factor); 
   }
};
class Triangle: public Shape
{
   private :
   int factor;
public:
   Triangle()
   {
      factor = 100;      
   }
   int getArea()
   { 
      return (width * height)/2; 
   }
};


int main(void)
{
   Rectangle Rect;
   Triangle  Tri;
 
   Rect.setWidth(5);
   Rect.setHeight(7);
   // 输出对象的面积
   cout << "Total Rectangle area: " << Rect.getArea() << endl;
 
   Tri.setWidth(5);
   Tri.setHeight(7);
   // 输出对象的面积
   cout << "Total Triangle area: " << Tri.getArea() << endl; 


   Shape *shape = new Rectangle();
   shape->setWidth(5);
   shape->setHeight(7);
   // 输出对象的面积
   cout << "Total Rectangle area: " << shape->getArea() << endl;
 
   return 0;
}
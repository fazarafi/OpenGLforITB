#ifndef Line_H
#define Line_H

#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <math.h>

using namespace std;

class Point
{
public:
	Point() : x(0), y(0){}

	Point(int ax, int ay){
		x = ax;
		y = ay;
	}

	Point(const Point& p){
		(*this).x = p.x;
		(*this).y = p.y;
	}

	Point& operator=(const Point &p){
		x = p.x;
		y = p.y;
		return *this;
	}

	bool operator==(const Point &p){
        if((*this).x == p.x){
            if((*this).y == p.y){
                return true;
            }else{
                return false;
            }
        }else{
            return false;
        }
	}

	bool operator!=(const Point &p){
        if(*this == p){
            return false;
        }else{
            return true;
        }
	}

	int getX(){
		return x;
	}

	int getY(){
		return y;
	}

	void setX(int ax){
		x = ax;
	}

	void setY(int ay){
		y = ay;
	}

	void Move(int dx, int dy){
		(*this).x += dx;
		(*this).y += dy;
	}

	void rotateP(double degrees, const Point& center = Point()){
        double rad = degrees * 3.14/180;
        (*this).x = center.x + ((*this).x-center.x)*cos(rad) - ((*this).y - center.y)*sin(rad);
        (*this).y = center.y + ((*this).x-center.x)*sin(rad) + ((*this).y-center.y)*cos(rad);
	}

	void Scale(float sx, float sy,const Point& center = Point()){
		(*this).x = center.x + floor((float)((*this).x-center.x)*sx);
		(*this).y = center.y + floor((float)((*this).y-center.y)*sy);
	}

	// void ScaleClip(float sx, float sy, int x1, int x2)

	void printPoint(){
		std::cout << x << " " << y << " ";
	}

private:
	int x;
	int y;

};



class Bangunan
{
    public:

        Bangunan(vector<Point> points){
			for(int i = 0; i < points.size(); i++){
				(*this).listPoint.push_back(points[i]);
			}
            (*this).height = 40;
        }

		int getTotalPoint() {
			return (*this).listPoint.size();
		}
		
		Point getPoint(int idx) {
			return (*this).listPoint[idx];
		}
		
		int getX(int idx) {
			return (*this).listPoint[idx].getX();
		}
		
		int getY(int idx) {
			return (*this).listPoint[idx].getY();
		}
		
		int getHeight() {
			return height;
		}

    private:
        vector<Point> listPoint;
		float height;
};



#endif // Line_H

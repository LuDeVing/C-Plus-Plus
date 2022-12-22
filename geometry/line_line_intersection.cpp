#include <iostream>
#include <utility>

struct line{
	double x1, y1, x2, y2;
};

double cross(double x1, double y1, double x2, double y2, double x3, double y3){
	return (((x2 - x1) * (y3 - y1)) - ((x3 - x1) * (y2 - y1)));
}

// returns if there is an intersection and the point of intersection

std::pair<bool, std::pair<double, double> > intersection(line a, line b){
	
	// cross product will positive number if a point is
	// on the left of the line and negative if it is
	// on the right
	
	double n1 = cross(a.x1, a.y1, a.x2, a.y2, b.x1, b.y1);
	double n2 = cross(a.x1, a.y1, a.x2, a.y2, b.x2, b.y2);
	
	if(n2 < n1) std::swap(n1, n2);
	
	bool areOnDifferentSides = (n2 >= 0) && (n1 <= 0);
	
	n1 = cross(b.x1, b.y1, b.x2, b.y2, a.x1, a.y1);
	n2 = cross(b.x1, b.y1, b.x2, b.y2, a.x2, a.y2);
	
	if(n2 < n1) std::swap(n1, n2);
	
	areOnDifferentSides &= (n2 >= 0) && (n1 <= 0);
	
	if(!areOnDifferentSides){
		// if points are on the same side of the line
		// program deduces that lines arent crossing
		return {false, {0, 0}};
	}
	
	// gets the line eqution's constants (y = m * x + k)
			
	double m1 = (a.y2 - a.y1) / (a.x2 - a.x1);
	double k1 = a.y1 - a.x1 * m1;	
	double m2 = (b.y2 - b.y1) / (b.x2 - b.x1);
	double k2 = b.y1 - b.x1 * m2;
	
	// checks if any of the lines are vertical
	
	double intx = (k2 - k1) / (m1 - m2);
	double inty = intx * m1 + k1;
	
	// solves for y1 = y2
	// if its posible to solve
	// the equation it means
	// that lines are intersecting
	
	if(a.x2 - a.x1 == 0 && b.x2 - b.x1 != 0){	
		return {true, {a.x1, (m2 * a.x1) + k2}};
	}
	
	if(b.x2 - b.x1 == 0 && a.x2 - a.x1 != 0){	
		return {true, {b.x1, (m1 * b.x1) + k1}};	
	}
	
	if(a.x2 - a.x1 == 0 && b.x2 - b.x1 != 0){
		return {false, {0, 0}};
	}
	
	return {true, {intx, inty}};
	
}

int main(){
	
	line line1, line2;
	
	std::cin>>line1.x1>>line1.y1>>line1.x2>>line1.y2;
	std::cin>>line2.x1>>line2.y1>>line2.x2>>line2.y2;
	
	std::pair<bool, std::pair<double, double> > inter = intersection(line1, line2);
		
	if(inter.first){
		std::cout<<"Lines intersect!"<<std::endl;
		std::cout<<inter.second.first<<' ';
		std::cout<<inter.second.second<<std::endl;
	}
	else  std::cout<<"Lines don't intersect!"<<std::endl;

	return 0;
	
}

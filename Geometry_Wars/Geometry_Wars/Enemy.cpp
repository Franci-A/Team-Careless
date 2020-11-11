#include "Enemy.h"
#include "ScreenResolution.h"
//
//CircleShape DrawShape(Enemy enemy) {
//	if (enemy.GetShape() == "Circle") {
//		cout << "Circle" << endl;
//		CircleShape shape(50);
//		return shape;
//	}
//	else if (enemy.GetShape() == "Rectangle") {
//		cout << "Rectangle" << endl;
//	}
//	else if (enemy.GetShape() == "Square") {
//		cout << "Square" << endl;
//	}
//	else if (enemy.GetShape() == "Triangle") {
//		cout << "Triangle" << endl;
//	}
//	else if (enemy.GetShape() == "Octagon") {
//		cout << "Octagon" << endl;
//	}
//	else if (enemy.GetShape() == "Convex") {
//		cout << "Convex" << endl;
//	}
//}


CircleShape DrawShape(string enemy, int rng) {
	
	if (enemy == "Circle") {
		CircleShape shape(rng);
		return shape;
	}
	else if (enemy == "Square") {
		CircleShape square(rng, 4);
		return square;
	}
	else if (enemy == "Pentagon") {
		CircleShape pentagon(rng, 5);
	}
	else if (enemy == "Hexagon") {
		CircleShape hexagon(rng, 6);
		return hexagon;
	}
	else if (enemy == "Heptagon") {
		CircleShape octagon(rng, 7);
		return octagon;
	}
	else if (enemy == "Octagon") {
		CircleShape octagon(rng, 8);
		return octagon;
	}
	else if (enemy == "Enneagone") {
		CircleShape octagon(rng, 9);
		return octagon;
	}
	else if (enemy == "Decagone") {
		CircleShape octagon(rng, 10);
		return octagon;
	}
	//else if (enemy == "Rectangle") {
	//	RectangleShape shape(50);
	//	return  shape;
	//}
	//else if (enemy == "Convex") {
	//	cout << "Convex" << endl;
	//}
	//CircleShape shape(100);
	//return shape;
}

void EnemySetPosition(CircleShape &shape, int width, int height) {

	srand(time(NULL));
	int rngWidth = rand() % width + 1;
	int rngHeight = rand() % height + 1;
	int rngWallSpawn = rand() % 4 + 1;

	//UP
	if (rngWallSpawn == 1) {
		shape.setPosition(rngWidth, 0);
	}
	//RIGHT
	else if (rngWallSpawn == 2) {
		shape.setPosition(width, rngHeight);
	}
	//DOWN
	else if (rngWallSpawn == 3) {
		shape.setPosition(rngWidth, height);
	}
	//LEFT
	else if (rngWallSpawn == 4) {
		shape.setPosition(0, rngHeight);

	}

	
}

void EnemySetColor(CircleShape &shape) {

	srand(time(NULL));
	int rngColor = rand() % 7 + 1;

	if (rngColor == 1) {
		shape.setFillColor(Color::White);
	}
	else if (rngColor == 2) {
		shape.setFillColor(Color::Red);
	}
	else if (rngColor == 3) {
		shape.setFillColor(Color::Green);
	}
	else if (rngColor == 4) {
		shape.setFillColor(Color::Blue);
	}
	else if (rngColor == 5) {
		shape.setFillColor(Color::Yellow);
	}
	else if (rngColor == 6) {
		shape.setFillColor(Color::Cyan);
	}
	else if (rngColor == 7) {
		shape.setFillColor(Color::Magenta);
	}
}

CircleShape EnemyCreate(int widht, int height) {

	#pragma region Shape
		vector<string> shapeVect{
			"Circle",
			"Triangle",
			"Square",
			"Pentagon",
			"Hexagon",
			"Heptagon",
			"Octagon",
			"Enneagone",
			"Decagone",
		};
	#pragma endregion
	srand(time(NULL));
	int rngRadius = rand() % 50 + 10;
	int rngShape = rand() % shapeVect.size();
	CircleShape shape = DrawShape(shapeVect.at(rngShape), rngRadius);
	EnemySetPosition(shape, widht - 100, height - 100);
	EnemySetColor(shape);
	return shape;
}
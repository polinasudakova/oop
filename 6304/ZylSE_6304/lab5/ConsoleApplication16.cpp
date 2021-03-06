#include "stdafx.h"
#include "shared_ptr.cpp"
#include "shape.h"
#include "vector.cpp"
#include <ctime>
#define NumberOfShapes 5
#define ValueRange 100

void generateShapes(stepik::vector<stepik::shared_ptr<Shape>>& Shapes)
{
	srand(time(NULL));
	for (stepik::shared_ptr<Shape> &shape : Shapes)
	{
		int object = rand() % 3;
		switch (object)
		{
		
		case 0:
		{
			shape.reset(new Rhomb({ (double)rand() / ValueRange, (double)rand() / ValueRange }, ((double)rand() / ValueRange),((double)rand()/ValueRange)));
			break;
		}

		case 1:
		{
			shape.reset(new Square({ (double)rand() / ValueRange, (double)rand() / ValueRange }, (double)rand() / ValueRange));
			break;
		}
		case 2:
		{
			shape.reset(new Trapezium({ (double)rand() / ValueRange, (double)rand() / ValueRange }, ((double)rand() / ValueRange), ((double)rand() / ValueRange), ((double)rand()/ValueRange)));
			break;
		}
		}
	}
}

stepik::shared_ptr<Shape> findFirstShapeByParametr(stepik::vector<stepik::shared_ptr<Shape>> shapes, bool(*function)(Shape&))
{
	for (stepik::shared_ptr<Shape> &shape : shapes)
	{
		if (function(*shape))
			return shape;
	}
	return stepik::shared_ptr<Shape>(NULL);
}

void SeparateOnTwoRanges(stepik::vector<stepik::shared_ptr<Shape>> &shapes, stepik::vector<stepik::shared_ptr<Shape>> &first, stepik::vector<stepik::shared_ptr<Shape>> &second, bool(*separator)(Shape&))
{
	for (stepik::shared_ptr<Shape> &shape : shapes)
	{
		if (separator(*shape))
			first.push_back(shape);
		else
			second.push_back(shape);
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");

	stepik::vector<stepik::shared_ptr<Shape>> shapes(NumberOfShapes);

	generateShapes(shapes);

	/*for each (stepik::shared_ptr<Shape> shape in shapes)
	{
	std::cout << *shape << std::endl;
	}*/

	stepik::shared_ptr<Shape> object = findFirstShapeByParametr(shapes, [](Shape& shape) {return shape.center.x>50; });//find a shape which centerX is more than 50

	std::cout << "Первый эл по зад критерию" << std::endl;
	std::cout << *object << std::endl;

	stepik::vector<stepik::shared_ptr<Shape>> first;
	stepik::vector<stepik::shared_ptr<Shape>> second;

	SeparateOnTwoRanges(shapes, first, second, [](Shape& shape) {return shape.center.x > 100; });

	std::cout << "первый диапазон:" << std::endl << std::endl;
	for each (stepik::shared_ptr<Shape> shape in first)
	{
		std::cout << *shape << std::endl;
	}

	std::cout << "второй диапазон:" << std::endl << std::endl;
	for each (stepik::shared_ptr<Shape> shape in second)
	{
		std::cout << *shape << std::endl;
	}
	return 0;
}

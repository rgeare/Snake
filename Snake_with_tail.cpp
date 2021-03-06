#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
using namespace std;
class Point {
private:
	int x;
	int y;
public:
	Point (int a, int b) {
		x = a;
		y = b;
	}
	Point () {
		x = 0;
		y = 0;
	}

	void setPoint(int a, int b) {
		x = a;
		y = b;
	}
	int getX() {
		return x;
	}
	int getY() {
		return y;
	}
};

class SnakeGame {
private:
	char area[10][10];
	Point head;
	Point body[64];
	Point tail;
	Point food;
	int score;
	int Length;
	int flag =0;
public:
	SnakeGame() {
		Length = 3;
		score = 0;
		head.setPoint(1, 3);
		body[0].setPoint(1, 2);
		body[1].setPoint(1, 1);
		tail.setPoint(1, 1);

		//娩
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (i == 0 || i == 9 || j == 0 || j == 9)area[i][j] = '#';
				else area[i][j] = ' ';
			}
		}


		area[head.getX()][head.getY()] = 'X';
		//	for(int i=0;i<Length-3;i++)
		area[body[0].getX()][body[0].getY()] = 'O';

		area[tail.getX()][tail.getY()] = 'O';

		for(int i = 0 ;i<5;i++)
			printf("body[%d] = %d,%d\n",i,body[i].getX(), body[i].getY());
	}
	// 76:left 85:up 82:right 68:down
	bool checkSpace(int step) {
		if (step == 76) {
			return !(area[head.getX()][head.getY() - 1] == '#' || area[head.getX()][head.getY() - 1] == 'O');
		} else if (step == 85) {
			return !(area[head.getX() - 1][head.getY()] == '#' || area[head.getX() - 1][head.getY()] == 'O');
		} else if (step == 82) {
			return !(area[head.getX()][head.getY() + 1] == '#' || area[head.getX()][head.getY() + 1] == 'O');
		} else if (step == 68) {
			return !(area[head.getX() + 1][head.getY()] == '#' || area[head.getX() + 1][head.getY()] == 'O');
		}

	}
	void run (int step) {
		tail.setPoint(body[Length - 2].getX(),body[Length - 2].getY());

		int tempX = tail.getX();
		int tempY = tail.getY();

		area[tail.getX()][tail.getY()] = ' ';

		for (int i = Length-1; i > 0; i--)
			body[i].setPoint(body[i - 1].getX(), body[i - 1].getY());
		body[0].setPoint(head.getX(), head.getY());

		if (step == 76) {
			head.setPoint(head.getX(), head.getY() - 1);
		} else if (step == 85) {
			head.setPoint(head.getX() - 1, head.getY());
		} else if (step == 82) {
			head.setPoint(head.getX(), head.getY() + 1);
		} else if (step == 68) {
			head.setPoint(head.getX() + 1, head.getY());
		}


		for (int i = 0; i < Length-2; i++)
			area[body[i].getX()][body[i].getY()] = 'O';

		area[head.getX()][head.getY()] = 'X';
		Eatfood(tempX,tempY);
	}
	void printArea() {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++)cout << area[i][j];
			cout << endl;
		}
	}

	void Foodset()
	{
		int foodX, foodY;
		srand( (unsigned)time(NULL));
		//	do{
		foodX = (rand() % 8) + 1;
		foodY = (rand() % 8) + 1;

		//	}while(foodX==head.getX() || for(int i=0;i<Length-3;i++)foodX==body[i].getX(), || foodX==tail.getX() || foodY==head.getY() || for(int i=0;i<Length-3;i++)foodY==body[i].getY(), || foodY==tail.getY());
		for(int i=0;i<Length-2;i++)
			if((foodX != body[i].getX() && foodY != body[i].getY()) || (foodX != head.getX() && foodY != head.getY()))
				food.setPoint(foodX, foodY);
		area[food.getX()][food.getY()] = '*';
	}

	void Eatfood(int tempX,int tempY)
	{

		if (head.getX() == food.getX() && head.getY() == food.getY())
		{
			score = score + 100;
			Length++;
			body[Length-1].setPoint(tempX, tempY);
			area[body[Length-1].getX()][body[Length-1].getY()] = 'O';
			Foodset();
		}
	}

	void Printscore() {
		cout << score;
	}




};
int  main() {
	SnakeGame sg;
	char step;
	sg.Foodset();
	while (1) {

		sg.printArea();
		cout << "ヘ玡だ计:";
		sg.Printscore();
		cout << endl ;
		cout << "L:left U:up R:right D:down" << endl ;
		cout << "> input step : ";
		cin >> step;


		if (step == 76 || step == 85 || step == 82 || step == 68) {
			if (sg.checkSpace(step)) {
				sg.run(step);
			} else {
				cout << endl << "GameOver" << endl;
				break;
			}
		}

		system("cls");



	}


	return 0 ;
}


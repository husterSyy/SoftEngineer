#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//����
typedef struct ball
{
	double x;       //Բ��x����
	double y;		//Բ��y����
	double r;		//Բ�뾶
}Ball;

//���������Ѿ����õ�����
typedef struct ballList
{
	struct ballList * next;
	Ball ball;
}BallList;

void insert(Ball ball);						//��������
double distance(Ball b1, Ball b2);          //�ж�����֮��ľ���
double abs1(double num);					    //ȡ����ֵ
int judge(Ball b);							//�ж��¼���������Ƿ���Ϲ���
void putBall();								//�ı�����ĳ�ʼλ�ã������������������
void putPoint(double x, double y);			//���õ�

BallList *head = NULL;
double step = 0.01;							//�ı�����λ�õ���С��λ
int num = 0;                                //��������ĸ���
double sumr = 0;							//������¼r^2֮��

int main()
{
	int n, pointNum, i;
	printf("������ռ�����Ҫ���õ���������: ");
	scanf_s("%d", &n);
	printf("������ռ��ڵ������: ");
	scanf_s("%d", &pointNum);
	for (i = 0; i < pointNum; i++)
	{
		printf("�������%d���������(����ÿո����)��", i + 1);
		double x, y;
		scanf_s("%lf %lf", &x, &y);
		putPoint(x, y);
	}
	printf("\n����\t x����\t y����\t �뾶\t r^2֮��\n");
	for (i = 0; i < n; i++)
	{
		putBall();
	}
	printf("\nr^2֮��Ϊ:\t %lf\n", sumr);
	system("pause");
	return 0;
}

void putPoint(double x, double y)
{
	Ball ball = { x, y, 0 };
	insert(ball);
}

void insert(Ball ball)
{
	ballList * newBall = (ballList *)malloc(sizeof(ballList));
	newBall->ball = ball;
	newBall->next = head;
	head = newBall;
}

void putBall()
{
	Ball ball = { -1 + step, -1 + step, 0 };
	Ball maxBall = ball;
	int i, j;
	for (i = 0; ball.x < 1; ++i)
	{
		ball.x += step;
		ball.y = -1 + step;
		for (j = 0; ball.y < 1; ++j)
		{
			ball.y += step;
			ball.r = 0;
			double rstep = 0.1;
			while (rstep > 0.00001)
			{
				if (ball.r > maxBall.r)
				{
					maxBall = ball;
				}
				ball.r += rstep;
				if (!judge(ball))
				{
					ball.r -= rstep;
					rstep /= 10;
				}
			}
		}
	}
	if (judge(maxBall))
	{
		insert(maxBall);
		num++;
		sumr += maxBall.r * maxBall.r;
		printf("%d\t %.3lf\t %.3lf\t %.3lf\t %lf \n", num, maxBall.x, maxBall.y, maxBall.r, sumr);
	}
}

int judge(Ball b)
{
	if ((abs1(b.x) + b.r) > 1 || (abs1(b.y) + b.r) > 1)
	{
		return false;
	}
	ballList *tmp = head;
	while (tmp)
	{
		Ball ball = tmp->ball;
		if (distance(b, ball) < b.r + ball.r)
		{
			return false;
		}
		tmp = tmp->next;
	}
	return true;
}

double abs1(double num)
{
	if (num > 0)
		return num;
	return 0 - num;
}

double distance(Ball b1, Ball b2)
{
	double x1 = b1.x;
	double y1 = b1.y;
	double x2 = b2.x;
	double y2 = b2.y;
	return pow((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2), 0.5);
}
#include <stdio.h>
#include <math.h>

char compareDouble(double a, double b);
int compareDoubleInt(double a, double b);
int trianglePossible(double a, double b, double c);
int calculateShape(double* area, double* circ, char* sh);

int main(void) {
	double ar1, ar2; // area of shape1&2
	double ci1, ci2; // circumference of shape1&2
	char sh1, sh2; // input for shape 1&2
	printf("Obrazec #1\n");
	if (calculateShape(&ar1, &ci1, &sh1) == 1) {
		printf("Nespravny vstup.\n");
		return 1;
	}
	printf("Obrazec #2\n");
	if (calculateShape(&ar2, &ci2, &sh2) == 1) {
		printf("Nespravny vstup.\n");
		return 1;
	}

	if (1) {
		char shape1[16];
		sprintf(shape1, sh1 == 'T' ? "trojuhelnik" : (sh1 == 'R' ? "obdelnik" : "ctverec"));
		char shape2[16];
		sprintf(shape2, sh2 == 'T' ? "trojuhelnik" : (sh2 == 'R' ? "obdelnik" : "ctverec"));
		// double eq
		char eq1 = compareDouble(ci1, ci2);
		char eq2 = compareDouble(ar1, ar2);
		printf("Obvod: %s #1 %c %s #2\n", shape1, eq1, shape2);
		printf("Obsah: %s #1 %c %s #2\n", shape1, eq2, shape2);
	}

}

char compareDouble(double a, double b) {
	double eps = __DBL_EPSILON__ * 1000 * (fabs(a) + fabs(b)) / 2;

	if (fabs(a - b) < eps)
		return '='; // 0

	else if (a > b)
		return '>';

	else
		return '<';
}

int compareDoubleInt(double a, double b) {
	double eps = __DBL_EPSILON__ * 1000 * (fabs(a) + fabs(b)) / 2;
	if (fabs(a - b) < eps)
		return 0;
	else if (a > b)
		return 1;
	else
		return -1;
}

int trianglePossible(double a, double b, double c) {
	if (compareDoubleInt(a + b, c) &&
		 compareDoubleInt(a + c, b) && compareDoubleInt(b + c, a))
		return 1;
	else
		return 0;
}

int calculateShape(double* area, double* circ, char* sh) {
	char shape = 0;
	double a = 0, b = 0, c = 0;
	int scan = scanf(" %c %lf %lf %lf ", &shape, &a, &b, &c);
	if (scan  < 2)
		return 1;
	*sh = shape;
	switch (shape) {
		case 'T':
		{	if (a <= 0 || b <= 0 || c <= 0 || !trianglePossible(a,b,c))
				return 1;
			//heron's formula
			double s = (a + b + c) / 2;
			*area = sqrt(s*(s-a)*(s-b)*(s-c));
			*circ = a + b + c;
			break;
		}
		case 'R':
		{	if (a <= 0 || b <= 0 || a == b)
				return 1;
			*area = a * b;
			*circ = (a + b) * 2;
			break;
		}
		case 'S':
		{	if (a <= 0)
				return 1;
			*area = a * a;
			*circ = 4 * a;
			break;
		}
		default:
			return 1;
	}
	return 0;
}



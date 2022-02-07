#include <stdio.h>
#include <math.h>
#include <string.h>

// NOTE: reval(), strev(), fromDeci() taken from https://www.geeksforgeeks.org/convert-base-decimal-vice-versa/ and modified
/* To return char for a value. For example '2'
	is returned for 2. 'A' is returned for 10. 'B'
	for 11 */
char reVal(int num)
{
    if (num >= 0 && num <= 9)
        return (char)(num + '0');
    else
        return (char)(num - 10 + 'a');
}
 
// Utility function to reverse a string
void strev(char *str)
{
    int len = strlen(str);
    for (int i = 0; i < len/2; i++)
    {
        char temp = str[i];
        str[i] = str[len-i-1];
        str[len-i-1] = temp;
    }
}
 
// Function to convert a given decimal number
// to a base 'base' and
char* fromDeci(char res[], int base, int inputNum)
{
    int index = 0;  // Initialize index of result
 
    // Convert input number is given base by repeatedly
    // dividing it by base and taking remainder
    while (inputNum > 0)
    {
        res[index++] = reVal(inputNum % base);
        inputNum /= base;
    	res[index] = '\0';
    }
 
    // Reverse the result
    strev(res);
 
    return res;
}

int main(void) {
	printf("Pozice a soustava:\n");
	int position = -1, system = 0;
	int scan = 0;
	while ((scan = scanf(" %d %d ", &position, &system)) == 2) {

		if (position < 0 || system < 2 || system > 36) {
			printf("Nespravny vstup.\n");
			return 1;
		}
		
		// which number are we on now in decimal
		long dec = -1;
		// currExp calculates jump to next number
		int currExp = 1;
		long lastIter = 0;
		// cycle ends on first digit of searched number
		for (long i = 0; i <= position; i += currExp) {
			++dec;
			if ((dec / pow(system, currExp)) >= 1)
				++currExp;
			lastIter = i;
		}
		
		char res[100] = {'0'};
		printf("%s\n", fromDeci(res, system, dec));
		for (int i = lastIter; i < position; i++)
			printf(" ");
		printf("^\n");
	}
	
	if (!feof(stdin) || scan == 1)
		printf("Nespravny vstup.\n");
	return 0;
}


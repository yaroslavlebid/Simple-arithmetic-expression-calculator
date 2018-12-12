#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 255 // max size of array

int main(void)
{

	char str[MAX]; // string for expression
	char zn[MAX]; // array for sign of operations
	double dg[MAX]; // array for numbers

	printf("\n\n  *=*=*=*=*arithmetic expression calculator*=*=*=*=*\n\n\n");

	printf("> Enter your expression (operations *,/,+,-)"
		"\nDon't use brackets or space.\n\n");

	gets(str); // use enter a string

	// Checking the expression for the correct input
	for (char *p = str; *p != '\0'; p++) {
		if ((int)*p < '*' || (int)*p == ',' || (int)*p > '9') {
			printf("\n> Input error. Your expression has an invalid symbol.\n"
				"It is allowed to enter only digits, the dot \ '. \', And operations characters *, /, +,- \n Repeat the entry! \n \n");
			rewind(stdin);
			gets(str);
			p = str;
			continue;
		}
		if (*p == '-' || *p == '+' || *p == '*' || *p == '/' || *p == '.') {
			p++;
			if (*p == '-' || *p == '+' || *p == '*' || *p == '/' || *p == '.') {
				printf("\n> Input error. You entered several operations (or dots) in a row. \nRepeat the entry!\n\n");
				rewind(stdin);
				gets(str);
				p = str;
				continue;
			}
			else p--;
		}
	}

	char *p = str; // pointer to string
	char *pzn = zn; // pointer to string with signs
	long double *pdg = dg; // pointer array with numbers

	double answer = 0; // result of expression

	while (*p != '\0') {
		if (*p == '-') { // check or expression starts with a minus
			*pdg = strtod(p, &p, 0); pdg++; // if so, then we write 1 operand with the sign '-'
		}

		// write to the array with numbers 2 operands, as well as a sign between them
		while (pdg != dg + 2 && *p != '\0') {

			if (*p == '-' || *p == '+' || *p == '*' || *p == '/') {
				*pzn = *p; p++; pzn++;
			}

			if (isdigit(*p)) {
				*pdg = strtod(p, &p, 0); pdg++;
			}
		}

		// check the next sign after the 2nd digit
		// if it is multiplication, or division, then write the characters and numbers in the arrays
		// before the operation with a lower seniority (ie + or -) will not be met.
		while (*p == '*' || *p == '/') {
			*pzn = *p; p++; pzn++;
			if (isdigit(*p)) {
				*pdg = strtod(p, &p, 0); pdg++;
			}
		}


		pzn--; pdg--;	

		// Perform operations until 1 operand remains
		while (pdg != dg) {
			switch (*pzn) {
			case '*':
				*(pdg - 1) = (*(pdg - 1)) * (*pdg);
				pdg--; pzn--;
				break;
			case '/':
				*(pdg - 1) = (*(pdg - 1)) / (*pdg);
				pdg--; pzn--;
				break;
			case '+':
				*(pdg - 1) = (*(pdg - 1)) + (*pdg);
				pdg--; pzn--;
				break;
			case '-':
				*(pdg - 1) = (*(pdg - 1)) - (*pdg);
				pdg--; pzn--;
				break;
			}
		}

		answer = answer + (*pdg); // add the value to the answer
		// and return to the beginning of the cycle if there are still characters in the inserted tape
	}

	printf("\n\n> RESULT:  %lf\n\n", answer);
	system("pause");
}
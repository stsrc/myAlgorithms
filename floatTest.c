#include <stdio.h>

int main(void) {
	for (int i = 0; i <= 20; i++) {
		float wrongnumber = 1.0f / (float) i;
		printf("1.0f / (float) %d equals to: %.20f\n", i, wrongnumber);
	}
	return 0;
}

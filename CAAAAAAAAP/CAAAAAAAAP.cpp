#include "pch.h"
#include "tipsware.h"


int main()
{
	for (int i = 1; i < 10; i++) {
		printf(20, 5 + i * 20, "2 * %d = %d", i, 2 * i);
	}
	ShowDisplay();
	return 0;
}

#include <unistd.h>

int main()
{
	write(1, "Hello World!\n", 13);
	_exit(0);
}
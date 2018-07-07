#include <iostream>
#include <Vector2f.h>

int main() 
{

	std::cout << "Hello World!\n";

	Vector2f vec = Vector2f(13.0f, 37.0f);

	std::cout << vec.X() << vec.Y() << "\n";

	system("pause");
	return 0;
}
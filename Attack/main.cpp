#include "Animation.h"

int main()
{
	//.:: Temporary code :::
	int sizeX = GetSystemMetrics(SM_CXSCREEN);
	int sizeY = GetSystemMetrics(SM_CYSCREEN);

	if (sizeX != 1280 && sizeY != 1024)
	{
		sizeX = 1920;
		sizeY = 1080;
	}
	//::::::::::::::::::::::

	RenderWindow app(VideoMode(sizeX, sizeY), "Attack", Style::Fullscreen);
	CircleShape shape(100.f);
	shape.setFillColor(Color::Red);
	shape.setPosition(sizeX /2, sizeY /2);

	while (app.isOpen())
	{
		Event event;
		while (app.pollEvent(event))
		{
			if (event.key.code == Keyboard::Escape)
				app.close();
		}

		app.clear();
		app.draw(shape);
		app.display();
	}

	return 0;
}

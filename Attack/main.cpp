#include "Animation.h"

int main()
{
	using namespace sf;

	RenderWindow app(VideoMode(700, 500), "Attack", Style::Close);
	CircleShape shape(100.f);
	shape.setFillColor(Color::Red);


	while (app.isOpen())
	{
		Event event;
		while (app.pollEvent(event))
		{
			if (event.type == Event::Closed)
				app.close();
		}

		app.clear();
		app.draw(shape);
		app.display();
	}

	return 0;
}
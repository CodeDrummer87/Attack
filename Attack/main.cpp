#include <SFML\Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

int main()
{
	cout << "Test App run" << endl;

	RenderWindow app(VideoMode(200, 200), "Test", Style::Close);
	CircleShape shape(100.f);
	shape.setFillColor(Color::Green);

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
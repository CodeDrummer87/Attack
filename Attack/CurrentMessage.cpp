#include "CurrentMessage.h"

extern View view;

CurrentMessage::CurrentMessage()
{}

CurrentMessage::CurrentMessage(string message_, Font font, unsigned int size, Color color_, string name_)
{
	name = name_;

	message = Text(message_, font, size);
	message.setFillColor(color_);
	x = view.getCenter().x - 200;
	y = view.getCenter().y - 200;
	message.setPosition(x, y);

	isCreated = false;
	endDisplayTime = 0;

	status = ALIVE;
}

CurrentMessage::~CurrentMessage()
{}

void CurrentMessage::update()
{
	x = view.getCenter().x - 200;
	y = view.getCenter().y - 200;

	if (status == DEAD)
		isExist = false;
}

void CurrentMessage::draw(RenderWindow &app)
{
	message.setPosition(x, y);
	app.draw(message);
}

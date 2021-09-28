
View view;

void setViewCoordinates(int sizeX, int sizeY, double x, double y, int index)
{
	if (x < sizeX / 2)
		x = sizeX / 2;

	if (x > mapsWidth[index] * 32 - sizeX / 2 - 32)
		x = mapsWidth[index] * 32 - sizeX / 2 - 32;

	if (y > mapsHeight[index] * 32 - sizeY / 2 - 32)
		y = mapsHeight[index] * 32 - sizeY / 2 - 32;

	if (y < sizeY / 2)
		y = sizeY / 2;

	view.setCenter(float(x), float(y));
}

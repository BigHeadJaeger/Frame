#pragma once
enum RenderType
{
	PARTICLE_BILL_BOARD,
	PARTICLE_METABALL
};

struct Size2D
{
	int width;
	int height;

	Size2D(int _width = 0, int _height = 0)
	{
		width = _width;
		height = _height;
	}
};

struct Size3D
{
	int width;
	int height;
	int depth;

	Size3D(int _width = 0, int _height = 0, int _depth = 0)
	{
		width = _width;
		height = _height;
		depth = _depth;
	}
};
#pragma once
#include "gameNode.h"

struct tagParts
{
	Image* img;
	float x, y;
	int currentFrameX;
	int currentFrameY;
};

struct tagAsriel
{
	Image* img;
	float x, y;
	int currentFrameX;
	int currentFrameY;

	tagParts face;
	tagParts armL;
	tagParts armR;
	tagParts body;
	tagParts foot;
	tagParts neck;
	tagParts necklace;
	tagParts neckSide;
	tagParts upArmL;
	tagParts upArmR;

};

class asriel : public gameNode
{
private:
	tagAsriel _asriel;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void imgSet();
	void asrielSet();
};


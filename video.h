#pragma once
class video
{
public:
	video(int speed,int x,int y,int width,int height)
	:speed(speed),x(x),y(y),width(width),height(height){}
	video();
	~video();
	int speed;
	int x;
	int y;
	int width;
	int height;
};


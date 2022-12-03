#pragma once
class Screen : public Singleton<Screen>
{
public:
	Screen();
	Screen(int , int );
	~Screen();
public:
	static void SetSize(int, int);
public:
	static int width;
	static int height;
private:

};


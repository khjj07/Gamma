#pragma once

/// <summary>
/// ȭ�� ������ �����ϴ� class
/// </summary>
class Screen : public Singleton<Screen>
{
public:
	Screen();
	Screen(int , int );
	~Screen();

public:
	static void SetSize(int, int);

public:
	static int width; //����ȭ���� �ʺ�
	static int height; //����ȭ���� ����

};


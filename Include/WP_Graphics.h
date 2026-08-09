#pragma once
class WP_Graphics
{
private:
	static bool s_glewInit;

public:

	static void InitialiseGLFW();

	static void InitialiseGlew();

	static bool GetIsGlewInit();

	static void Cleanup();
};
#include "Application.h"
#include <iostream>
#include <fstream>
#include <sstream>

void Application::ThrowIfFailed1(HRESULT hr, const std::string& msg) {
	if (FAILED(hr)) {
		throw std::runtime_error(msg);
	}
}

void Application::ThrowIfFailed1(HRESULT hr) {
	ThrowIfFailed1(hr, ":(");
}

HWND Application::GetWindowNativeHandler1() const
{
	return glfwGetWin32Window(window);
}

void Application::keyCallback1(int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	//teclas para mover	
}


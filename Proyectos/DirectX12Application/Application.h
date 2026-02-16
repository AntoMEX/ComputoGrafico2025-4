#pragma once

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
// Para obtener el HWND de la ventana de GLFW
#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3native.h"

#include <iostream>
#include <vector>
#include <windows.h>


// Librerías de DirectX 12
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl/client.h> // Para Microsoft::WRL::ComPtr


#include <map>
#include <string>


//https://github.com/microsoft/DirectX-Headers/tree/main



class Application
{
private:
	void ThrowIfFailed1(HRESULT hr, const std::string& msg);
	void ThrowIfFailed1(HRESULT hr);
	void setupGeometry1();
	void setupShaders1();
	void setupDevice1();
	void setupCommandQueue1();
	void setupSwapChain1();
	void setupDescriptorHeap1();
	void setupRenderTargetView1();
	void setupCommandAllocator1();
	void setupCommandList1();
	void swapBuffers1();

	std::string readFile(const std::string& filename);

	// --- Configuración y Constantes ---
	static const UINT BUFFER_COUNT = 2; // Double buffering
	const int WINDOW_WIDTH = 1024;
	const int WINDOW_HEIGHT = 768;

	// --- Variables Globales de DX12 ---
	Microsoft::WRL::ComPtr<IDXGIFactory4> factory;

	Microsoft::WRL::ComPtr<ID3D12Device> g_device;
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> g_commandQueue;
	Microsoft::WRL::ComPtr<IDXGISwapChain4> g_swapChain;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> g_rtvHeap;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> g_commandAllocator;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> g_commandList;


	Microsoft::WRL::ComPtr<ID3D12Resource> g_renderTargets[BUFFER_COUNT];
	UINT g_frameIndex;
	UINT g_rtvDescriptorSize;



public:
	const int Width{ 1280 };
	const int Height{ 1024 };
	GLFWwindow* window;
	HWND GetWindowNativeHandler1() const;
	void setup1();
	void update1();
	void draw1();
	void clearColorBuffer1(const float& r, const float& g, const float& b, const float& a);
	void keyCallback1(int key, int scancode, int action, int mods);

	void setupDepthBuffer1();
};
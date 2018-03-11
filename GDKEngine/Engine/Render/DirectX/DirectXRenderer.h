#pragma once
#ifndef GDK_DXRENDERER_H
#define GDK_DXRENDERER_H
#include "../IRenderer.h"
#include "DXModel.h"
#pragma comment(lib, "winmm.lib")
#ifdef USE_DX10
#ifdef _DEBUG
#   pragma comment(lib, "d3dx10d.lib")
#else
#   pragma comment(lib, "d3dx10.lib")
#endif
#pragma comment(lib, "d3d10.lib")
#else
#ifdef USE_DX9
#ifdef _DEBUG
#   pragma comment(lib, "d3dx9d.lib")
#else
#   pragma comment(lib, "d3dx9.lib")
#endif
#pragma comment(lib, "d3d9.lib")
#endif
#endif

class DirectXRenderer : public IRenderer 
{
public:
	HWND renderWindow;
	D3DDEVTYPE deviceType = D3DDEVTYPE::D3DDEVTYPE_HAL;
	int g_WindowWidth, g_WindowHeight;

#ifdef USE_DX9
	IDirect3D9* g_pD3D;
	// global declarations
	LPDIRECT3D9 d3d;				 // the pointer to our Direct3D interface
	LPDIRECT3DDEVICE9 d3ddev;		 // the pointer to the device class

#endif // USE_DX9

	
	
	
	
	//====================================================================================================
#ifdef USE_DX10
	ID3D10Device* pD3DDevice = 0;
	ID3D10Texture2D* pBackBuffer;
	IDXGISwapChain* pSwapChain;
	ID3D10RenderTargetView* pRenderTargetView;
#endif // USE_DX10


	const D3DXVECTOR3 dV, dU;               //default view and up vectors
	D3DXVECTOR3 eye, view, up;
	D3DXVECTOR3 forward, strafeRight;

	//matrices
	D3DXMATRIX viewMatrix;
	D3DXMATRIX projectionMatrix;
	D3DXMATRIX rotationMatrix;
	

	//set projection methods
	void setPerspectiveProjection(float FOV, float aspectRatio, float zNear, float zFar) 
	{
		//convert FOV from degrees to radians
		FOV = FOV * (float)DEG_TO_RAD;
		fov = FOV;
		this->aspectRatio = aspectRatio;
		this->Near = zNear;
		this->Far = zFar;
		D3DXMatrixPerspectiveFovLH(&projectionMatrix, fov, this->aspectRatio, this->Near, this->Far);
	}


	//get methods
	D3DXMATRIX& getViewMatrix() { return viewMatrix; }
	D3DXMATRIX& getProjectionMatrix() { return projectionMatrix; }


	void updateView()
	{
		if (!transform)return;
		//create rotation matrix
		//D3DXMatrixRotationYawPitchRoll(&rotationMatrix, heading, pitch, 0);
		auto quat = D3DXQUATERNION(transform->rotation.x, transform->rotation.y, transform->rotation.z, transform->rotation.w);
		D3DXMatrixRotationQuaternion(&rotationMatrix, &quat);

		//create new view and up vectors
		D3DXVec3TransformCoord(&view, &dV, &rotationMatrix);
		D3DXVec3TransformCoord(&up, &dU, &rotationMatrix);

		//create new forward and strafe vectors
		D3DXVec3Normalize(&forward, &view);
		D3DXVec3Cross(&strafeRight, &up, &view);
		D3DXVec3Normalize(&strafeRight, &strafeRight);

		//take into account eye position
		view = eye + view;

		D3DXMatrixPerspectiveFovLH(&projectionMatrix, fov, aspectRatio, Near, Far);
		//update view matrix
		D3DXMatrixLookAtLH(&viewMatrix, &eye, &view, &up);
	}



	//====================================================================================================
	
	
	DirectXRenderer()
	{
		
	}

	bool Init(HINSTANCE hInst, HWND renderWindow, int width, int height, bool bWindowed) 
	{
		this->renderWindow = renderWindow;

#ifdef USE_DX9
		d3d = Direct3DCreate9(D3D_SDK_VERSION);    // create the Direct3D interface

		D3DPRESENT_PARAMETERS d3dpp;    // create a struct to hold various device information

		ZeroMemory(&d3dpp, sizeof(d3dpp));    // clear out the struct for use
		d3dpp.Windowed = TRUE;    // program windowed, not fullscreen
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;    // discard old frames
		d3dpp.hDeviceWindow = renderWindow;    // set the window to be used by Direct3D


									   // create a device class using this information and the info from the d3dpp stuct
		d3d->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			renderWindow,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&d3ddev);
#endif // USE_DX9

#ifdef USE_DX10
		// Create the clear the DXGI_SWAP_CHAIN_DESC structure 
		DXGI_SWAP_CHAIN_DESC swapChainDesc; 
		ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
		
		// Fill in the needed values 
		swapChainDesc.BufferCount = 1; 
		swapChainDesc.BufferDesc.Width = width; 
		swapChainDesc.BufferDesc.Height = height; 
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; 
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 60; 
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1; 
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; 
		swapChainDesc.OutputWindow = renderWindow; 
		swapChainDesc.SampleDesc.Count = 1; 
		swapChainDesc.SampleDesc.Quality = 0; 
		swapChainDesc.Windowed = TRUE;

		// Create the D3D device and the swap chain 
		HRESULT hr = D3D10CreateDeviceAndSwapChain(NULL, D3D10_DRIVER_TYPE_REFERENCE, NULL, 0, D3D10_SDK_VERSION, &swapChainDesc, &pSwapChain, &pD3DDevice);
		
		// Error checking. Make sure the device was created 
		if (hr != S_OK) 
		{ 
			return false; 
		}
		
		// Get the back buffer from the swapchain 
		ID3D10Texture2D *pBackBuffer; 
		hr = pSwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), (LPVOID*) &pBackBuffer); 
		if (hr != S_OK) 
		{ 
			return false;
		}
		// create the render target view 
		hr = pD3DDevice->CreateRenderTargetView(pBackBuffer, NULL, &pRenderTargetView);
	
		// release the back buffer 
		pBackBuffer->Release();
	
		// Make sure the render target view was created successfully 
		if (hr != S_OK) 
		{ 
			return false; 
		}
	
		// set the render target 
		pD3DDevice->OMSetRenderTargets(1, &pRenderTargetView, NULL);
		
		// create and set the viewport 
		D3D10_VIEWPORT viewPort; 
		viewPort.Width = width; 
		viewPort.Height = height; 
		viewPort.MinDepth = 0.0f; 
		viewPort.MaxDepth = 1.0f; 
		viewPort.TopLeftX = 0; 
		viewPort.TopLeftY = 0; 
		pD3DDevice->RSSetViewports(1, &viewPort);
#endif // USE_DX10
		return true;

	}

	bool Setup()
	{
		
		return true;
	}

	int Run()
	{
		MSG msg;
		ZeroMemory(&msg, sizeof(MSG));

		static float previousTime = (float)timeGetTime();
		static const float targetFramerate = 30.0f;
		static const float maxTimeStep = 1.0f / targetFramerate;

		// The message loop will run until the WM_QUIT message is received.
		while (true)
		{
			
				float currentTime = (float)timeGetTime();
				// Calculate the delta time (in seconds)
				float deltaTime = (currentTime - previousTime) / 1000.0f;
				previousTime = currentTime;

				// Cap the delta (useful for debugging)
				deltaTime = min(deltaTime, maxTimeStep);

				// If there are no messages to handle on the message queue,
				// update render our game.
				Update(deltaTime);
		}

		return msg.wParam;
	}

	bool Display(float timeDelta) {
		//if (Device) {
		//	Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		//		0x00000000, 1.0f, 0);
		//	// Swap the back and front buffers. 
		//	Device->Present(0, 0, 0, 0);
		//}
		return     true;
	}

	void Update(float deltaTime)
	{
		// Rate of rotation in units/second
		const float fRotationRateY = D3DX_PI / 4.0f;
		const float fRotationRateZ = D3DX_PI / 2.0f;
		
		updateView();

		// Redraw our window
		if(renderWindow)
			RedrawWindow(renderWindow, NULL, NULL, RDW_INTERNALPAINT);
	}

	void Render() 
	{
#ifdef USE_DX10
		if (pD3DDevice != NULL) { 
			updateView();
			// clear the target buffer 
			pD3DDevice->ClearRenderTargetView(pRenderTargetView, D3DXCOLOR (0.0f, 0.0f, 0.0f, 0.0f));
			
			// All drawing will go here.
			
			// display the next item in the swap chain 
			pSwapChain->Present(0, 0);
		}
#endif // USE_DX10

#ifdef USE_DX9
		// clear the window to a deep blue
		d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(150, 150, 150), 1.0f, 0);
		


		//D3DXMATRIX matProjection;								// the projection transform matrix
		//D3DXMatrixPerspectiveFovLH(&matProjection,
		//	D3DXToRadian(fov),									// the horizontal field of view
		//	(FLOAT)g_WindowWidth / (FLOAT)g_WindowHeight,		// aspect ratio
		//	Near,												// the near view-plane
		//	Far);												// the far view-plane
		//d3ddev->SetTransform(D3DTS_PROJECTION, &matProjection);    // set the projection
		
		d3ddev->BeginScene();    // begins the 3D scene

		// do 3D rendering on the back buffer here
		//Render layers
		for (auto x : currentScene->hierarchy) 
		{
			for (Component* c : x->components)
			{
				if (MeshRenderer* mr = dynamic_cast<MeshRenderer*>(c)) 
				{
					
				}
			}
		}


		d3ddev->EndScene();    // ends the 3D scene

		d3ddev->Present(NULL, NULL, NULL, NULL);    // displays the created frame
#endif // USE_DX9

	}

	void SwapBuffers() 
	{
	
	}
	
	void Release()
	{
#ifdef USE_DX10
		// release the rendertarget
		if (pRenderTargetView) { pRenderTargetView->Release(); }
		// release the swapchain 
		if (pSwapChain) { pSwapChain->Release(); }
		// release the D3D Device 
		if (pD3DDevice) { pD3DDevice->Release(); }
#endif // USE_DX10

#ifdef USE_DX9

#endif // USE_DX9

		
	}
};
#endif // !GDK_DXRENDERER_H


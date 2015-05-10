#ifndef _SLIDER_
#define _SLIDER_

#include <d3d9.h>
#include <D3DX9Shader.h>
#include<string>
#include<fstream>
#include<istream>
#include <cassert>
#include<iostream>
#include<cstdint>

class Slider
{

private:


	IDirect3DDevice9* m_direct3dDevice;

	LPD3DXSPRITE			sprite;
	LPDIRECT3DTEXTURE9		menuBar;
	D3DXVECTOR3				pos;
	

	LPCSTR					m_label;
	RECT					m_labelRect;
	ID3DXFont*				m_labelFont;
	D3DCOLOR				m_fontColor;


	//slider 
	LPD3DXSPRITE sliderSprite;
	LPDIRECT3DTEXTURE9 slider;
	D3DXVECTOR3 sliderpos;
	float xleftLimiter;
	float xrightLimiter;

	float minX;
	float maxX;
	float m_value;

	//slider button
	LPD3DXSPRITE SliderButtonsprite;
	LPDIRECT3DTEXTURE9 sliderButton;
	D3DXVECTOR3 sliderButtonpos;

	//function pointer
    typedef void  (*func)(float);

public:
    bool fieldSelected;
	bool fieldHighlighted;
	void init(IDirect3DDevice9 * i_direct3dDevice,LPCSTR i_text, int x, int y, int minX, int maxX,  func i_callback);
	func callback;
	void draw();
	void update();

};

#endif  //_SLIDER_

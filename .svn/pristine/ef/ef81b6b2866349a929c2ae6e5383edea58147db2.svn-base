#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <d3d9.h>
#include <D3DX9Shader.h>
#include<string>
#include<fstream>
#include<istream>
#include <cassert>
#include<iostream>
#include<cstdint>

class Button
{

private:
	LPD3DXSPRITE sprite;
	LPDIRECT3DTEXTURE9 menuBar;
	D3DXVECTOR3 pos;
	

	LPCSTR m_text;
	RECT rct;
	ID3DXFont *m_font;
	D3DCOLOR fontColor;
	IDirect3DDevice9* m_direct3dDevice;

	//function pointer
    typedef void (*func)(bool);

public:
    bool fieldSelected;
	bool fieldHighlighted;

	func callback;
	void init(IDirect3DDevice9 * i_direct3dDevice,LPCSTR i_text, int x, int y, func i_callback);
	void draw();
	void selected(bool status);
	void update();
};

#endif  //_BUTTON_H_

#ifndef _CHECKBOX_
#define _CHECKBOX_

#include <d3d9.h>
#include <D3DX9Shader.h>
#include<string>
#include<fstream>
#include<istream>
#include <cassert>
#include<iostream>
#include<cstdint>

class Checkbox
{

	private:
	//background sprite
	LPD3DXSPRITE sprite;
	LPDIRECT3DTEXTURE9 menuBar;
	D3DXVECTOR3 pos;


	//Text
	LPCSTR m_text;
	RECT rct;
	ID3DXFont *m_font;
	D3DCOLOR fontColor;
	IDirect3DDevice9* m_direct3dDevice;

	//checkbox sprite
	LPD3DXSPRITE checkBoxSprite;
	LPDIRECT3DTEXTURE9 checkbox;
	D3DXVECTOR3 checkBoxpos;

	//function pointer
    typedef void  (*func)(bool);

public:
	bool fieldSelected;
	bool fieldHighlighted;
	bool checkBoxSelected;

    func callback;

	void update();
	void init(IDirect3DDevice9 * i_direct3dDevice,LPCSTR i_text, int x, int y, func i_callback);
	void draw();
	void selected(bool status);

};


#endif
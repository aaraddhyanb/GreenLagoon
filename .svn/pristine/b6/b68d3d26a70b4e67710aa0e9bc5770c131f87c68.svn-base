#ifndef _TEXTFIELD_
#define _TEXTFIELD_

#include <d3d9.h>
#include <D3DX9Shader.h>
#include<string>
#include<fstream>
#include<istream>
#include <cassert>
#include<iostream>
#include<cstdint>

class TextField
{

private:
	LPD3DXSPRITE			sprite;
	LPDIRECT3DTEXTURE9		menuBar;
	D3DXVECTOR3				pos;
	

	LPCSTR					m_label;
	RECT					m_labelRect;
	ID3DXFont*				m_labelFont;
	D3DCOLOR				m_fontColor;

	LPCSTR					m_value;
	RECT					m_valueRect;
	ID3DXFont*				m_valueFont;

	
	IDirect3DDevice9*		m_direct3dDevice;
	
	//function pointer
    typedef float  (*func)(void);

public:	
    TextField();

    bool fieldSelected;
	bool fieldHighlighted;
	void init(IDirect3DDevice9 * i_direct3dDevice,LPCSTR i_text, int x, int y, func callback);
	func i_callback;
	void draw();
	void update();

};

#endif  //_TEXTFIELD_

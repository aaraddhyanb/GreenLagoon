#ifndef _RENDERER_WIDGETS_
#define _RENDERER_WIDGETS_

#include <vector>
#include "UserInput.h"
#include "TextField.h"
#include "Checkbox.h"
#include "Slider.h"
#include "Button.h"
#include<map>
using namespace std;

class RendererWidgets
{
private:

	std::map<int,TextField>     m_textFieldsList;
	std::map<int,Checkbox>      m_checkboxList;
	std::map<int,Slider>        m_sliderList;
	std::map<int,Button>        m_buttonList;

	IDirect3DDevice9*           m_direct3dDevice;

	//label
	LPCSTR						m_label;
	RECT						m_labelRect;
	ID3DXFont*					m_labelFont;
	D3DCOLOR					m_fontColor;

	//background sprite
	LPD3DXSPRITE				sprite;
	LPDIRECT3DTEXTURE9			menuBar;
	D3DXVECTOR3					pos;

	static RendererWidgets*     rendererWidgets;
	int							id_assigner;
	int                         widget_id;
	bool						highlighted;
	bool						containerOpen;


	//guarding singleton
	RendererWidgets();
	RendererWidgets(const RendererWidgets&);
	RendererWidgets& operator=(const RendererWidgets&);

public:
	
	static RendererWidgets & Singleton()
	{
		if(rendererWidgets==NULL)
		rendererWidgets=new RendererWidgets();
		
		return *rendererWidgets;
	}

	void drawText(std::string label, float left, float top, float right, float bottom );
	void AddTextField(LPCSTR i_text, int x, int y, float (*func)(void));
	void AddCheckBox(LPCSTR i_text, int x, int y, void (*func)(bool));
	void AddSlider(LPCSTR i_text, int x, int y, int minX, int maxX, void (*func)(float));
	void AddButton(LPCSTR i_text, int x, int y,void (*func)(bool));
	void update();
	void draw();
	void init(IDirect3DDevice9 * i_direct3dDevice);
	bool show;
   
};


#endif

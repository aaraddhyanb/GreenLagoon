#include "TextField.h"

TextField::TextField()
{
}

void TextField::init(IDirect3DDevice9 * i_direct3dDevice,LPCSTR i_text, int x, int y,func callback)
{

	//draw label
	m_direct3dDevice=i_direct3dDevice; 
	D3DXCreateFont( m_direct3dDevice, 20, 0, FW_BOLD, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"), &m_labelFont);
	m_fontColor = D3DCOLOR_ARGB(255,0,0,255); 
    fieldSelected=false;
	fieldHighlighted=false;

    // Create a rectangle to indicate where on the screen it should be drawn
	m_labelRect.left=x+30;
	m_labelRect.right=x+150+30;
	m_labelRect.top=y+20;
	m_labelRect.bottom=y+50+20;
 
	m_label=i_text;
		
	//draw value 
	D3DXCreateFont( m_direct3dDevice, 20, 0, FW_BOLD, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"), &m_valueFont);
    // Create a rectangle to indicate where on the screen it should be drawn
	m_valueRect.left=x+100+30;
	m_valueRect.right=x+100+150+30;
	m_valueRect.top=y+20;
	m_valueRect.bottom=y+50+20;
 
	pos.x=x;
	pos.y=y;
	pos.z=0.0f;
	D3DXCreateTextureFromFile(m_direct3dDevice,"data/Textures/menubar.png",&menuBar); 				
	D3DXCreateSprite(m_direct3dDevice, &sprite );
		 
	//assigning callback function
	i_callback=callback;
}


void TextField::update()
{
	if(fieldHighlighted)
	{
			if(  GetAsyncKeyState(VK_RIGHT)&0X8000==0X8000)
				{

			    }
	}
}

void TextField::draw()
{
	    if(fieldHighlighted)
             D3DXCreateTextureFromFile(m_direct3dDevice,"data/Textures/selectedmenubar.png",&menuBar); 		
		else
			 D3DXCreateTextureFromFile(m_direct3dDevice,"data/Textures/menubar.png",&menuBar);

	    sprite->Begin(D3DXSPRITE_ALPHABLEND);
		sprite->Draw(menuBar,NULL,NULL,&pos,0xFFFFFFFF);
		sprite->End();

		// Draw some text 
		m_labelFont->DrawText(NULL, m_label, -1, &m_labelRect, 0, m_fontColor );
		std::string value=std::to_string((long double)i_callback());
		m_value=value.c_str();
		m_valueFont->DrawText(NULL, m_value, -1, &m_valueRect, 0, m_fontColor );
	
}
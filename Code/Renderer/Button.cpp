#include "Button.h"
#include "UserInput.h"

void Button::init(IDirect3DDevice9 * i_direct3dDevice,LPCSTR i_text, int x,  int y,func i_callback)
{
	fieldSelected=false;
    fieldHighlighted=false;

	//draw text
	m_direct3dDevice=i_direct3dDevice; 
	D3DXCreateFont( m_direct3dDevice, 20, 0, FW_BOLD, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"), &m_font );
	fontColor = D3DCOLOR_ARGB(255,0,0,255); 

    // Create a rectangle to indicate where on the screen it should be drawn
	rct.left=x+30;
	rct.right=x+100+30;
	rct.top=y+20;
	rct.bottom=y+100+20;
 
	m_text=i_text;
		
	pos.x=x;
	pos.y=y;
	pos.z=0.0f;
	D3DXCreateTextureFromFile(m_direct3dDevice,"data/Textures/button.png",&menuBar); 				
	D3DXCreateSprite(m_direct3dDevice, &sprite );
		
	callback=i_callback;

}

void Button::update()
{
	if(fieldHighlighted)
	{
	     if( GetAsyncKeyState(VK_RIGHT)&0X8000==0X8000)
		   {
				fieldSelected=true;
				callback(true);
	
			}
		}
}

void Button::draw()
{
	     if(fieldHighlighted)
	         D3DXCreateTextureFromFile(m_direct3dDevice,"data/Textures/buttonHighlighted.png",&menuBar); 		
		else
			 D3DXCreateTextureFromFile(m_direct3dDevice,"data/Textures/button.png",&menuBar);
	   
		 if(fieldSelected)
	        {
				D3DXCreateTextureFromFile(m_direct3dDevice,"data/Textures/pressedButton.png",&menuBar); 
				fieldSelected=false;
		   }

	    sprite->Begin(D3DXSPRITE_ALPHABLEND);
		sprite->Draw(menuBar,NULL,NULL,&pos,0xFFFFFFFF);
		sprite->End();

		// Draw some text 
		m_font->DrawText(NULL, m_text, -1, &rct, 0, fontColor );
	
}
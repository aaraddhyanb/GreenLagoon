#include "Checkbox.h"
#include "UserInput.h"


void Checkbox::init(IDirect3DDevice9 * i_direct3dDevice,LPCSTR i_text, int x, int y, func i_callback)
{

	//draw text
	m_direct3dDevice=i_direct3dDevice; 
	D3DXCreateFont( m_direct3dDevice, 20, 0, FW_BOLD, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"), &m_font );
	fontColor = D3DCOLOR_ARGB(255,0,0,255); 
	fieldSelected=false;
	fieldHighlighted=false;
	checkBoxSelected=false;

       // Create a rectangle to indicate where on the screen it should be drawn
		rct.left=x+30;
		rct.right=x+150+30;
		rct.top=y+20;
		rct.bottom=y+50+20;
 
		m_text=i_text;
		
		pos.x=x;
		pos.y=y;
		pos.z=0.0f;
		D3DXCreateTextureFromFile(m_direct3dDevice,"data/Textures/menubar.png",&menuBar); 				
	    D3DXCreateSprite(m_direct3dDevice, &sprite );

		//checkbox
		checkBoxpos.x=x+175;
		checkBoxpos.y=y;
		checkBoxpos.z=0.0f;
		D3DXCreateTextureFromFile(m_direct3dDevice,"data/Textures/checkboxchecked.png",&checkbox); 				
	    D3DXCreateSprite(m_direct3dDevice, &checkBoxSprite ); 
		
		callback=i_callback;
}

void Checkbox::update()
{
	if(fieldHighlighted)
	{
			if(  GetAsyncKeyState(VK_RIGHT)&0X8000==0X8000)
				{
			
					if(checkBoxSelected)
						{
							checkBoxSelected=false;
							callback(false);
					    }
					else
					{
						   checkBoxSelected=true;
							callback(true);
					}

		    	}
		}
}


void Checkbox::draw()
{
	    if(fieldHighlighted)
	         D3DXCreateTextureFromFile(m_direct3dDevice,"data/Textures/selectedmenubar.png",&menuBar); 		
		else
			 D3DXCreateTextureFromFile(m_direct3dDevice,"data/Textures/menubar.png",&menuBar);

		 if(checkBoxSelected)
	        D3DXCreateTextureFromFile(m_direct3dDevice,"data/Textures/checkboxchecked.png",&checkbox); 		
		else
			 D3DXCreateTextureFromFile(m_direct3dDevice,"data/Textures/checkbox.png",&checkbox);

	  
	    sprite->Begin(D3DXSPRITE_ALPHABLEND);
		sprite->Draw(menuBar,NULL,NULL,&pos,0xFFFFFFFF);
		sprite->End();

		
	
		checkBoxSprite->Begin(D3DXSPRITE_ALPHABLEND);
		checkBoxSprite->Draw(checkbox,NULL,NULL,&checkBoxpos,0xFFFFFFFF);
		checkBoxSprite->End();

		// Draw some text 
		m_font->DrawText(NULL, m_text, -1, &rct, 0, fontColor );
}
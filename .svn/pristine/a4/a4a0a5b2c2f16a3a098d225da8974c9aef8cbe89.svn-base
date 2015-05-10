#include "Slider.h"
#include "UserInput.h"

#define DISTANCE 170


void Slider::init(IDirect3DDevice9 * i_direct3dDevice,LPCSTR i_text, int x,  int y,int i_minX, int i_maxX, func i_callback)
{

	//sprite 
	m_direct3dDevice=i_direct3dDevice; 

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

	pos.x=x;
	pos.y=y;
	pos.z=0.0f;
	D3DXCreateTextureFromFile(m_direct3dDevice,"data/Textures/menubar.png",&menuBar); 				
	D3DXCreateSprite(m_direct3dDevice, &sprite );

		
	sliderpos.x=x+200;
	sliderpos.y=y;
	sliderpos.z=0.0f;
	D3DXCreateTextureFromFile(m_direct3dDevice,"data/Textures/slider.png",&slider); 				
	D3DXCreateSprite(m_direct3dDevice, &sliderSprite );
		 
	//sprite button
	sliderButtonpos.x=x+170+60;
	sliderButtonpos.y=y+15;
	sliderButtonpos.z=0.0f;
	D3DXCreateTextureFromFile(m_direct3dDevice,"data/Textures/sliderButton.png",&sliderButton); 				
	D3DXCreateSprite(m_direct3dDevice, &SliderButtonsprite );
	xleftLimiter=sliderButtonpos.x;
	xrightLimiter=sliderButtonpos.x+DISTANCE;
	minX=i_minX;
	maxX=i_maxX;
	m_value=0.0f;

	//assigning callback function
	callback=i_callback;
		
}

void Slider::update()
{
	if(fieldHighlighted)
	 {
		if(  GetAsyncKeyState(VK_LEFT)&0X8000==0X8000)
			{
				if(m_value>minX)
				  { 
					  if(sliderButtonpos.x> xleftLimiter)
					  {
						  sliderButtonpos.x-=DISTANCE/maxX;
						  m_value-=1.0f;
						  callback(m_value);
					  }
				  }
			 }

		 if( GetAsyncKeyState(VK_RIGHT)&0X8000==0X8000)
			{
				if(m_value<maxX)
				  { 
					   if(sliderButtonpos.x< xrightLimiter)
					  {
						  sliderButtonpos.x+=DISTANCE/maxX;
						   m_value+=1.0f;
						  callback(m_value);
					  }
				  }

			}
	 }
}


void Slider::draw()
{
	 //slider
	sliderSprite->Begin(D3DXSPRITE_ALPHABLEND);
	sliderSprite->Draw(slider,NULL,NULL,&sliderpos,0xFFFFFFFF);
	sliderSprite->End();

	 if(fieldHighlighted)
             D3DXCreateTextureFromFile(m_direct3dDevice,"data/Textures/selectedmenubar.png",&menuBar); 		
		else
			 D3DXCreateTextureFromFile(m_direct3dDevice,"data/Textures/menubar.png",&menuBar);

	    sprite->Begin(D3DXSPRITE_ALPHABLEND);
		sprite->Draw(menuBar,NULL,NULL,&pos,0xFFFFFFFF);
		sprite->End();

		// Draw some text 
		m_labelFont->DrawText(NULL, m_label, -1, &m_labelRect, 0, m_fontColor );

	 //slider button
	SliderButtonsprite->Begin(D3DXSPRITE_ALPHABLEND);
	SliderButtonsprite->Draw(sliderButton,NULL,NULL,&sliderButtonpos,0xFFFFFFFF);
	SliderButtonsprite->End();


}
#include"RendererWidgets.h"
#include <stddef.h>

RendererWidgets* RendererWidgets::rendererWidgets=NULL;

RendererWidgets::RendererWidgets()
{
	containerOpen=false;
	highlighted=false;
	show=false;
	id_assigner=0;
}

void RendererWidgets::init(IDirect3DDevice9 * i_direct3dDevice)
{
	
	m_direct3dDevice=i_direct3dDevice;

	//draw label
	m_direct3dDevice=i_direct3dDevice; 
	D3DXCreateFont( m_direct3dDevice, 20, 0, FW_BOLD, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"), &m_labelFont);
	m_fontColor = D3DCOLOR_ARGB(255,0,0,255); 
    show=false;
	widget_id=0;
    // Create a rectangle to indicate where on the screen it should be drawn
	m_labelRect.left=40;
	m_labelRect.right=40+150+30;
	m_labelRect.top=40;
	m_labelRect.bottom=40+50+20;
 
	m_label="Renderer";

	pos.x=20;
	pos.y=20;
	pos.z=0.0f;
	D3DXCreateTextureFromFile(m_direct3dDevice,"data/Textures/menubar.png",&menuBar); 				
	D3DXCreateSprite(m_direct3dDevice, &sprite );
}


void RendererWidgets::AddTextField(LPCSTR i_text, int x, int y, float (*func)(void))
{
	
	TextField *text;
	text=new TextField();
    text->init(m_direct3dDevice,i_text, x, y, func);
	m_textFieldsList.insert(std::make_pair(id_assigner++,*text));
}


void RendererWidgets::AddCheckBox(LPCSTR i_text, int x, int y,void (*func)(bool))
{

	Checkbox *checkbox;
	checkbox=new Checkbox();
    checkbox->init(m_direct3dDevice,i_text, x, y, func);
	m_checkboxList.insert(std::make_pair(id_assigner++,*checkbox));
}


void RendererWidgets::AddButton(LPCSTR i_text, int x, int y, void (*func)(bool))
{

	Button *button;
	button=new Button();
    button->init(m_direct3dDevice,i_text, x, y,func);
	m_buttonList.insert(std::make_pair(id_assigner++,*button));
}


void RendererWidgets::AddSlider(LPCSTR i_text,int x, int y, int minX, int maxX, void (*func)(float))
{

	Slider *slider;
	slider=new Slider();
    slider->init(m_direct3dDevice,i_text, x, y, minX, maxX, func);
	m_sliderList.insert(std::make_pair(id_assigner++,*slider));
}


void RendererWidgets::update()
{
	if(highlighted==true && show==true)
	{
	   if(  cs6963::UserInput::IsKeyPressed(VK_BACK))
		{
			   containerOpen=false;

		}

	   if(!containerOpen)
	   {
		   if( cs6963::UserInput::IsKeyPressed(VK_RIGHT))
			{

					containerOpen=true;
			}
	   }
	}
		
		if( GetAsyncKeyState(VK_UP)&0X8000==0X8000)
		{
			if(containerOpen==false && show==true)
			{
				if(highlighted)
				  highlighted=false;
				else 
					highlighted=true;
			}

			if(containerOpen==true && show==true && highlighted==true)
			{
				 if (m_textFieldsList.find(widget_id)!=m_textFieldsList.end())
					{
						std::map<int, TextField>::iterator it;
						it=m_textFieldsList.find(widget_id);
						(*it).second.fieldHighlighted=false;

					}
				    if (m_checkboxList.find(widget_id)!=m_checkboxList.end())
					{
						std::map<int, Checkbox>::iterator it;
						it=m_checkboxList.find(widget_id);
						(*it).second.fieldHighlighted=false;
					}
					 if (m_sliderList.find(widget_id)!=m_sliderList.end())
					{
						std::map<int, Slider>::iterator it;
						it=m_sliderList.find(widget_id);
						(*it).second.fieldHighlighted=false;
					}
					  if (m_buttonList.find(widget_id)!=m_buttonList.end())
					{
						std::map<int, Button>::iterator it;
						it=m_buttonList.find(widget_id);
						(*it).second.fieldHighlighted=false;
					}

			
				if(widget_id>0)
				   widget_id--;

				   if (m_textFieldsList.find(widget_id)!=m_textFieldsList.end())
					{
						std::map<int, TextField>::iterator it;
						it=m_textFieldsList.find(widget_id);
						(*it).second.fieldHighlighted=true;
					}
				    if (m_checkboxList.find(widget_id)!=m_checkboxList.end())
					{
						std::map<int, Checkbox>::iterator it;
						it=m_checkboxList.find(widget_id);
						(*it).second.fieldHighlighted=true;
					}
					 if (m_sliderList.find(widget_id)!=m_sliderList.end())
					{
						std::map<int, Slider>::iterator it;
						it=m_sliderList.find(widget_id);
						(*it).second.fieldHighlighted=true;
					}
					  if (m_buttonList.find(widget_id)!=m_buttonList.end())
					{
						std::map<int, Button>::iterator it;
						it=m_buttonList.find(widget_id);
						(*it).second.fieldHighlighted=true;
					}
			}

		
		}
		if( GetAsyncKeyState(VK_DOWN)&0X8000==0X8000)
		{
		   if(!containerOpen)
			{
				if(highlighted)
				  highlighted=false;
				else 
					highlighted=true;
			}

		   if(containerOpen==true && show==true && highlighted==true)
			{
				if (m_textFieldsList.find(widget_id)!=m_textFieldsList.end())
					{
						std::map<int, TextField>::iterator it;
						it=m_textFieldsList.find(widget_id);
						(*it).second.fieldHighlighted=false;

					}
				    if (m_checkboxList.find(widget_id)!=m_checkboxList.end())
					{
						std::map<int, Checkbox>::iterator it;
						it=m_checkboxList.find(widget_id);
						(*it).second.fieldHighlighted=false;
					}
					 if (m_sliderList.find(widget_id)!=m_sliderList.end())
					{
						std::map<int, Slider>::iterator it;
						it=m_sliderList.find(widget_id);
						(*it).second.fieldHighlighted=false;
					}
					  if (m_buttonList.find(widget_id)!=m_buttonList.end())
					{
						std::map<int, Button>::iterator it;
						it=m_buttonList.find(widget_id);
						(*it).second.fieldHighlighted=false;
					}

				  	if(widget_id<id_assigner-1)
				        widget_id++;

				  if (m_textFieldsList.find(widget_id)!=m_textFieldsList.end())
					{
						std::map<int, TextField>::iterator it;
						it=m_textFieldsList.find(widget_id);
						(*it).second.fieldHighlighted=true;
					}
				    if (m_checkboxList.find(widget_id)!=m_checkboxList.end())
					{
						std::map<int, Checkbox>::iterator it;
						it=m_checkboxList.find(widget_id);
						(*it).second.fieldHighlighted=true;
					}
					 if (m_sliderList.find(widget_id)!=m_sliderList.end())
					{
						std::map<int, Slider>::iterator it;
						it=m_sliderList.find(widget_id);
						(*it).second.fieldHighlighted=true;
					}
					  if (m_buttonList.find(widget_id)!=m_buttonList.end())
					{
						std::map<int, Button>::iterator it;
						it=m_buttonList.find(widget_id);
						(*it).second.fieldHighlighted=true;
					}
				
			}
		}
		if( GetAsyncKeyState(VK_TAB)&0X8000==0X8000)
		{
			if(show)
		      show=false;
			else 
				show=true;
		}

	if(containerOpen==true && show==true)
	{
		for(std::map<int,TextField>::iterator it=m_textFieldsList.begin();it!=m_textFieldsList.end(); ++it)
			(*it).second.update();

		for(std::map<int,Checkbox>::iterator it=m_checkboxList.begin();it!=m_checkboxList.end(); ++it)
			(*it).second.update();

		for(std::map<int,Slider>::iterator it=m_sliderList.begin();it!=m_sliderList.end(); ++it)
			(*it).second.update();

		for(std::map<int,Button>::iterator it=m_buttonList.begin();it!=m_buttonList.end(); ++it)
			(*it).second.update();	
	}
}

void RendererWidgets::drawText(std::string label, float left, float top, float right, float bottom )
{
	D3DCOLOR color=(255,0,0);
	RECT labelRect;
	labelRect.left=(long)left;
	labelRect.top=(long)top;
	labelRect.right=(long)right;
	labelRect.bottom=(long)bottom;
	m_labelFont->DrawText(NULL, (LPCSTR)label.c_str(), -1, &labelRect, 0, color );
}

void RendererWidgets::draw()
{
	if(show)
	{
		if(highlighted)
             D3DXCreateTextureFromFile(m_direct3dDevice,"data/Textures/selectedmenubar.png",&menuBar); 		
		else
			 D3DXCreateTextureFromFile(m_direct3dDevice,"data/Textures/menubar.png",&menuBar);

	    sprite->Begin(D3DXSPRITE_ALPHABLEND);
		sprite->Draw(menuBar,NULL,NULL,&pos,0xFFFFFFFF);
		sprite->End();

		m_labelFont->DrawText(NULL, m_label, -1, &m_labelRect, 0, m_fontColor );
	}

	if(containerOpen==true && show==true)
	{
		/*for(int i=0;i<id_assigner;i++)
		{
		           if (m_textFieldsList.find(i)!=m_textFieldsList.end())
					{
						std::map<int, TextField>::iterator it;
						it=m_textFieldsList.find(i);
						(*it).second.draw();

					}
				    if (m_checkboxList.find(i)!=m_checkboxList.end())
					{
						std::map<int, Checkbox>::iterator it;
						it=m_checkboxList.find(i);
						(*it).second.draw();
					}
					 if (m_sliderList.find(i)!=m_sliderList.end())
					{
						std::map<int, Slider>::iterator it;
						it=m_sliderList.find(i);
						(*it).second.draw();
					}
					  if (m_buttonList.find(i)!=m_buttonList.end())
					{
						std::map<int, Button>::iterator it;
						it=m_buttonList.find(i);
						(*it).second.draw();
					}

		}*/
		for(std::map<int,TextField>::iterator it=m_textFieldsList.begin();it!=m_textFieldsList.end(); ++it)
			(*it).second.draw();

		for(std::map<int,Checkbox>::iterator it=m_checkboxList.begin();it!=m_checkboxList.end(); ++it)
			(*it).second.draw();

		for(std::map<int,Slider>::iterator it=m_sliderList.begin();it!=m_sliderList.end(); ++it)
			(*it).second.draw();

		for(std::map<int,Button>::iterator it=m_buttonList.begin();it!=m_buttonList.end(); ++it)
			(*it).second.draw();	
			
	}
}
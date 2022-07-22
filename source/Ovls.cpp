#include "Ovls.hpp"

Warnings::Warnings(std::string head, std::string sub)
{
    this->_head = head;
    this->_sub = sub;
}

void Warnings::Draw(void) const
{
	RenderD7::OnScreen(Top);
	RenderD7::DrawRect(0, msgposy, 400, 70, RenderD7::Color::Hex("#111111"));
	RenderD7::DrawRect(0, msgposy, 400, 25, RenderD7::Color::Hex("#222222"));
	RenderD7::DrawText(2, msgposy+3, 0.7f, RenderD7::Color::Hex("#ffffff"), _head);
	RenderD7::DrawText(2, msgposy+30, 0.6f, RenderD7::Color::Hex("#ffffff"), _sub);
}

void Warnings::Logic()
{
	this->delay++/*=(int)RenderD7::GetDeltaTime()*/;
	if (msgposy > 170 && delay < 2*60) msgposy--/*=(int)RenderD7::GetDeltaTime()*/;
	
	if (delay >= 5*60)
	{
		msgposy++/*=(int)RenderD7::GetDeltaTime*/;
		if(msgposy > 400) this->Kill();
	}
}
#include "renderd7.hpp"

int main()
{
    RenderD7::Init::Main();
    
    while(RenderD7::MainLoop())
    {
        if (d7_hDown & KEY_START) RenderD7::ExitApp();
        RenderD7::OnScreen(Bottom);
        
        RenderD7::OnScreen(Top);
        RenderD7::DrawText(0, 0, 0.7f, C2D_Color32(255, 255, 255, 255), RenderD7::GetFramerate());
        for (int i = 0; i < 255; i++)
        {
             RenderD7::DrawRect(i, 55, i, 20, C2D_Color32((u8)i, 0, 0, 255));
             RenderD7::DrawRect(i, 85, i, 20, C2D_Color32(0, (u8)i, 0, 255));
             RenderD7::DrawRect(i, 115, i, 20, C2D_Color32(0, 0, (u8)i, 255));
        }
        C3D_FrameEnd(0);
    }
    RenderD7::Exit::Main();
}

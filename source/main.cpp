#include "renderd7.hpp"
#include "nightlyreader.hpp"

int main()
{
    RenderD7::Init::Main();
  
    while(RenderD7::MainLoop())
    {
        if (d7_hDown & KEY_START) RenderD7::ExitApp();
        RenderD7::Scene::DoDraw();
        RenderD7::Scene::DoLogic(d7_hDown, d7_hHeld, d7_hUp, d7_touch);
        C3D_FrameEnd(0);
    }
    RenderD7::Exit::Main();
}

#include "renderd7.hpp"
#include "nightlyreader.hpp"
#include "scenes.hpp"

int main()
{
    RenderD7::Init::Main("Dev-Helper");
   // consoleInit(GFX_BOTTOM, NULL);
    RenderD7::Scene::Load(std::make_unique<DBSel>());
    while(RenderD7::MainLoop())
    {
        if (d7_hDown & KEY_START) RenderD7::ExitApp();
  
        C3D_FrameEnd(0);
    }
    RenderD7::Exit::Main();
}

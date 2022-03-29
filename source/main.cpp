#include "renderd7.hpp"
#include "nightlyreader.hpp"
#include "scenes.hpp"
#include "log.hpp"

Log log;

int main()
{
    log.Init("DevHelper.log");
    RenderD7::Init::Main("Dev-Helper");
    log.Write("Loaded RenderD7");
    RenderD7::Scene::Load(std::make_unique<DBSel>());
    log.Write("Loading Scene");
    while(RenderD7::MainLoop())
    {
        if (d7_hDown & KEY_START) RenderD7::ExitApp();
  
        C3D_FrameEnd(0);
    }
    log.Write("Call RD7::Exit::Main");
    RenderD7::Exit::Main();
}

#include "renderd7.hpp"
#include "nightlyreader.hpp"
#include "scenes.hpp"
#include "log.hpp"

Log flog;

int main()
{
    if (osGetWifiStrength() == 0)
    {
        RenderD7::Error::DisplayFatalError("DevHelper->Error", "You are not Connected To Wifi or your connection is bad.")
    }
     
    flog.Init("sdmc:/DevHelper.log");
    RenderD7::Init::Main("Dev-Helper");
    flog.Write("Loaded RenderD7");
    RenderD7::Scene::Load(std::make_unique<DBSel>());
    flog.Write("Loading Scene");
    while(RenderD7::MainLoop())
    {
        if (d7_hDown & KEY_START) RenderD7::ExitApp();
  
        C3D_FrameEnd(0);
    }
    flog.Write("Call RD7::Exit::Main");
    RenderD7::Exit::Main();
}

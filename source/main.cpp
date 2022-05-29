#include "renderd7.hpp"
#include "nightlyreader.hpp"
#include "scenes.hpp"
#include "log.hpp"
#include "Ovls.hpp"

Log flog;

bool __l = false;

int timer = 10000;

bool CheckWifiStatus(void) {
	u32 wifiStatus;
	bool res = false;

	if (R_SUCCEEDED(ACU_GetWifiStatus(&wifiStatus)) && wifiStatus) res = true;

	return res;
}

int main()
{     
    flog.Init("DevHelper");
    RenderD7::Init::Main("Dev-Helper");
    flog.Write("Loaded RenderD7");
    /*consoleInit(GFX_BOTTOM, NULL);*/
    if (CheckWifiStatus())
    {
        RenderD7::Scene::Load(std::make_unique<DBSel>());
        __l = true;
    }
    flog.Write("Loading Scene");
    while(RenderD7::MainLoop())
    {
        if (!CheckWifiStatus())
        {
            timer++;
            if (timer >= 10000){
                timer = 0;
                RenderD7::AddOvl(std::make_unique<Warnings>("Warning", "No Wifi Connection"));
            }
        }
        if (!__l && CheckWifiStatus())
        {
            timer = 10000;
            RenderD7::Scene::Load(std::make_unique<DBSel>());
            __l = true;
        }
        if (d7_hDown & KEY_START) RenderD7::ExitApp();
  
        RenderD7::FrameEnd();
    }
    flog.Write("Call RD7::Exit::Main");
    RenderD7::Exit::Main();
}

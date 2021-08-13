#include "renderd7.hpp"
#include "nightlyreader.hpp"

std::string standard = "https://github.com/NPI-D7/nightlys/raw/master/nightlys-Database.ini";
DBLoader dbl;
int main()
{
    RenderD7::Init::Main();
    dbl.LoadDB(standard);
    dbl.DownloadEntry(4);

    while(RenderD7::MainLoop())
    {
        if (d7_hDown & KEY_START) RenderD7::ExitApp();
        RenderD7::OnScreen(Bottom);
        
        RenderD7::OnScreen(Top);
        RenderD7::DrawText(0, 0, 0.7f, C2D_Color32(255, 255, 255, 255), RenderD7::GetFramerate() + dbl.GetRepoName());
        
        C3D_FrameEnd(0);
    }
    RenderD7::Exit::Main();
}

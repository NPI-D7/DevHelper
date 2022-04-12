#include "scenes.hpp"
#include "log.hpp"
#include <curl/curl.h>

std::string standard = "https://github.com/NPI-D7/nightlys/raw/master/nightlys-Database.ini";

extern curl_off_t downloadTotal;
extern curl_off_t downloadNow;
extern Log flog;

void DrawFMBG()
{
    RenderD7::DrawRect(0, 49, 400, 18, RenderD7::Color::Hex("#CCCCCC"));
    RenderD7::DrawRect(0, 85, 400, 18, RenderD7::Color::Hex("#CCCCCC"));
    RenderD7::DrawRect(0, 121, 400, 18, RenderD7::Color::Hex("#CCCCCC"));
    RenderD7::DrawRect(0, 157, 400, 18, RenderD7::Color::Hex("#CCCCCC"));
    RenderD7::DrawRect(0, 193, 400, 18, RenderD7::Color::Hex("#CCCCCC"));
}

DBSel::DBSel()
{
    flog.Write("Loaded SetState");
    state = DB;
    flog.Write("Loading DB");
    RenderD7::Msg::Display("Dev_Helper->LoadingDB", "Loading Database ...", Top);
    dbld.LoadDB(standard);
}
void DBSel::Draw(void) const
{
     if (state == DB){
         flog.Write("Draw DB STate");
         RenderD7::OnScreen(Top);
         D_P();
         RenderD7::DrawRect(0, 0, 400, 240, RenderD7::Color::Hex("#EEEEEE"));
         D_P();
         DrawFMBG();
         D_P();
         RenderD7::DrawTLBtns(lst, RenderD7::Color::Hex("#CCCCCC"), dirsel <= 6 ? dirsel : 6);
         for (int Idx = 0; Idx < 7 && Idx < (int)dbld.db.e_list.size(); Idx++) {
     
	     	RenderD7::DrawTextCentered(0, this->lst[Idx].y + 7, 0.5f, RenderD7::Color::Hex("#EEEEEE"), dbld.db.e_list[SPos + Idx].name, 400);
         };
         RenderD7::OnScreen(Bottom);
         D_P();
         RenderD7::DrawRect(0, 0, 320, 240, RenderD7::Color::Hex("#EEEEEE"));
         D_P();
     }
     if (state == APPV){
         flog.Write("Draw Appv STate");
         RenderD7::OnScreen(Top);
         D_P();
         RenderD7::DrawRect(0, 0, 400, 240, RenderD7::Color::Hex("#EEEEEE"));
         D_P();
         DrawFMBG();
         D_P();
         RenderD7::DrawTLBtns(lst, RenderD7::Color::Hex("#CCCCCC"), SPos);
         for (int Idx = 0; Idx < 7 && Idx < (int)dbld.versions.size(); Idx++) {
     
	     	RenderD7::DrawTextCentered(0, this->lst[Idx].y + 7, 0.5f, RenderD7::Color::Hex("#EEEEEE"), dbld.versions[SPos + Idx].ver, 400);
         };
         RenderD7::OnScreen(Bottom);
         D_P();
         RenderD7::DrawRect(0, 0, 320, 240, RenderD7::Color::Hex("#EEEEEE"));
         D_P();
     }
}

void DBSel::Logic(u32 hDown, u32 hHeld, u32 hUp, touchPosition touch)
{
     if (state == DB) {
         if (hDown & KEY_A) {
            RenderD7::Msg::DisplayWithProgress("DevHelper->Download-APPV", "Downloading App Data ...", (float)downloadNow, (float)downloadTotal, RenderD7::Color::Hex("#00ff00"));
            dbld.DownloadEntry(dirsel);
            dbld.LoadEntry(dirsel); state = APPV; dirsel = 0;
        }
         if (hDown & KEY_UP && dirsel > 0) dirsel--;
         if (hDown & KEY_DOWN && dirsel < (int)dbld.db.e_list.size() - 1) dirsel++;
         if (hDown & KEY_LEFT && dirsel - 6 > 0) dirsel -= 6;
         if (hDown & KEY_RIGHT && dirsel + 6 < (int)dbld.db.e_list.size() - 1) dirsel += 6;
         if (dirsel < this->SPos) this->SPos = dirsel;
         else if (dirsel > this->SPos + 7 - 1) this->SPos = dirsel - 7 + 1;
     }
     if (state == APPV) {
         if (hDown & KEY_A) {
             RenderD7::Msg::DisplayWithProgress("DevHelper->Download-3dsx", "Downloading 3dsx ...", (float)downloadNow, (float)downloadTotal, RenderD7::Color::Hex("#00ff00"));
             dbld.Download3dsx(dirsel);
     }
         if (hDown & KEY_B) {dirsel = 0; state = DB;}
         if (hDown & KEY_UP && dirsel > 0) dirsel--;
         if (hDown & KEY_DOWN && dirsel < (int)dbld.versions.size() - 1) dirsel++;
         if (hDown & KEY_LEFT && dirsel - 6 > 0) dirsel -= 6;
         if (hDown & KEY_RIGHT && dirsel + 6 < (int)dbld.versions.size() - 1) dirsel += 6;
         if (dirsel < this->SPos) this->SPos = dirsel;
         else if (dirsel > this->SPos + 7 - 1) this->SPos = dirsel - 7 + 1;
     }
}

#include "scenes.hpp"

std::string standard = "https://github.com/NPI-D7/nightlys/raw/master/nightlys-Database.ini";

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
    state = DB;
    dbld.LoadDB(standard);
    D_P();
}
void DBSel::Draw(void) const
{
     if (state == DB){
         RenderD7::OnScreen(Top);
         D_P();
         RenderD7::DrawRect(0, 0, 400, 240, RenderD7::Color::Hex("#EEEEEE"));
         D_P();
         DrawFMBG();
         D_P();
         RenderD7::DrawTLBtns(lst, RenderD7::Color::Hex("#CCCCCC"), dirsel <= 6 ? dirsel : 6);
         for (int Idx = 0; Idx < 6 && Idx < (int)dbld.db.e_list.size(); Idx++) {
     
	     	RenderD7::DrawTextCentered(0, this->lst[Idx].y + 7, 0.5f, RenderD7::Color::Hex("#111111"), dbld.db.e_list[SPos + Idx].name, 400);
         };
         RenderD7::OnScreen(Bottom);
         D_P();
         RenderD7::DrawRect(0, 0, 320, 240, RenderD7::Color::Hex("#EEEEEE"));
         D_P();
     }
     if (state == APPV){
         RenderD7::OnScreen(Top);
         D_P();
         RenderD7::DrawRect(0, 0, 400, 240, RenderD7::Color::Hex("#EEEEEE"));
         D_P();
         DrawFMBG();
         D_P();
         RenderD7::DrawTLBtns(lst, RenderD7::Color::Hex("#CCCCCC"), dirsel <= 6 ? dirsel : 6);
         for (int Idx = 0; Idx < 6 && Idx < (int)dbld.versions.size(); Idx++) {
     
	     	RenderD7::DrawTextCentered(0, this->lst[Idx].y + 7, 0.5f, RenderD7::Color::Hex("#111111"), dbld.versions[SPos + Idx].ver, 400);
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
         if (hDown & KEY_A) {dbld.DownloadEntry(dirsel); state = APPV;}
         if (hDown & KEY_UP && dirsel > 0) dirsel--;
         if (hDown & KEY_DOWN && dirsel < (int)dbld.db.e_list.size() - 1) dirsel++;
         if (hDown & KEY_LEFT && dirsel - 6 > 0) dirsel -= 6;
         if (hDown & KEY_RIGHT && dirsel + 6 < (int)dbld.db.e_list.size() - 1) dirsel += 6;
         if (dirsel < this->SPos) this->SPos = dirsel;
         else if (dirsel > this->SPos + 6 - 1) this->SPos = dirsel - 6 + 1;
     }
     if (state == APPV) {
        // if (hDown & KEY_A) dbld.DownloadEntry(dirsel);
         if (hDown & KEY_UP && dirsel > 0) dirsel--;
         if (hDown & KEY_DOWN && dirsel < (int)dbld.versions.size() - 1) dirsel++;
         if (hDown & KEY_LEFT && dirsel - 6 > 0) dirsel -= 6;
         if (hDown & KEY_RIGHT && dirsel + 6 < (int)dbld.versions.size() - 1) dirsel += 6;
         if (dirsel < this->SPos) this->SPos = dirsel;
         else if (dirsel > this->SPos + 6 - 1) this->SPos = dirsel - 6 + 1;
     }
}

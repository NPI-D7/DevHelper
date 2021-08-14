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
    dbld.LoadDB(standard);
}
void DBSel::Draw(void) const
{
    RenderD7::OnScreen(Top);
    RenderD7::DrawRect(0, 0, 400, 240, RenderD7::Color::Hex("#EEEEEE"));
    DrawFMBG();

    RenderD7::DrawTLBtns(lst, RenderD7::Color::Hex("#CCCCCC"), dirsel);
    for (int Idx = 0; Idx < 6 && Idx < (int)this->dbld.db.e_list.size(); Idx++) {
		
		RenderD7::DrawTextCentered(0, this->lst[Idx].y + 7, 0.5f, RenderD7::Color::Hex("#111111"), dbld.db.e_list[Idx].name, 240);
    };
    RenderD7::OnScreen(Bottom);
    RenderD7::DrawRect(0, 0, 320, 240, RenderD7::Color::Hex("#EEEEEE"));
}

void DBSel::Logic(u32 hDown, u32 hHeld, u32 hUp, touchPosition touch)
{
    if (hDown & KEY_A) dbld.DownloadEntry(dirsel);
    if (hDown & KEY_UP && dirsel > 0) dirsel--;
    if (hDown & KEY_DOWN && dirsel < (int)dbld.db.e_list.size() - 1) dirsel++;
    if (hDown & KEY_LEFT && dirsel - 6 > 0) dirsel -= 6;
    if (hDown & KEY_RIGHT && dirsel + 6 < (int)dbld.db.e_list.size() - 1) dirsel += 6;
}

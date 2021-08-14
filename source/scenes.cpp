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

    std::string dirs;
    for (int i = this->dirsel < 9 ? 0 : this->dirsel - 9; (int)dbld.db.e_list.size() && i < ((this->dirsel < 9) ? 10 : this->dirsel + 1); i++)
    {
        if (i == dirsel)
        {
            dirs += "> " + dbld.db.e_list[i].name + "\n";
        }
        else
        {
            dirs += dbld.db.e_list[i].name + "\n";
        } 
    }
    for (uint i = 0; i < ((dbld.db.e_list.size() < 10) ? 10 - dbld.db.e_list.size() : 0); i++) {
		dirs += "\n\n";
	}

    RenderD7::DrawText(10, 30, 0.6f, RenderD7::Color::Hex("#111111"), dirs.c_str());
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

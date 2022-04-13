#include "scenes.hpp"
#include "log.hpp"

std::string standard = "https://github.com/NPI-D7/nightlys/raw/master/nightlys-Database.ini";

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
    dbld.LoadDB(standard);
}

int timer = 0;

void DBSel::Draw(void) const
{
    if (state == DB){
        flog.Write("Draw DB STate");
        RenderD7::OnScreen(Top);
        RenderD7::DrawRect(0, 0, 400, 240, RenderD7::Color::Hex("#EEEEEE"));
        RenderD7::DrawRect(0, 0, 400, 26, RenderD7::Color::Hex("#111111"));
        RenderD7::DrawText(2, 4, 0.7f, RenderD7::Color::Hex("#eeeeee"), "DevHelper->DB Browser");
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
        RenderD7::DrawTextCentered(0, 216, 0.7f, RenderD7::Color::Hex("#111111"), "Entry: " + std::to_string((dirsel + 1)) + "/" + std::to_string(dbld.db.e_list.size()), 400);
        RenderD7::OnScreen(Bottom);
        RenderD7::DrawRect(0, 0, 320, 240, RenderD7::Color::Hex("#EEEEEE"));
    }
    if (state == APPV){
        flog.Write("Draw Appv STate");
        RenderD7::OnScreen(Top);
        RenderD7::DrawRect(0, 0, 400, 240, RenderD7::Color::Hex("#EEEEEE"));
        RenderD7::DrawRect(0, 0, 400, 26, RenderD7::Color::Hex("#111111"));
        RenderD7::DrawText(2, 4, 0.7f, RenderD7::Color::Hex("#eeeeee"), "DevHelper->App-Ver Browser");
        DrawFMBG();
        std::string dirs;
        for (int i = this->dirsel < 9 ? 0 : this->dirsel - 9; (int)dbld.versions.size() && i < ((this->dirsel < 9) ? 10 : this->dirsel + 1); i++)
        {
            if (i == dirsel)
            {
                dirs += "> " + dbld.versions[i].ver + "\n";
            }
            else
            {
                dirs += dbld.versions[i].ver + "\n";
            } 
        }
        for (uint i = 0; i < ((dbld.versions.size() < 10) ? 10 - dbld.versions.size() : 0); i++) {
	    	dirs += "\n\n";
	    }
        RenderD7::DrawText(10, 30, 0.6f, RenderD7::Color::Hex("#111111"), dirs.c_str());
        RenderD7::DrawTextCentered(0, 216, 0.7f, RenderD7::Color::Hex("#111111"), "Version: " + std::to_string((dirsel + 1)) + "/" + std::to_string(dbld.versions.size()), 400);
        RenderD7::OnScreen(Bottom);
        RenderD7::DrawRect(0, 0, 320, 240, RenderD7::Color::Hex("#EEEEEE"));
        RenderD7::DrawText(2, 4, 0.7f, RenderD7::Color::Hex("#111111"), "Name: " + dbld.versions[dirsel].Name);
        RenderD7::DrawText(2, 24, 0.7f, RenderD7::Color::Hex("#111111"), "Author: " + dbld.versions[dirsel].author);
        RenderD7::DrawText(2, 44, 0.7f, RenderD7::Color::Hex("#111111"), "Commit: " + dbld.versions[dirsel].commit_tag);
        RenderD7::DrawText(2, 64, 0.7f, RenderD7::Color::Hex("#111111"), "Desc: " + dbld.versions[dirsel].desc);
        RenderD7::DrawText(2, 84, 0.7f, RenderD7::Color::Hex("#111111"), "Version: " + dbld.versions[dirsel].ver);
    }
}

void DBSel::Logic(u32 hDown, u32 hHeld, u32 hUp, touchPosition touch)
{
     if (state == DB) {
         if (hDown & KEY_A) {
            timer = 0;
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
        timer ++;
        if (hDown & KEY_A && timer > 60) {
             dbld.Download3dsx(dirsel);
        }
        if (hDown & KEY_Y) {
             dbld.InstallCia(dirsel);
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

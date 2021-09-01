#include "renderd7.hpp"
#include "nightlyreader.hpp"

class DBSel : public RenderD7::Scene
{
     public:
     DBSel();
     void Draw(void) const override;
     void Logic(u32 hDown, u32 hHeld, u32 hUp, touchPosition touch) override;
     private:
     int dirsel = 0;
     int SPos = 0;
     DBLoader dbld;
     std::vector<RenderD7::TLBtn> lst = {
          {0, 30, 400, 30},
          {0, 60, 400, 30},
          {0, 90, 400, 30},
          {0, 120, 400, 30},
          {0, 150, 400, 30},
          {0, 180, 400, 30},
          {0, 210, 400, 30}
     };
};

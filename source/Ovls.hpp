#pragma once
#include "renderd7.hpp"

class Warnings : public RenderD7::Ovl
{
    public:
    Warnings(std::string head, std::string sub);
    void Draw(void) const override;
    void Logic() override;
    private:
    std::string _head, _sub;
    int msgposy = 240;
    int delay = 0;
};

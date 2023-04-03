#pragma once

#include <wx/wx.h>
#include <wx/graphics.h>

#include <memory>

class MyButton : public wxWindow
{
public:
    MyButton(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style = 0, const wxString &name = wxPanelNameStr)
        : wxWindow(parent, id, pos, size, style | wxFULL_REPAINT_ON_RESIZE, name)
    {
        this->Bind(wxEVT_PAINT, &MyButton::OnPaint, this);
    }

    void OnPaint(wxPaintEvent &event)
    {
        wxPaintDC dc(this);

        std::unique_ptr<wxGraphicsContext> gc{wxGraphicsContext::Create(dc)};

        if (gc)
        {
            DrawOnContext(*gc);
        }
    }

    void DrawOnContext(wxGraphicsContext &gc)
    {
        wxColor color{"#EA3B2D"};

        gc.SetBrush(wxBrush(color));

        auto buttonRect = this->GetClientRect();

        gc.DrawRoundedRectangle(buttonRect.GetLeft(),
                                buttonRect.GetTop(),
                                buttonRect.GetWidth(),
                                buttonRect.GetHeight(),
                                buttonRect.GetHeight() / 6);

        wxFont font(wxFontInfo({0, buttonRect.GetHeight() / 2}).FaceName("Arial"));

        gc.SetFont(font, *wxWHITE);

        double textWidth, textHeight;
        gc.GetTextExtent(this->text, &textWidth, &textHeight);

        gc.Clip(buttonRect.GetLeft(),
                buttonRect.GetTop(),
                buttonRect.GetWidth(),
                buttonRect.GetHeight());

        gc.DrawText(this->text,
                    (buttonRect.GetWidth() - textWidth) / 2.0,
                    (buttonRect.GetHeight() - textHeight) / 2.0);
    }

    std::string text;
};

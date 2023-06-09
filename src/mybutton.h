#pragma once

#include <wx/wx.h>
#include <wx/graphics.h>

#include <memory>

class MyButton : public wxWindow
{
public:
    MyButton(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style = 0, const wxString &name = wxPanelNameStr)
        : wxWindow()
    {
        SetBackgroundStyle(wxBG_STYLE_TRANSPARENT);
        wxWindow::Create(parent, id, pos, size, style, name);

#if defined(__WXMSW__)
        int extendedStyle = GetWindowLong(GetHWND(), GWL_EXSTYLE);
        SetWindowLong(GetHWND(), GWL_EXSTYLE, extendedStyle | WS_EX_TRANSPARENT);
#endif

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

    void Save(std::string filePath)
    {
        double scale = GetDPIScaleFactor(); // matching the screen DPI

        wxBitmap bitmap;
        bitmap.CreateWithDIPSize(GetClientRect().GetSize() * GetContentScaleFactor(), scale, 32);
        bitmap.UseAlpha();

        wxMemoryDC dc(bitmap);
        dc.SetUserScale(scale, scale);

        std::unique_ptr<wxGraphicsContext> gc{wxGraphicsContext::Create(dc)};

        if (gc)
        {
            DrawOnContext(*gc);
        }

        bitmap.SaveFile(filePath, wxBITMAP_TYPE_PNG);
    }

    std::string text;
};

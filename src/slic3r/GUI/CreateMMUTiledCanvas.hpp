#ifndef slic3r_GUI_CreateMMUTiledCanvas_hpp_
#define slic3r_GUI_CreateMMUTiledCanvas_hpp_

#include <map>
#include <vector>
#include <regex>

#include "OptionsGroup.hpp"

#include "GUI_App.hpp"

#include <wx/combobox.h>
#include <wx/gbsizer.h>

namespace Slic3r { 
namespace GUI {
    class CreateMMUTiledCanvas;

    class MyDynamicConfig : public DynamicConfig
    {
    public:
        ConfigDef config_def;
        const ConfigDef* def() const override { return &config_def; }
    };

    class BasicDrawPane : public wxPanel
    {

    public:
        wxSize previous_size;

        wxBitmap bmp;
        wxBitmap cache;
        MyDynamicConfig* conf;
        CreateMMUTiledCanvas* parent;

        std::vector<std::pair<wxColour, int>> all_colours;
        std::vector<std::pair<wxColour, int>> colours;
        std::vector<std::pair<wxColour, wxColour>> translate;

        BasicDrawPane(wxWindow* parent, MyDynamicConfig* config);

        void paintEvent(wxPaintEvent& evt);
        void paintNow();

        void render(wxDC& dc);

        void BasicDrawPane::loadImage(std::string filepath);
        void BasicDrawPane::redrawImage();

        // some useful events
        /*
         void mouseMoved(wxMouseEvent& event);
         void mouseDown(wxMouseEvent& event);
         void mouseWheelMoved(wxMouseEvent& event);
         void mouseReleased(wxMouseEvent& event);
         void rightClick(wxMouseEvent& event);
         void mouseLeftWindow(wxMouseEvent& event);
         void keyPressed(wxKeyEvent& event);
         void keyReleased(wxKeyEvent& event);
         */

        DECLARE_EVENT_TABLE()
    };

class CreateMMUTiledCanvas : public DPIDialog
{

public:
    CreateMMUTiledCanvas(GUI_App* app, MainFrame* mainframe);
    virtual ~CreateMMUTiledCanvas();

    BasicDrawPane* get_canvas() { return canvas; }
    void refresh_description();
    
    void close_me(wxCommandEvent& event_args);

    void on_dpi_changed(const wxRect& suggested_rect) override;
    void create_geometry(wxCommandEvent& event_args);

    std::shared_ptr<ConfigOptionsGroup> group_size;
    std::shared_ptr<ConfigOptionsGroup> group_colors;
    MyDynamicConfig conf;

    wxStaticText* nbExtruders;
    wxTextCtrl* filename_ctrl;

    BasicDrawPane* canvas;

    MainFrame* main_frame;
    GUI_App* gui_app;
    wxGridBagSizer* main_sizer;
    wxGridBagSizer* upper_sizer;
    wxComboBox* cmb_add_replace;

    std::regex word_regex;
    bool update_done = false;

    boost::filesystem::path opened_file;

    bool ready = false;

};

} // namespace GUI
} // namespace Slic3r

#endif

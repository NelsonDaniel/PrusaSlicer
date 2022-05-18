#ifndef slic3r_CreateFontNameImageJob_hpp_
#define slic3r_CreateFontNameImageJob_hpp_

#include <vector>
#include <string>
#include <GL/glew.h>
#include <wx/string.h>
#include <wx/fontenc.h>
#include "Job.hpp"

namespace Slic3r::GUI {

/// <summary>
/// Keep data for rasterization of text by font face
/// </summary>
struct FontImageData
{
    // Text to rasterize
    std::string    text;
    // Define font face
    wxString       font_name;
    wxFontEncoding encoding;
    // texture for copy result to
    GLuint         texture_id;
    // Index of face name, define place in texture
    size_t index;
    // Height of each text
    // And Limit for width
    Vec2i  size; // in px

    // bigger value create darker image
    // divide value 255
    unsigned char gray_level = 5;
};

/// <summary>
/// Create image for face name
/// </summary>
class CreateFontImageJob : public Job
{
    FontImageData              m_input;
    std::vector<unsigned char> m_result;
    Point                      m_tex_size;
public:
    CreateFontImageJob(FontImageData &&input);
    /// <summary>
    /// Rasterize text into image (result)
    /// </summary>
    /// <param name="ctl">Check for cancelation</param>
    void process(Ctl &ctl) override;

    /// <summary>
    /// Copy image data into OpenGL texture
    /// </summary>
    /// <param name="canceled"></param>
    /// <param name=""></param>
    void finalize(bool canceled, std::exception_ptr &);
};

} // namespace Slic3r::GUI

#endif // slic3r_CreateFontNameImageJob_hpp_
#include <htmlengine/HTML/HTMLText.hpp>

namespace HTMLEngine::HTML
{
    HTMLText::HTMLText()
        : XML::XMLText()
    {
    }

    void HTMLText::draw(const Cairo::RefPtr<Cairo::Context>& cr)
    {
        cr->move_to(10, 10);
        cr->set_source_rgb(0.8, 0.2, 0.2);
        Cairo::RefPtr<Cairo::ToyFontFace> font =
            Cairo::ToyFontFace::create("Bitstream Charter",
                                    Cairo::FONT_SLANT_ITALIC,
                                    Cairo::FONT_WEIGHT_BOLD);
        cr->set_font_face(font);
        cr->set_font_size(TEXT_DEFAULT_SIZE);
        cr->show_text(get_value());
    }

    HTMLText::~HTMLText()
    {
    }
}
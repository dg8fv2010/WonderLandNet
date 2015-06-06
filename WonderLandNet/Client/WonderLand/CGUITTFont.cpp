#include "irrlicht.h"
#include "CGUITTFont.h"
namespace irr
{
namespace gui
{

CGUITTGlyph::CGUITTGlyph() : IUnknown()
{
	tex = NULL;
	image = NULL;
}

CGUITTGlyph::~CGUITTGlyph()
{
	if (image) delete image;
//	if (tex) Driver->removeTexture(tex);
}

void CGUITTGlyph::cache(u32 idx)
{
	FT_Set_Pixel_Sizes(*face,0,size);
	if (!FT_Load_Glyph(*face,idx,FT_LOAD_NO_HINTING|FT_LOAD_NO_BITMAP)){
		FT_GlyphSlot glyph = (*face)->glyph;
		FT_Bitmap  bits;
		if (glyph->format == ft_glyph_format_outline ){
			if (!FT_Render_Glyph( glyph, FT_RENDER_MODE_NORMAL)){
				bits = glyph->bitmap;
				u8 *pt = bits.buffer;
				image = new u8[bits.width * bits.rows];
				memcpy(image,pt,bits.width * bits.rows);
				top = glyph->bitmap_top;
				left = glyph->bitmap_left;
				imgw = 1;
				imgh = 1;
				texw = bits.width;
				texh = bits.rows;
				for(;;){
					if (imgw > texw){
						break;
					} else {
						imgw <<= 1;
					}
				}
				for(;;){
					if (imgh > texh){
						break;
					} else {
						imgh <<= 1;
					}
				}
				if (imgw > imgh){
					imgh = imgw;
				} else {
					imgw = imgh;
				}
				u32 *texd = new u32[imgw*imgh];
				memset(texd,0,imgw*imgh*sizeof(u32));
				u32 *texp = texd;
				offset = size - bits.rows;
				bool cflag = (Driver->getDriverType() == video::EDT_DIRECTX8);
				for (int i = 0;i < bits.rows;i++){
					u32 *rowp = texp;
					for (int j = 0;j < bits.width;j++){
						if (*pt){
							if (cflag){
								*rowp = *pt;
								*rowp *= 0x01010101;
							} else {
								*rowp = *pt << 24;
								*rowp |= 0xffffff;
							}
						} else {
							*rowp = 0;
						}
						pt++;
						rowp++;
					}
					texp += imgw;
				}
				c8 name[128];
				sprintf(name,"TTFontGlyph%d",idx);
				video::IImage *img = Driver->createImageFromData(video::ECF_A8R8G8B8,core::dimension2d<s32>(imgw,imgh),texd);
				bool flg16 = Driver->getTextureCreationFlag(video::ETCF_ALWAYS_16_BIT);
				bool flg32 = Driver->getTextureCreationFlag(video::ETCF_ALWAYS_32_BIT);
				Driver->setTextureCreationFlag(video::ETCF_ALWAYS_16_BIT,false);
				Driver->setTextureCreationFlag(video::ETCF_ALWAYS_32_BIT,true);
				tex = Driver->addTexture(name,img);
				Driver->setTextureCreationFlag(video::ETCF_ALWAYS_32_BIT,flg32);
				Driver->setTextureCreationFlag(video::ETCF_ALWAYS_16_BIT,flg16);
				delete texd;
				cached = true;
			}
		}
	}
	if (!FT_Load_Glyph(*face,idx,FT_LOAD_NO_HINTING|FT_LOAD_RENDER|FT_LOAD_MONOCHROME)){
		FT_GlyphSlot glyph = (*face)->glyph;
		FT_Bitmap bits = glyph->bitmap;
		u8 *pt = bits.buffer;
		top16 = glyph->bitmap_top;
		left16 = glyph->bitmap_left;
		imgw16 = 1;
		imgh16 = 1;
		texw16 = bits.width;
		texh16 = bits.rows;
		for(;;){
			if (imgw16 >= texw16){
				break;
			} else {
				imgw16 <<= 1;
			}
		}
		for(;;){
			if (imgh16 >= texh16){
				break;
			} else {
				imgh16 <<= 1;
			}
		}
		if (imgw16 > imgh16){
			imgh16 = imgw16;
		} else {
			imgw16 = imgh16;
		}
		u16 *texd16 = new u16[imgw16*imgh16];
		memset(texd16,0,imgw16*imgh16*sizeof(u16));
		u16 *texp16 = texd16;
		offset = size - bits.rows;
		for (int y = 0;y < bits.rows;y++){
			u16 *rowp = texp16;
			for (int x = 0;x < bits.width;x++){
				if (pt[y * bits.pitch + (x / 8)] & (0x80 >> (x % 8))){
					*rowp = 0xffff;
				}
				rowp++;
			}
			texp16 += imgw16;
		}
		c8 name[128];
		sprintf(name,"TTFontGlyph%d_16",idx);
		video::IImage *img = Driver->createImageFromData(video::ECF_A1R5G5B5,core::dimension2d<s32>(imgw16,imgh16),texd16);
		tex16 = Driver->addTexture(name,img);
		Driver->makeColorKeyTexture(tex16,video::SColor(0,0,0,0));
		delete texd16;
	}
}

//! constructor
CGUITTFont::CGUITTFont(video::IVideoDriver* driver)
: Driver(driver)
{
	#ifdef _DEBUG
	setDebugName("CGUITTFont");
	#endif

	if (Driver)
		Driver->grab();
	AntiAlias = false;
	TransParency = false;
}



//! destructor
CGUITTFont::~CGUITTFont()
{
	if (Driver)
		Driver->drop();
}

//! loads a font file
bool CGUITTFace::load(const c8* filename)
{
	if (FT_Init_FreeType( &library )){
		return	false;
	}
	if (FT_New_Face( library,filename,0,&face )){
		return	false;
	}
	return	true;
}

bool CGUITTFont::attach(CGUITTFace *Face,u32 size)
{
	if (!Driver)
		return false;

	tt_face = Face;

	Glyphs.reallocate(tt_face->face->num_glyphs);
	Glyphs.set_used(tt_face->face->num_glyphs);
	for (int i = 0;i < tt_face->face->num_glyphs;i++){
		Glyphs[i].Driver = Driver;
		Glyphs[i].size = size;
		Glyphs[i].face = &(tt_face->face);
		Glyphs[i].cached = false;
//		Glyphs[i].cache((wchar_t)i + 1);
	}
	return	true;
}

u32 CGUITTFont::getGlyphByChar(wchar_t c){
	u32 idx = FT_Get_Char_Index( tt_face->face, c );
	if (idx && !Glyphs[idx - 1].cached)	Glyphs[idx - 1].cache(idx);
	return	idx;
}

//! returns the dimension of a text
core::dimension2d<s32> CGUITTFont::getDimension(const wchar_t* text)
{
	core::dimension2d<s32> dim(0, Glyphs[0].size);

	for(const wchar_t* p = text; *p; ++p)
	{
		dim.Width += getWidthFromCharacter(*p);
	}

	return dim;
}


inline s32 CGUITTFont::getWidthFromCharacter(wchar_t c)
{
	u32 n = getGlyphByChar(c);
	if ( n > 0){
		int w = Glyphs[n - 1].texw;
		s32 left = Glyphs[n - 1].left;
		if (w + left > 0) return w + left;
	}
	if (c >= 0x2000){
		return	Glyphs[0].size;
	} else {
		return	Glyphs[0].size / 2;
	}
}


//! draws an text and clips it to the specified rectangle if wanted
void CGUITTFont::draw(const wchar_t* text, const core::rect<s32>& position, video::SColor color, bool hcenter, bool vcenter, const core::rect<s32>* clip)
{
	if (!Driver)
		return;

	core::dimension2d<s32> textDimension;
	core::position2d<s32> offset = position.UpperLeftCorner;
	video::SColor colors[4];
	for (int i = 0;i < 4;i++){
		colors[i] = color;
	}

    if (hcenter || vcenter)
	{
		textDimension = getDimension(text);

		if (hcenter)
			offset.X = ((position.getWidth() - textDimension.Width)>>1) + offset.X;

		if (vcenter)
			offset.Y = ((position.getHeight() - textDimension.Height)>>1) + offset.Y;
	}

	u32 n;
	
	while(*text)
	{
		n = getGlyphByChar(*text);
		if ( n > 0){
			if (AntiAlias){
				s32 imgw = Glyphs[n-1].imgw;
				s32 imgh = Glyphs[n-1].imgh;
				s32 texw = Glyphs[n-1].texw;
				s32 texh = Glyphs[n-1].texh;
				s32 offx = Glyphs[n-1].left;
				s32 offy = Glyphs[n-1].size - Glyphs[n-1].top;
				if (Driver->getDriverType() != video::EDT_SOFTWARE){
					if (!TransParency)	color.color |= 0xff000000;
					Driver->draw2DImage(Glyphs[n-1].tex,core::position2d<s32>(offset.X+offx,offset.Y+offy),core::rect<s32>(0,0,imgw-1,imgh-1),clip,color,true);
				} else {
					s32 a = color.getAlpha();
					s32 r = color.getRed();
					s32 g = color.getGreen();
					s32 b = color.getBlue();
					u8 *pt = Glyphs[n-1].image;
					if (!TransParency)	a = 255;
					for (int y = 0;y < texh;y++){
						for (int x = 0;x < texw;x++){
							if (!clip || clip->isPointInside(core::position2d<s32>(offset.X+x+offx,offset.Y+y+offy))){
								if (*pt){
									Driver->draw2DRectangle(video::SColor((a * *pt)/255,r,g,b),core::rect<s32>(offset.X+x+offx,offset.Y+y+offy,offset.X+x+offx+1,offset.Y+y+offy+1));
								}
								pt++;
							}
						}
					}
				}
			} else {
				s32 imgw = Glyphs[n-1].imgw16;
				s32 imgh = Glyphs[n-1].imgh16;
				s32 texw = Glyphs[n-1].texw16;
				s32 texh = Glyphs[n-1].texh16;
				s32 offx = Glyphs[n-1].left16;
				s32 offy = Glyphs[n-1].size - Glyphs[n-1].top16;
				if (!TransParency){
					color.color |= 0xff000000;
				}
				Driver->draw2DImage(Glyphs[n-1].tex16,core::position2d<s32>(offset.X+offx,offset.Y+offy),core::rect<s32>(0,0,imgw-1,imgh-1),clip,color,true);
			}
			offset.X += getWidthFromCharacter(*text);
		} else {
			offset.X += getWidthFromCharacter(*text);
		}

		++text;
	}
}

//! Calculates the index of the character in the text which is on a specific position.
s32 CGUITTFont::getCharacterFromPos(const wchar_t* text, s32 pixel_x)
{
	s32 x = 0;
	s32 idx = 0;

	while (text[idx])
	{
		x += getWidthFromCharacter(text[idx]);

		if (x >= pixel_x)
			return idx;

		++idx;
	}

	return -1;
}

#if	0

#endif
} // end namespace gui
} // end namespace irr

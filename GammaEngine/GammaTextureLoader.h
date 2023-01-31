using namespace spine;
using namespace GammaEngine;

class GammaTextureLoader : public TextureLoader {
public:
    GammaTextureLoader() { }
    virtual ~GammaTextureLoader() { }

    // Called when the atlas loads the texture of a page.
    virtual void load(AtlasPage& page, const String& path) {

        wstring* bitmap = new wstring(path.buffer(), path.buffer() + strlen(path.buffer()));
        GraphicSystem::LoadBitmapImage(*bitmap);
        page.setRendererObject(bitmap);
        vector2 size = GraphicSystem::GetBitmapSize(*bitmap);
        page.width=size.x;
        page.height=size.y;
    }

    // Called when the atlas is disposed and itself disposes its atlas pages.
    virtual void unload(void* texture) {
        // the texture parameter is the texture we stored in the page via page->setRendererObject()
        //engine_disposeTexture(texture);
    }
}
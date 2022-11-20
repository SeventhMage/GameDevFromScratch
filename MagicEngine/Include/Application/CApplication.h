#ifndef _MAGIC_C_APPLLICATION_H_
#define _MAGIC_C_APPLLICATION_H_

#include "ApplicationMCR.h"
#include "Graphic/Rendering/IRenderer.h"
#include "Scene/ISceneManager.h"

namespace Magic
{
    class CApplication
    {
    public:
        virtual ~CApplication();
        virtual bool OnInitialize() { return true; }
        virtual bool OnTerminate() { return true; }
        virtual void OnUpdate() {}

        inline void SetFPS(int fps) { _FPS = fps; }
        inline int GetFPS() { return _FPS; }
        inline int GetMaxFPS() { return _MaxFPS; }

        inline int GetWindowWidth() { return _WindowWidth; }
        inline int GetWindowHeight() { return _WindowHeight; }
        static void Run();

    protected:
        CApplication();
        void StartMain();
        void Update();
        static CApplication *TheApp;
        IRenderer *Renderer;
        ISceneManager *SceneManager;
    private:
        int _FPS;
        int _MaxFPS;
        int _WindowWidth;
        int _WindowHeight;
    };
}

#endif
#include "Application/CApplication.h"

namespace Magic
{
    CApplication *CApplication::TheApp = nullptr;

    void CApplication::Run()
    {
        TheApp->OnInitialize();
        TheApp->StartMain();
        TheApp->OnTerminate();
    }

    void CApplication::Update()
    {
        Renderer->Begin();
        OnUpdate();
        Renderer->Render();
        Renderer->End();
    }
}
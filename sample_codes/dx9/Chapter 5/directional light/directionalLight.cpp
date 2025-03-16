#include "d3dUtility.h"
#include "drawer.h"

//
// Globals
//
const int Width = 800;
const int Height = 600;


//
// Framework Functions
//

void lights() {
    //
    // Setup a directional light.
    //
    D3DXVECTOR3 dir(2.0f, 2.0f, 2.0f);
    D3DXCOLOR c = d3d::WHITE;
    D3DLIGHT9 dirLight = d3d::InitDirectionalLight(&dir, &c);

    //
    // Set and Enable the light.
    //
    Device->SetLight(0, &dirLight);
    Device->LightEnable(0, true);

    //
    // Set lighting related render states.
    //
    Device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
    Device->SetRenderState(D3DRS_SPECULARENABLE, false);

    //
    // Set the projection matrix.
    //
    D3DXMATRIX proj;
    D3DXMatrixPerspectiveFovLH(
        &proj,
        D3DX_PI * 0.25f, // 45 - degree
        (float)Width / (float)Height,
        1.0f,
        1000.0f);
    Device->SetTransform(D3DTS_PROJECTION, &proj);
}

bool Setup() {
    drawHat();
    drawHead();
    drawEyes();
    drawNose();
    drawEars();
    drawMouth();
    drawBody();
    drawHand();
    drawLeg();
    drawFoot();

    lights();

    return true;
}

void Cleanup() {
    for (int i = 0; i < oCount; i++)
        d3d::Release<ID3DXMesh *>(Objects[i]);
}

bool Display(float timeDelta) {
    if (Device) {
        //
        // Update the scene: update camera position.
        //

        static float angle = (3.0f * D3DX_PI) / 2.0f;
        static float height = 0.0f;
        static float y_target = -4.0f;

        if (::GetAsyncKeyState(VK_LEFT) & 0x8000f)
            angle -= 0.5f * timeDelta;

        if (::GetAsyncKeyState(VK_RIGHT) & 0x8000f)
            angle += 0.5f * timeDelta;

        if (::GetAsyncKeyState(VK_UP) & 0x8000f)
            height += 5.0f * timeDelta;

        if (::GetAsyncKeyState(VK_DOWN) & 0x8000f)
            height -= 5.0f * timeDelta;

        if (::GetAsyncKeyState(0x57) & 0x8000f)
            y_target += 5.0f * timeDelta;

        if (::GetAsyncKeyState(0x53) & 0x8000f)
            y_target -= 5.0f * timeDelta;

        //D3DXVECTOR3 position(cosf(angle) * 7.0f, 0.0f, sinf(angle) * 7.0f);
        //D3DXVECTOR3 target(0.0f, height, 0.0f);
        D3DXVECTOR3 position(cosf(angle) * 7.0f, height, sinf(angle) * 7.0f);
        D3DXVECTOR3 target(0.0f, y_target, 0.0f);
        D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
        D3DXMATRIX V;
        D3DXMatrixLookAtLH(&V, &position, &target, &up);

        Device->SetTransform(D3DTS_VIEW, &V);

        //
        // Draw the scene:
        //
        Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0);
        Device->BeginScene();

        for (int i = 0; i < oCount; i++) {

            // set material and world matrix for ith object, then render
            // the ith object.
            Device->SetTransform(D3DTS_WORLD, &Worlds[i]);
            Device->SetMaterial(&Mtrls[i]);
            Objects[i]->DrawSubset(0);
        }

        Device->EndScene();
        Device->Present(0, 0, 0, 0);
    }
    return true;
}


//
// WndProc
//
LRESULT CALLBACK d3d::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
switch( msg )
{
case WM_DESTROY:
::PostQuitMessage(0);
break;

case WM_KEYDOWN:
if( wParam == VK_ESCAPE )
::DestroyWindow(hwnd);
break;
}
return ::DefWindowProc(hwnd, msg, wParam, lParam);
}

//
// WinMain
//
int WINAPI WinMain(HINSTANCE hinstance,
HINSTANCE prevInstance,
        PSTR cmdLine,
int showCmd)
{
if(!d3d::InitD3D(hinstance,
        Width, Height, true, D3DDEVTYPE_HAL, &Device))
{
::MessageBox(0, (LPCWSTR) "InitD3D() - FAILED", 0, 0);
return 0;
}

if(!Setup())
{
::MessageBox(0, (LPCWSTR) "Setup() - FAILED", 0, 0);
return 0;
}

d3d::EnterMsgLoop( Display );

Cleanup();

Device->Release();

return 0;
}
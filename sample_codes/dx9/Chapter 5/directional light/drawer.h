#include "d3dUtility.h"
#include <iostream>

using namespace std;

IDirect3DDevice9* Device = 0;

const int oCount = 15;

ID3DXMesh* Objects[oCount] = {0, // hat
                              0, // head
                              0, // eye
                              0, // eye
                              0, // nose
                              0, // ear
                              0, // ear
                              0, // mouth
                              0, // body
                              0, // hand
                              0, // hand
                              0, // leg
                              0, // leg
                              0, // foot
                              0  // foot
};

D3DXMATRIX Worlds[oCount];
D3DMATERIAL9 Mtrls[oCount];


void drawHat() {
    // create the object !
    D3DXCreateTorus(Device,
        1.0f, // inner radius
        0.5f, // outer radius
        100, // sides
        100,  // rings
        &Objects[0],
        0);

    //
    // Build world matrices - position the objects in world space.
    //
    D3DXMatrixTranslation(&Worlds[0], 0.0f, 1.2f, 0.0f);
 
    //
    // Setup the object's materials.
    //
    Mtrls[0] = d3d::RED_MTRL;

    // rotate
    D3DXMATRIX hat, hatRotate;
    D3DXMatrixRotationX(&hatRotate, 1.5f);
    // hat = hatRotate * World[i]
    D3DXMatrixMultiply(&hat, &hatRotate, &Worlds[0]);
    
    // save changed matrix to Worlds matrix
    Worlds[0] = hat;
}

void drawHead() {
    D3DXCreateSphere(Device,
        1.0f, // Radius
        100, // Slices
        100, // Stacks
        &Objects[1], // ppMesh
        0);

    D3DXMatrixTranslation(&Worlds[1], 0.0f, 0.0f, 0.0f);

    Mtrls[1] = d3d::SKIN_MTRL;
}

void drawEyes() {
    D3DXCreateSphere(Device,
        0.1f, // Radius
        100, // Slices
        100, // Stacks
        &Objects[2], // ppMesh
        0);

    D3DXCreateSphere(Device,
        0.1f, // Radius
        100, // Slices
        100, // Stacks
        &Objects[3], // ppMesh
        0);

    D3DXMatrixTranslation(&Worlds[2], 0.3f, 0.0f, -0.9f);  // eyes
    D3DXMatrixTranslation(&Worlds[3], -0.3f, 0.0f, -0.9f); //eyes 

    Mtrls[2] = d3d::GREEN_MTRL;
    Mtrls[3] = d3d::GREEN_MTRL;
}    

void drawNose() {
    D3DXCreateCylinder(Device,
        0.08f, // radius at negative z end
        0.08f, // radius at positive z end
        0.7f,  // length of cylinder
        100, // slices
        100, // stacks
        &Objects[4],
        0);

    D3DXMatrixTranslation(&Worlds[4], 0.0f, -0.0f, -0.9f);// nose

    Mtrls[4] = d3d::SKIN_MTRL;

    // rotate
    D3DXMATRIX nose, noseRotate;
    D3DXMatrixRotationX(&noseRotate, -1.2f);
    // hat = hatRotate * World[i]
    D3DXMatrixMultiply(&nose, &noseRotate, &Worlds[4]);

    // save changed matrix to Worlds matrix
    Worlds[4] = nose;
}

void drawEars() {
    D3DXCreateCylinder(Device,
        0.1f, // radius at negative z end
        0.2f, // radius at positive z end
        0.1f,  // length of cylinder
        100, // slices
        100, // stacks
        &Objects[5],
        0);

    D3DXCreateCylinder(Device,
        0.1f, // radius at negative z end
        0.2f, // radius at positive z end
        0.1f,  // length of cylinder
        100, // slices
        100, // stacks
        &Objects[6],
        0);

    D3DXMatrixTranslation(&Worlds[5], 1.0f, 0.0f, 0.0f);
    D3DXMatrixTranslation(&Worlds[6], -1.0f, 0.0f, 0.0f);

    Mtrls[5] = d3d::SKIN_MTRL;
    Mtrls[6] = d3d::SKIN_MTRL;

    // rotate
    D3DXMATRIX ear1, ear2, earRotate1, earRotate2;
    D3DXMatrixRotationY(&earRotate1, 0.7f);
    D3DXMatrixRotationY(&earRotate2, -0.7f);
    // hat = hatRotate * World[i]
    D3DXMatrixMultiply(&ear1, &earRotate1, &Worlds[6]);
    D3DXMatrixMultiply(&ear2, &earRotate2, &Worlds[5]);

    // save changed matrix to Worlds matrix
    Worlds[6] = ear1;
    Worlds[5] = ear2;
}

void drawMouth() {
    D3DXCreateTorus(Device,
        0.1f, // inner radius
        0.15f, // outer radius
        100, // sides
        100,  // rings
        &Objects[7],
        0);

    D3DXMatrixTranslation(&Worlds[7], 0.0f, -0.6f, -0.8f); // mouth

    Mtrls[7] = d3d::BLACK_MTRL;
}

void drawBody() {
    D3DXCreateTorus(Device,
        1.1f, // inner radius
        1.0f, // outer radius
        100, // sides
        100,  // rings
        &Objects[8],
        0);

    D3DXMatrixTranslation(&Worlds[8], 0.0f, -3.0f, 0.0f);  // body

    Mtrls[8] = d3d::VIVID_MTRL;
}

void drawHand() {
    D3DXCreateCylinder(Device,
        0.2f, // radius at negative z end
        0.2f, // radius at positive z end
        3.0f,  // length of cylinder
        100, // slices
        100, // stacks
        &Objects[9],
        0);

    D3DXCreateCylinder(Device,
        0.2f, // radius at negative z end
        0.2f, // radius at positive z end
        3.0f,  // length of cylinder
        100, // slices
        100, // stacks
        &Objects[10],
        0);

    D3DXMatrixTranslation(&Worlds[9], 2.5f, -3.0f, -0.8f);
    //D3DXMatrixTranslation(&Worlds[10], -1.8f, -3.0f, -0.8f);
    D3DXMatrixTranslation(&Worlds[10], 2.5f, -3.0f, -0.8f);

    Mtrls[9] = d3d::RED_MTRL;
    Mtrls[10] = d3d::SKIN_MTRL;

    D3DXMATRIX hand1, hand2, handRotate1, handRotate2;
    cout << hand1 << " " << &hand2;
    D3DXMatrixRotationZ(&handRotate1, 3.14f / 3);
    D3DXMatrixMultiply(&hand1, &handRotate1, &Worlds[9]);
    D3DXMatrixRotationX(&handRotate2, 3.14f / 4);
    D3DXMatrixMultiply(&hand2, &handRotate2, &Worlds[10]);

    Worlds[9] = hand1;
    Worlds[10] = hand2;



    //// rotate
    //D3DXMATRIX hand1, hand2, handRotate1, handRotate2;
    //D3DXMatrixRotationY(&handRotate1, -2.0f);
    //D3DXMatrixMultiply(&hand1, &handRotate1, &Worlds[9]);
    ////D3DXMatrixRotationY(&handRotate2, -0.2f);

    //D3DXMatrixRotationX(&handRotate1, +1.5f);
    ////D3DXMatrixRotationX(&handRotate2, +1.2f);
    //// hat = hatRotate * World[i]
    //D3DXMatrixMultiply(&hand1, &handRotate1, &hand1);
    ////D3DXMatrixMultiply(&hand2, &handRotate2, &Worlds[10]);

    //// save changed matrix to Worlds matrix
    //Worlds[9] = hand1;
    //Worlds[10] = hand2;
}

void drawLeg() {
    D3DXCreateCylinder(Device,
        0.4f, // radius at negative z end
        0.25f, // radius at positive z end
        3.0f,  // length of cylinder
        100, // slices
        100, // stacks
        &Objects[11],
        0);

    D3DXCreateCylinder(Device,
        0.4f, // radius at negative z end
        0.25f, // radius at positive z end
        3.0f,  // length of cylinder
        100, // slices
        100, // stacks
        &Objects[12],
        0);

    D3DXMatrixTranslation(&Worlds[11], -1.2f, -5.8f,0.0f);
    //D3DXMatrixTranslation(&Worlds[10], -1.8f, -3.0f, -0.8f);
    D3DXMatrixTranslation(&Worlds[12], 1.2f, -5.8f, 0.0f);

    Mtrls[11] = d3d::VIVID2_MTRL;
    Mtrls[12] = d3d::VIVID2_MTRL;

    D3DXMATRIX leg1, leg2, legRotate1, legRotate2;
    D3DXMatrixRotationX(&legRotate1, 3.14f / 2);
    D3DXMatrixMultiply(&leg1, &legRotate1, &Worlds[11]);
    D3DXMatrixRotationX(&legRotate2, 3.14f / 2);
    D3DXMatrixMultiply(&leg2, &legRotate2, &Worlds[12]);

    Worlds[11] = leg1;
    Worlds[12] = leg2;
}

void drawFoot() {
    D3DXCreateCylinder(Device,
        0.35f, // radius at negative z end
        0.4f, // radius at positive z end
        0.15f,  // length of cylinder
        100, // slices
        100, // stacks
        &Objects[13],
        0);

    D3DXCreateCylinder(Device,
        0.35f, // radius at negative z end
        0.4f, // radius at positive z end
        0.15f,  // length of cylinder
        100, // slices
        100, // stacks
        &Objects[14],
        0);

    D3DXMatrixTranslation(&Worlds[13], -1.2f, -7.35f, -0.1f);
    D3DXMatrixTranslation(&Worlds[14], 1.2f, -7.35f, -0.1f);

    Mtrls[13] = d3d::BLUE_MTRL;
    Mtrls[14] = d3d::BLUE_MTRL;

    D3DXMATRIX foot1, foot2, footRotate1, footRotate2;
    D3DXMatrixRotationX(&footRotate1, 3.14f / 2);
    D3DXMatrixMultiply(&foot1, &footRotate1, &Worlds[13]);
    D3DXMatrixRotationX(&footRotate2, 3.14f / 2);
    D3DXMatrixMultiply(&foot2, &footRotate2, &Worlds[14]);

    Worlds[13] = foot1;
    Worlds[14] = foot2;
}
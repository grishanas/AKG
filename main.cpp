#include <vector>
#include <cmath>
#include <iostream>
#include "geometry.h"

#include <SFML/Graphics.hpp>

#include "model.h"
#include "main.h"
#include "Camera.h"
#include "Lab_part_2.h"


Model *model1 = NULL;
//Model *model2 = NULL;
const int width  = 800;
const int height = 800;
const int depth = 255;

using namespace std;
using namespace sf;

pix pixarray[width][height];
Texture tex;
std::vector<Vertex> vertes;

void line(int x0, int y0, int x1, int y1, Uint32 color);
void loadbitmap(Model* model);
void displaybitmap();
void Thriangle(Vec3i screen_coords[3]);

int main(int argc, char** argv) {

    if (2 == argc) {
        model1 = new Model(argv[1]);
    }
    else {
        //model1 = new Model("obj/model.obj");
        model1 = new Model("obj/nigga.obj");
    }


    RenderWindow window(VideoMode(width, height), "Renderer", sf::Style::Close);

    Camera *cam = new Camera();

    window.setFramerateLimit(60);

    loadbitmap(model1);
    displaybitmap();

    sf::Clock clock;
    sf::Clock fps;
    sf::Vector2f mousePosPrev;

    const float cameraSpeed = 0.05f;

    while (window.isOpen()) {

        std::cout << fps.restart().asMilliseconds() << endl;
        Event event;
        while (window.pollEvent(event)) {

            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case Keyboard::W:
                    //model1->traslate(sf::Vector3f(0, 0.01, 0));
                    cam->ChangePosition(sf::Vector3f(0, 0.01, 0));
                    break;
                case Keyboard::A:
                    //model1->traslate(sf::Vector3f(-0.01, 0, 0));
                    cam->ChangePosition(sf::Vector3f(-0.01, 0, 0));
                    break;
                case Keyboard::S:
                    //model1->traslate(sf::Vector3f(0, -0.01, 0));
                    cam->ChangePosition(sf::Vector3f(0, -0.01, 0));
                    break;
                case Keyboard::D:
                    //model1->traslate(sf::Vector3f(0.01, 0, 0));
                    cam->ChangePosition(sf::Vector3f(0.01, 0, 0));
                    break;
                default:
                    break;
                }



            }
            if (event.type == Event::MouseMoved)
            {

                if (Mouse::isButtonPressed(Mouse::Button::Left))
                {
                    sf::Vector2f(mousePosPrev.x - event.mouseMove.x, mousePosPrev.y - event.mouseMove.y);

                    model1->rotate(sf::Vector3f((mousePosPrev.y - event.mouseMove.y) * 0.002, (mousePosPrev.x - event.mouseMove.x) * 0.002, 0));

                }

                mousePosPrev = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
            }
            if (event.type == Event::MouseWheelScrolled)
            {
                model1->scale(sf::Vector3f(1 * pow(1.02, event.mouseWheelScroll.delta), 1 * pow(1.02, event.mouseWheelScroll.delta), 1 * pow(1.02, event.mouseWheelScroll.delta)));

            }
        }



        memset(pixarray, 0, width * height * sizeof(pix));
        loadbitmap(model1);
        displaybitmap();

        window.clear();


        sf::RenderStates states;
        states.texture = &tex;
        window.draw(&vertes[0], 4, sf::Quads, states);

        window.display();


    }

    return 0;
}

void loadbitmap(Model *model) {

    
    
    for (int i=0; i<model->nfaces(); i++) {
        std::vector<int> face = model->face(i);
        Vec3i screen_coords[3];
        Vec3f world_coords[3];
        for (int j=0; j<3; j++) {
            Vec3f v0 = model->vert(face[j]);
            screen_coords[j] = Vec3i(((v0.x + 1.) * width / 2.),((v0.y + 1.) * height / 2.),((v0.z+1)* depth/2));
            world_coords[j] = v0;
            Vec3f v1 = model->vert(face[(j+1)%3]);
            int x0 = (v0.x+1.)*width/2.;
            int y0 = (v0.y+1.)*height/2.;
            int x1 = (v1.x+1.)*width/2.;
            int y1 = (v1.y+1.)*height/2.;
            line(x0, y0, x1, y1, 0xFFFFFFFF);
        }
        //Thriangle(screen_coords);
        
           
        
    }

    //ZBuffering(model, *pixarray);
    return;
}

void displaybitmap() {

    Image img;
    unsigned char* ptr1;

    ptr1 = &pixarray[0][0].r;

    img.create(width, height, ptr1);
    tex.loadFromImage(img);

    vertes.resize(4);
    vertes.shrink_to_fit();

    vertes[0].position = sf::Vector2f(0, 0);
    vertes[1].position = sf::Vector2f(0, height);
    vertes[2].position = sf::Vector2f(width, height);
    vertes[3].position = sf::Vector2f(width, 0);
    vertes[0].texCoords = sf::Vector2f(0, 0);
    vertes[1].texCoords = sf::Vector2f(0, height);
    vertes[2].texCoords = sf::Vector2f(width, height);
    vertes[3].texCoords = sf::Vector2f(width, 0);

    return;
}

void Thriangle(Vec3i screen_coords[3])
{
    if (screen_coords[0].y > screen_coords[1].y) std::swap(screen_coords[0], screen_coords[1]);
    if (screen_coords[0].y > screen_coords[2].y) std::swap(screen_coords[0], screen_coords[2]);
    if (screen_coords[1].y > screen_coords[2].y) std::swap(screen_coords[1], screen_coords[2]);
    int TotalHeight = screen_coords[2].y - screen_coords[0].y;
    for (int i = screen_coords[0].y; i < screen_coords[2].y; i++)
    {
        bool secondHalf = i > screen_coords[1].y - screen_coords[0].y || screen_coords[1].y == screen_coords[0].y;
        int SegmentHeight = secondHalf ? screen_coords[2].y - screen_coords[1].y : screen_coords[1].y == screen_coords[0].y;
        float alp = (float)i / TotalHeight;
        float bet = (float)(i - (secondHalf ? screen_coords[1].y - screen_coords[0].y : 0));
        Vec3i A = screen_coords[0] + (screen_coords[2] - screen_coords[0])*alp;
        Vec3i B = secondHalf ? screen_coords[1] + (screen_coords[2] - screen_coords[1])*(bet) : screen_coords[0] + (screen_coords[1] - screen_coords[0])*bet;
        if (A.x > B.x)
            swap(A, B);

        for (int j = A.x; j < B.x; j++)
        {
            if (j < 0 || i<0 || j >= width || i>= height)
                continue;
            pixarray[j][i].g = 0xff;
            pixarray[j][i].t = 0xff;
        }


    }

}


void line(int x0, int y0, int x1, int y1, Uint32 color) {
    bool steep = false;

    if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    for (int x = x0; x <= x1; x++) {
        double t = (x - x0) / (float)(x1 - x0);
        int y = y0 * (1. - t) + y1 * t;
        if (y < 0 || x < 0 || x >= width || y >= height)
            continue;
        if (steep) {
            
            pixarray[x][y].r = color >> 6;
            pixarray[x][y].g = (color >> 4) % 256;
            pixarray[x][y].b = (color >> 2) % 256;
            pixarray[x][y].t = color % 256;
        }
        else {
            pixarray[y][x].r = color >> 6;
            pixarray[y][x].g = (color >> 4) % 256;
            pixarray[y][x].b = (color >> 2) % 256;
            pixarray[y][x].t = color % 256;
        }
    }
}
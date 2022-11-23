#include <vector>
#include <cmath>
#include <iostream>
#include "geometry.h"

#include <SFML/Graphics.hpp>

#include "model.h"
#include "main.h"
#include "Camera.h"
#include "Lab_part_2.h"
#include "Matrix.h"


Model* model1 = NULL;
Camera* cam = NULL;
sf::Vector3f lightPos = { 100.f, 0.f, 0.f };
//Model *model2 = NULL;


using namespace std;
using namespace sf;

pix pixarray[width][height];
float PixDepth[width][height];
Texture tex;
std::vector<Vertex> vertes;

void line(sf::Vector3f firstPont, sf::Vector3f secondPoint, Uint32 color);
void line(int x0, int y0, int x1, int y1, Uint32 color);
void loadbitmap(Model* model);
void displaybitmap();
void Thriangle(sf::Vector3f screen_coords[3], float colorPercent);
void ZBuffering(sf::Vector3i screen_coords[3]);

int main(int argc, char** argv) {

    if (2 == argc) {
        model1 = new Model(argv[1]);
    }
    else {
        //model1 = new Model("obj/model.obj");
        model1 = new Model("obj/nigga.obj");
    }



    RenderWindow window(VideoMode(width, height), "Renderer", sf::Style::Close);

    cam = new Camera();
    model1->traslate(sf::Vector3f(0.2f, 0.2f, 0));

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
                    cam->ChangeAngle(sf::Vector2f(0, cameraSpeed));
                    break;
                case Keyboard::A:
                    //model1->traslate(sf::Vector3f(-0.01, 0, 0));
                    cam->ChangeAngle(sf::Vector2f(-cameraSpeed, 0));
                    break;
                case Keyboard::S:
                    //model1->traslate(sf::Vector3f(0, -0.01, 0));
                    cam->ChangeAngle(sf::Vector2f(0, -cameraSpeed));
                    break;
                case Keyboard::D:
                    //model1->traslate(sf::Vector3f(0.01, 0, 0));
                    cam->ChangeAngle(sf::Vector2f(cameraSpeed, 0));
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
                //model1->scale(sf::Vector3f(1 * pow(1.02, event.mouseWheelScroll.delta), 1 * pow(1.02, event.mouseWheelScroll.delta), 1 * pow(1.02, event.mouseWheelScroll.delta)));
                cam->ChangeRadius(event.mouseWheelScroll.delta * 1.5f);
            }
        }

        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height; j++)
            {
                PixDepth[i][j] = -1000.f;
            }
        }

        memset(pixarray, 0x0, width * height * sizeof(pix));
        loadbitmap(model1);
        //loadbitmap(model2);
        displaybitmap();

        window.clear();


        sf::RenderStates states;
        states.texture = &tex;
        window.draw(&vertes[0], 4, sf::Quads, states);

        window.display();


    }

    return 0;
}

void loadbitmap(Model* model) {

    sf::Vector3f pos = cam->getDecartPos();

    float min = std::numeric_limits<float>().max();
    float max = std::numeric_limits<float>().min();

    for (auto& vertex : model->getVerteses())
    {
        auto distance = pow(pow(vertex.x - pos.x, 2) + pow(vertex.y - pos.y, 2) + pow(vertex.z - pos.z, 2), 0.5);
        if (distance > max)
        {
            max = distance;

        }
        if (distance < min)
        {
            min = distance;
        }
    }

    //cam->SetCollaider(min);
    //cam->SetFar(max);
    float maxValue = 0;

    for (int i = 0; i < model->nfaces(); i++) {
        std::vector<int> face = model->face(i);
        sf::Vector3f screen_coords[3];
        sf::Vector3i world_coords[3];
        sf::Vector3f firstPoint;
        sf::Vector3f secondPoint;
        sf::Vector3f Lambert[3];
        for (int j = 0; j < 3; j++) {
            sf::Vector3f v0 = sf::Vector3f(model->vert(face[j]).x, model->vert(face[j]).y, model->vert(face[j]).z);
            sf::Vector3f v1 = sf::Vector3f(model->vert(face[(j + 1) % 3]).x, model->vert(face[(j + 1) % 3]).y, model->vert(face[(j + 1) % 3]).z);
            firstPoint = cam->Render(v0);
            secondPoint = cam->Render(v1);

            auto tmp = model->getNormals().at(face[j]);
            Lambert[j] = Normilize(sf::Vector3f(tmp.x,tmp.y,tmp.z));
            screen_coords[j] = firstPoint;
            //line(firstPoint, secondPoint, 0xFFFFFFFF);//firstPointp.x, firstPointp.y, secondPointp.x, secondPointp.y, 0xFFFFFFFF);
        }
        sf::Vector3f fNormalz = Normilize(Cross((Lambert[1]- Lambert[0]),(Lambert[2]- Lambert[1])));
        sf::Vector3f tmp = (screen_coords[0] + screen_coords[1] + screen_coords[2]);
        tmp.x /= 3;
        tmp.y /= 3;
        tmp.z /= 3;

        auto temp1 = Normilize(tmp-lightPos);


        float colorPercent = cos(FindAngle(temp1, fNormalz));

        Thriangle(screen_coords, colorPercent);



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

void ZBuffering(sf::Vector3i screen_coords[3])
{
    if (screen_coords[0].y > screen_coords[1].y) std::swap(screen_coords[0], screen_coords[1]);
    if (screen_coords[0].y > screen_coords[2].y) std::swap(screen_coords[0], screen_coords[2]);
    if (screen_coords[1].y > screen_coords[2].y) std::swap(screen_coords[1], screen_coords[2]);
    for (int i = screen_coords[0].y; i < screen_coords[1].y; i++)
    {

    }
}

bool isValid(sf::Vector3f screen_coord)
{
    return screen_coord.x > 0 && screen_coord.x <= width && screen_coord.y > 0 && screen_coord.y < height;
}


void Thriangle(sf::Vector3f screen_coords[3], float colorPercent)
{



    if (!(isValid(screen_coords[0]) && isValid(screen_coords[1]) && isValid(screen_coords[2]))) return;
    if (screen_coords[0].y > screen_coords[1].y)
    {
        std::swap(screen_coords[0], screen_coords[1]);
    }

    if (screen_coords[0].y > screen_coords[2].y)
    {
        std::swap(screen_coords[0], screen_coords[2]);
    }
    if (screen_coords[1].y > screen_coords[2].y)
    {
        std::swap(screen_coords[1], screen_coords[2]);
    }


    for (int i = screen_coords[0].y; i < screen_coords[1].y; i++)
    {

        double Depth = 0, kDepth = 0;
        double t = (i - screen_coords[0].y) / (float)(screen_coords[1].y - screen_coords[0].y);
        int A = screen_coords[0].x * (1. - t) + screen_coords[1].x * t;
        double DepthA = screen_coords[0].z + (screen_coords[2].z - screen_coords[0].z) / (screen_coords[2].y - screen_coords[0].y) * (i - screen_coords[0].y);


        t = (i - screen_coords[0].y) / (float)(screen_coords[2].y - screen_coords[0].y);
        int B = screen_coords[0].x * (1. - t) + screen_coords[2].x * t;
        double DepthB = screen_coords[0].z + (screen_coords[1].z - screen_coords[0].z) / (screen_coords[1].y - screen_coords[0].y) * (i - screen_coords[0].y);
        if (A > B)
            swap(A, B);

        Depth = DepthA;
        for (int j = A; j <= B; j++)
        {
            if (j < 0 || i < 0 || j >= width || i >= height || PixDepth[i][j] >(Depth + (j - A) * (DepthB - DepthA)))
            {
                /*pixarray[i][j].b = 0xff * colorPercent;*/
                continue;
            }

            pixarray[i][j].g = 0xff * colorPercent;
            pixarray[i][j].r = 0x00 * colorPercent;
            pixarray[i][j].b = 0x00 * colorPercent;
            pixarray[i][j].t = 0xff;
            PixDepth[i][j] = Depth + (j - A) * (DepthB - DepthA);


        }
    }


    for (int i = screen_coords[1].y; i < screen_coords[2].y; i++)
    {
        double Depth = 0, kDepth = 0;
        double t = (i - screen_coords[1].y) / (float)(screen_coords[2].y - screen_coords[1].y);
        int A = screen_coords[1].x * (1. - t) + screen_coords[2].x * t;
        double DepthA = screen_coords[0].z + (screen_coords[2].z - screen_coords[0].z) / (screen_coords[2].y - screen_coords[0].y) * (i - screen_coords[0].y);

        t = (i - screen_coords[0].y) / (float)(screen_coords[2].y - screen_coords[0].y);
        int B = screen_coords[0].x * (1. - t) + screen_coords[2].x * t;
        double DepthB = screen_coords[1].z + (screen_coords[2].z - screen_coords[1].z) / (screen_coords[2].y - screen_coords[1].y) * (i - screen_coords[1].y);
        if (A > B)
            swap(A, B);
        Depth = DepthA;
        for (int j = A; j <= B; j++)
        {
            if (j < 0 || i < 0 || j >= width || i >= height || PixDepth[i][j] >(Depth + (j - A) * (DepthB - DepthA)))
            {
               /* pixarray[i][j].b = 0xff * colorPercent;*/
                continue;
            }
            pixarray[i][j].g = 0xff * colorPercent;
            pixarray[i][j].r = 0x00 * colorPercent;
            pixarray[i][j].b = 0x00 * colorPercent;
            pixarray[i][j].t = 0xff;
            PixDepth[i][j] = Depth + (j - A) * (DepthB - DepthA);
        }
    }

}

void line(sf::Vector3f firstPoint, sf::Vector3f secondPoint, Uint32 color)
{
    if (!(isValid(firstPoint) && isValid(secondPoint))) return;
    bool steep = false;
    double Depth = 0, kDepth = 0;

    if (std::abs(firstPoint.x - secondPoint.x) < std::abs(firstPoint.y - secondPoint.y)) {
        std::swap(secondPoint.x, secondPoint.y);
        std::swap(firstPoint.x, firstPoint.y);
        steep = true;
    }
    if (firstPoint.x > secondPoint.x) {
        std::swap(firstPoint, secondPoint);
    }
    for (int x = firstPoint.x; x < secondPoint.x; x++)
    {
        double t = (x - firstPoint.x) / (float)(secondPoint.x - firstPoint.x);
        Depth = firstPoint.z + (secondPoint.z - firstPoint.z) / (secondPoint.x - firstPoint.x) * (x - firstPoint.x);
        int y = firstPoint.y * (1. - t) + secondPoint.y * t;

        if (y < 0 || x < 0 || x >= width || y >= height || PixDepth[x][y]>Depth)
            continue;

        if (steep) {

            pixarray[x][y].r = color >> 6;
            pixarray[x][y].g = (color >> 4) % 256;
            pixarray[x][y].b = (color >> 2) % 256;
            pixarray[x][y].t = color % 256;
            PixDepth[x][y] = Depth;
        }
        else {
            pixarray[y][x].r = color >> 6;
            pixarray[y][x].g = (color >> 4) % 256;
            pixarray[y][x].b = (color >> 2) % 256;
            pixarray[y][x].t = color % 256;
            PixDepth[y][x] = Depth;
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
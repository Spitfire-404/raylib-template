#pragma once
#include "myMath.h"
#include <cmath>
#include <exception>
#include <fstream>
#include <iostream>
#include <raylib.h>
#include <string>
#include <vector>

class CustomException : public std::exception {
private:
  std::string message;

public:
  // Constructor accepting a custom error message
  explicit CustomException(const std::string &msg) : message(msg) {}

  // Override what() to return the error message
  const char *what() const noexcept override { return message.c_str(); }
};

struct Vertex {
  Vec3 pos;
  Vec2 screen;
  Vec3 normal;
};
struct texCoord : Vec2 {
  using Vec2::Vec2;

  texCoord() = default;
  explicit texCoord(const Vec2 &value) : Vec2(value) {}
};

class obj3d {
private:
    std::vector<Vertex> vertexArr;
    std::vector<texCoord> texArr;
    int vertexNum =0;

  // remember here int* is a int[3]
  std::vector<std::vector<int*>> faceArr;


public:
    const std::string name;
    Vec3 pos;
    Vec3 rot;

    int getVertexNun(){
        return vertexNum;
    }



  obj3d(const std::string &fileName)
  : obj3d(fileName, 0, 0, 0, 0, 0, 0) {}
  obj3d(const std::string &fileName, int x, int y, int z)
  : obj3d(fileName, x, y, z, 0, 0, 0) {}

  obj3d(const std::string &fileName, int x, int y, int z, int xR, int yR,
        int zR)
      : pos(x, y, z) {

    std::ifstream modelFile("src/models/" + fileName);
    if (!modelFile.is_open()) {
      throw CustomException("file read error: " + fileName);
    }
    // read into class
    std::string currentLine;
    while (std::getline(modelFile, currentLine)) {
      switch (currentLine[0]) {
      case '#':
        break;

      case 'v':
        vertexParse(currentLine);
        vertexNum++;
        break;

      case 'f':
        faceParse(currentLine);
        break;

      case 'l':
        lineParse(currentLine);
        break;

        // default:
        // throw CustomException("got bad line: " + currentLine);
      }
    }

    std::cout << "obj3d created from: " << fileName << '\n';
  };

  ~obj3d(){
      for(std::vector<int*> v : faceArr){
          for(int* arr : v){
              delete[] arr;
          }
      }
  }



      bool firstN = true;
  void vertexParse(std::string in) {

      int start = 2;

      switch (in[1]) {
          case ' ':
              break;
          case 'n':
              start++;
              if(firstN){
                  vertexNum = 0;
                  firstN = false;
              }
              break;
          case 't':
              start++;
              break;
          default:
              throw CustomException("not standard vert: " + in);
              return;
      }


    std::string temp;
    float vec[3];
    int i = 0;

    for (char c : in.substr(start)) {
      switch (c) {
      case ' ':
        vec[i] = std::stof(temp);
        i++;
        temp.clear();
        break;
      default:
        temp.push_back(c);
        break;
      }
    }
    vec[i] = std::stof(temp);

    switch (in[1]) {
        case ' ':
            vertexArr.push_back(Vertex{Vec3(vec), Vec2(), Vec3() });//Vec2()});
            break;
        case 'n':
            vertexArr[vertexNum].normal = Vec3(vec);
            break;
        case 't':
            texArr.push_back((texCoord)vec);
            vertexNum--;
            break;
    }
  };

  void faceParse(std::string in) {
    if (in[1] != ' ') {
      throw CustomException("not standard face: " + in);
      return;
    }

    // -1 is empty
    int arr[3] = {-1, -1, -1};
    std::vector<int*> temp;
    int i = 0;
    std::string value;

    for (char c : in.substr(2)) {
      if (c == '/' || c == ' ') {
        if (!value.empty()) {
          arr[i] = std::stoi(value);
          value.clear();
        }

        if (c == '/') {
          if (i < 2) {
            i++;
          }
        } else {
          temp.push_back(new int[3]{arr[0], arr[1], arr[2]});
          arr[0] = arr[1] = arr[2] = -1;
          i = 0;
        }
      } else {
        value.push_back(c);
      }
    }

    if (!value.empty()) {
      arr[i] = std::stoi(value);
    }
    temp.push_back(new int[3]{arr[0], arr[1], arr[2]});


    faceArr.push_back(temp);
  };
  void lineParse(std::string in) {
    throw CustomException("lines not implemented yet");
  };


  void scale(double in){
      for (std::size_t i = 0; i < vertexArr.size(); ++i) {
          vertexArr[i].pos.x *= in;
          vertexArr[i].pos.y *= in;
          vertexArr[i].pos.z *= in;
      }

      calcuationUpdate();
  }




  void draw() {
    std::cout << "drawCall for: " << this << std::endl;

    for(Vertex v : vertexArr){
        DrawPixel(v.screen.x, v.screen.y, BLACK);
    }
    for(std::vector<int*>v : faceArr){
        int index1 = v[0][0] - 1;
        int index2 = v[1][0] - 1;
        int index3 = v[2][0] - 1;

        DrawLine(vertexArr[index1].screen.x, vertexArr[index1].screen.y,
                 vertexArr[index2].screen.x, vertexArr[index2].screen.y, RED);

        DrawLine(vertexArr[index2].screen.x, vertexArr[index2].screen.y,
                 vertexArr[index3].screen.x, vertexArr[index3].screen.y, RED);

        DrawLine(vertexArr[index3].screen.x, vertexArr[index3].screen.y,
                 vertexArr[index1].screen.x, vertexArr[index1].screen.y, RED);

    }

  };
  void calcuationUpdate()
  {
      const float centerX = GetScreenWidth() * 0.5f;
      const float centerY = GetScreenHeight() * 0.5f;

      const float fovDegrees = 90.0f;
      const float fovRadians = fovDegrees * PI / 180.0f;

      const float focalLength =
          (GetScreenHeight() * 0.5f) / std::tan(fovRadians * 0.5f);
      const float nearPlane = 0.1f;

      for (std::size_t i = 0; i < vertexArr.size(); ++i) {
          const float cameraX = vertexArr[i].pos.x + pos.x;
          const float cameraY = vertexArr[i].pos.y + pos.y;
          const float cameraZ = vertexArr[i].pos.z + pos.z;

          if (cameraZ <= nearPlane) {
              // This point is on or behind the camera plane.
              continue;
          }
          //backface culling
          if(false){
              continue;
          }

          vertexArr[i].screen.x =
              centerX + cameraX * focalLength / cameraZ;

          vertexArr[i].screen.y =
              centerY - cameraY * focalLength / cameraZ;
      }
  }
};

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
};

struct TexCoord : Vec2 {
  using Vec2::Vec2;

  TexCoord() = default;
  explicit TexCoord(const Vec2 &value) : Vec2(value) {}
};

struct Triangle{
    Vertex* points[3] {nullptr,nullptr,nullptr};
    Vec3 normals[3];
    TexCoord texCoords[3];

    Triangle(Vertex* v[3], Vec3 n[3], TexCoord t[3])
    : points{v[0],v[1],v[2],}, normals{n[0],n[1],n[2],}, texCoords{t[0],t[1],t[2]} {}
};

class obj3d {
private:
    std::vector<Vertex> vertexArr;
    std::vector<Triangle> triArr;


public:
    const std::string name;
    Vec3 pos;
    Vec3 rot;
    double scale;





  obj3d(const std::string &fileName)
  : obj3d(fileName, 0, 0, 0, 0, 0, 0) {}
  obj3d(const std::string &fileName, int x, int y, int z)
  : obj3d(fileName, x, y, z, 0, 0, 0) {}

  obj3d(const std::string &fileName, int x, int y, int z, int xR, int yR,int zR): pos(x, y, z) {



    std::ifstream modelFile("src/models/" + fileName);
    if (!modelFile.is_open()) {
      throw CustomException("file read error: " + fileName);
    }


    std::vector<Vec3> tempNormalArr;
    std::vector<TexCoord> tempTexArr;
    bool firstN = true;
    const auto vertexParse = [this, &tempNormalArr, &tempTexArr](std::string in) {

        int start = 2;

        switch (in[1]) {
            case ' ':
                break;
            case 'n':
                start++;
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
              vertexArr.push_back(Vertex{Vec3(vec), Vec2()});
              break;
          case 'n':
              tempNormalArr.push_back(Vec3(vec));
              break;
          case 't':
              tempTexArr.push_back(TexCoord(Vec2(vec)));
              break;
      }
    };

    const auto faceParse = [this, &tempNormalArr, &tempTexArr](std::string in) {
      if (in[1] != ' ') {
        throw CustomException("not standard face: " + in);
        return;
      }



      Vertex* p[3];
      Vec3 n[3];
      TexCoord t[3];

      std::string value;

      int i = 0;
      int s = 0;

      const auto storeValue = [&]() {
          switch (s) {
              case 0:
                  p[i] = &vertexArr[std::stof(value) - 1];
                  break;
              case 1:
                  t[i] = tempTexArr[std::stof(value) - 1];
                  break;
              case 2:
                  n[i] = tempNormalArr[std::stof(value) - 1];
                  break;
          }
      };

      for (const char c : in.substr(2)) {
          switch (c) {
              case '/':
                  storeValue();
                  s++;
                  value.clear();
                  break;
              case ' ':
                  storeValue();
                  i++;
                  s = 0;
                  value.clear();
                  break;
              default:
                  value.push_back(c);
          }
      }
      storeValue();

      triArr.push_back(Triangle(p,n,t));

    };

    // read into class
    std::string currentLine;
    while (std::getline(modelFile, currentLine)) {
      switch (currentLine[0]) {
      case '#':
        break;

      case 'v':
        vertexParse(currentLine);
        break;

      case 'f':
        faceParse(currentLine);
        break;

        // default:
        // throw CustomException("got bad line: " + currentLine);
      }
    }




    std::cout << "obj3d created from: " << fileName << '\n';
  }






  enum axis{
      x,y,z
  };
  void rotate(axis a, double degrees){
      double rad = degrees*(PI/180);
      // wip
      switch (a) {
          case axis::x:
              // newY = y·cos(angle) - z·sin(angle)
              // newZ = y·sin(angle) + z·cos(angle)
              break;
          case axis::y:
              break;
          case axis::z:
              break;
      }
  }



  void draw() {
    std::cout << "drawCall for: " << this << std::endl;


    for(const Triangle& t : triArr){

        if(Dot(t.points[0]->pos+pos, t.normals[0]) >0){
            continue;
        }
        DrawLine(t.points[0]->screen.x, t.points[0]->screen.y,
                 t.points[1]->screen.x, t.points[1]->screen.y, RED);

        DrawLine(t.points[1]->screen.x, t.points[1]->screen.y,
                 t.points[2]->screen.x, t.points[2]->screen.y, RED);

        DrawLine(t.points[2]->screen.x, t.points[2]->screen.y,
                 t.points[0]->screen.x, t.points[0]->screen.y, RED);

    }

  }
  void calcuationUpdate()
  {
      /*
       original model position
               ↓
       rotation around the model origin/pivot
               ↓
       object translation (`pos`)
               ↓
       perspective projection
               ↓
       screen position
       */


      const float centerX = GetScreenWidth() * 0.5f;
      const float centerY = GetScreenHeight() * 0.5f;

      const float fovDegrees = 90.0f;
      const float fovRadians = fovDegrees * PI / 180.0f;

      const float focalLength =
          (GetScreenHeight() * 0.5f) / std::tan(fovRadians * 0.5f);
      const float nearPlane = 0.1f;



      for (Vertex& vReal : vertexArr) {

          Vertex temp = Vertex(vReal);

          temp.pos.x *= scale;
          temp.pos.y *= scale;
          temp.pos.z *= scale;


          temp.pos = temp.pos + this->pos;

          if (temp.pos.z <= nearPlane) {
              // This point is on or behind the camera plane.
              continue;
          }

          vReal.screen.x =
              centerX + temp.pos.x * focalLength / temp.pos.z;

          vReal.screen.y =
              centerY - temp.pos.y * focalLength / temp.pos.z;

      }
  }
};

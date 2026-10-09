#pragma once
#include "myMath.h"
#include <cstdlib>
#include <forward_list>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <raylib.h>
#include <string>
#include <thread>
#include <utility>
#include <vector>

using namespace std;

class CustomException : public std::exception {
private:
  std::string message;

public:
  // Constructor accepting a custom error message
  explicit CustomException(const std::string &msg) : message(msg) {}

  // Override what() to return the error message
  const char *what() const noexcept override { return message.c_str(); }
};

class obj3d {
private:
  std::vector<Vec3> vertexArr;
  // remember here int* is a int[3]
  std::vector<vector<int*>> faceArr;

  Vec3 pos;
  Vec3 rot;

public:
  obj3d(const std::string &fileName) : obj3d(fileName, 0, 0, 0, 0, 0, 0) {}
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
    string currentLine;
    while (getline(modelFile, currentLine)) {
      switch (currentLine[0]) {
      case '#':
        break;

      case 'v':
        vertexParse(currentLine);
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
      for(vector<int*> v : faceArr){
          for(int* arr : v){
              delete[] arr;
          }
      }
  }



  void vertexParse(string in) {
    if (in[1] != ' ') {
      //throw CustomException("not standard vert: " + in);
      return;
    }

    string temp;
    float vec[3];
    int i = 0;

    for (char c : in.substr(2)) {
      switch (c) {
      case ' ':
        vec[i] = std::stof(temp);
        // isNeg? -vec[i]:
        i++;
        temp.clear();
        break;
      default:
        temp.push_back(c);
        break;
      }
    }
    vec[i] = std::stof(temp);

    vertexArr.push_back(Vec3(vec));
  };
  void faceParse(string in) {
    if (in[1] != ' ') {
      throw CustomException("not standard face: " + in);
      return;
    }

    int arr[3] = {-1, -1, -1};
    vector<int*> temp;
    int i = 0;
    string value;

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
  void lineParse(string in) {
    throw CustomException("lines not implemented yet");
  };







  void draw() { cout << "drawCall for: " << this << endl; };
  void calcuationUpdate() {
    cout << "updateCall for: " << this << endl;
    cout << "verts:" << "\n";
    for (Vec3 v : vertexArr) {
      cout << v.toSting() << "\n";
    }
  };
};

class Renderer {
public:
  static const int CALC = 0;
  static const int DRAW = 1;

  forward_list<obj3d *> renderList;
  Renderer() {};

  void update(int call) {

    vector<thread> threads;
    for (obj3d *current : renderList) {

      thread t([current, call]() -> void {
        switch (call) {
        case CALC:
          current->calcuationUpdate();
          break;
        case DRAW:
          current->draw();
          break;
        }
      });
      t.detach();
    }

    for (thread &t : threads) {
      t.join();
    }
  };

  void add(obj3d *obj) { renderList.push_front(obj); }
};

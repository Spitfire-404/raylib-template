#pragma once
#include "myMath.h"
#include "obj3d.h"
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


class Renderer {
public:
  enum updateType{ CALC, DRAW };

  vector<obj3d *> renderList;
  Renderer() {};

  void update(updateType call) {

    vector<thread> threads;
    for (obj3d *current : renderList) {

      threads.emplace_back(
          ([current, call]() -> void
                {
                switch (call) {
                case CALC:
                  current->calcuationUpdate();
                  break;
                case DRAW:
                  current->draw();
                  break;
                }
          })
      );

    }

    for (thread &t : threads) {
      t.join();
    }
  };

  void add(obj3d *obj) { renderList.push_back(obj); }
};

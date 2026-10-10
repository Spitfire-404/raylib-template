#pragma once
#include "obj3d.h"
#include <thread>
#include <vector>

class Renderer {
public:
  enum updateType{ CALC, DRAW };

  std::vector<obj3d *> renderList;
  Renderer() {};

  void update(updateType call) {

    std::vector<std::thread> threads;
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

    for (std::thread &t : threads) {
      t.join();
    }
  };

  void add(obj3d *obj) { renderList.push_back(obj); }
};

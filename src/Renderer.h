#pragma once
#include <raylib.h>
#include <myMath.h>
#include <string>
#include <iostream>
#include "linkedList.h"

using namespace std;


class obj3d{
    public:
    obj3d(){};
    obj3d(string fileName){
        cout << "obj3d created from: " << fileName << endl;
    };
    void draw(){
        cout << "drawCall for: " << this << endl;
    };
};

class Renderer{
    public:
    linkedList<obj3d> renderList;
    Renderer(){};

    void update(){
        linkedList<obj3d> current;
        current.next = &renderList;
        while (current.next != nullptr)
        {
            current = *current.next;

            current.value.draw();
        }
        
    };

    void add(obj3d obj){
        renderList.append(obj);
    }

};
#pragma once
#include <raylib.h>
#include <myMath.h>
#include <string>
#include <iostream>
#include <vector>
#include "linkedList.h"

using namespace std;


class obj3d{
    private:
    vector<Vec3> vertexArr;
    string file;

    public:
    obj3d(string fileName): file(fileName){



        cout << "obj3d created from: " << fileName << endl;
    };
    void draw(){
        cout << "drawCall for: " << this->file << endl;
    };
    void update(){
        cout << "updateCall for: " << this->file << endl;
    };
    
};

class Renderer{
    public:
    linkedList<obj3d>* renderList = nullptr;
    Renderer(){};

    void update(){
        if(renderList==nullptr) return;

        linkedList<obj3d> *current = renderList;
        while (current != nullptr)
        {
            current->value.update();
            current = current->next;
        }

    };

    void add(obj3d obj){
        linkedList<obj3d>::add(renderList, obj);
    }

};
#pragma once
#include <raylib.h>
#include <myMath.h>
#include <string>
#include <iostream>
#include <vector>
#include <thread>
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
    void calcuationUpdate(){
        cout << "updateCall for: " << this->file << endl;
    };
    
};

class Renderer{
    public:
    static const int CALC = 0;
    static const int DRAW = 1;
    
    linkedList<obj3d>* renderList = nullptr;
    Renderer(){};

    void update(int call){
        if(renderList==nullptr) return;

        linkedList<obj3d> *current = renderList;

        vector<thread> threads;
        while (current != nullptr)
        {

            thread t
            (
                [current, call]()-> void{
                    switch (call)
                    {
                    case CALC:
                        current->value.calcuationUpdate();
                        break;
                    case DRAW:
                        current->value.draw();
                        break;
                    }

                }
            );
            t.detach();
            current = current->next;
        }

        for(thread& t: threads){
            t.join();
        }


    };

    void add(obj3d obj){
        linkedList<obj3d>::add(renderList, obj);
    }

};
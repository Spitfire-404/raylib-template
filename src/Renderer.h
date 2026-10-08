#pragma once
#include <raylib.h>
#include "myMath.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <utility>
#include "linkedList.h"

using namespace std;

class CustomException : public std::exception {
private:
    std::string message;

public:
    // Constructor accepting a custom error message
    explicit CustomException(const std::string& msg) : message(msg) {}

    // Override what() to return the error message
    const char* what() const noexcept override {
        return message.c_str();
    }
};


  class obj3d {
private:
    std::vector<Vec3> vertexArr;
    std::vector<Vec3> lineArr;
    std::vector<Vec3> faceArr;

    Vec3 pos;
    Vec3 rot;

    public:
    obj3d(const std::string& fileName)
    {obj3d(fileName, 0,0,0, 0,0,0);};
    obj3d(const std::string& fileName, int x, int y, int z)
    {obj3d(fileName, x,y,z, 0,0,0);};
    obj3d(const std::string& fileName, int x, int y, int z, int xR, int yR, int zR): pos(x,y,z)
    {
        std::ifstream modelFile("src/models/"+fileName);
        if(!modelFile.is_open()){
            throw CustomException("file read error: "+ fileName);
        }
        // read into class
        string currentLine;
        while (getline(modelFile, currentLine))
        {
            switch (currentLine[0])
            {
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

                //default:
                //throw CustomException("got bad line: " + currentLine);

            }

        }




        std::cout << "obj3d created from: " << fileName << '\n';
    };
    void vertexParse(string in){
        if (in[1] != ' '){
            throw CustomException("not standard vert: "+in);
            return;
        }

        string temp;
        float vec[3];
        int i = 0;
        bool isNeg = false;
        for (char c : in.substr(2)) {
            switch (c) {
                case ' ':
                done:
                    vec[i] = std::stof(temp);
                    //isNeg? -vec[i]:
                    i++;
                    isNeg = false;
                    temp.clear();
                    break;
                case '-':
                    isNeg = true;
                default:
                    temp.push_back(c);
                    break;
            }
        }
        //goto done;
        vertexArr.push_back(Vec3(vec));

    };
    void faceParse  (string in){

    };
    void lineParse  (string in){

    };



    void draw(){
        cout << "drawCall for: " << this << endl;
    };
    void calcuationUpdate(){
        cout << "updateCall for: " << this << endl;
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
        thread(
            [=]()->void{
                linkedList<obj3d>::add(renderList, obj);

            }
        ).detach();
    }

};

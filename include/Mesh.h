//
// Created by Marco Otero on 2/22/25.
//

#ifndef MESH_H
#define MESH_H
#include <glad/glad.h>
#include <vector>
#include <iostream>

using std::vector;

class Mesh {
private:
    //basically series of numbers, think of as unsigned int
    // Reference containers for the Vartex Array Object, the Vertex Buffer Object, and the Element Buffer Object
    GLuint VAO, VBO, EBO;
    std::vector<float> vertices;
    std::vector<GLuint> indices;

public:
    //vertices are float because window is from (-1.0,-1.0) --> (1,1)
    //indices is only positive nums
    Mesh(const vector<float>& vertices,const vector<GLuint>& indices);
    ~Mesh();
    void loadVertices(const vector<float>& vertices);
    void setupMesh();
    void render() const;
};



#endif //MESH_H

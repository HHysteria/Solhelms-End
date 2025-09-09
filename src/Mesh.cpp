//
// Created by Marco Otero on 2/22/25.
//

#include "Mesh.h"

Mesh::Mesh(const vector<float> &vertices, const vector<GLuint> &indices) : vertices(vertices), indices(indices)
{
    setupMesh();
}

Mesh::~Mesh()
{
    //Have to delete VAO,VBO,and EBO created
    //I dont fucking know why but God says so
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(1, &this->VBO);
    glDeleteBuffers(1, &this->EBO);
}

void Mesh::loadVertices(const vector<float> &vertices) {
    //changes private member
    this->vertices = vertices;

    // Update the VBO with the new vertex data
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(float), vertices.data());
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::setupMesh() {
    //Generate buffers with only one object in each
    glGenVertexArrays(1, &this->VAO); //Vertex Array Object
    glGenBuffers(1, &this->VBO); //Vertex Buffer Object
    glGenBuffers(1, &this->EBO); //Element Buffer Object

    /*
     * first line, Binding of the VAO
     * second line, Binding of the VBO and upload buffer data (i.e. the number vertices)
     * third line, Binding of the EBO and upload buffer data (i.e. the number of indices in vertices)
     */

    glBindVertexArray(this->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    /*
     * Configure vertex attributes
     *
     * first line, configures the VERTEX ATTRIBUTE so openGL can read VBO
     * second line, Enable the VERTEX ATTRIBUTE so that OpenGL knows to use it
     */

    // Configure vertex attributes
    // Position attribute (3 floats)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Texture coordinate attribute (2 floats)
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //Unbind buffers, have to unbind in this order because of the way uploaded it
    glBindBuffer(GL_ARRAY_BUFFER, 0);            //VBO
    glBindVertexArray(0);                               //VAO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);    //EBO
}

void Mesh::render() const {
    //Bind VAO
    glBindVertexArray(this->VAO);

    //Draw the stuff, count should be size of indices vector
    glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, nullptr);

    //Unbind VAO
    glBindVertexArray(0);
}

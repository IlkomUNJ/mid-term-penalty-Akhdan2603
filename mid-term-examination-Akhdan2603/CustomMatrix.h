#ifndef CUSTOMMATRIX_H
#define CUSTOMMATRIX_H

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

class CustomMatrix{

public:
    bool mat[3][3]={0};

    CustomMatrix(){
        // Default constructor initializes to all false
    }

<<<<<<< HEAD
<<<<<<< HEAD
    // Alternate way to instantiate the class
    CustomMatrix(bool m[3][3]){
        for (int i=0; i<3; i++) {
            for(int j=0; j<3; j++){
=======
=======
>>>>>>> origin
    CustomMatrix(bool m[3][3]){
        const int m_size = sizeof(m) / sizeof(m[0]);
        for (int i=0;i< m_size;i++) {
            for(int j=0; j < sizeof(m[0]);j++){
<<<<<<< HEAD
>>>>>>> ac2c49d7612f40d7c84d890309aef828ac9af1c2
=======
>>>>>>> origin
                mat[i][j] = m[i][j];
            }
        }
    }

    void fillMatrix(bool m[3][3]){
<<<<<<< HEAD
        for (int i=0; i<3; i++) {
            for(int j=0; j<3; j++){
=======
        const int m_size = sizeof(m) / sizeof(m[0]);
        for (int i=0;i< m_size;i++) {
            for(int j=0; j < sizeof(m[0]);j++){
<<<<<<< HEAD
>>>>>>> ac2c49d7612f40d7c84d890309aef828ac9af1c2
=======
>>>>>>> origin
                mat[i][j] = m[i][j];
            }
        }
    }

    // Check if matrix is empty (all false)
    bool isEmpty() const {
        for (int i=0; i<3; i++) {
            for(int j=0; j<3; j++){
                if(mat[i][j]) return false;
            }
        }
        return true;
    }

    // Print matrix for debugging
    void print() const {
        for (int i=0; i<3; i++) {
            for(int j=0; j<3; j++){
                cout << mat[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Compare with another matrix
    bool equals(const CustomMatrix& other) const {
        for (int i=0; i<3; i++) {
            for(int j=0; j<3; j++){
                if(mat[i][j] != other.mat[i][j]) return false;
            }
        }
        return true;
    }

    // Calculate similarity percentage with another matrix
    float similarity(const CustomMatrix& other) const {
        int matchCount = 0;
        for (int i=0; i<3; i++) {
            for(int j=0; j<3; j++){
                if(mat[i][j] == other.mat[i][j]) matchCount++;
            }
        }
        return (float)matchCount / 9.0f;
    }

};

#endif

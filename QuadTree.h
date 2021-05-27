#include "Node.h"
#include <vector>

class QuadTree {
private:
    Node* root;
    int height;
    int width;
    int maxVal;
    
    vector<vector<vector<Point >>> divideIntoQuadrants(const vector<vector<Point>> &pixels) const {
        vector<vector<vector<Point>>> fourQuadrants;

        int extraRow = 0, extraColumn = 0;
        if(height % 2 != 0)
            ++extraRow;

        if(width % 2 != 0)
            ++extraColumn;

        for (int i = 0; i < height - extraRow; i+= height / 2 ) {
            for (int j = 0; j < width - extraColumn; j+= width / 2 ){
                vector<vector<Point>> matrix;
                for (int k = i; k < height / 2 + i + (i != 0 and extraRow); ++k) {
                    vector<Point> row;
                    for (int l = j; l < width / 2 + j + (j != 0 and extraColumn); ++l) {
                        row.push_back(pixels[k][l]);
                        cout << pixels[k][l].value << " ";
                    }
                    matrix.push_back(row);
                    row.clear();
                    cout << endl;
                }
                cout<<"+++++" << endl;
                fourQuadrants.push_back(matrix);
                matrix.clear();
            }
        }
        return fourQuadrants;
    }
    
    double averageOfMatrix(const vector<vector<Point>> &pixels){
        double sum = 0;
        double count = 0;
        for(int k = 0 ; k < pixels.size() ; ++k ){
            for(int l = 0 ; l < pixels[0].size() ; ++l ){
                sum += pixels[k][l].value;
                ++count;
            }
        }
        if(count == 1)
            return -1;
        
        return sum/count;
    }

    vector<vector<Point>> integerToPoints(vector<vector<int>> pixels){
        vector<vector<Point>> result;
        for(int k = 0 ; k < pixels.size() ; ++k ){
            vector<Point> row;
            for(int l = 0 ; l < pixels[0].size() ; ++l ){
                Point temp(k,l,pixels[k][l]);
                row.push_back(temp);
            }
            result.push_back(row);
            row.clear();
        }
        return result;
    }


public:

    QuadTree(int width, int height, int maxVal, vector<vector<int>> pixels) {
        this->width = width;
        this->height = height;
        this->maxVal = maxVal;
        build(integerToPoints(pixels));
    }
    
    void print(vector<vector<int>> pixels){
        for(int k = 0 ; k < pixels.size() ; ++k ){
            for(int l = 0 ; l < pixels[0].size() ; ++l ){
                cout << pixels[k][l] << " ";
            }
            cout << endl;
        }
    }


    void build(vector<vector<Point>> pixels) {            
        vector<vector<vector<Point >>> fourQuadrants = divideIntoQuadrants(pixels);
        cout << endl << "wiii -> " << calculateQuadrantNumber(fourQuadrants[1][0][0],height,width)<< " x:"<< fourQuadrants[1][0][0].x << " y:"<< fourQuadrants[1][0][0].y;
        cout << "\nh: " << height << " \nwidth: " << width;
        root = insert(root, pixels);
    }

    Node* insert(Node* node, vector<vector<Point>> pixels){
        if(node == nullptr){
            node = new Node();
        }else {
            vector<vector<vector<Point >>> fourQuadrants = divideIntoQuadrants(pixels);
            for (int i = 0; i < 4; ++i) {
                recursiveInsert(node, fourQuadrants[i], i);
            }
        }
        return node;
    }
    
    Node* recursiveInsert(Node* node, vector<vector<Point>> quadrant, int nq){
        double average = averageOfMatrix(quadrant);
        if (average == 0 || average== this->maxVal) {
            Point t(quadrant[0][0].x, quadrant[0][0].y, average);
            node->getTurn(nq) = new Node(t); //valor 0
        } else {
           // node = recursiveInsert(node->getTurn(nq),);
            //continuar la recursión
        }
    }
    
    int calculateQuadrantNumber(Point pixel, int h, int w){
        int halfW = w/2;
        int halfH = h/2;
        
        if(pixel.x < halfW && pixel.y < halfH){
            return 0;
        } else if(pixel.x >= halfW && pixel.y < halfH){
            return 1;
        } else if(pixel.x < halfW && pixel.y >= halfH){
            return 2;
        } else if(pixel.x >= halfW && pixel.y >= halfH){
            return 3;
        }
        return -1;
    }
    
    
    








};
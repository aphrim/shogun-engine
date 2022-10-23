#include "obj.hpp"

namespace SHOGUN {

void addVert(std::vector<float>* ret, std::vector<float>& vertexPositions, std::vector<float>& textureCords, std::vector<float>& normals, int vertexI, int textureI, int normalI)
{
    ret->push_back(vertexPositions[vertexI * 3]);
    ret->push_back(vertexPositions[vertexI * 3 + 1]);
    ret->push_back(vertexPositions[vertexI * 3 + 2]);

    if (normalI != -1) {
        ret->push_back(normals[normalI * 3]);
        ret->push_back(normals[normalI * 3 + 1]);
        ret->push_back(normals[normalI * 3 + 2]);
    } else {
        ret->push_back(0);
        ret->push_back(0);
        ret->push_back(0);
    }

    if (textureI != -1) {
        ret->push_back(textureCords[textureI * 2]);
        ret->push_back(textureCords[textureI * 2 + 1]);
    } else {
        ret->push_back(0);
        ret->push_back(0);
    }
}

std::vector<float> OBJParser::parseObj(const char* objPath) {
    std::stringstream objData;

    try {
        std::ifstream objFile; 
        objFile.open(objPath);

        objData << objFile.rdbuf();
        objFile.close();
    }
    catch(std::ifstream::failure e)
    {
        std::cout << "Invalid model path or something it didn't read" << std::endl;
    }

    std::vector<float> vertexPositions{0,0,0}, textureCords {0,0}, normals{0, 0, 0};
    std::vector<std::vector<std::pair<int, std::pair<int, int>>>> polygons;

    std::string curLine;
    while (getline(objData, curLine)) {
        if (curLine.size() == 0) continue;
        if (curLine[0] == '#') continue;

        std::stringstream lineStream(curLine);
        char c;

        if (curLine[0] == 'v') {
            if (curLine[1] == 't') {
                float u, v;
                lineStream >> c >> c >> u >> v;
                textureCords.push_back(u);
                textureCords.push_back(v);
            } else if (curLine[1] == 'n') {
                float x, y, z;
                lineStream >> c >> c >> x >> y >> z;
                normals.push_back(x);
                normals.push_back(y);
                normals.push_back(z);
            } else if (curLine[1] == ' ') {
                float x, y, z;
                lineStream >> c >> x >> y >> z;
                vertexPositions.push_back(x);
                vertexPositions.push_back(y);
                vertexPositions.push_back(z);
            }
        }
        if (curLine[0] == 'f') {
            polygons.push_back(std::vector<std::pair<int, std::pair<int, int>>>());
            lineStream >> c;
            while (true) {
                std::pair<int, std::pair<int, int>> p(0,{-1, -1});
                std::string v;
                lineStream >> v;
                if (v == "") break;
                std::stringstream vstream(v);

                vstream >> p.first;
                if (v.find("/") != std::string::npos && v.find("//") == std::string::npos) {
                    vstream >> c >> p.second.first;
                    if (v.find("/", v.find("/") + 1) != std::string::npos) {
                        vstream >> c >> p.second.second;
                    }
                }
                polygons.back().push_back(p);
            }
        }
    }

    std::vector<float> ret;

    for (std::vector<std::pair<int, std::pair<int, int>>> polygon : polygons) {
        for (int i = 2; i < polygon.size(); i++) {
            addVert(&ret, vertexPositions, textureCords, normals, polygon[0].first, polygon[0].second.first, polygon[0].second.second);
            addVert(&ret, vertexPositions, textureCords, normals, polygon[i-1].first, polygon[i-1].second.first, polygon[i-1].second.second);
            addVert(&ret, vertexPositions, textureCords, normals, polygon[i].first, polygon[i].second.first, polygon[i].second.second);
        }
    }

    return ret;
}

}


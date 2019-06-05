//C++ source code to read stl file and mapping it to vertexes, colors and faces.
//VIETNAM National University HCM - University Of Information Technology

//=========================================================================
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <future>
#include "mex.h"

using namespace std;

#define kVERTEX "vertex"
#define kCOLOR "color"

struct ModelData {
  std::vector<double> vertexes;
  std::vector<double> colors;
  std::vector<double> faces;

  int getNumberOfVertexes() {
    return vertexes.size() / 3;
  }

  void setFaces() {
    faces.clear();
    int size = vertexes.size() / 3;
    for (int i = 1; i <= size; i++)
      faces.push_back(i);
  }

  void setColorsIfNotExists() {
    if (colors.size() == 0) {
      int numberOfVertexes = getNumberOfVertexes();
      for(int i = 0; i < numberOfVertexes; i++) {
        colors.push_back(0.2980); //R
        colors.push_back(0.5725); //G
        colors.push_back(0.6863); //B
      }
    }
  }
};

vector<string> split(const string& str, const string& delim);

void getDataInLine(string stringInLine, string key, vector<double> &data) {
  std::vector<string> vString = split(stringInLine, " ");
  for (auto i = vString.cbegin(); i != vString.cend(); ++i)
  {
    string dataString = *i;
    if (dataString.find(key) == std::string::npos) {
      data.push_back(stod(dataString.c_str()));
    }
  }
}

vector<string> split(const string& str, const string& delim) {
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}

ModelData retrieveData(string fileName) {
  string line;
  ifstream myfile (fileName);
  ModelData data;

  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      if (line.find(kVERTEX) != std::string::npos) {
        getDataInLine(line, kVERTEX, data.vertexes);
      } else if (line.find(kCOLOR) != std::string::npos) {
        getDataInLine(line, kCOLOR, data.colors);
      }
    }
    data.setFaces();
    data.setColorsIfNotExists();
    myfile.close();
  }
  else cout << "Unable to open file";

  return data;
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    //---------------------------------------------------------------------
    //Get filePath input from Matlab
    //---------------------------------------------------------------------
    char* filePath = mxArrayToString(prhs[0]);
    //---------------------------------------------------------------------
    //Use future in c++ to run async task to retrieve data from file path
    //---------------------------------------------------------------------
    std::future<ModelData> futureTask = std::async(retrieveData,filePath);
    
    ModelData data = futureTask.get();
    //---------------------------------------------------------------------
    //Because the data.vertexes is now array not nx3 matrix, so we want to 
    //get n then divide 3
    //nx3 matrix match with nxvector, which vector structure x,y,z
    //---------------------------------------------------------------------
    int numberOfVertexes = data.vertexes.size() / 3;

    plhs[0]=mxCreateDoubleMatrix(3, numberOfVertexes, mxREAL);    //vertexes
    plhs[1]=mxCreateDoubleMatrix(3, numberOfVertexes, mxREAL);    //colors
    plhs[2]=mxCreateDoubleMatrix(3, numberOfVertexes / 3,mxREAL); //faces

    double* vertexes = mxGetPr(plhs[0]);
    double* colors = mxGetPr(plhs[1]);
    double* faces = mxGetPr(plhs[2]);
    //---------------------------------------------------------------------
    //fill Output
    //---------------------------------------------------------------------
    std::copy(data.vertexes.begin(), data.vertexes.end(), vertexes);
    std::copy(data.colors.begin(), data.colors.end(), colors);
    std::copy(data.faces.begin(), data.faces.end(), faces);
}


//-----------------------------------------------------------------------------
// Copyright (c) 2007 dhpoware. All Rights Reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------
//
// The methods normalize() and scale() are based on source code from
// http://www.mvps.org/directx/articles/scalemesh9.htm.
//
// The addVertex() method is based on source code from the Direct3D MeshFromOBJ
// sample found in the DirectX SDK.
//
// The generateTangents() method is based on public source code from
// http://www.terathon.com/code/tangent.php.
//
// The importGeometryFirstPass(), importGeometrySecondPass(), and
// importMaterials() methods are based on source code from Nate Robins' OpenGL
// Tutors programs (http://www.xmission.com/~nate/tutors.html).
//
//-----------------------------------------------------------------------------

#include <algorithm>
#include <cmath>
#include <cstring>
#include <limits>
#include <string>
#include "model_obj.h"
#include "fstream.h"

int totalVertices;

char outPutFilename;

using std::ios;


float COLLISION_BOUNDS[6];


namespace
{
    bool MeshCompFunc(const ModelOBJ::Mesh &lhs, const ModelOBJ::Mesh &rhs)
    {
        return lhs.pMaterial->alpha > rhs.pMaterial->alpha;
    }
}
#include "fstream.h"
ModelOBJ::ModelOBJ()
{
    m_hasPositions = true;
    m_hasNormals = true;
    m_hasTextureCoords = true;
    m_hasTangents = true;

    m_numberOfVertexCoords = 0;
    m_numberOfTextureCoords = 0;
    m_numberOfNormals = 0;
    m_numberOfTriangles = 0;
    m_numberOfMaterials = 0;
    m_numberOfMeshes = 0;

    m_center[0] = m_center[1] = m_center[2] = 0.0f;
    m_width = m_height = m_length = m_radius = 0.0f;

	



}

ModelOBJ::~ModelOBJ()
{
    destroy();
}

void ModelOBJ::bounds(float center[3], float &width, float &height,
                      float &length, float &radius) const
{
    float xMax = std::numeric_limits<float>::min();
    float yMax = std::numeric_limits<float>::min();
    float zMax = std::numeric_limits<float>::min();

    float xMin = std::numeric_limits<float>::max();
    float yMin = std::numeric_limits<float>::max();
    float zMin = std::numeric_limits<float>::max();

    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

    int numVerts = static_cast<int>(m_vertexBuffer.size());



   
    for (int i = 0; i < numVerts; ++i)
    {
        x = m_vertexBuffer[i].position[0];
        y = m_vertexBuffer[i].position[1];
        z = m_vertexBuffer[i].position[2];

        if (x < xMin)
            xMin = x;

        if (x > xMax)
            xMax = x;

        if (y < yMin)
            yMin = y;

        if (y > yMax)
            yMax = y;

        if (z < zMin)
            zMin = z;

        if (z > zMax)
            zMax = z;
    }

    center[0] = (xMin + xMax) / 2.0f;
    center[1] = (yMin + yMax) / 2.0f;
    center[2] = (zMin + zMax) / 2.0f;

    width = xMax - xMin;
    height = yMax - yMin;
    length = zMax - zMin;


COLLISION_BOUNDS[0] = xMin;
COLLISION_BOUNDS[1] = xMax;
COLLISION_BOUNDS[2] = yMin;
COLLISION_BOUNDS[3] = yMax;
COLLISION_BOUNDS[4] = zMin;
COLLISION_BOUNDS[5] = zMax;



    radius = std::max(std::max(width, height), length);


  
    
}



bool ModelOBJ::import(const char *pszFilename, bool rebuildNormals)
{



    FILE *pFile = fopen(pszFilename, "r");

    if (!pFile)
        return false;

    // Extract the directory the OBJ file is in from the file name.
    // This directory path will be used to load the OBJ's associated MTL file.

    m_directoryPath.clear();

    std::string filename = pszFilename;
    std::string::size_type offset = filename.find_last_of('\\');

    if (offset != std::string::npos)
    {
        m_directoryPath = filename.substr(0, ++offset);
    }
    else
    {
        offset = filename.find_last_of('/');

        if (offset != std::string::npos)
            m_directoryPath = filename.substr(0, ++offset);
    }

//==========================================================================================
int sizeOfDirectory = m_directoryPath.size();  
int sizeOfTotalPath = filename.size();  

int sizeOfFilename = sizeOfTotalPath - sizeOfDirectory;

std:: string passFilename(filename, sizeOfDirectory, sizeOfFilename-4);
//=================================================================================================================   
    importGeometryFirstPass(pFile);
    rewind(pFile);
    importGeometrySecondPass(pFile);
    fclose(pFile);
    buildMeshes();
    bounds(m_center, m_width, m_height, m_length, m_radius);
//=================================================================================================================
generateTangents();
totalVertices = getNumberOfVertices();
//=================================================================================================================


std::string makeDirectory = "MKDIR ";
std::string fileName_makeDirectory = makeDirectory + passFilename;
const char * fileName_makeDirectory_OUT = fileName_makeDirectory.c_str();
system(fileName_makeDirectory_OUT);
//####################################################################################################################################
//####################################################################################################################################
//#################################################################################################################################### 
//####################################################################################################################################
//####################################################################################################################################
//####################################################################################################################################
std::string INDICES = "_INDICES.cpp";
std::string fileName_INDICES = passFilename + "/" + passFilename + INDICES;
const char * fileName_INDICES_OUT = fileName_INDICES.c_str();
ofstream outIndices(fileName_INDICES_OUT);

    outIndices << "GLuint " << passFilename << "_INDICES[] = \n" << "{\n"  << "     //number of vertices = " << static_cast<int>(m_indexBuffer.size()) << "\n\n";   
    
    for (int i = 0; i < static_cast<int>(m_indexBuffer.size()); i += 3)
    {
        outIndices << m_indexBuffer[i + 0] << ", ";
        outIndices << m_indexBuffer[i + 1]<< ", ";
        outIndices << m_indexBuffer[i + 2] << ",\n"; 
    } 
outIndices << "};\n";     
//------------------------------------------------------------------------------     
//####################################################################################################################################
//####################################################################################################################################
//#################################################################################################################################### 
//####################################################################################################################################
//####################################################################################################################################
//####################################################################################################################################
std::string VERTICES = ".cpp";
std::string fileName_VERTICES = passFilename + "/" + passFilename + VERTICES;
const char * fileName_VERTICES_OUT = fileName_VERTICES.c_str();
ofstream outVertices(fileName_VERTICES_OUT);

    outVertices << "GLfloat " << passFilename << "[] = \n" << "{\n"  << "     //number of vertices = " << static_cast<int>(m_indexBuffer.size()) << "\n\n";   

    const float *pNormal = 0;   
    const float *pTangent = 0;   
    const float *pBitangent = 0;    
    
    int numVerts = static_cast<int>(m_vertexBuffer.size());    
   
    for (int i = 0; i < numVerts; ++i)
    {
        outVertices << m_vertexBuffer[i].position[0] << ",";
        outVertices << m_vertexBuffer[i].position[1] << ",";
        outVertices << m_vertexBuffer[i].position[2] << ",";
        //--------------------------------------------------
        pNormal = m_vertexBuffer[i].normal;
        
        outVertices << pNormal[0] << ",";
        outVertices << pNormal[1] << ",";
        outVertices << pNormal[2] << ",";  
        //--------------------------------------------------         
        pTangent = m_vertexBuffer[i].tangent;
        
        //outVertices << pTangent[0] << ", ";
        //outVertices << pTangent[1] << ", ";
        //outVertices << pTangent[2] << ", "; 
        //--------------------------------------------------          
        pBitangent = m_vertexBuffer[i].bitangent;       //pVertex0->bitangent[0]
        
        //outVertices << pBitangent[0] * -1.0 << ", ";
        //outVertices << pBitangent[1] * -1.0  << ", ";
        //outVertices << pBitangent[2] * -1.0  << ", "; 
        //--------------------------------------------------          
        
        outVertices << m_vertexBuffer[i].texCoord[0] << ", ";
        outVertices << m_vertexBuffer[i].texCoord[1] << ",\n";    
    }
outVertices << "};\n";  

//####################################################################################################################################
//####################################################################################################################################
//####################################################################################################################################


//####################################################################################################################################
//####################################################################################################################################
//####################################################################################################################################
std::string GLOBALS = "_GLOBALS.cpp";
std::string fileName_GLOBALS = passFilename + "/" + passFilename + GLOBALS;
const char * fileName_GLOBALS_OUT = fileName_GLOBALS.c_str();
ofstream out_Globals(fileName_GLOBALS_OUT);

         out_Globals << "GLfloat     " << passFilename << "_POSITION[]            =  {  0.0, 0.0, 0.0, 1.0};                                                                   "        << "\n";
         out_Globals << "GLfloat     " << passFilename << "_ROTATE[]              =  {  0.0, 1.0,  0.0, 0.0};                                                                  "        << "\n";  
         out_Globals << "GLfloat     " << passFilename << "_SCALE[]               =  {  1.0, 1.0,  1.0, 1.0};                                                                  "        << "\n";          
         out_Globals << "//-----------------------------------------------------------------                                                                                   "        << "\n";         
         out_Globals << "GLfloat     " << passFilename << "_LIGHT_POSITION_01[]   =  {  2.0, 15.0, 30.0, 1.0};                                                                 "        << "\n";           
         out_Globals << "GLfloat     " << passFilename << "_SHININESS             =    80.0;                                                                                   "        << "\n";   
         out_Globals << "GLfloat     " << passFilename << "_ATTENUATION           =     1.0;                                                                                   "        << "\n";         
         out_Globals << "//-----------------------------------------------------------------                                                                                   "        << "\n";
         out_Globals << "GLuint      " << passFilename << "_VBO;                                                                                                               "        << "\n";             
         out_Globals << "GLuint      " << passFilename << "_INDICES_VBO;                                                                                                       "        << "\n";             
         out_Globals << "//-----------------------------------------------------------------                                                                                   "        << "\n";         
         out_Globals << "GLuint      " << passFilename << "_NORMALMAP;                                                                                                         "        << "\n";
         out_Globals << "GLuint      " << passFilename << "_TEXTUREMAP;                                                                                                        "        << "\n"; 

         out_Globals << "//====================================================================================   "        <<"\n";       
         out_Globals << "GLfloat " << passFilename << "_boundingBox[6]; "                                                 <<"\n";   

//####################################################################################################################################
//####################################################################################################################################
//####################################################################################################################################
std::string INIT = "_INIT.cpp";
std::string fileName_INIT = passFilename + "/" + passFilename + INIT;
const char * fileName_INIT_OUT = fileName_INIT.c_str();
ofstream out_Init(fileName_INIT_OUT);

         out_Init << "        //------------------------------------------------------------------------------------------                                                       "        << "\n";
         out_Init << "        #ifdef __APPLE__                                                                                                                                   "        << "\n";
         out_Init << "        //---------------                                                                                                                                  "        << "\n";
         out_Init << "        filePathName = [[NSBundle mainBundle] pathForResource:@\"" << passFilename << "_DOT3\" ofType:@\"bmp\"];                                           "        << "\n";
         out_Init << "        if(filePathName != nil)                                                                                                                                "        << "\n";        
         out_Init << "        {                                                                                                                                                  "        << "\n";  
         out_Init << "                image = imgLoadImage([filePathName cStringUsingEncoding:NSASCIIStringEncoding]);                                                           "        << "\n";
         out_Init << "                glGenTextures(1, &" << passFilename << "_NORMALMAP);                                                                                       "        << "\n";
         out_Init << "                glBindTexture(GL_TEXTURE_2D, " << passFilename << "_NORMALMAP);                                                                            "        << "\n";
         out_Init << "                ConfigureAndLoadTexture(image->data,  image->width, image->height );                                                                       "        << "\n";
         out_Init << "                imgDestroyImage(image);                                                                                                                    "        << "\n";
         out_Init << "        }else                                                                                                                                              "        << "\n";         
         out_Init << "            {                                                                                                                                              "        << "\n";        
         out_Init << "               //add error file output here                                                                                                                "        << "\n";          
         out_Init << "            }                                                                                                                                              "        << "\n";       
         out_Init << "            filePathName = nil;                                                                                                                            "        << "\n";     
         out_Init << "        //---------------------                                                                                                                            "        << "\n";
         out_Init << "        filePathName = [[NSBundle mainBundle] pathForResource:@\"" << passFilename << "\" ofType:@\"png\"];                                                "        << "\n";
         out_Init << "        if(filePathName != nil)                                                                                                                                "        << "\n";        
         out_Init << "        {                                                                                                                                                  "        << "\n";  
         out_Init << "                image = imgLoadImage([filePathName cStringUsingEncoding:NSASCIIStringEncoding]);                                                           "        << "\n";
         out_Init << "                glGenTextures(1, &" << passFilename << "_TEXTUREMAP);                                                                                      "        << "\n";
         out_Init << "                glBindTexture(GL_TEXTURE_2D, " << passFilename << "_TEXTUREMAP);                                                                           "        << "\n";
         out_Init << "                ConfigureAndLoadTexture(image->data,  image->width, image->height );                                                                       "        << "\n";
         out_Init << "                imgDestroyImage(image);                                                                                                                    "        << "\n";
         out_Init << "        }else                                                                                                                                              "        << "\n";         
         out_Init << "            {                                                                                                                                              "        << "\n";        
         out_Init << "               //add error file output here                                                                                                                "        << "\n";          
         out_Init << "            }                                                                                                                                              "        << "\n";      
         out_Init << "            filePathName = nil;                                                                                                                            "        << "\n";     
         out_Init << "        //---------------                                                                                                                                  "        << "\n";
         out_Init << "        #endif                                                                                                                                             "        << "\n";
         out_Init << "        //------------------------------------------------------------------------------------------                                                       "        << "\n";
         out_Init << "        #ifdef WIN32                                                                                                                                       "        << "\n";
         out_Init << "        loadTexture(\"_MODEL_FOLDERS_/" << passFilename << "/" << passFilename << "_DOT3.bmp\",          " << passFilename << "_NORMALMAP);                "        << "\n";
         out_Init << "        loadTexture(\"_MODEL_FOLDERS_/" << passFilename << "/" << passFilename << ".png\",               " << passFilename << "_TEXTUREMAP);               "        << "\n";
         out_Init << "        #endif                                                                                                                                             "        << "\n";
         out_Init << "        //------------------------------------------------------------------------------------------------------------//___LOAD_VBO                        "        << "\n";
         out_Init << "        #include    \"" << passFilename << ".cpp\"                                                                                                         "        << "\n";
         out_Init << "        glGenBuffers(1,              &" << passFilename << "_VBO);                                                                                         "        << "\n";
         out_Init << "        glBindBuffer(GL_ARRAY_BUFFER, " << passFilename << "_VBO);                                                                                         "        << "\n";
         out_Init << "        glBufferData(GL_ARRAY_BUFFER, sizeof(" << passFilename << "), " << passFilename << ", GL_STATIC_DRAW);                                             "        << "\n";
         out_Init << "        glBindBuffer(GL_ARRAY_BUFFER, 0);                                                                                                                  "        << "\n";
         out_Init << "        //------------------------------------------------------------------------------------------------------------                                     "        << "\n";       
         out_Init << "        #include    \"" << passFilename << "_INDICES.cpp\"                                                                                                 "        << "\n";
         out_Init << "        glGenBuffers(1,              &" << passFilename << "_INDICES_VBO);                                                                                   "        << "\n";
         out_Init << "        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, " << passFilename << "_INDICES_VBO);                                                                           "        << "\n";
         out_Init << "        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(" << passFilename << "_INDICES), " << passFilename << "_INDICES, GL_STATIC_DRAW);                       "        << "\n";
         out_Init << "        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);                                                                                                            "        << "\n";
         out_Init << "        //------------------------------------------------------------------------------------------------------------                                       "        << "\n";     

         //==================================================================================================================================
      
        float smallest_X, largest_X,smallest_Y, largest_Y,smallest_Z, largest_Z;
        //------------------------------------------------------------------------------------
        smallest_X = m_vertexBuffer[0].position[0];
        largest_X  = smallest_X;
        smallest_Y = m_vertexBuffer[0].position[1];
        largest_Y  = smallest_Y;
        smallest_Z = m_vertexBuffer[0].position[2];
        //------------------------------------------------------------------------------------
        for(int i = 0; i < numVerts; i++)
        {
                if(m_vertexBuffer[i].position[0] < smallest_X)
                {
                    smallest_X = m_vertexBuffer[i].position[0];
                } 
                if(m_vertexBuffer[i].position[0] > largest_X)
                {
                    largest_X  = m_vertexBuffer[i].position[0];                
                }      
                //--------------------------------------------
                if(m_vertexBuffer[i].position[1] < smallest_Y)
                {
                    smallest_Y = m_vertexBuffer[i].position[1];
                } 
                if(m_vertexBuffer[i].position[1] > largest_Y)
                {
                    largest_Y  = m_vertexBuffer[i].position[1];                
                }      
                //--------------------------------------------        
                if(m_vertexBuffer[i].position[2] < smallest_Z)
                {
                    smallest_Z = m_vertexBuffer[i].position[2];
                } 
                if(m_vertexBuffer[i].position[2] > largest_Z)
                {
                    largest_Z  = m_vertexBuffer[i].position[2];                
                }      
                //--------------------------------------------        
        }        
        
         out_Init << "        //====================================================================================   "        <<"\n";       
         out_Init << "        " << passFilename << "_boundingBox[0] = " << smallest_X                                           <<";\n";    
         out_Init << "        " << passFilename << "_boundingBox[1] = " << largest_X                                            <<";\n";  
         out_Init << "        " << passFilename << "_boundingBox[2] = " << smallest_Y                                           <<";\n";  
         out_Init << "        " << passFilename << "_boundingBox[3] = " << largest_Y                                            <<";\n";  
         out_Init << "        " << passFilename << "_boundingBox[4] = " << smallest_Z                                           <<";\n";  
         out_Init << "        " << passFilename << "_boundingBox[5] = " << largest_Z                                            <<";\n";   

         out_Init << "        //====================================================================================   "        <<"\n";       

         out_Init << "        collisionBoxArray[boxCount][0] = " << smallest_X        << ";\n"; //boxCount_starts_at_zero_and_is_incremented_with_each_file_load
         out_Init << "        collisionBoxArray[boxCount][1] = " << largest_X         << ";\n"; 
         out_Init << "        collisionBoxArray[boxCount][2] = " << smallest_Y        << ";\n"; 
         out_Init << "        collisionBoxArray[boxCount][3] = " << largest_Y         << ";\n"; 
         out_Init << "        collisionBoxArray[boxCount][4] = " << smallest_Z        << ";\n"; 
         out_Init << "        collisionBoxArray[boxCount][5] = " << largest_Z         << ";\n";     
         out_Init << "        collisionBoxArray[boxCount][6] = boxCount"              << ";\n";  //this_is_used_to_reject_self_collision_false_positive    
         out_Init << "        boxCount++;"                                            << "\n";        
    
//####################################################################################################################################
//####################################################################################################################################
//####################################################################################################################################
std::string RENDER = "_RENDER.cpp";
std::string fileName_RENDER = passFilename + "/" + passFilename + RENDER;
const char * fileName_RENDER_OUT = fileName_RENDER.c_str();
ofstream out_Render(fileName_RENDER_OUT);
   
         out_Render << "    glBindBuffer(GL_ARRAY_BUFFER, " << passFilename << "_VBO);                                                                                                 "        << "\n";
         out_Render << "    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, " << passFilename << "_INDICES_VBO);                                                                                                                                "        << "\n";
         out_Render << "    //----------------------------------------------------------------------------------------------------------------------------------------------           "        << "\n";
         out_Render << "    LoadIdentity(modelView);                                                                                                                                   "        << "\n";
         out_Render << "    Translate(modelView, " << passFilename << "_POSITION[0], " << passFilename << "_POSITION[1], " << passFilename << "_POSITION[2]);                          "        << "\n";
         out_Render << "    Rotate(modelView, " << passFilename << "_ROTATE[0], " << passFilename << "_ROTATE[1], " << passFilename << "_ROTATE[2], " << passFilename << "_ROTATE[3]); "        << "\n\n";

         out_Render << "//======================================================================================================                                                       "        << "\n";         
        
         out_Render << "    //SelectShader(shaderNumber);                                                                                                                              "        << "\n";         
        
        
         out_Render << "//======================================================================================================                                                       "        << "\n\n";         
         
         out_Render << "    glActiveTexture ( GL_TEXTURE1 );                                                                                                                           "        << "\n";
         out_Render << "    glBindTexture(GL_TEXTURE_2D, " << passFilename << "_NORMALMAP);                                                                                            "        << "\n";
         out_Render << "    //---                                                                                                                                                      "        << "\n";
         out_Render << "    glActiveTexture (GL_TEXTURE0);                                                                                                                             "        << "\n";
         out_Render << "    glBindTexture(GL_TEXTURE_2D, " << passFilename << "_TEXTUREMAP);                                                                                           "        << "\n";  
         out_Render << "    //---------------------------------------------------------------------------------------------------------------------------------------------------      "        << "\n";
         out_Render << "    glDrawElements(GL_TRIANGLES, " << static_cast<int>(m_indexBuffer.size()) << ", GL_UNSIGNED_INT, 0);                                                                                                     "        << "\n\n"; 
//####################################################################################################################################
//####################################################################################################################################
//#################################################################################################################################### 
//####################################################################################################################################
//####################################################################################################################################
//####################################################################################################################################
std::string SHUTDOWN = "_SHUTDOWN.cpp";
std::string fileName_SHUTDOWN = passFilename + "/" + passFilename + SHUTDOWN;
const char * fileName_SHUTDOWN_OUT = fileName_SHUTDOWN.c_str();
ofstream out_ShutDown(fileName_SHUTDOWN_OUT); 
 
         out_ShutDown << "                    if(" << passFilename << "_NORMALMAP != 0)                                                                                                      "        << "\n"; 
         out_ShutDown << "                    {                                                                                                                                              "        << "\n"; 
         out_ShutDown << "                            glDeleteTextures(1, &" << passFilename << "_NORMALMAP);                                                                                "        << "\n"; 
         out_ShutDown << "                            " << passFilename << "_NORMALMAP = 0;                                                                                                  "        << "\n"; 
         out_ShutDown << "                    }                                                                                                                                              "        << "\n"; 
         out_ShutDown << "                    if(" << passFilename << "_TEXTUREMAP  != 0)                                                                                                    "        << "\n"; 
         out_ShutDown << "                    {                                                                                                                                              "        << "\n"; 
         out_ShutDown << "                            glDeleteTextures(1, &" << passFilename << "_TEXTUREMAP);                                                                               "        << "\n"; 
         out_ShutDown << "                            " << passFilename << "_TEXTUREMAP  = 0;                                                                                                "        << "\n"; 
         out_ShutDown << "                    }                                                                                                                                              "        << "\n"; 
         out_ShutDown << "                    if(" << passFilename << "_VBO  != 0)                                                                                                           "        << "\n"; 
         out_ShutDown << "                    {                                                                                                                                              "        << "\n"; 
         out_ShutDown << "                            glDeleteBuffers(1, &" << passFilename << "_VBO);                                                                                       "        << "\n"; 
         out_ShutDown << "                            " << passFilename << "_VBO  = 0;                                                                                                       "        << "\n"; 
         out_ShutDown << "                    }                                                                                                                                              "        << "\n"; 
         out_ShutDown << "                    if(" << passFilename << "_INDICES_VBO  != 0)                                                                                                   "        << "\n"; 
         out_ShutDown << "                    {                                                                                                                                              "        << "\n"; 
         out_ShutDown << "                            glDeleteBuffers(1, &" << passFilename << "_INDICES_VBO);                                                                               "        << "\n"; 
         out_ShutDown << "                            " << passFilename << "_INDICES_VBO  = 0;                                                                                               "        << "\n"; 
         out_ShutDown << "                    }                                                                                                                                              "        << "\n"; 

 
//#################################################################################################################################### 
//####################################################################################################################################
//####################################################################################################################################
//####################################################################################################################################




std::string LOCATION_STRINGS = "_LOCATION_STRINGS.cpp";
std::string fileName_LOCATION_STRINGS = passFilename + "/" + LOCATION_STRINGS;
const char * fileName_LOCATION_STRINGS_OUT = fileName_LOCATION_STRINGS.c_str();
ofstream out_LOCATION_STRINGS(fileName_LOCATION_STRINGS_OUT); 
 
         out_LOCATION_STRINGS << "#include \"_MODEL_FOLDERS_/" << passFilename << "/" << passFilename << "_Globals.cpp\"                                                                "        <<"\n";                                              
         out_LOCATION_STRINGS << "//====================================================================================                                                                "        <<"\n";           
         out_LOCATION_STRINGS << "#include \"_MODEL_FOLDERS_/" << passFilename << "/" << passFilename << "_Init.cpp\"                                                                   "        <<"\n";          
         out_LOCATION_STRINGS << "//====================================================================================                                                                "        <<"\n";           
         out_LOCATION_STRINGS << "#include \"_MODEL_FOLDERS_/" << passFilename << "/" << passFilename << "_Shadow_01.cpp\"                                                              "        <<"\n";         
         out_LOCATION_STRINGS << "//====================================================================================                                                                "        <<"\n";                  
         out_LOCATION_STRINGS << "#include \"_MODEL_FOLDERS_/" << passFilename << "/" << passFilename << "_Shadow_00.cpp\"                                                              "        <<"\n";           
         out_LOCATION_STRINGS << "//====================================================================================                                                                "        <<"\n";                    
         out_LOCATION_STRINGS << "#include \"_MODEL_FOLDERS_/" << passFilename << "/" << passFilename << "_Render.cpp\"                                                                 "        <<"\n";
         out_LOCATION_STRINGS << "//====================================================================================                                                                "        <<"\n";                    
         out_LOCATION_STRINGS << "#include \"_MODEL_FOLDERS_/" << passFilename << "/" << passFilename << "_Keyboard.cpp\"                                                               "        <<"\n";         
         out_LOCATION_STRINGS << "//====================================================================================                                                                "        <<"\n";                  
         out_LOCATION_STRINGS << "#include \"_MODEL_FOLDERS_/" << passFilename << "/" << passFilename << "_COLLISION.cpp\"                                                              "        <<"\n";    
         out_LOCATION_STRINGS << "//====================================================================================                                                                "        <<"\n";       
         out_LOCATION_STRINGS << "#include \"_MODEL_FOLDERS_/" << passFilename << "/" << passFilename << "_Shutdown.cpp\"                                                               "        <<"\n";    
         out_LOCATION_STRINGS << "//====================================================================================                                                                "        <<"\n";       

//#################################################################################################################################### 
//####################################################################################################################################
//####################################################################################################################################
//####################################################################################################################################
//std::string GLOBALS = "_GLOBALS.cpp";
//std::string fileName_GLOBALS = passFilename + "/" + passFilename + GLOBALS;
//const char * fileName_GLOBALS_OUT = fileName_GLOBALS.c_str();
//ofstream out_Globals(fileName_GLOBALS_OUT);
/*

std::string BOX_COLLISION_A = "_BOX_COLLISION_A.cpp";
std::string fileName_BOX_COLLISION_A = passFilename + "/" + passFilename + BOX_COLLISION_A;
const char * fileName_BOX_COLLISION_A_OUT = fileName_BOX_COLLISION_A.c_str();
ofstream out_BOX_COLLISION_A(fileName_BOX_COLLISION_A_OUT);                                                                                                                                             

      
        float smallest_X, largest_X,smallest_Y, largest_Y,smallest_Z, largest_Z;
        //------------------------------------------------------------------------------------
        smallest_X = m_vertexBuffer[0].position[0];
        largest_X  = smallest_X;
        smallest_Y = m_vertexBuffer[0].position[1];
        largest_Y  = smallest_Y;
        smallest_Z = m_vertexBuffer[0].position[2];
        //------------------------------------------------------------------------------------
        for(int i = 0; i < numVerts; i++)
        {
                if(m_vertexBuffer[i].position[0] < smallest_X)
                {
                    smallest_X = m_vertexBuffer[i].position[0];
                } 
                if(m_vertexBuffer[i].position[0] > largest_X)
                {
                    largest_X  = m_vertexBuffer[i].position[0];                
                }      
                //--------------------------------------------
                if(m_vertexBuffer[i].position[1] < smallest_Y)
                {
                    smallest_Y = m_vertexBuffer[i].position[1];
                } 
                if(m_vertexBuffer[i].position[1] > largest_Y)
                {
                    largest_Y  = m_vertexBuffer[i].position[1];                
                }      
                //--------------------------------------------        
                if(m_vertexBuffer[i].position[2] < smallest_Z)
                {
                    smallest_Z = m_vertexBuffer[i].position[2];
                } 
                if(m_vertexBuffer[i].position[2] > largest_Z)
                {
                    largest_Z  = m_vertexBuffer[i].position[2];                
                }      
                //--------------------------------------------        
        }        
        
        
         out_BOX_COLLISION_A << "//====================================================================================   "        <<"\n";       
         out_BOX_COLLISION_A << " GLfloat " << passFilename << "_boundingBox[0] = " << smallest_X                                  <<"\n";    
         out_BOX_COLLISION_A << " GLfloat " << passFilename << "_boundingBox[1] = " << largest_X                                   <<"\n";  
         out_BOX_COLLISION_A << " GLfloat " << passFilename << "_boundingBox[2] = " << smallest_Y                                  <<"\n";  
         out_BOX_COLLISION_A << " GLfloat " << passFilename << "_boundingBox[3] = " << largest_Y                                   <<"\n";  
         out_BOX_COLLISION_A << " GLfloat " << passFilename << "_boundingBox[4] = " << smallest_Z                                  <<"\n";  
         out_BOX_COLLISION_A << " GLfloat " << passFilename << "_boundingBox[5] = " << largest_Z                                   <<"\n";   


         out_BOX_COLLISION_A << "//====================================================================================   "        <<"\n";       



        out_BOX_COLLISION_A << "collisionBoxArray[boxCount][0] = " << smallest_X        << ";\n"; //boxCount_starts_at_zero_and_is_incremented_with_each_file_load
        out_BOX_COLLISION_A << "collisionBoxArray[boxCount][1] = " << largest_X         << ";\n"; 
        out_BOX_COLLISION_A << "collisionBoxArray[boxCount][2] = " << smallest_Y        << ";\n"; 
        out_BOX_COLLISION_A << "collisionBoxArray[boxCount][3] = " << largest_Y         << ";\n"; 
        out_BOX_COLLISION_A << "collisionBoxArray[boxCount][4] = " << smallest_Z        << ";\n"; 
        out_BOX_COLLISION_A << "collisionBoxArray[boxCount][5] = " << largest_Z         << ";\n";     
        out_BOX_COLLISION_A << "collisionBoxArray[boxCount][6] = boxCount"              << ";\n";  //this_is_used_to_reject_self_collision_false_positive    
        out_BOX_COLLISION_A << "boxCount++;"                                             << "\n";        
*/ 
//#################################################################################################################################### 
//####################################################################################################################################
//####################################################################################################################################
//####################################################################################################################################

//=================================================================================================================


    if (rebuildNormals)
    {
        generateNormals();
    }
    else
    {
        if (!hasNormals())
            generateNormals();
    }

    // Build tangents is required.


    
for (int i = 0; i < m_numberOfMaterials; ++i)
    {
        if (!m_materials[i].bumpMapFilename.empty())
        {
            generateTangents();
            break;
        }
    }





    return true;
}
/*
void ModelOBJ::normalize(float scaleTo, bool center)
{
    float width = 0.0f;
    float height = 0.0f;
    float length = 0.0f;
    float radius = 0.0f;
    float centerPos[3] = {0.0f};

    bounds(centerPos, width, height, length, radius);

    float scalingFactor = scaleTo / radius;
    float offset[3] = {0.0f};

    if (center)
    {
        offset[0] = -centerPos[0];
        offset[1] = -centerPos[1];
        offset[2] = -centerPos[2];
    }
    else
    {
        offset[0] = 0.0f;
        offset[1] = 0.0f;
        offset[2] = 0.0f;
    }

    scale(scalingFactor, offset);
    bounds(m_center, m_width, m_height, m_length, m_radius);




}
*/
void ModelOBJ::reverseWinding()
{
    int swap = 0;


   
    // Reverse face winding.
    for (int i = 0; i < static_cast<int>(m_indexBuffer.size()); i += 3)
    {
        swap = m_indexBuffer[i + 1];
        m_indexBuffer[i + 1] = m_indexBuffer[i + 2];
        m_indexBuffer[i + 2] = swap;
    }

    float *pNormal = 0;
    float *pTangent = 0;

    // Invert normals and tangents.
    for (int i = 0; i < static_cast<int>(m_vertexBuffer.size()); ++i)
    {
        pNormal = m_vertexBuffer[i].normal;
        pNormal[0] = -pNormal[0];
        pNormal[1] = -pNormal[1];
        pNormal[2] = -pNormal[2];

        
        pTangent = m_vertexBuffer[i].tangent;
        pTangent[0] = -pTangent[0];
        pTangent[1] = -pTangent[1];
        pTangent[2] = -pTangent[2];
    }



}
/*
void ModelOBJ::scale(float scaleFactor, float offset[3])
{
    float *pPosition = 0;

    for (int i = 0; i < static_cast<int>(m_vertexBuffer.size()); ++i)
    {
        pPosition = m_vertexBuffer[i].position;

        pPosition[0] += offset[0];
        pPosition[1] += offset[1];
        pPosition[2] += offset[2];

        pPosition[0] *= scaleFactor;
        pPosition[1] *= scaleFactor;
        pPosition[2] *= scaleFactor;
    }
}
*/
void ModelOBJ::addTrianglePos(int index, int material, int v0, int v1, int v2)
{
    Vertex vertex =
    {
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 0.0f, 0.0f
    };

    m_attributeBuffer[index] = material;

    vertex.position[0] = m_vertexCoords[v0 * 3];
    vertex.position[1] = m_vertexCoords[v0 * 3 + 1];
    vertex.position[2] = m_vertexCoords[v0 * 3 + 2];
    m_indexBuffer[index * 3] = addVertex(v0, &vertex);

    vertex.position[0] = m_vertexCoords[v1 * 3];
    vertex.position[1] = m_vertexCoords[v1 * 3 + 1];
    vertex.position[2] = m_vertexCoords[v1 * 3 + 2];
    m_indexBuffer[index * 3 + 1] = addVertex(v1, &vertex);

    vertex.position[0] = m_vertexCoords[v2 * 3];
    vertex.position[1] = m_vertexCoords[v2 * 3 + 1];
    vertex.position[2] = m_vertexCoords[v2 * 3 + 2];
    m_indexBuffer[index * 3 + 2] = addVertex(v2, &vertex);
}

void ModelOBJ::addTrianglePosNormal(int index, int material, int v0, int v1,
                                    int v2, int vn0, int vn1, int vn2)
{
    Vertex vertex =
    {
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f
    };

    m_attributeBuffer[index] = material;

    vertex.position[0] = m_vertexCoords[v0 * 3];
    vertex.position[1] = m_vertexCoords[v0 * 3 + 1];
    vertex.position[2] = m_vertexCoords[v0 * 3 + 2];
    vertex.normal[0] = m_normals[vn0 * 3];
    vertex.normal[1] = m_normals[vn0 * 3 + 1];
    vertex.normal[2] = m_normals[vn0 * 3 + 2];
    m_indexBuffer[index * 3] = addVertex(v0, &vertex);

    vertex.position[0] = m_vertexCoords[v1 * 3];
    vertex.position[1] = m_vertexCoords[v1 * 3 + 1];
    vertex.position[2] = m_vertexCoords[v1 * 3 + 2];
    vertex.normal[0] = m_normals[vn1 * 3];
    vertex.normal[1] = m_normals[vn1 * 3 + 1];
    vertex.normal[2] = m_normals[vn1 * 3 + 2];
    m_indexBuffer[index * 3 + 1] = addVertex(v1, &vertex);

    vertex.position[0] = m_vertexCoords[v2 * 3];
    vertex.position[1] = m_vertexCoords[v2 * 3 + 1];
    vertex.position[2] = m_vertexCoords[v2 * 3 + 2];
    vertex.normal[0] = m_normals[vn2 * 3];
    vertex.normal[1] = m_normals[vn2 * 3 + 1];
    vertex.normal[2] = m_normals[vn2 * 3 + 2];
    m_indexBuffer[index * 3 + 2] = addVertex(v2, &vertex);
}

void ModelOBJ::addTrianglePosTexCoord(int index, int material, int v0, int v1,
                                      int v2, int vt0, int vt1, int vt2)
{
    Vertex vertex =
    {
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f
    };

    m_attributeBuffer[index] = material;

    vertex.position[0] = m_vertexCoords[v0 * 3];
    vertex.position[1] = m_vertexCoords[v0 * 3 + 1];
    vertex.position[2] = m_vertexCoords[v0 * 3 + 2];
    vertex.texCoord[0] = m_textureCoords[vt0 * 2];
    vertex.texCoord[1] = m_textureCoords[vt0 * 2 + 1];
    m_indexBuffer[index * 3] = addVertex(v0, &vertex);

    vertex.position[0] = m_vertexCoords[v1 * 3];
    vertex.position[1] = m_vertexCoords[v1 * 3 + 1];
    vertex.position[2] = m_vertexCoords[v1 * 3 + 2];
    vertex.texCoord[0] = m_textureCoords[vt1 * 2];
    vertex.texCoord[1] = m_textureCoords[vt1 * 2 + 1];
    m_indexBuffer[index * 3 + 1] = addVertex(v1, &vertex);

    vertex.position[0] = m_vertexCoords[v2 * 3];
    vertex.position[1] = m_vertexCoords[v2 * 3 + 1];
    vertex.position[2] = m_vertexCoords[v2 * 3 + 2];
    vertex.texCoord[0] = m_textureCoords[vt2 * 2];
    vertex.texCoord[1] = m_textureCoords[vt2 * 2 + 1];
    m_indexBuffer[index * 3 + 2] = addVertex(v2, &vertex);
}

void ModelOBJ::addTrianglePosTexCoordNormal(int index, int material, int v0,
                                            int v1, int v2, int vt0, int vt1,
                                            int vt2, int vn0, int vn1, int vn2)
{
    Vertex vertex =
    {
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f
    };

    m_attributeBuffer[index] = material;

    vertex.position[0] = m_vertexCoords[v0 * 3];
    vertex.position[1] = m_vertexCoords[v0 * 3 + 1];
    vertex.position[2] = m_vertexCoords[v0 * 3 + 2];
    vertex.texCoord[0] = m_textureCoords[vt0 * 2];
    vertex.texCoord[1] = m_textureCoords[vt0 * 2 + 1];
    vertex.normal[0] = m_normals[vn0 * 3];
    vertex.normal[1] = m_normals[vn0 * 3 + 1];
    vertex.normal[2] = m_normals[vn0 * 3 + 2];
    m_indexBuffer[index * 3] = addVertex(v0, &vertex);

    vertex.position[0] = m_vertexCoords[v1 * 3];
    vertex.position[1] = m_vertexCoords[v1 * 3 + 1];
    vertex.position[2] = m_vertexCoords[v1 * 3 + 2];
    vertex.texCoord[0] = m_textureCoords[vt1 * 2];
    vertex.texCoord[1] = m_textureCoords[vt1 * 2 + 1];
    vertex.normal[0] = m_normals[vn1 * 3];
    vertex.normal[1] = m_normals[vn1 * 3 + 1];
    vertex.normal[2] = m_normals[vn1 * 3 + 2];
    m_indexBuffer[index * 3 + 1] = addVertex(v1, &vertex);

    vertex.position[0] = m_vertexCoords[v2 * 3];
    vertex.position[1] = m_vertexCoords[v2 * 3 + 1];
    vertex.position[2] = m_vertexCoords[v2 * 3 + 2];
    vertex.texCoord[0] = m_textureCoords[vt2 * 2];
    vertex.texCoord[1] = m_textureCoords[vt2 * 2 + 1];
    vertex.normal[0] = m_normals[vn2 * 3];
    vertex.normal[1] = m_normals[vn2 * 3 + 1];
    vertex.normal[2] = m_normals[vn2 * 3 + 2];
    m_indexBuffer[index * 3 + 2] = addVertex(v2, &vertex);
}

int ModelOBJ::addVertex(int hash, const Vertex *pVertex)
{
    int index = -1;
    std::map<int, std::vector<int> >::const_iterator iter = m_vertexCache.find(hash);

    if (iter == m_vertexCache.end())
    {
        // Vertex hash doesn't exist in the cache.

        index = static_cast<int>(m_vertexBuffer.size());
        m_vertexBuffer.push_back(*pVertex);
        m_vertexCache.insert(std::make_pair(hash, std::vector<int>(1, index)));
    }
    else
    {
        // One or more vertices have been hashed to this entry in the cache.

        const std::vector<int> &vertices = iter->second;
        const Vertex *pCachedVertex = 0;
        bool found = false;

        for (std::vector<int>::const_iterator i = vertices.begin(); i != vertices.end(); ++i)
        {
            index = *i;
            pCachedVertex = &m_vertexBuffer[index];

            if (memcmp(pCachedVertex, pVertex, sizeof(Vertex)) == 0)
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            index = static_cast<int>(m_vertexBuffer.size());
            m_vertexBuffer.push_back(*pVertex);
            m_vertexCache[hash].push_back(index);
        }
    }

    return index;
}

void ModelOBJ::buildMeshes()
{
    // Group the model's triangles based on material type.

    Mesh *pMesh = 0;
    int materialId = -1;
    int numMeshes = 0;

    // Count the number of meshes.
    for (int i = 0; i < static_cast<int>(m_attributeBuffer.size()); ++i)
    {
        if (m_attributeBuffer[i] != materialId)
        {
            materialId = m_attributeBuffer[i];
            ++numMeshes;
        }
    }

    // Allocate memory for the meshes and reset counters.
    m_numberOfMeshes = numMeshes;
    m_meshes.resize(m_numberOfMeshes);
    numMeshes = 0;
    materialId = -1;

    // Build the meshes. One mesh for each unique material.
    for (int i = 0; i < static_cast<int>(m_attributeBuffer.size()); ++i)
    {
        if (m_attributeBuffer[i] != materialId)
        {
            materialId = m_attributeBuffer[i];
            pMesh = &m_meshes[numMeshes++];            
            pMesh->pMaterial = &m_materials[materialId];
            pMesh->startIndex = i * 3;
            ++pMesh->triangleCount;
        }
        else
        {
            ++pMesh->triangleCount;
        }
    }

    // Sort the meshes based on its material alpha. Fully opaque meshes
    // towards the front and fully transparent towards the back.
    std::sort(m_meshes.begin(), m_meshes.end(), MeshCompFunc);
}

void ModelOBJ::generateNormals()
{
    const int *pTriangle = 0;
    Vertex *pVertex0 = 0;
    Vertex *pVertex1 = 0;
    Vertex *pVertex2 = 0;
    float edge1[3] = {0.0f, 0.0f, 0.0f};
    float edge2[3] = {0.0f, 0.0f, 0.0f};
    float normal[3] = {0.0f, 0.0f, 0.0f};
    float length = 0.0f;
    totalVertices = getNumberOfVertices();
    int totalTriangles = getNumberOfTriangles();

    // Initialize all the vertex normals.
    for (int i = 0; i < totalVertices; ++i)
    {
        pVertex0 = &m_vertexBuffer[i];
        pVertex0->normal[0] = 0.0f;
        pVertex0->normal[1] = 0.0f;
        pVertex0->normal[2] = 0.0f;
    }

    // Calculate the vertex normals.
    for (int i = 0; i < totalTriangles; ++i)
    {
        pTriangle = &m_indexBuffer[i * 3];

        pVertex0 = &m_vertexBuffer[pTriangle[0]];
        pVertex1 = &m_vertexBuffer[pTriangle[1]];
        pVertex2 = &m_vertexBuffer[pTriangle[2]];

        // Calculate triangle face normal.

        edge1[0] = pVertex1->position[0] - pVertex0->position[0];
        edge1[1] = pVertex1->position[1] - pVertex0->position[1];
        edge1[2] = pVertex1->position[2] - pVertex0->position[2];

        edge2[0] = pVertex2->position[0] - pVertex0->position[0];
        edge2[1] = pVertex2->position[1] - pVertex0->position[1];
        edge2[2] = pVertex2->position[2] - pVertex0->position[2];

        normal[0] = (edge1[1] * edge2[2]) - (edge1[2] * edge2[1]);
        normal[1] = (edge1[2] * edge2[0]) - (edge1[0] * edge2[2]);
        normal[2] = (edge1[0] * edge2[1]) - (edge1[1] * edge2[0]);

        // Accumulate the normals.

        pVertex0->normal[0] += normal[0];
        pVertex0->normal[1] += normal[1];
        pVertex0->normal[2] += normal[2];

        pVertex1->normal[0] += normal[0];
        pVertex1->normal[1] += normal[1];
        pVertex1->normal[2] += normal[2];

        pVertex2->normal[0] += normal[0];
        pVertex2->normal[1] += normal[1];
        pVertex2->normal[2] += normal[2];
    }

    // Normalize the vertex normals.
    for (int i = 0; i < totalVertices; ++i)
    {
        pVertex0 = &m_vertexBuffer[i];

        length = 1.0f / sqrtf(pVertex0->normal[0] * pVertex0->normal[0] +
            pVertex0->normal[1] * pVertex0->normal[1] +
            pVertex0->normal[2] * pVertex0->normal[2]);

        pVertex0->normal[0] *= length;
        pVertex0->normal[1] *= length;
        pVertex0->normal[2] *= length;
    }
/*

//-------------------------------------------------------------------------------
*/    
    
    m_hasNormals = true;
}

void ModelOBJ::generateTangents()
{
    const int *pTriangle = 0;
    Vertex *pVertex0 = 0;
    Vertex *pVertex1 = 0;
    Vertex *pVertex2 = 0;
    float edge1[3] = {0.0f, 0.0f, 0.0f};
    float edge2[3] = {0.0f, 0.0f, 0.0f};
    float texEdge1[2] = {0.0f, 0.0f};
    float texEdge2[2] = {0.0f, 0.0f};
    float tangent[3] = {0.0f, 0.0f, 0.0f};
    float bitangent[3] = {0.0f, 0.0f, 0.0f};
    float det = 0.0f;
    float nDotT = 0.0f;
    float bDotB = 0.0f;
    float length = 0.0f;
    int totalVertices = getNumberOfVertices();
    int totalTriangles = getNumberOfTriangles();

    // Initialize all the vertex tangents and bitangents.
    for (int i = 0; i < totalVertices; ++i)
    {
        pVertex0 = &m_vertexBuffer[i];

        pVertex0->tangent[0] = 0.0f;
        pVertex0->tangent[1] = 0.0f;
        pVertex0->tangent[2] = 0.0f;
        pVertex0->tangent[3] = 0.0f;

        pVertex0->bitangent[0] = 0.0f;
        pVertex0->bitangent[1] = 0.0f;
        pVertex0->bitangent[2] = 0.0f;
    }
//========================================================================================
		

	// Calculate the vertex tangents and bitangents.
    for (int i = 0; i < totalTriangles; ++i)
    {
        pTriangle = &m_indexBuffer[i * 3];

        pVertex0 = &m_vertexBuffer[pTriangle[0]];
        pVertex1 = &m_vertexBuffer[pTriangle[1]];
        pVertex2 = &m_vertexBuffer[pTriangle[2]];

        // Calculate the triangle face tangent and bitangent.

       
                   // out << pVertex0 << ", ";
                   // out << pVertex1 << ", ";
                   // out << pVertex2 << ",\n";	


	
		//========================================================================================
		
		edge1[0] = pVertex1->position[0] - pVertex0->position[0];
        edge1[1] = pVertex1->position[1] - pVertex0->position[1];
        edge1[2] = pVertex1->position[2] - pVertex0->position[2];

        edge2[0] = pVertex2->position[0] - pVertex0->position[0];
        edge2[1] = pVertex2->position[1] - pVertex0->position[1];
        edge2[2] = pVertex2->position[2] - pVertex0->position[2];

        texEdge1[0] = pVertex1->texCoord[0] - pVertex0->texCoord[0];
        texEdge1[1] = pVertex1->texCoord[1] - pVertex0->texCoord[1];

        texEdge2[0] = pVertex2->texCoord[0] - pVertex0->texCoord[0];
        texEdge2[1] = pVertex2->texCoord[1] - pVertex0->texCoord[1];

        det = texEdge1[0] * texEdge2[1] - texEdge2[0] * texEdge1[1];

        if (fabs(det) < 1e-6f)
        {
            tangent[0] = 1.0f;
            tangent[1] = 0.0f;
            tangent[2] = 0.0f;

            bitangent[0] = 0.0f;
            bitangent[1] = 1.0f;
            bitangent[2] = 0.0f;
        }
        else
        {
            det = 1.0f / det;

            tangent[0] = (texEdge2[1] * edge1[0] - texEdge1[1] * edge2[0]) * det;
            tangent[1] = (texEdge2[1] * edge1[1] - texEdge1[1] * edge2[1]) * det;
            tangent[2] = (texEdge2[1] * edge1[2] - texEdge1[1] * edge2[2]) * det;

            bitangent[0] = (-texEdge2[0] * edge1[0] + texEdge1[0] * edge2[0]) * det;
            bitangent[1] = (-texEdge2[0] * edge1[1] + texEdge1[0] * edge2[1]) * det;
            bitangent[2] = (-texEdge2[0] * edge1[2] + texEdge1[0] * edge2[2]) * det;
        }

        // Accumulate the tangents and bitangents.

        pVertex0->tangent[0] += tangent[0];
        pVertex0->tangent[1] += tangent[1];
        pVertex0->tangent[2] += tangent[2];
        pVertex0->bitangent[0] += bitangent[0];
        pVertex0->bitangent[1] += bitangent[1];
        pVertex0->bitangent[2] += bitangent[2];

        pVertex1->tangent[0] += tangent[0];
        pVertex1->tangent[1] += tangent[1];
        pVertex1->tangent[2] += tangent[2];
        pVertex1->bitangent[0] += bitangent[0];
        pVertex1->bitangent[1] += bitangent[1];
        pVertex1->bitangent[2] += bitangent[2];

        pVertex2->tangent[0] += tangent[0];
        pVertex2->tangent[1] += tangent[1];
        pVertex2->tangent[2] += tangent[2];
        pVertex2->bitangent[0] += bitangent[0];
        pVertex2->bitangent[1] += bitangent[1];
        pVertex2->bitangent[2] += bitangent[2];
    }


    // Orthogonalize and normalize the vertex tangents.
    for (int i = 0; i < totalVertices; ++i)
    {
        pVertex0 = &m_vertexBuffer[i];

        // Gram-Schmidt orthogonalize tangent with normal.

        nDotT = pVertex0->normal[0] * pVertex0->tangent[0] +
                pVertex0->normal[1] * pVertex0->tangent[1] +
                pVertex0->normal[2] * pVertex0->tangent[2];

        pVertex0->tangent[0] -= pVertex0->normal[0] * nDotT;
        pVertex0->tangent[1] -= pVertex0->normal[1] * nDotT;
        pVertex0->tangent[2] -= pVertex0->normal[2] * nDotT;

        // Normalize the tangent.

        length = 1.0f / sqrtf(pVertex0->tangent[0] * pVertex0->tangent[0] +
                              pVertex0->tangent[1] * pVertex0->tangent[1] +
                              pVertex0->tangent[2] * pVertex0->tangent[2]);

        pVertex0->tangent[0] *= length;
        pVertex0->tangent[1] *= length;
        pVertex0->tangent[2] *= length;

        // Calculate the handedness of the local tangent space.
        // The bitangent vector is the cross product between the triangle face
        // normal vector and the calculated tangent vector. The resulting
        // bitangent vector should be the same as the bitangent vector
        // calculated from the set of linear equations above. If they point in
        // different directions then we need to invert the cross product
        // calculated bitangent vector. We store this scalar multiplier in the
        // tangent vector's 'w' component so that the correct bitangent vector
        // can be generated in the normal mapping shader's vertex shader.
        //
        // Normal maps have a left handed coordinate system with the origin
        // located at the top left of the normal map texture. The x coordinates
        // run horizontally from left to right. The y coordinates run
        // vertically from top to bottom. The z coordinates run out of the
        // normal map texture towards the viewer. Our handedness calculations
        // must take this fact into account as well so that the normal mapping
        // shader's vertex shader will generate the correct bitangent vectors.
        // Some normal map authoring tools such as Crazybump
        // (http://www.crazybump.com/) includes options to allow you to control
        // the orientation of the normal map normal's y-axis.

        bitangent[0] = (pVertex0->normal[1] * pVertex0->tangent[2]) - 
                       (pVertex0->normal[2] * pVertex0->tangent[1]);
        bitangent[1] = (pVertex0->normal[2] * pVertex0->tangent[0]) -
                       (pVertex0->normal[0] * pVertex0->tangent[2]);
        bitangent[2] = (pVertex0->normal[0] * pVertex0->tangent[1]) - 
                       (pVertex0->normal[1] * pVertex0->tangent[0]);

        bDotB = bitangent[0] * pVertex0->bitangent[0] + 
                bitangent[1] * pVertex0->bitangent[1] + 
                bitangent[2] * pVertex0->bitangent[2];

        pVertex0->tangent[3] = (bDotB < 0.0f) ? 1.0f : -1.0f;

        pVertex0->bitangent[0] = bitangent[0];
        pVertex0->bitangent[1] = bitangent[1];
        pVertex0->bitangent[2] = bitangent[2];
    }

    m_hasTangents = true;
}

void ModelOBJ::importGeometryFirstPass(FILE *pFile)
{
    m_hasTextureCoords = false;
    m_hasNormals = false;

    m_numberOfVertexCoords = 0;
    m_numberOfTextureCoords = 0;
    m_numberOfNormals = 0;
    m_numberOfTriangles = 0;

    int v = 0;
    int vt = 0;
    int vn = 0;
    char buffer[256] = {0};
    std::string name;

    while (fscanf(pFile, "%s", buffer) != EOF)
    {
        switch (buffer[0])
        {
        case 'f':   // v, v//vn, v/vt, v/vt/vn.
            fscanf(pFile, "%s", buffer);

            if (strstr(buffer, "//")) // v//vn
            {
                sscanf(buffer, "%d//%d", &v, &vn);
                fscanf(pFile, "%d//%d", &v, &vn);
                fscanf(pFile, "%d//%d", &v, &vn);
                ++m_numberOfTriangles;

                while (fscanf(pFile, "%d//%d", &v, &vn) > 0)
                    ++m_numberOfTriangles;
            }
            else if (sscanf(buffer, "%d/%d/%d", &v, &vt, &vn) == 3) // v/vt/vn
            {
                fscanf(pFile, "%d/%d/%d", &v, &vt, &vn);
                fscanf(pFile, "%d/%d/%d", &v, &vt, &vn);
                ++m_numberOfTriangles;

                while (fscanf(pFile, "%d/%d/%d", &v, &vt, &vn) > 0)
                    ++m_numberOfTriangles;
            }
            else if (sscanf(buffer, "%d/%d", &v, &vt) == 2) // v/vt
            {
                fscanf(pFile, "%d/%d", &v, &vt);
                fscanf(pFile, "%d/%d", &v, &vt);
                ++m_numberOfTriangles;

                while (fscanf(pFile, "%d/%d", &v, &vt) > 0)
                    ++m_numberOfTriangles;
            }
            else // v
            {
                fscanf(pFile, "%d", &v);
                fscanf(pFile, "%d", &v);
                ++m_numberOfTriangles;

                while (fscanf(pFile, "%d", &v) > 0)
                    ++m_numberOfTriangles;
            }
            break;

        case 'm':   // mtllib
            fgets(buffer, sizeof(buffer), pFile);
            sscanf(buffer, "%s %s", buffer, buffer);
            name = m_directoryPath;
            name += buffer;
            importMaterials(name.c_str());
            break;

        case 'v':   // v, vt, or vn
            switch (buffer[1])
            {
            case '\0':
                fgets(buffer, sizeof(buffer), pFile);
                ++m_numberOfVertexCoords;
                break;

            case 'n':
                fgets(buffer, sizeof(buffer), pFile);
                ++m_numberOfNormals;
                break;

            case 't':
                fgets(buffer, sizeof(buffer), pFile);
                ++m_numberOfTextureCoords;

            default:
                break;
            }
            break;

        default:
            fgets(buffer, sizeof(buffer), pFile);
            break;
        }
    }

    m_hasPositions = m_numberOfVertexCoords > 0;
    m_hasNormals = m_numberOfNormals > 0;
    m_hasTextureCoords = m_numberOfTextureCoords > 0;

    // Allocate memory for the OBJ model data.
    m_vertexCoords.resize(m_numberOfVertexCoords * 3);
    m_textureCoords.resize(m_numberOfTextureCoords * 2);
    m_normals.resize(m_numberOfNormals * 3);
    m_indexBuffer.resize(m_numberOfTriangles * 3);
    m_attributeBuffer.resize(m_numberOfTriangles);

    // Define a default material if no materials were loaded.
    if (m_numberOfMaterials == 0)
    {
        Material defaultMaterial =
        {
            0.2f, 0.2f, 0.2f, 1.0f,
            0.8f, 0.8f, 0.8f, 1.0f,
            0.0f, 0.0f, 0.0f, 1.0f,
            0.0f,
            1.0f,
            std::string("default"),
            std::string(),
            std::string()
        };

        m_materials.push_back(defaultMaterial);
        m_materialCache[defaultMaterial.name] = 0;
    }
}

void ModelOBJ::importGeometrySecondPass(FILE *pFile)
{
    int v[3] = {0};
    int vt[3] = {0};
    int vn[3] = {0};
    int numVertices = 0;
    int numTexCoords = 0;
    int numNormals = 0;
    int numTriangles = 0;
    int activeMaterial = 0;
    char buffer[256] = {0};
    std::string name;
    std::map<std::string, int>::const_iterator iter;

    while (fscanf(pFile, "%s", buffer) != EOF)
    {
        switch (buffer[0])
        {
        case 'f': // v, v//vn, v/vt, or v/vt/vn.
            v[0]  = v[1]  = v[2]  = 0;
            vt[0] = vt[1] = vt[2] = 0;
            vn[0] = vn[1] = vn[2] = 0;

            fscanf(pFile, "%s", buffer);

            if (strstr(buffer, "//")) // v//vn
            {
                sscanf(buffer, "%d//%d", &v[0], &vn[0]);
                fscanf(pFile, "%d//%d", &v[1], &vn[1]);
                fscanf(pFile, "%d//%d", &v[2], &vn[2]);

                v[0] = (v[0] < 0) ? v[0] + numVertices - 1 : v[0] - 1;
                v[1] = (v[1] < 0) ? v[1] + numVertices - 1 : v[1] - 1;
                v[2] = (v[2] < 0) ? v[2] + numVertices - 1 : v[2] - 1;

                vn[0] = (vn[0] < 0) ? vn[0] + numNormals - 1 : vn[0] - 1;
                vn[1] = (vn[1] < 0) ? vn[1] + numNormals - 1 : vn[1] - 1;
                vn[2] = (vn[2] < 0) ? vn[2] + numNormals - 1 : vn[2] - 1;

                addTrianglePosNormal(numTriangles++, activeMaterial,
                    v[0], v[1], v[2], vn[0], vn[1], vn[2]);

                v[1] = v[2];
                vn[1] = vn[2];

                while (fscanf(pFile, "%d//%d", &v[2], &vn[2]) > 0)
                {
                    v[2] = (v[2] < 0) ? v[2] + numVertices - 1 : v[2] - 1;
                    vn[2] = (vn[2] < 0) ? vn[2] + numNormals - 1 : vn[2] - 1;

                    addTrianglePosNormal(numTriangles++, activeMaterial,
                        v[0], v[1], v[2], vn[0], vn[1], vn[2]);

                    v[1] = v[2];
                    vn[1] = vn[2];
                }
            }
            else if (sscanf(buffer, "%d/%d/%d", &v[0], &vt[0], &vn[0]) == 3) // v/vt/vn
            {
                fscanf(pFile, "%d/%d/%d", &v[1], &vt[1], &vn[1]);
                fscanf(pFile, "%d/%d/%d", &v[2], &vt[2], &vn[2]);

                v[0] = (v[0] < 0) ? v[0] + numVertices - 1 : v[0] - 1;
                v[1] = (v[1] < 0) ? v[1] + numVertices - 1 : v[1] - 1;
                v[2] = (v[2] < 0) ? v[2] + numVertices - 1 : v[2] - 1;

                vt[0] = (vt[0] < 0) ? vt[0] + numTexCoords - 1 : vt[0] - 1;
                vt[1] = (vt[1] < 0) ? vt[1] + numTexCoords - 1 : vt[1] - 1;
                vt[2] = (vt[2] < 0) ? vt[2] + numTexCoords - 1 : vt[2] - 1;

                vn[0] = (vn[0] < 0) ? vn[0] + numNormals - 1 : vn[0] - 1;
                vn[1] = (vn[1] < 0) ? vn[1] + numNormals - 1 : vn[1] - 1;
                vn[2] = (vn[2] < 0) ? vn[2] + numNormals - 1 : vn[2] - 1;

                addTrianglePosTexCoordNormal(numTriangles++, activeMaterial,
                    v[0], v[1], v[2], vt[0], vt[1], vt[2], vn[0], vn[1], vn[2]);

                v[1] = v[2];
                vt[1] = vt[2];
                vn[1] = vn[2];

                while (fscanf(pFile, "%d/%d/%d", &v[2], &vt[2], &vn[2]) > 0)
                {
                    v[2] = (v[2] < 0) ? v[2] + numVertices - 1 : v[2] - 1;
                    vt[2] = (vt[2] < 0) ? vt[2] + numTexCoords - 1 : vt[2] - 1;
                    vn[2] = (vn[2] < 0) ? vn[2] + numNormals - 1 : vn[2] - 1;

                    addTrianglePosTexCoordNormal(numTriangles++, activeMaterial,
                        v[0], v[1], v[2], vt[0], vt[1], vt[2], vn[0], vn[1], vn[2]);

                    v[1] = v[2];
                    vt[1] = vt[2];
                    vn[1] = vn[2];
                }
            }
            else if (sscanf(buffer, "%d/%d", &v[0], &vt[0]) == 2) // v/vt
            {
                fscanf(pFile, "%d/%d", &v[1], &vt[1]);
                fscanf(pFile, "%d/%d", &v[2], &vt[2]);

                v[0] = (v[0] < 0) ? v[0] + numVertices - 1 : v[0] - 1;
                v[1] = (v[1] < 0) ? v[1] + numVertices - 1 : v[1] - 1;
                v[2] = (v[2] < 0) ? v[2] + numVertices - 1 : v[2] - 1;

                vt[0] = (vt[0] < 0) ? vt[0] + numTexCoords - 1 : vt[0] - 1;
                vt[1] = (vt[1] < 0) ? vt[1] + numTexCoords - 1 : vt[1] - 1;
                vt[2] = (vt[2] < 0) ? vt[2] + numTexCoords - 1 : vt[2] - 1;

                addTrianglePosTexCoord(numTriangles++, activeMaterial,
                    v[0], v[1], v[2], vt[0], vt[1], vt[2]);

                v[1] = v[2];
                vt[1] = vt[2];

                while (fscanf(pFile, "%d/%d", &v[2], &vt[2]) > 0)
                {
                    v[2] = (v[2] < 0) ? v[2] + numVertices - 1 : v[2] - 1;
                    vt[2] = (vt[2] < 0) ? vt[2] + numTexCoords - 1 : vt[2] - 1;

                    addTrianglePosTexCoord(numTriangles++, activeMaterial,
                        v[0], v[1], v[2], vt[0], vt[1], vt[2]);

                    v[1] = v[2];
                    vt[1] = vt[2];
                }
            }
            else // v
            {
                sscanf(buffer, "%d", &v[0]);
                fscanf(pFile, "%d", &v[1]);
                fscanf(pFile, "%d", &v[2]);

                v[0] = (v[0] < 0) ? v[0] + numVertices - 1 : v[0] - 1;
                v[1] = (v[1] < 0) ? v[1] + numVertices - 1 : v[1] - 1;
                v[2] = (v[2] < 0) ? v[2] + numVertices - 1 : v[2] - 1;

                addTrianglePos(numTriangles++, activeMaterial, v[0], v[1], v[2]);

                v[1] = v[2];

                while (fscanf(pFile, "%d", &v[2]) > 0)
                {
                    v[2] = (v[2] < 0) ? v[2] + numVertices - 1 : v[2] - 1;

                    addTrianglePos(numTriangles++, activeMaterial, v[0], v[1], v[2]);

                    v[1] = v[2];
                }
            }
            break;

        case 'u': // usemtl
            fgets(buffer, sizeof(buffer), pFile);
            sscanf(buffer, "%s %s", buffer, buffer);
            name = buffer;
            iter = m_materialCache.find(buffer);
            activeMaterial = (iter == m_materialCache.end()) ? 0 : iter->second;
            break;

        case 'v': // v, vn, or vt.
            switch (buffer[1])
            {
            case '\0': // v
                fscanf(pFile, "%f %f %f",
                    &m_vertexCoords[3 * numVertices],
                    &m_vertexCoords[3 * numVertices + 1],
                    &m_vertexCoords[3 * numVertices + 2]);
                ++numVertices;
                break;

            case 'n': // vn
                fscanf(pFile, "%f %f %f",
                    &m_normals[3 * numNormals],
                    &m_normals[3 * numNormals + 1],
                    &m_normals[3 * numNormals + 2]);
                ++numNormals;
                break;

            case 't': // vt
                fscanf(pFile, "%f %f",
                    &m_textureCoords[2 * numTexCoords],
                    &m_textureCoords[2 * numTexCoords + 1]);
                ++numTexCoords;
                break;

            default:
                break;
            }
            break;

        default:
            fgets(buffer, sizeof(buffer), pFile);
            break;
        }
    }
}

bool ModelOBJ::importMaterials(const char *pszFilename)
{
    FILE *pFile = fopen(pszFilename, "r");

    if (!pFile)
        return false;

    Material *pMaterial = 0;
    int illum = 0;
    int numMaterials = 0;
    char buffer[256] = {0};

    // Count the number of materials in the MTL file.
    while (fscanf(pFile, "%s", buffer) != EOF)
    {
        switch (buffer[0])
        {
        case 'n': // newmtl
            ++numMaterials;
            fgets(buffer, sizeof(buffer), pFile);
            sscanf(buffer, "%s %s", buffer, buffer);
            break;

        default:
            fgets(buffer, sizeof(buffer), pFile);
            break;
        }
    }

    rewind(pFile);

    m_numberOfMaterials = numMaterials;
    numMaterials = 0;
    m_materials.resize(m_numberOfMaterials);

    // Load the materials in the MTL file.
    while (fscanf(pFile, "%s", buffer) != EOF)
    {
        switch (buffer[0])
        {
        case 'N': // Ns
            fscanf(pFile, "%f", &pMaterial->shininess);

            // Wavefront .MTL file shininess is from [0,1000].
            // Scale back to a generic [0,1] range.
            pMaterial->shininess /= 1000.0f;
            break;

        case 'K': // Ka, Kd, or Ks
            switch (buffer[1])
            {
            case 'a': // Ka
                fscanf(pFile, "%f %f %f",
                    &pMaterial->ambient[0],
                    &pMaterial->ambient[1],
                    &pMaterial->ambient[2]);
                pMaterial->ambient[3] = 1.0f;
                break;

            case 'd': // Kd
                fscanf(pFile, "%f %f %f",
                    &pMaterial->diffuse[0],
                    &pMaterial->diffuse[1],
                    &pMaterial->diffuse[2]);
                pMaterial->diffuse[3] = 1.0f;
                break;

            case 's': // Ks
                fscanf(pFile, "%f %f %f",
                    &pMaterial->specular[0],
                    &pMaterial->specular[1],
                    &pMaterial->specular[2]);
                pMaterial->specular[3] = 1.0f;
                break;

            default:
                fgets(buffer, sizeof(buffer), pFile);
                break;
            }
            break;

        case 'T': // Tr
            switch (buffer[1])
            {
            case 'r': // Tr
                fscanf(pFile, "%f", &pMaterial->alpha);
                pMaterial->alpha = 1.0f - pMaterial->alpha;
                break;

            default:
                fgets(buffer, sizeof(buffer), pFile);
                break;
            }
            break;

        case 'd':
            fscanf(pFile, "%f", &pMaterial->alpha);
            break;

        case 'i': // illum
            fscanf(pFile, "%d", &illum);

            if (illum == 1)
            {
                pMaterial->specular[0] = 0.0f;
                pMaterial->specular[1] = 0.0f;
                pMaterial->specular[2] = 0.0f;
                pMaterial->specular[3] = 1.0f;
            }
            break;

        case 'm': // map_Kd, map_bump
            if (strstr(buffer, "map_Kd") != 0)
            {
                fgets(buffer, sizeof(buffer), pFile);
                sscanf(buffer, "%s %s", buffer, buffer);
                pMaterial->colorMapFilename = buffer;
            }
            else if (strstr(buffer, "map_bump") != 0)
            {
                fgets(buffer, sizeof(buffer), pFile);
                sscanf(buffer, "%s %s", buffer, buffer);
                pMaterial->bumpMapFilename = buffer;
            }
            else
            {
                fgets(buffer, sizeof(buffer), pFile);
            }
            break;

        case 'n': // newmtl
            fgets(buffer, sizeof(buffer), pFile);
            sscanf(buffer, "%s %s", buffer, buffer);

            pMaterial = &m_materials[numMaterials];
            pMaterial->ambient[0] = 0.2f;
            pMaterial->ambient[1] = 0.2f;
            pMaterial->ambient[2] = 0.2f;
            pMaterial->ambient[3] = 1.0f;
            pMaterial->diffuse[0] = 0.8f;
            pMaterial->diffuse[1] = 0.8f;
            pMaterial->diffuse[2] = 0.8f;
            pMaterial->diffuse[3] = 1.0f;
            pMaterial->specular[0] = 0.0f;
            pMaterial->specular[1] = 0.0f;
            pMaterial->specular[2] = 0.0f;
            pMaterial->specular[3] = 1.0f;
            pMaterial->shininess = 0.0f;
            pMaterial->alpha = 1.0f;
            pMaterial->name = buffer;
            pMaterial->colorMapFilename.clear();
            pMaterial->bumpMapFilename.clear();

            m_materialCache[pMaterial->name] = numMaterials;
            ++numMaterials;
            break;

        default:
            fgets(buffer, sizeof(buffer), pFile);
            break;
        }
    }

    fclose(pFile);
    return true;
}
void ModelOBJ::destroy()
{
   

	
	
	m_hasPositions = false;
    m_hasTextureCoords = false;
    m_hasNormals = false;
    m_hasTangents = false;

    m_numberOfVertexCoords = 0;
    m_numberOfTextureCoords = 0;
    m_numberOfNormals = 0;
    m_numberOfTriangles = 0;
    m_numberOfMaterials = 0;
    m_numberOfMeshes = 0;

    m_center[0] = m_center[1] = m_center[2] = 0.0f;
    m_width = m_height = m_length = m_radius = 0.0f;

    m_directoryPath.clear();

    m_meshes.clear();
    m_materials.clear();
    m_vertexBuffer.clear();
    m_indexBuffer.clear();
    m_attributeBuffer.clear();

    m_vertexCoords.clear();
    m_textureCoords.clear();
    m_normals.clear();

    m_materialCache.clear();
    m_vertexCache.clear();



}

#define var GLfloat
//####################################################################################################################

#ifdef WIN32
        #define   glGenerateMipmap       glGenerateMipmapEXT
        #define   glGenFramebuffers      glGenFramebuffersEXT
        #define   glBindFramebuffer      glBindFramebufferEXT
        #define   glFramebufferTexture2D glFramebufferTexture2DEXT
         
        #define   STRICT
        #define   WIN32_LEAN_AND_MEAN
        #include <windows.h>
        #include <iostream.h>
        #include <fstream.h>
        //using namespace std; //___used for string object

        //-----------------------------------------------------------------------------

        #include <GL/gl.h>
        #include <GL/glu.h>
        #include "headerFiles/glext.h"
        #include "headerFiles/glext_Init_A.cpp"

        void InitGL(void);
        void RenderGL(void);
        
        void ProcessKeyboard(void);
                
        GLsizei  viewWidth;
        GLsizei  viewHeight;
        
        //----------------------------------------------------------------------
        GLfloat  PassMouseMovement[2];

        //-------------------------------
        var keys[256], keypressed[256];
        #include "cpp/WGL_ARB_multisample.h"
        //-------------------------------

        #include "headerFiles/VSync.h"
        
        #include <windows.h>

        void      ConfigureAndLoadTexture(GLubyte *textureData, GLint texWidth, GLint texHeight );
        #include "headerFiles/glaux.h"
        #include "headerFiles/FreeImage.h"
        #include "cpp/freeImage.cpp"
        //------------------------------------------
 
#endif

//####################################################################################################################

        GLfloat  PassTouchMovement[3];



//####################################################################################################################

#include <math.h>
  
//####################################################################################################################

#include "MATRIX_MATH.cpp"

//####################################################################################################################

//--------------------------------------------------------------------------------------------------------------
#define BUFFER_OFFSET(i) ((char *)0 + (i))
//----------------------------------------------------------------------------------------

        extern GLuint msaaFramebuffer;

        void RenderGL(void);
        void InitGL  (void);
        void shutDownGL(void);
      
        #ifdef __APPLE__
               GLsizei viewWidth;
               GLsizei viewHeight;
               GLuint  viewFramebuffer;
        #endif
          
        //-------------------------------------------------------------------------------


GLuint m_uiShadowMapTexture;
GLuint m_uiFrameBufferObject;



//#########################################################################################################


void ConfigureAndLoadTexture(GLubyte *textureData, GLint texWidth, GLint texHeight )
{

        #ifdef __APPLE__
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
        glGenerateMipmap(GL_TEXTURE_2D);
        #endif
        
        #ifdef WIN32
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri( GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS, GL_TRUE );
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, textureData);
        #endif
}

//===============================================================================================================================


var     modelView[16];
var     projection[16];
var     mvpMatrix[16];
var     mvpMatrixInverse[16];
var     lightMatrix[16];
var     moveSetMatrix[16];
var     ProjectionShadow[16];
var     modelViewShadow[16];
var     viewMatrix[16];

var     LightModelViewMatrix[16];


float   modelWorld[16];
float   LightView[16];
float   LightProjection[16];
float   modelViewInverse[16];

float   tempMatrix[16];

var     textureMatrix[16] = {   0.5f, 0.0f, 0.0f, 0.0f,
                                0.0f, 0.5f, 0.0f, 0.0f,
                                0.0f, 0.0f, 0.5f, 0.0f,
                                0.5f, 0.5f, 0.5f, 1.0f   };

var     inverseMatrix[16];


//============================================================================================================================

var     moveShadowPivot_Z = 0.0;


#include "GLOBALS.cpp"


//============================================================================================================================

void setupTransforms_MainColor(void)
{
        LoadIdentity(modelView);
        LookAt(modelView,    eyeposition[0],
                             eyeposition[1],
                             eyeposition[2],
                             lookAt[0],
                             lookAt[1],
                             lookAt[2],
                             upVector[0],
                             upVector[1],
                             upVector[2]);
        
        Rotate(modelView, 0.0, 1.0, 0.0, turnTable);
        //--------------------------------------------------------------------------------------
        LoadIdentity(viewMatrix);
        AssignMatrix(viewMatrix, modelView);
        InvertMatrix(viewMatrix, viewMatrix);
        //--------------------------------------------------------------------------------------
        Translate(modelView, moveSet[0] , moveSet[1] , moveSet[2] );
        Rotate(modelView, 1.0, 0.0, 0.0, rotateModelWithLeftMouse[0]);
        Rotate(modelView, 0.0, 1.0, 0.0, rotateModelWithLeftMouse[1]);
}

//============================================================================================================================


void setupTransforms_Shadows(void)
{
        LoadIdentity(LightModelViewMatrix);
        LookAt(LightModelViewMatrix,  eyeposition[0] + eyeposition_SHADOW[0] - eyeposition[0] * adjustLookAtMove[0],
                                      eyeposition[1] + eyeposition_SHADOW[1] - eyeposition[1] * adjustLookAtMove[1],
                                      eyeposition[2] + eyeposition_SHADOW[2] - eyeposition[2] * adjustLookAtMove[2],
                                      lookAt[0]      + lookAt_SHADOW[0],
                                      lookAt[1]      + lookAt_SHADOW[1],
                                      lookAt[2]      + lookAt_SHADOW[2],
                                      upVector[0],
                                      upVector[1],
                                      upVector[2]);

        Rotate(LightModelViewMatrix, 0.0, 1.0, 0.0, turnTable * scaleTurnTable);
        //--------------------------------------------------------------------------------------
        AssignMatrix(modelViewShadow, LightModelViewMatrix);
        //--------------------------------------------------------------------------------------
        Translate(LightModelViewMatrix, moveSet[0] + moveShadow[0] , moveSet[1] + moveShadow[1] , moveSet[2] + moveShadow[2]);
        Rotate(LightModelViewMatrix, 1.0, 0.0, 0.0, rotateModelWithLeftMouse[0]);
        Rotate(LightModelViewMatrix, 0.0, 1.0, 0.0, rotateModelWithLeftMouse[1]);

}
//############################################################################################################################
//############################################################################################################################
//############################################################################################################################

var shaderNumber = 0;

void SelectShader(var shaderNumber)
{
        
        //--------------------------------------------------------------------------------------
        if(shaderNumber == 26)
        {
                #include "_SHADERS/plastic/rubber/rubber_SHADER_RENDER.cpp"
        }
        //--------------------------------------------------------------------------------------
        if(shaderNumber == 44)
        {
                #include "_SHADERS/ConeStep_01/steepPointy_SHADER_RENDER.cpp"
        }
        //--------------------------------------------------------------------------------------
        if(shaderNumber == 45)
        {
                #include "_SHADERS/ConeStep_01/shallowRound_SHADER_RENDER.cpp"
        }
        //--------------------------------------------------------------------------------------
        if(shaderNumber == 46)
        {
                #include "_SHADERS/wood/goldenSunset/goldenSunset_SHADER_RENDER.cpp"
        }
        //--------------------------------------------------------------------------------------
        if(shaderNumber == 47)
        {
                #include "_SHADERS/SHADOWS/shadow_32bit_Stride_SHADER_RENDER.cpp"
        }
        //--------------------------------------------------------------------------------------
        if(shaderNumber == 48)
        {
                #include "_SHADERS/SHADOWS/shadow_44bit_Stride_SHADER_RENDER.cpp"
        }
        //--------------------------------------------------------------------------------------
        if(shaderNumber == 49)
        {
                #include "_SHADERS/marble/geod_A/geod_A_SHADER_RENDER.cpp"
        }
        //--------------------------------------------------------------------------------------
        if(shaderNumber == 50)
        {
                #include "_SHADERS/leaves/A/leaves_A_SHADER_RENDER.cpp"
        }
        //--------------------------------------------------------------------------------------
        if(shaderNumber == 51)
        {
                #include "_SHADERS/plastic/hardShinyBumpPlastic/hardShinyBumpPlastic_SHADER_RENDER.cpp"
        }    
        //--------------------------------------------------------------------------------------
      
   
}

//################################################################################################################################
//################################################################################################################################
//################################################################################################################################

void InitGL( void )//__END_INIT__@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
{
        //==========================================================================
        #ifdef WIN32
            #include "cpp/setPixelFormat.cpp"
            #include "headerFiles/glext_Init_B.cpp"
            //-------------------------------------
            SetVSyncState(true);
            //-------------------------------------
            PassMouseMovement[0]        = rotateModelWithLeftMouse[0];
            PassMouseMovement[1]        = rotateModelWithLeftMouse[1];
        #endif
                   



#ifdef WIN32        
        //==========================================================================================================================================================================
        glGenTextures(1, &m_uiShadowMapTexture);
        glBindTexture(GL_TEXTURE_2D, m_uiShadowMapTexture);
        //-------------------------------------------------
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, (GLsizei)viewWidth * 1.2, (GLsizei)viewHeight, 0, GL_DEPTH_COMPONENT,  GL_UNSIGNED_INT,  NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        //------------------------------------------------------------------
        glGenFramebuffers(1, &m_uiFrameBufferObject);
        glBindFramebuffer(GL_FRAMEBUFFER, m_uiFrameBufferObject);
        //---------------------
        glDrawBuffer(GL_NONE);//_ON_SOME_MACHINES_THIS_IS_REQUIRED / ON_SOME_IT_FAILS
        glReadBuffer(GL_NONE);//_THIS_MAY_BE_OPTIONAL
        //---------------------
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_uiShadowMapTexture, 0);     
        glBindFramebuffer(GL_FRAMEBUFFER, 0);        
        //===============================================================================================================================
 #endif
	   
        
 #ifdef __APPLE__
        //==========================================================================================================================================================================
        glGenTextures(1, &m_uiShadowMapTexture);
        glBindTexture(GL_TEXTURE_2D, m_uiShadowMapTexture);
        //-------------------------------------------------
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, .
                     , 1000, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        //------------------------------------------------------------------
        glGenFramebuffers(1, &m_uiFrameBufferObject);
        glBindFramebuffer(GL_FRAMEBUFFER, m_uiFrameBufferObject);
        //---------------------
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_uiShadowMapTexture, 0);     
        glBindFramebuffer(GL_FRAMEBUFFER, 0);        
        //===============================================================================================================================
 #endif

 
#include "INITIALIZE.cpp"

//====================================================================================================================================


    glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LEQUAL);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glAlphaFunc(GL_GREATER, 0.1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
        
//====================================================================================================================================

    



}//__END_INIT__@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



//#####################################################################################################################################
//#####################################################################################################################################
//#####################################################################################################################################
//#####################################################################################################################################


void RenderGL(void)
{
                        #ifdef __APPLE__   
                        //***************************************************************
                        //eyeposition[0] -= PassTouchMovement[0];
                        //eyeposition[1] -= PassTouchMovement[1];
                        //eyeposition[2] -= PassTouchMovement[2];                   
                        
                        //PassTouchMovement[0] = 0.0;
                        //PassTouchMovement[1] = 0.0;
                        //PassTouchMovement[2] = 0.0;
                //***************************************************************
                        #endif               
        
                        #ifdef WIN32  
                        //***************************************************************
                        rotateModelWithLeftMouse[0] = PassMouseMovement[0];
                        rotateModelWithLeftMouse[1] = PassMouseMovement[1];
                        //***************************************************************
                        #endif            
            
        
//turnTable += 0.1;


//====================================================================================================================================
///////////////________FRAMEBUFFER_SHADOWS_BEGINS_HERE______________FRAMEBUFFER_SHADOWS_BEGINS_HERE___________________________________
///////////////________FRAMEBUFFER_SHADOWS_BEGINS_HERE______________FRAMEBUFFER_SHADOWS_BEGINS_HERE___________________________________
//====================================================================================================================================
        #include "runDepth_FBO.cpp"
//====================================================================================================================================
///////////////________FRAMEBUFFER_SHADOWS_BEGINS_HERE______________FRAMEBUFFER_SHADOWS_BEGINS_HERE___________________________________
///////////////________FRAMEBUFFER_SHADOWS_BEGINS_HERE______________FRAMEBUFFER_SHADOWS_BEGINS_HERE___________________________________
//====================================================================================================================================
//=============
//====================================================================================================================================
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//====================================================================================================================================    
        //glActiveTexture (GL_TEXTURE0);
        //glBindTexture(GL_TEXTURE_2D, shadowMap_TEXTURE);  
        //#include "flatten_3D_RENDER.cpp"
//====================================================================================================================================
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//====================================================================================================================================
//=============
//====================================================================================================================================
//************************************************************************************************************************************
//************************************************************************************************************************************
//====================================================================================================================================
        //#include "_MODEL_FOLDERS_/lightSpheres/lightSpheres_Render.cpp"
        //*****************************************************************
        //#include "_MODEL_FOLDERS_/lightSpheres/blurLightSpheres_Render.cpp"
//====================================================================================================================================
//************************************************************************************************************************************
//************************************************************************************************************************************
//====================================================================================================================================
//=============
//====================================================================================================================================
//####################################################################################################################################
//####################################################################################################################################
//====================================================================================================================================
#ifdef __APPLE__
        glBindFramebuffer(GL_FRAMEBUFFER, msaaFramebuffer);
#endif       
        //=====================================================================   

        #include "drawMainColor_FBO.cpp"
        
        //------------------------------------------
//glBindFramebuffer(GL_FRAMEBUFFER, 0);
        //------------------------------------------     
//====================================================================================================================================
//####################################################################################################################################
//####################################################################################################################################
//====================================================================================================================================
//=============
//====================================================================================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//====================================================================================================================================
/*
        glActiveTexture (GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, m_uiShadowMapTexture);
        glActiveTexture (GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_uiShadowMapTexture);//facing_UP_TEXTUREMAP
        #include "_MODEL_FOLDERS_/frameBufferPlane/frameBufferPlane_Render.cpp"
*/
 //====================================================================================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//====================================================================================================================================

 
}//_END_RenderGL()


//####################################################################################################################################
//####################################################################################################################################
//####################################################################################################################################
//####################################################################################################################################

#ifdef WIN32
void ProcessKeyboard(void)
{

    //=======================================================================================



    //=======================================================================================
    if (keys[VK_NUMPAD6])
    {
             knight_POSITION[0]         +=  0.05;
    }
    if (keys[VK_NUMPAD4])
    {
             knight_POSITION[0]         -=  0.05;
    }
    if (keys[VK_NUMPAD8])
    {
             knight_POSITION[1]         +=  0.05;
    }
    if (keys[VK_NUMPAD2])
    {
             knight_POSITION[1]         -=  0.05;
    }
    if (keys[VK_NUMPAD7])
    {
             knight_POSITION[2]         +=  0.05;
    }
    if (keys[VK_NUMPAD9])
    {
             knight_POSITION[2]         -=  0.05;
    }
   //=======================================================================================
    if (keys['L'] && !keys[VK_SHIFT])
    {
             hardShinyBumpPlastic_LIGHT_POSITION_01[0]         +=  0.15;
    }
    if (keys['J'] && !keys[VK_SHIFT])
    {
             hardShinyBumpPlastic_LIGHT_POSITION_01[0]         -=  0.15;
    }    
    if (keys['I'] && !keys[VK_SHIFT])
    {
             hardShinyBumpPlastic_LIGHT_POSITION_01[1]         +=  0.15;
    } 
    if (keys['K'] && !keys[VK_SHIFT])
    {
             hardShinyBumpPlastic_LIGHT_POSITION_01[1]         -=  0.15;
    }
    if (keys['O'] && !keys[VK_SHIFT])
    {
             hardShinyBumpPlastic_LIGHT_POSITION_01[2]         +=  0.15;
    }
    if (keys['U'] && !keys[VK_SHIFT])  
    {
             hardShinyBumpPlastic_LIGHT_POSITION_01[2]         -=  0.15;
    }
    //--------------------------------------------------------------------------
    if (keys['X'])
    {
            shininess_hardShinyBumpPlastic                       +=  1.1;
    }
    if (keys['Z'])
    {
            shininess_hardShinyBumpPlastic                       -=  1.1;
    }
    if (keys['M'])
    {
             ambient_hardShinyBumpPlastic                    +=  0.01;
    }
    if (keys['N'])
    {
             ambient_hardShinyBumpPlastic                    -=  0.01;
    }      
    //==================================================================================================================================
 
  
    if(keys[VK_F8])
    {
         ofstream outSettings("settings.cpp");
             
         //------------------------------------------------------------------------------------------------------------------------------
         outSettings << "var         frameBufferPlane_SCALE[]      =  {"   
                                  << frameBufferPlane_SCALE[0]     << ", "
                                  << frameBufferPlane_SCALE[1]     << ", "
                                  << frameBufferPlane_SCALE[2]     << "};\n\n";            
         //------------------------------------------------------------------------------------------------------------------------------
         outSettings << "var         shallowRound_SHININESS        =  "    
                                  << shallowRound_SHININESS       << ";\n\n";   
         //------------------------------------------------------------------------------------------------------------------------------
         outSettings << "var         frameBufferPlane_GaussianHorizontal_blurRadius        =  "    
                                  << frameBufferPlane_GaussianHorizontal_blurRadius        << ";\n\n";                        
         //------------------------------------------------------------------------------------------------------------------------------
         outSettings << "var         hardShinyBumpPlastic_LIGHT_POSITION_01[]    =  {"   
                                  << hardShinyBumpPlastic_LIGHT_POSITION_01[0] << ", "
                                  << hardShinyBumpPlastic_LIGHT_POSITION_01[1] << ", "
                                  << hardShinyBumpPlastic_LIGHT_POSITION_01[2]       << "};\n";        
         //-------------------------------------------------------------------------------------------------------------------------------
         outSettings << "var         shininess_hardShinyBumpPlastic         =  "    
                                  << shininess_hardShinyBumpPlastic         << ";\n";
         //---------------------------------------------------------------------------------------------------------------------------         
         outSettings << "var         ambient_hardShinyBumpPlastic      =  "    
                                  << ambient_hardShinyBumpPlastic     << ";\n\n"; 
         //------------------------------------------------------------------------------------------------------------------------------
        
         outSettings << "var         scaleTurnTable         =  "    
                                  << scaleTurnTable         << ";\n";
         //------------------------------------------------------------------------------------------------------------------------------
         outSettings << "var         steepPointy_linearAttenuation           =  "    
                                  << steepPointy_linearAttenuation           << ";\n";
         //------------------------------------------------------------------------------------------------------------------------------
         outSettings << "var         steepPointy_quadraticAttenuation        =  "    
                                  << steepPointy_quadraticAttenuation        << ";\n\n";
         //------------------------------------------------------------------------------------------------------------------------------
         outSettings << "var         knight_POSITION[]       =  {"   
                                  << knight_POSITION[0]      << ", "
                                  << knight_POSITION[1]      << ", "
                                  << knight_POSITION[2]      << "};\n\n";
         //------------------------------------------------------------------------------------------------------------------------------

         outSettings << "var           eyeposition[]      =  {"   
                                    << eyeposition[0]     << ", "
                                    << eyeposition[1]     << ", "
                                    << eyeposition[2]     << ", 0.0};\n";                
         //------------------------------------------------------------------------------------------------------------------------------
         outSettings << "var           lookAt[]        =  {"   
                                    << lookAt[0]       << ", "
                                    << lookAt[1]       << ", "
                                    << lookAt[2]       << ", 0.0};\n";             
         //------------------------------------------------------------------------------------------------------------------------------
         outSettings << "var           rotateModelWithLeftMouse[]       =  {"   
                                    << rotateModelWithLeftMouse[0]      << ", "
                                    << rotateModelWithLeftMouse[1]      << "};\n\n"; 
         //------------------------------------------------------------------------------------------------------------------------------
         outSettings << "var           eyeposition_SHADOW[]       =  {"   
                                    << eyeposition_SHADOW[0]      << ", "
                                    << eyeposition_SHADOW[1]      << ", "
                                    << eyeposition_SHADOW[2]      << ", 1.0};\n";                
         //------------------------------------------------------------------------------------------------------------------------------
         outSettings << "var           eyeposition_SHADOW[]       =  {"   
                                    << eyeposition_SHADOW[0]      << ", "
                                    << eyeposition_SHADOW[1]      << ", "
                                    << eyeposition_SHADOW[2]      << "}; \n";         
    //----------------------------------------------------------------------------------------------------------------
        
    }
      
      
    //====================================================================================================================================
 
 
//=======================================================================================
    if (keys['A'] && !keys[VK_SHIFT])
	{
          turnTable += 0.1;
          //lookAt[0]      -= 0.15;
    }	
//-----------------------------------     
    if (keys['D'] && !keys[VK_SHIFT])
	{
          turnTable -= 0.1;
          //lookAt[0]      += 0.15;    
    }
//=================================== 
    if (keys['S'] && !keys[VK_SHIFT])
	{
          eyeposition[1] += 0.15;
          //lookAt[1]      -= 0.15;   
    }
//-----------------------------------	
    if (keys['W'] && !keys[VK_SHIFT])
	{
          eyeposition[1] -= 0.15;       
          //lookAt[1]      += 0.15;    
//-----------------------------------  
    }    
    if (keys['Q'] && !keys[VK_SHIFT])
	{
          eyeposition[2] += 0.15;      
          //lookAt[2]       -= 0.15;     
    }
//===================================   
    if (keys['E'] && !keys[VK_SHIFT])
	{
          eyeposition[2] -= 0.15;
          //lookAt[2]      += 0.15;     
    }
//===================================  	

//=======================================================================================
//=======================================================================================
    if (keys['A'] && keys[VK_SHIFT])
	{
          eyeposition_SHADOW[0]    += 0.01;
    }	
//-----------------------------------     
    if (keys['D'] && keys[VK_SHIFT])
	{ 
          eyeposition_SHADOW[0]    -= 0.01;
    }
//=================================== 
    if (keys['S'] && keys[VK_SHIFT])
	{
          eyeposition_SHADOW[1] += 0.01;
    }
//-----------------------------------
    if (keys['W'] && keys[VK_SHIFT])
	{
          eyeposition_SHADOW[1] -= 0.01;
    }
//===================================
    if (keys['Q'] && keys[VK_SHIFT])
	{
          eyeposition_SHADOW[2] += 0.01;
    }
//-----------------------------------  	
    if (keys['E'] && keys[VK_SHIFT])
	{
          eyeposition_SHADOW[2] -= 0.01;
    }
//=======================================================================================
     
}//_END_ProcessKeyboard()
#endif


//#####################################################################################################################################
//#####################################################################################################################################
//#####################################################################################################################################
//#####################################################################################################################################



void shutDownGL( void )
{
        
        //====================================================================================
        //#include "_MODEL_FOLDERS_/shallowRound/shallowRound_Shutdown.cpp"
/*       
        //====================================================================================
        #include "_SHADERS/plastic/hardShinyBumpPlastic/hardShinyBumpPlastic_SHADER_SHUTDOWN.cpp"        
        
        //====================================================================================
        #include "_SHADERS/leaves/A/leaves_A_SHADER_SHUTDOWN.cpp"
        
        
        //====================================================================================
        #include "_MODEL_FOLDERS_/lightSpheres/lightSpheres_Shutdown.cpp"
        //====================================================================================
        #include "_MODEL_FOLDERS_/floorStraps/floorStraps_Shutdown.cpp"
        //====================================================================================
        #include "_MODEL_FOLDERS_/wallStraps/wallStraps_Shutdown.cpp"
        //====================================================================================
        #include "_MODEL_FOLDERS_/blocksEdging/blocksEdging_Shutdown.cpp"
        //====================================================================================
        #include "_MODEL_FOLDERS_/pillerPlantPot/pillerPlantPot_Shutdown.cpp"
        //====================================================================================
        #include "_MODEL_FOLDERS_/plant_v005/plant_v005_Shutdown.cpp"                                                               
        //====================================================================================                                                                
        #include "_MODEL_FOLDERS_/mouldings/mouldings_Shutdown.cpp"                                                               
        //====================================================================================                                                                
        #include "_MODEL_FOLDERS_/chassisFan/chassisFan_Shutdown.cpp"                                                               
        //====================================================================================                                                                
*/
   
}


//=====================================================================================================================================
//-------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------
//=====================================================================================================================================





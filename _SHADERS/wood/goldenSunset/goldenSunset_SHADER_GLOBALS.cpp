GLfloat     globalLinearAttenuation                     =    0.09;
GLfloat     lightPositionMultiplier[]                   = {  1.0, 1.0, 1.0,1.0};
                      
var         goldenSunset_LIGHT_POSITION_01[]            = {  -0.068917, 3.9, -0.715183, 1};

var         ambient_goldenSunset                        =     0.451993; 
var         shininess_goldenSunset                      =    65.0;

//--------------------------------------------------
GLfloat     offset_goldenSunset[]                       = { 0.0,  0.0,  0.0,  1.0};                                           
GLfloat     tileJump_goldenSunset[]                     = { 0.0,  0.0,  0.0,  1.0};                                           
//=====================================================================================|_SHADER
GLuint      goldenSunset_SHADER_VERTEX;                                                                                 
GLuint      goldenSunset_SHADER_FRAGMENT;                                                                               
GLuint      goldenSunset_SHADER;     
//-------------------------------------------------------------------------------------|_CONFIGURABLE_UNIFORMS
GLuint      UNIFORM_LIGHT_POSITION_01_goldenSunset;                                                                     
GLuint      UNIFORM_LIGHT_POSITION_02_goldenSunset; 
GLuint      UNIFORM_LIGHT_POSITION_03_goldenSunset; 
GLuint      UNIFORM_shininess_goldenSunset;
GLuint      UNIFORM_ambient_goldenSunset;
GLuint      UNIFORM_counter_goldenSunset;                                                                               
//-------------------------------------------------------------------------------------|_CORRECTION_UNIFORMS
GLuint      UNIFORM_offset_goldenSunset;                                                                                
GLuint      UNIFORM_tileJump_goldenSunset;                                                                              
//-------------------------------------------------------------------------------------|_MATRIX_UNIFORMS
GLuint      UNIFORM_MODELVIEW_goldenSunset;                                                                             
GLuint      UNIFORM_MODELVIEWPROJ_goldenSunset;                                                                         
//----
GLuint      UNIFORM_SHADOW_PROJ_goldenSunset;
GLuint      UNIFORM_modelViewShadow_goldenSunset;
//----
GLuint      UNIFORM_viewMatrix_goldenSunset; 
//----
GLuint      UNIFORM_LIGHT_MATRIX_goldenSunset;                                                                          
GLuint      UNIFORM_TEXTURE_MATRIX_goldenSunset;                                                                        
//-------------------------------------------------------------------------------------|_TEXTURE_UNIFORMS
GLuint      UNIFORM_ShadowTexture_goldenSunset;                                                                        
GLuint      UNIFORM_TEXTURE_DOT3_goldenSunset;                                                                          
GLuint      UNIFORM_TEXTURE_goldenSunset; 

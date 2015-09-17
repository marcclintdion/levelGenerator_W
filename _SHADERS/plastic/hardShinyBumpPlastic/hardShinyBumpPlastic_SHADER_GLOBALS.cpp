                    
var         hardShinyBumpPlastic_LIGHT_POSITION_01[]    =  {12.13, 31.2209, 32.95, 1.0};
var         shininess_hardShinyBumpPlastic              =  14.65;
var         ambient_hardShinyBumpPlastic                =  1.354;

//--------------------------------------------------
GLfloat     offset_hardShinyBumpPlastic[]                 = { 0.0,  0.0,  0.0,  1.0};                                           
GLfloat     tileJump_hardShinyBumpPlastic[]               = { 0.0,  0.0,  0.0,  1.0};                                           
//=====================================================================================|_SHADER
GLuint      hardShinyBumpPlastic_SHADER_VERTEX;                                                                                 
GLuint      hardShinyBumpPlastic_SHADER_FRAGMENT;                                                                               
GLuint      hardShinyBumpPlastic_SHADER;     
//-------------------------------------------------------------------------------------|_CONFIGURABLE_UNIFORMS
GLuint      UNIFORM_LIGHT_POSITION_01_hardShinyBumpPlastic;                                                                     
GLuint      UNIFORM_LIGHT_POSITION_02_hardShinyBumpPlastic; 
GLuint      UNIFORM_LIGHT_POSITION_03_hardShinyBumpPlastic; 
GLuint      UNIFORM_shininess_hardShinyBumpPlastic;
GLuint      UNIFORM_ambient_hardShinyBumpPlastic;
GLuint      UNIFORM_counter_hardShinyBumpPlastic;                                                                               
//-------------------------------------------------------------------------------------|_CORRECTION_UNIFORMS
GLuint      UNIFORM_offset_hardShinyBumpPlastic;                                                                                
GLuint      UNIFORM_tileJump_hardShinyBumpPlastic;                                                                              
//-------------------------------------------------------------------------------------|_MATRIX_UNIFORMS
GLuint      UNIFORM_MODELVIEW_hardShinyBumpPlastic;                                                                             
GLuint      UNIFORM_MODELVIEWPROJ_hardShinyBumpPlastic;                                                                         
//----
GLuint      UNIFORM_SHADOW_PROJ_hardShinyBumpPlastic;
GLuint      UNIFORM_modelViewShadow_hardShinyBumpPlastic;
//----
GLuint      UNIFORM_viewMatrix_hardShinyBumpPlastic; 
//----
GLuint      UNIFORM_LIGHT_MATRIX_hardShinyBumpPlastic;                                                                          
GLuint      UNIFORM_TEXTURE_MATRIX_hardShinyBumpPlastic;                                                                        
//-------------------------------------------------------------------------------------|_TEXTURE_UNIFORMS
GLuint      UNIFORM_ShadowTexture_hardShinyBumpPlastic;                                                                        
GLuint      UNIFORM_TEXTURE_DOT3_hardShinyBumpPlastic;                                                                          
GLuint      UNIFORM_TEXTURE_hardShinyBumpPlastic; 

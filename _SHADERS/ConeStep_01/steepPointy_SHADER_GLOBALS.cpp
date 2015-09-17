var         steepPointy_constantAttenuation                           =     2.0;
var         steepPointy_linearAttenuation                             =    -0.2645;
var         steepPointy_quadraticAttenuation                          =     0.0152;
                               
var         steepPointy_LIGHT_POSITION_01[]                           =  {  2.5, 4.90094, 17.701, 0.0};
                               
var         steepPointy_SHININESS                                     =     0.261004;

//==============================================================================                                                                      

GLuint      steepPointy_SHADER_VERTEX;                                                                                                      
GLuint      steepPointy_SHADER_FRAGMENT;                                                                                                    
GLuint      steepPointy_SHADER;                                                                                                             
//--------------------------------------                                                                                                  
GLuint      UNIFORM_MODELVIEWPROJ_steepPointy;
GLuint      UNIFORM_MODELVIEW_steepPointy;                                                                                             
//----
GLuint      UNIFORM_SHADOW_PROJ_steepPointy;   
GLuint      UNIFORM_modelViewShadow_steepPointy;   
//----
GLuint      UNIFORM_viewMatrix_steepPointy; 
//----
GLuint      UNIFORM_LIGHT_MATRIX_steepPointy;  
GLuint      UNIFORM_textureMatrix_steepPointy;
GLuint      UNIFORM_INVERSEMATRIX_steepPointy;
//------------------------------------------------                                                                                                  
GLuint      UNIFORM_LIGHT_POSITION_01_steepPointy;                                                                                          
//------------------------------------------------  
GLuint      UNIFORM_QUADRATIC_ATTENUATION_steepPointy; 
GLuint      UNIFORM_LINEAR_ATTENUATION_steepPointy; 
GLuint      UNIFORM_CONSTANT_ATTENUATION_steepPointy; 
//------------------------------------------------  

GLuint      UNIFORM_SHININESS_steepPointy; 
GLuint      UNIFORM_offset_steepPointy; 
GLuint      UNIFORM_zDirBias_steepPointy;  
GLuint      UNIFORM_TEXTURE_SHADOW_steepPointy;                                                                                              
GLuint      UNIFORM_TEXTURE_HEIGHT_steepPointy;
GLuint      UNIFORM_TEXTURE_DOT3_steepPointy;
GLuint      UNIFORM_TEXTURE_steepPointy;                         

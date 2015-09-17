var           shallowRound_LIGHT_POSITION_01[]                             =  {2.5, 24.401, 17.701, 0.0};
var           shallowRound_SHININESS                                       =   1.581;

// var           shallowRound_constantAttenuation                             =   0.001;
// var           shallowRound_linearAttenuation                               =   0.385;
// var           shallowRound_quadraticAttenuation                            =   0.063;

GLuint      shallowRound_SHADER_VERTEX;                                                                                                      
GLuint      shallowRound_SHADER_FRAGMENT;                                                                                                    
GLuint      shallowRound_SHADER;                                                                                                             
//--------------------------------------                                                                                                  
GLuint      UNIFORM_MODELVIEWPROJ_shallowRound;  
GLuint      UNIFORM_MODELVIEW_shallowRound;                                                                                             
//----
GLuint      UNIFORM_SHADOW_PROJ_shallowRound;   
GLuint      UNIFORM_modelViewShadow_shallowRound; 
//----
GLuint      UNIFORM_viewMatrix_shallowRound; 
//----
GLuint      UNIFORM_LIGHT_MATRIX_shallowRound;  
GLuint      UNIFORM_textureMatrix_shallowRound;
GLuint      UNIFORM_INVERSEMATRIX_shallowRound;
//------------------------------------------------                                                                                                  
GLuint      UNIFORM_LIGHT_POSITION_01_shallowRound;                                                                                          
//------------------------------------------------  
GLuint      UNIFORM_QUADRATIC_ATTENUATION_shallowRound; 
GLuint      UNIFORM_LINEAR_ATTENUATION_shallowRound; 
GLuint      UNIFORM_CONSTANT_ATTENUATION_shallowRound; 
//------------------------------------------------  

GLuint      UNIFORM_SHININESS_shallowRound; 
GLuint      UNIFORM_offset_shallowRound; 
GLuint      UNIFORM_zDirBias_shallowRound;  
GLuint      UNIFORM_TEXTURE_LightMap_shallowRound;
GLuint      UNIFORM_TEXTURE_SHADOW_shallowRound;                                                                                              
GLuint      UNIFORM_TEXTURE_HEIGHT_shallowRound;
GLuint      UNIFORM_TEXTURE_DOT3_shallowRound;
GLuint      UNIFORM_TEXTURE_shallowRound;       

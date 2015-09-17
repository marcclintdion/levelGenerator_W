var         chromatic_dispersion_LIGHT_POSITION_01[]    =  {13.2, -50.1, 84.7, 1.0};

var         chromatic_dispersion_ATTENUATION    =  0.285;
var         chromatic_dispersion_SHININESS    =  3.35595;
//-------------------------------------- 
GLuint      chromatic_dispersion_SHADER_VERTEX;                                                                                                      
GLuint      chromatic_dispersion_SHADER_FRAGMENT;                                                                                                    
GLuint      chromatic_dispersion_SHADER;                                                                                                             
//--------------------------------------                                                                                                  
GLuint      UNIFORM_MODELVIEWPROJ_chromatic_dispersion;                                                                                              
GLuint      UNIFORM_LIGHT_MATRIX_chromatic_dispersion;                                                                                               
//--------------------------------------                                                                                                  
GLuint      UNIFORM_LIGHT_POSITION_01_chromatic_dispersion;                                                                                          
GLuint      UNIFORM_SHININESS_chromatic_dispersion;                                                                                                  
GLuint      UNIFORM_ATTENUATION_chromatic_dispersion;                                                                                                  
GLuint      UNIFORM_TEXTURE_DOT3_chromatic_dispersion;                                                                                               
GLuint      UNIFORM_TEXTURE_chromatic_dispersion;        

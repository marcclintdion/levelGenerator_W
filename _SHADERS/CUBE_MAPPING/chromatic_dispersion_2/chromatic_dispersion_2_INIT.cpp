    #ifdef __APPLE__                                                                                                                          
      #import <OpenGLES/ES2/gl.h>                                                                                                               
      #import <OpenGLES/ES2/glext.h>                                                                                                            
      #endif                                                                                                                                    
      //===============================================================================================                                         
      chromatic_dispersion_2_SHADER = glCreateProgram();                                                                                                         
      //---------------------------------------------------------------------                                                                   
      const GLchar *vertexSource_chromatic_dispersion_2 =                                                                                                        

      "    #define highp                                                                                       \n"                           

      "    uniform highp vec4   light_POSITION_01;                                                             \n"                           
      "    uniform       mat4   mvpMatrix;                                                                     \n"                           
      "    uniform       mat4   lightMatrix;                                                                   \n"                           

       
      "    attribute     vec4   position;                                                                      \n"                           
      "    attribute     vec3   normal;                                                                        \n"         
      "    attribute     vec2   texture;                                                                       \n"                           

      "    varying highp vec4   lightPosition_PASS;                                                            \n"                           
      "    varying highp vec3   normal_PASS;                                                                   \n"          
      
     
      "    varying highp vec3   column0;                                                                       \n"   
      "    varying highp vec3   column1;                                                                       \n"   
      "    varying highp vec3   column2;                                                                       \n"        
      
      "    varying highp vec2   varTexcoord;                                                                   \n"                           


      "    void main()                                                                                         \n"                           
      "    {                                                                                                   \n"                           

      "        normal_PASS           = -normalize(mvpMatrix * vec4(normal, 0.0)).xyz;                          \n"        
      
      "        vec3 positionW        = -normalize(mvpMatrix *  position).xyz;                                  \n" 

 
      "        column0               =  vec3(mvpMatrix[0].xyz);                                                \n"   
      "        column1               =  vec3(mvpMatrix[1].xyz);                                                \n"   
      "        column2               =  vec3(mvpMatrix[2].xyz);                                                \n"     
     
     
      "        lightPosition_PASS    =  normalize(lightMatrix * light_POSITION_01);                            \n"                           
      "        varTexcoord           =  texture;                                                               \n"                           
      "        gl_Position           =  mvpMatrix * position;                                                  \n"                           

      "    }\n";                                                                                                                             
      //---------------------------------------------------------------------                                                                   
      chromatic_dispersion_2_SHADER_VERTEX = glCreateShader(GL_VERTEX_SHADER);                                                                                   
      glShaderSource(chromatic_dispersion_2_SHADER_VERTEX, 1, &vertexSource_chromatic_dispersion_2, NULL);                                                                        
      glCompileShader(chromatic_dispersion_2_SHADER_VERTEX);                                                                                                     
      //---------------------------------------------------------------------                                                                   
      const GLchar *fragmentSource_chromatic_dispersion_2 =                                                                                                            

     
     
      " #ifdef GL_ES                                                                                                     \n"                       
      " #else                                                                                                            \n"                       
      " #define highp                                                                                                    \n"                       
      " #endif                                                                                                           \n"   
    
      "    uniform sampler2D     Texture1;                                                                               \n"                       
      "    uniform sampler2D     NormalMap;                                                                              \n"                       
      "    uniform samplerCube   EnvMap;                                                                                 \n"    
      "    uniform highp float   shininess;                                                                              \n"                       
      "    uniform highp float   attenuation;                                                                            \n"                       
      "    uniform highp vec4    light_POSITION_01;                                                                      \n"   
      "    varying highp vec4    lightPosition_PASS;                                                                     \n"                       
      "    varying highp vec3    normal_PASS;                                                                            \n"          
      "            highp vec3    R;                                                                                      \n"       
      "            highp vec3    TRed;                                                                                   \n"       
      "            highp vec3    TGreen;                                                                                 \n"       
      "            highp vec3    TBlue;                                                                                  \n"     
      
      "    varying highp vec3    column0;                                                                                \n"   
      "    varying highp vec3    column1;                                                                                \n"   
      "    varying highp vec3    column2;                                                                                \n"   
                  
      "    varying highp vec2    varTexcoord;                                                                            \n"                       
      "            highp float   reflectionFactor;                                                                       \n"  
      
      "            highp float   NdotL1;                                                                                 \n"                       
      "            highp vec3    normal;                                                                                 \n"                       
      "            highp vec3    NormalTex;                                                                              \n"                       

      "            highp vec4    color;                                                                                  \n"
     
      "     void main()                                                                                                  \n"                       
      "     {                                                                                                            \n"                       
      

      "         mat3 n = mat3(column0, column1, column2);                                                                \n"       
      
      
      "         NormalTex             =  texture2D(NormalMap,  varTexcoord).xyz;                                         \n"                       
      "         NormalTex             = (NormalTex - 0.5);                                                               \n"                       
      "         normal                =  normalize(n * NormalTex);                                                       \n"                       
      "         NdotL1                =  dot(normal, normalize(light_POSITION_01.xyz));                                  \n"                       

      "         R                     =  reflect(normalize(light_POSITION_01.xyz), normal);                              \n" 
     
      "         TRed                  =  refract(normalize(light_POSITION_01.xyz), normal, 1.05);                        \n" 
      "         TGreen                =  refract(normalize(light_POSITION_01.xyz), normal, 1.1);                         \n" 
      "         TBlue                 =  refract(normalize(light_POSITION_01.xyz), normal, 1.15);                        \n" 

      "         reflectionFactor      =  0.0 + attenuation * pow(NdotL1, shininess);                                     \n"        
      
      "         vec4 reflectedColor   =  textureCube(EnvMap, R);                                                         \n" 

      "         vec4 refractedColor;                                                                                     \n" 
      "         refractedColor.x      =  textureCube(EnvMap, TRed).x;                                                    \n" 
      "         refractedColor.y      =  textureCube(EnvMap, TGreen).y;                                                  \n" 
      "         refractedColor.z      =  textureCube(EnvMap, TBlue).z;                                                   \n" 
      "         refractedColor.w      =  1.0;                                                                            \n" 

      "         gl_FragColor          =  mix(refractedColor, reflectedColor,  reflectionFactor) * NdotL1 * 2.5;          \n"     
      
      "    }\n";                                                                                                                                   

      //---------------------------------------------------------------------                                                                         
      chromatic_dispersion_2_SHADER_FRAGMENT = glCreateShader(GL_FRAGMENT_SHADER);                                                                                     
      glShaderSource(chromatic_dispersion_2_SHADER_FRAGMENT, 1, &fragmentSource_chromatic_dispersion_2, NULL);                                                                          
      glCompileShader(chromatic_dispersion_2_SHADER_FRAGMENT);                                                                                                         
      //------------------------------------------------                                                                                              
      glAttachShader(chromatic_dispersion_2_SHADER, chromatic_dispersion_2_SHADER_VERTEX);                                                                                              
      glAttachShader(chromatic_dispersion_2_SHADER, chromatic_dispersion_2_SHADER_FRAGMENT);                                                                                            
      //------------------------------------------------                                                                                              
      glBindAttribLocation(chromatic_dispersion_2_SHADER,    0, "position");                                                                                            
      glBindAttribLocation(chromatic_dispersion_2_SHADER,    1, "normal");       
      glBindAttribLocation(chromatic_dispersion_2_SHADER,    2, "texture");                                                                                           
      //------------------------------------------------                                                                                              
      glLinkProgram(chromatic_dispersion_2_SHADER);                                                                                                                    
      //------------------------------------------------                                                                                              
      #ifdef __APPLE__                                                                                                                                
      glDetachShader(chromatic_dispersion_2_SHADER, chromatic_dispersion_2_SHADER_VERTEX);                                                                                              
      glDetachShader(chromatic_dispersion_2_SHADER, chromatic_dispersion_2_SHADER_FRAGMENT);                                                                                            
      #endif                                                                                                                                          
      //------------------------------------------------                                                                                              
      glDeleteShader(chromatic_dispersion_2_SHADER_VERTEX);                                                                                                            
      glDeleteShader(chromatic_dispersion_2_SHADER_FRAGMENT);                                                                                                          
      //------------------------------------------------------------------------------------------------------------//___LOAD_UNIFORMS                
      UNIFORM_MODELVIEWPROJ_chromatic_dispersion_2                   = glGetUniformLocation(chromatic_dispersion_2_SHADER,   "mvpMatrix");                                              
      UNIFORM_LIGHT_MATRIX_chromatic_dispersion_2                    = glGetUniformLocation(chromatic_dispersion_2_SHADER,   "lightMatrix");                                            
      UNIFORM_LIGHT_POSITION_01_chromatic_dispersion_2               = glGetUniformLocation(chromatic_dispersion_2_SHADER,   "light_POSITION_01");                                      
      UNIFORM_SHININESS_chromatic_dispersion_2                       = glGetUniformLocation(chromatic_dispersion_2_SHADER,   "shininess");                                              
      UNIFORM_ATTENUATION_chromatic_dispersion_2                     = glGetUniformLocation(chromatic_dispersion_2_SHADER,   "attenuation");                                              
      UNIFORM_TEXTURE_DOT3_chromatic_dispersion_2                    = glGetUniformLocation(chromatic_dispersion_2_SHADER,   "NormalMap");                                              
      UNIFORM_TEXTURE_chromatic_dispersion_2                         = glGetUniformLocation(chromatic_dispersion_2_SHADER,   "Texture1");                                   

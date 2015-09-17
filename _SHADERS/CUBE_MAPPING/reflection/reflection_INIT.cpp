    #ifdef __APPLE__                                                                                                                          
      #import <OpenGLES/ES2/gl.h>                                                                                                               
      #import <OpenGLES/ES2/glext.h>                                                                                                            
      #endif                                                                                                                                    
      //===============================================================================================                                         
      reflection_SHADER = glCreateProgram();                                                                                                         
      //---------------------------------------------------------------------                                                                   
      const GLchar *vertexSource_reflection =                                                                                                        

      "    #define highp                                                                                       \n"                           

      "    uniform highp vec4   light_POSITION_01;                                                             \n"                           
      "    uniform       mat4   mvpMatrix;                                                                     \n"                           
      "    uniform       mat4   lightMatrix;                                                                   \n"                           
                   
      
      "    attribute     vec4   position;                                                                      \n"                           
      "    attribute     vec3   normal;                                                                        \n"         
      "    attribute     vec2   texture;                                                                       \n"                           

      "    varying highp vec3   column0;                                                                       \n"   
      "    varying highp vec3   column1;                                                                       \n"   
      "    varying highp vec3   column2;                                                                       \n"  

      "    varying highp vec4   lightPosition_PASS;                                                            \n"                           
      "    varying highp vec3   normal_PASS;                                                                   \n"          
      "    varying highp vec2   varTexcoord;                                                                   \n"                           



      "    void main()                                                                                         \n"                           
      "    {                                                                                                   \n"                           

      "        normal_PASS           = -normalize(mvpMatrix * vec4(normal, 0.0)).xyz;                          \n"        
 
      "        column0               =  vec3(mvpMatrix[0].xyz);                                                \n"   
      "        column1               =  vec3(mvpMatrix[1].xyz);                                                \n"   
      "        column2               =  vec3(mvpMatrix[2].xyz);                                                \n"
            
      "        lightPosition_PASS    =  normalize(lightMatrix * light_POSITION_01);                            \n"                           
      "        varTexcoord           =  texture;                                                               \n"                           
      "        gl_Position           =  mvpMatrix * position;                                                  \n"                           

      "    }\n";                                                                                                                             
      //---------------------------------------------------------------------                                                                   
      reflection_SHADER_VERTEX = glCreateShader(GL_VERTEX_SHADER);                                                                                   
      glShaderSource(reflection_SHADER_VERTEX, 1, &vertexSource_reflection, NULL);                                                                        
      glCompileShader(reflection_SHADER_VERTEX);                                                                                                     
      //---------------------------------------------------------------------                                                                   
      const GLchar *fragmentSource_reflection =                                                                                                            

     
     
      " #ifdef GL_ES                                                                                                     \n"                       
      " #else                                                                                                            \n"                       
      " #define highp                                                                                                    \n"                       
      " #endif                                                                                                           \n"   
    
      "    uniform sampler2D     Texture1;                                                                               \n"                       
      "    uniform sampler2D     NormalMap;                                                                              \n"                       
      "    uniform samplerCube   darkCubeMap;                                                                                 \n"    
      "    uniform highp vec4    light_POSITION_01;                                                                      \n"       
      "    uniform highp float   shininess;                                                                              \n"                       
      "    uniform highp float   attenuation;                                                                            \n"                       

      "    varying highp vec3    column0;                                                                                \n"   
      "    varying highp vec3    column1;                                                                                \n"   
      "    varying highp vec3    column2;                                                                                \n"  

      "    varying highp vec4    lightPosition_PASS;                                                                     \n"                       
      "    varying highp vec3    normal_PASS;                                                                            \n"          
      "            highp vec3    reflection;                                                                             \n"       
      "    varying highp vec2    varTexcoord;                                                                            \n"                       

      "            highp float   NdotL1;                                                                                 \n"                       
      "            highp vec3    normal;                                                                                 \n"                       
      "            highp vec3    NormalTex;                                                                              \n"                       


      "            highp vec4    enviromentColor;                                                                        \n"
     
    
      "     void main()                                                                                                  \n"                       
      "     {                                                                                                            \n"                       
      "         mat3 n                =  mat3(column0, column1, column2);                                                \n"         
     
      "         NormalTex             =  texture2D(NormalMap,  varTexcoord).xyz;                                         \n"                       
      "         NormalTex             = (NormalTex - 0.5);                                                               \n"                       
      "         normal                =  normalize(NormalTex);                                                           \n"                       
      "         normal                =  normalize(n * NormalTex);                                                       \n"          
      
      "         NdotL1                =  dot(normal, normalize(light_POSITION_01.xyz));                                  \n"                     
      
      "         reflection            =  reflect(light_POSITION_01.xyz, normal);                                         \n" 
      "         reflection.y          =  reflection.y * -1.0;                                       \n"     
      
           
      "         enviromentColor       =  textureCube(darkCubeMap, reflection);                                                \n"  
     
      "         gl_FragColor          =  mix(vec4(1.0, 1.0, 1.0, 1.0), enviromentColor, attenuation) * NdotL1;           \n"                       

      "    }\n";                                                                                                                                   

      //---------------------------------------------------------------------                                                                         
      reflection_SHADER_FRAGMENT = glCreateShader(GL_FRAGMENT_SHADER);                                                                                     
      glShaderSource(reflection_SHADER_FRAGMENT, 1, &fragmentSource_reflection, NULL);                                                                          
      glCompileShader(reflection_SHADER_FRAGMENT);                                                                                                         
      //------------------------------------------------                                                                                              
      glAttachShader(reflection_SHADER, reflection_SHADER_VERTEX);                                                                                              
      glAttachShader(reflection_SHADER, reflection_SHADER_FRAGMENT);                                                                                            
      //------------------------------------------------                                                                                              
      glBindAttribLocation(reflection_SHADER,    0, "position");                                                                                            
      glBindAttribLocation(reflection_SHADER,    1, "normal");       
      glBindAttribLocation(reflection_SHADER,    2, "texture");                                                                                           
      //------------------------------------------------                                                                                              
      glLinkProgram(reflection_SHADER);                                                                                                                    
      //------------------------------------------------                                                                                              
      #ifdef __APPLE__                                                                                                                                
      glDetachShader(reflection_SHADER, reflection_SHADER_VERTEX);                                                                                              
      glDetachShader(reflection_SHADER, reflection_SHADER_FRAGMENT);                                                                                            
      #endif                                                                                                                                          
      //------------------------------------------------                                                                                              
      glDeleteShader(reflection_SHADER_VERTEX);                                                                                                            
      glDeleteShader(reflection_SHADER_FRAGMENT);                                                                                                          
      //------------------------------------------------------------------------------------------------------------//___LOAD_UNIFORMS                
      UNIFORM_MODELVIEWPROJ_reflection                   = glGetUniformLocation(reflection_SHADER,   "mvpMatrix");                                              
      UNIFORM_LIGHT_MATRIX_reflection                    = glGetUniformLocation(reflection_SHADER,   "lightMatrix");                                            
      UNIFORM_LIGHT_POSITION_01_reflection               = glGetUniformLocation(reflection_SHADER,   "light_POSITION_01");                                      
      UNIFORM_SHININESS_reflection                       = glGetUniformLocation(reflection_SHADER,   "shininess");                                              
      UNIFORM_ATTENUATION_reflection                     = glGetUniformLocation(reflection_SHADER,   "attenuation");                                              
      UNIFORM_TEXTURE_DOT3_reflection                    = glGetUniformLocation(reflection_SHADER,   "NormalMap");                                              
      UNIFORM_TEXTURE_reflection                         = glGetUniformLocation(reflection_SHADER,   "Texture1");                                   

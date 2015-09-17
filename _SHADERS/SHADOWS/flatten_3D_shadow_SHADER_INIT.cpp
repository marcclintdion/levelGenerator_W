      #ifdef __APPLE__                                                                                                                          
      #import <OpenGLES/ES2/gl.h>                                                                                                               
      #import <OpenGLES/ES2/glext.h>                                                                                                            
      #endif                                                                                                                                    
      //===============================================================================================                                         
      flatten_3D_shadow_SHADER = glCreateProgram();                                                                                                         
      //---------------------------------------------------------------------                                                                   
      const GLchar *vertexSource_flatten_3D_shadow =                                                                                                        

      "    #define highp                                                                                     \n"                           

      "    attribute       vec4   position;                                                                    \n"                           
      
      "    varying highp   vec2   vTexCoord;                                                                 \n"                           

      "    void main()                                                                                         \n"                           
      "    {                                                                                                   \n"                           
     
      "   vec2 Pos;                                                                                            \n"  
      "   Pos = sign(position.xy);                                                                             \n"  
 
      "   gl_Position = vec4(Pos, 0.0, 1.0);                                                                \n"  
        // Image-space
      "   vTexCoord = Pos * 0.5 + 0.5;                                                                     \n"  
     
      "    }\n";                                                                                                                             
      //---------------------------------------------------------------------                                                                   
      flatten_3D_shadow_SHADER_VERTEX = glCreateShader(GL_VERTEX_SHADER);                                                                                   
      glShaderSource(flatten_3D_shadow_SHADER_VERTEX, 1, &vertexSource_flatten_3D_shadow, NULL);                                                                        
      glCompileShader(flatten_3D_shadow_SHADER_VERTEX);                                                                                                     
      //---------------------------------------------------------------------                                                                   
      const GLchar *fragmentSource_flatten_3D_shadow =                                                                                                            

      " #ifdef GL_ES                                                                                                     \n"                       
      " #else                                                                                                     \n"                       
      " #define highp                                                                                                  \n"                       
      " #endif                                                                                                           \n"                       

      "    uniform sampler2D       Texture1;                                                                             \n"                       
      "    varying highp vec2    vTexCoord;                                                                          \n"                       

     
     
      "     void main()                                                                                                  \n"                       
      "     {                                                                                                                 \n"                       
//==============================================================================================================      
//==============================================================================================================  

      
      
      "  // gl_FragColor = (texture2D(Texture1, vTexCoord.st) - 0.5) * (max(1.3, 1.0) + 0.5) ;                              \n"   

      "   gl_FragColor = vec4(pow(texture2D(Texture1, vTexCoord.st).x, 1000.0)) + 0.5;                              \n"   

  
//==============================================================================================================      
//==============================================================================================================      
      "    }\n";                                                                                                                                   

      //---------------------------------------------------------------------                                                                         
      flatten_3D_shadow_SHADER_FRAGMENT = glCreateShader(GL_FRAGMENT_SHADER);                                                                                     
      glShaderSource(flatten_3D_shadow_SHADER_FRAGMENT, 1, &fragmentSource_flatten_3D_shadow, NULL);                                                                          
      glCompileShader(flatten_3D_shadow_SHADER_FRAGMENT);                                                                                                         
      //------------------------------------------------                                                                                              
      glAttachShader(flatten_3D_shadow_SHADER, flatten_3D_shadow_SHADER_VERTEX);                                                                                              
      glAttachShader(flatten_3D_shadow_SHADER, flatten_3D_shadow_SHADER_FRAGMENT);                                                                                            
      //------------------------------------------------                                                                                              
      glBindAttribLocation(flatten_3D_shadow_SHADER, 0, "position");                                                                                            
      glBindAttribLocation(flatten_3D_shadow_SHADER, 1, "texture");                                                                                             
      //glBindAttribLocation(flatten_3D_shadow _SHADER, 2, "normal");                                                                                           
      //------------------------------------------------                                                                                              
      glLinkProgram(flatten_3D_shadow_SHADER);                                                                                                                    
      //------------------------------------------------                                                                                              
      #ifdef __APPLE__                                                                                                                                
      glDetachShader(flatten_3D_shadow_SHADER, flatten_3D_shadow_SHADER_VERTEX);                                                                                              
      glDetachShader(flatten_3D_shadow_SHADER, flatten_3D_shadow_SHADER_FRAGMENT);                                                                                            
      #endif                                                                                                                                          
      //------------------------------------------------                                                                                              
      glDeleteShader(flatten_3D_shadow_SHADER_VERTEX);                                                                                                            
      glDeleteShader(flatten_3D_shadow_SHADER_FRAGMENT);                                                                                                          
      //------------------------------------------------------------------------------------------------------------//___LOAD_UNIFORMS                
      UNIFORM_TEXTURE_flatten_3D_shadow            = glGetUniformLocation(flatten_3D_shadow_SHADER,   "Texture1"); 
      //------------------------------------------------------------------------------------------------------------//___LOAD_TEXTURES                
      //------------------------------------------------------------------------------------------                                              

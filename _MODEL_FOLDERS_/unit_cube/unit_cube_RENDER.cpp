        glBindBuffer(GL_ARRAY_BUFFER, unit_cube_VBO);                                                                                                 
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, unit_cube_INDICES_VBO);                                                                                                                                
        //--------------------------------------------------------------------------------------------------

//======================================================================================================                                                       
    SelectShader(shaderNumber);                                                                                                                              
//======================================================================================================                                                       
    
        glActiveTexture ( GL_TEXTURE1 );                                                                                                                           
        glBindTexture(GL_TEXTURE_2D, unit_cube_NORMALMAP);                                                                                            
        //---                                                                                                                                                      
        glActiveTexture (GL_TEXTURE0);                                                                                                                             
        glBindTexture(GL_TEXTURE_2D, unit_cube_TEXTUREMAP);                                                                                           
    
    //-------------------------------------------------------------------------------------------------- 
  
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);                                                                                                     


    glBindBuffer(GL_ARRAY_BUFFER, unit_cube_VBO);                                                                                                 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, unit_cube_INDICES_VBO);                                                                                                                                
    //----------------------------------------------------------------------------------------------------------------------------------------------           
    LoadIdentity(modelView);                                                                                                                                   
    Translate(modelView, unit_cube_POSITION[0], unit_cube_POSITION[1], unit_cube_POSITION[2]);                          
    Rotate(modelView, unit_cube_ROTATE[0], unit_cube_ROTATE[1], unit_cube_ROTATE[2], unit_cube_ROTATE[3]); 

//======================================================================================================                                                       
    //SelectShader(shaderNumber);                                                                                                                              
//======================================================================================================                                                       

    glActiveTexture ( GL_TEXTURE1 );                                                                                                                           
    glBindTexture(GL_TEXTURE_2D, unit_cube_NORMALMAP);                                                                                            
    //---                                                                                                                                                      
    glActiveTexture (GL_TEXTURE0);                                                                                                                             
    glBindTexture(GL_TEXTURE_2D, unit_cube_TEXTUREMAP);                                                                                           
    //---------------------------------------------------------------------------------------------------------------------------------------------------      
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);                                                                                                     


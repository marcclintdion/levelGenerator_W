
   MultiplyMatrix(mvpMatrix, projection, modelView);                                                                                                                         
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__LIGHT             
    LoadIdentity(lightMatrix);                                                                                                                                                
    InvertMatrix(lightMatrix, modelView);                                                                                                                                     
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__LIGHT             
    LoadIdentity(textureMatrix);
    //Translate(textureMatrix, shadowsPositionOffset[0], shadowsPositionOffset[1], shadowsPositionOffset[2]);
    //Scale(textureMatrix, scaleShadows, scaleShadows, scaleShadows);   
 
 
 
 glUseProgram(hardShinyBumpPlastic_SHADER);          
          //------------------------------------------------------------------------------         
          glVertexAttribPointer(0,     3, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(0));                                                  
          glEnableVertexAttribArray(0);	                                                                                              
          glVertexAttribPointer(1,     3, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(12));                                                 
          glEnableVertexAttribArray(1);	                                                                                          
          glVertexAttribPointer(2,     2, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(24));                                                 
          glEnableVertexAttribArray(2);                                                                                               
          //------------------------------------------------------------------------------------------------                                
          glUniform4f(UNIFORM_LIGHT_POSITION_01_hardShinyBumpPlastic,          hardShinyBumpPlastic_LIGHT_POSITION_01[0],                       
                                                                       hardShinyBumpPlastic_LIGHT_POSITION_01[1],                       
                                                                       hardShinyBumpPlastic_LIGHT_POSITION_01[2],                       
                                                                       hardShinyBumpPlastic_LIGHT_POSITION_01[3]);                      
           
          glUniform4f(UNIFORM_offset_hardShinyBumpPlastic,                     offset[0], 
                                                                       offset[1], 
                                                                       offset[2], 
                                                                       offset[3]);                               
                                                                                                       
          glUniform4f(UNIFORM_tileJump_hardShinyBumpPlastic,                   tileJump_hardShinyBumpPlastic[0],                                
                                                                       tileJump_hardShinyBumpPlastic[1],                                
                                                                       tileJump_hardShinyBumpPlastic[2],                                
                                                                       tileJump_hardShinyBumpPlastic[3]);                               
         
          glUniform1f(UNIFORM_shininess_hardShinyBumpPlastic,                  shininess_hardShinyBumpPlastic);
          glUniform1f(UNIFORM_ambient_hardShinyBumpPlastic,                    ambient_hardShinyBumpPlastic);   
          glUniform1f(UNIFORM_counter_hardShinyBumpPlastic,                    globalLinearAttenuation);                  
          //------------------------------------------------------------------------------------------------
          glUniformMatrix4fv(UNIFORM_MODELVIEW_hardShinyBumpPlastic,       1, 0,         modelView);                                             
          glUniformMatrix4fv(UNIFORM_MODELVIEWPROJ_hardShinyBumpPlastic,   1, 0,         mvpMatrix);                                   
          //---------------     
          glUniformMatrix4fv(UNIFORM_viewMatrix_hardShinyBumpPlastic,      1, 0,         viewMatrix);     
          //---------------     
          glUniformMatrix4fv(UNIFORM_SHADOW_PROJ_hardShinyBumpPlastic,     1, 0,         ProjectionShadow);
          glUniformMatrix4fv(UNIFORM_modelViewShadow_hardShinyBumpPlastic, 1, 0,         modelViewShadow);    
          //---------------                                                                                                                                      //glUniformMatrix4fv(UNIFORM_MODELVIEWPROJ_INVERSE_hardShinyBumpPlastic, 1, 0, ModelViewProjectionInverse);                            
          glUniformMatrix4fv(UNIFORM_LIGHT_MATRIX_hardShinyBumpPlastic,    1, 0,         lightMatrix);                                           
          glUniformMatrix4fv(UNIFORM_TEXTURE_MATRIX_hardShinyBumpPlastic,  1, 0,         textureMatrix);                                       
          //-------------------------------------------------------------------------------------------------                                
          glUniform1i(UNIFORM_ShadowTexture_hardShinyBumpPlastic,  3);                                                                      
          glUniform1i(UNIFORM_TEXTURE_DOT3_hardShinyBumpPlastic,   1);                                                                        
          glUniform1i(UNIFORM_TEXTURE_hardShinyBumpPlastic,        0);                                                        
    //====================================================================================================================

//---------------------------------------------------------------
glActiveTexture ( GL_TEXTURE3 );                                                                                                                                          
glBindTexture(GL_TEXTURE_2D, m_uiShadowMapTexture);                                                                                                                          
//---  
